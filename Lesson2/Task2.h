#pragma once
#include<memory>
#include<vector>
#include<iostream>
#include<algorithm>
//useful links https://stackoverflow.com/questions/4476011/weak-ptr-and-parent-child-cyclic-dependencies
//https://computingonplains.wordpress.com/parent-child-implementation-shared_ptr/
//https://mbevin.wordpress.com/2012/11/18/smart-pointers/

//The Parent and Child classes form a circular reference to each other:
//a Parent object holds a shared_ptr to each of its children, whilst Children object stores a weak_ptr
//to its Parent object. If the child held a shared_ptr instead of weak_ptr to its Parent, then both
//parent and child objects can't be destroyed, the reference count variable would never reach 0


//Let's explain why it's like that
//There are two classes: A,B
//A holds pointer to B, B holds pointer to A
//when we call reset on B's shared_ptr or B goes out of the scope A will be still pointing to B, 
//so reference_count would be equal to 1 similarly for A's shared_ptr

namespace PointersTask {
	class Parent;

	class Child {
	public:
		Child(int id) : _wParent(std::weak_ptr<Parent>()), _id(id) {
			std::cout << "Child " << this << " with id=" << _id << " was created\n";
		}
		~Child() noexcept {
			std::cout << "Child " << this << " with id=" << _id << " was destroyed\n";
		}
		const int getID() const noexcept { return _id; }
		void cutParent();
	private:
		friend Parent;
		void setParent(const std::weak_ptr<Parent>& wParent) noexcept { _wParent = wParent; }
		friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Child>& pChild);

		std::weak_ptr<Parent> _wParent;
		int _id;
	};

	class Parent {
	public:
		Parent() {
			std::cout << "Parent " << this << " was created\n";
		}
		~Parent() noexcept {
			std::cout << "Parent " << this << " was destroyed\n";
		}
		static void addChild(const std::weak_ptr<Parent>& w_parent, const std::shared_ptr<Child>& p_child);
		std::shared_ptr<Child> removeChild(int id);
		std::shared_ptr<Child> findChild(int id);
	private:
		std::vector<std::shared_ptr<Child>> _childs;

		friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Parent>& pParent);
	};
	void Test();
}