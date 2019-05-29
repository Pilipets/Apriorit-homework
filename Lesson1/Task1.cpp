//Pure virtual function call

//This error occurs when your application indirectly calls a pure virtual member 
//function in a context where that call is not valid. In some cases, the compiler 
//detects this and reports the error when building the application. But ometimes the problem is 
//detected only at run-time. 

//The error could be commonly recognized within ctor and dtor calling of an abstract base class.
//but there are other reasons also(could be seen in provided links at the end).
namespace Testing1 {
	class Base;
	void ErrorInvoker(Base*);

	class Base
	{
	public:
		virtual void foo() = 0;
		Base() { ErrorInvoker(this); }
	};

	class Derived : Base
	{
		void foo() { }
	};

	void ErrorInvoker(Base* ptr)
	{
		ptr->foo();
	}
	void CtorError()
	{
		//The declaration of instance invokes Derived's ctor, which call Base's
		//ctor before Derived class being created, which call ErrorInvoker method. ErrorInvoker calls
		//Base::foo that is pure virtual function and this causes the run-time error.
		//When ErrorInvoker is called from Base's ctor child object hasn't been constructed yet, so
		//Base::foo isn't pointing to the Derived::foo as some people would assume.
		Derived instance;
		//We could move ErrorInvoker inside Base class and just call foo there. Result would be the
		//same.


		//Calling a pure virtual function is a programming error, so you need to find the call to the 
		//pure virtual function and rewrite the code so it is not called. 
		//One way to find a call to a pure virtual function is to replace the pure virtual function
		//with some implementation that print message to a kind of Log or throws a special kind of error.
		//this would be handy while debugging a program with pure virtual functions
		//Recommendation from microsoft: call the Windows API function DebugBreak from pure
		//virtual function. When using the debugger, DebugBreak will cause a hard-coded breakpoint. 
		//When the code stops running at this breakpoint, you can view the callstack to see where the function was called.
	}
}

//There a lot of examples with ctor calling. Let's create one with dtor
namespace Testing2 {
	class Base;

	class Base
	{
	public:
		virtual void foo() = 0;
		virtual ~Base() { ErrorInvoker(this); }
		void ErrorInvoker(Base *ptr) { ptr->foo(); }
	};

	class Derived : Base
	{
		void foo() { }
	};

	void DtorError()
	{
		
		Derived instance;

		//When test1 method ends objects which were allocated at the stack are destroyed.
		//In this case, it's instance object. As Base's dtor is virtual, dtor of Derived object
		//would be called first. After that Base::~Base is calling ErrorInvoker method
		//which is calling foo function on casted to Base class object. But at this point derived object
		//doesn't actually exist(because was destroyed before), so Base::foo is not a valid function 
		//and a pure virtual call error would be thrown
	}
}

//int main()
//{
//	//Testing1::CtorError();
//	//Testing2::DtorError();
//	return 0;
//}

//Useful links
//https://support.microsoft.com/ca-es/help/125749/description-of-the-r6025-run-time-error-in-visual-c
//https://stackoverflow.com/questions/4612702/what-can-cause-a-pure-virtual-function-call-in-c
