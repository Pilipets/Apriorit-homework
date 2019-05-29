#pragma once
//Написать собственный guard для управления ресурсами, отличными от памяти.
#include<iostream>
#include<thread>
using std::cout;
namespace Guards {
	//  Private copy constructor and copy assignment ensure classes derived 
	//  from class NonCopyable cannot be copied.
	class NonCopyable
	{
		NonCopyable(NonCopyable const &); // private copy constructor
		NonCopyable& operator = (NonCopyable const &); // private assignment operator
	protected:
		NonCopyable() {}
	};

	template<class T>
	class ScopeGuard : NonCopyable
	{
	public:
		explicit ScopeGuard(T &obj) : _acquired(true), resource(obj)
		{ /* Acquire resources here. */
			resource.acquire();
			cout << "Resource acquired from ScopeGuard\n";
		}

		~ScopeGuard() noexcept
		{
			if (_acquired)
			{ /* Release resources here. */
				resource.release();
				cout << "Resource released from ScopeGuard destructor\n";
			}
		}
		void release()
		{
			_acquired = false;
			resource.release();
			cout << "Resource released from ScopeGuard direct calling\n";
			/* Resources will no longer be released */
		}
	private:
		T& resource; //here could also be not reference but data instead
		bool _acquired;
		//_acquired variable is added optionally in order to have an option of releasing resource 
		//before going out of the scope by calling ScopeGuard::release method. But ScopeGuard also
		//maintains an option of implicit resource releasing for cases of exception safety
	};
}



namespace Testing1 {
	class MyClass
	{
	public:
		MyClass() {}
		void acquire() {
			//invoke some methods to acquire resources
			//it includes changing/erasing/updating some fields in another classes,data structures,
			//calling another methods and so forth and so on
			cout << "Resource acquired from Test class\n";
		}
		void release() {
			//invoke some methods to release resources
			cout << "Resource released from Test class\n";
		}
	};
	void test1()
	{
		cout << "----------Started test1------------\n";
		MyClass t1;
		Guards::ScopeGuard<MyClass> l1(t1);
		//Guards::ScopeGuard<Test> l2(l1); not allowed

		cout << "Work1 started\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		cout << "Work1 finished\n";
		l1.release(); //intentional calling release
		cout << "Work2 started\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		cout << "Work2 finished\n";
		cout << "----------Finished test1--------------\n\n";
	}

	void test2()
	{		//auto releasing of resources
		cout << "-----------Started test2-------------\n";
		MyClass t1;
		Guards::ScopeGuard<MyClass> l1(t1);
		//Guards::ScopeGuard<Test> l2(l1); not allowed

		cout << "Work3 started\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		cout << "Work3 finished\n";
		cout << "-----------Finished test2--------------\n\n";

	}

	void test3()
	{ //exception safety
		cout << "-----------Started test3-------------\n";
		MyClass t1;
		Guards::ScopeGuard<MyClass> l1(t1);
		std::this_thread::sleep_for(std::chrono::milliseconds(3500));
		cout << "Throwing an error\n";
		throw std::runtime_error("oops");
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		cout << "-----------Finished test3--------------\n\n";
	}

	void MainTest() 
	{
		Testing1::test1();
		Testing1::test2();

		try {
			Testing1::test3();
		}
		catch (const std::runtime_error& e)
		{
			cout << "Error was handled\n";
		}
	}
}
