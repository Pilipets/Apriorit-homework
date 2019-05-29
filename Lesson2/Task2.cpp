#include "Task2.h"

namespace PointersTask {
	void PointersTask::Child::cutParent()
	{
		//this method first erases child pointer from the parent by calling Parent::removeChild
		//and after that assignes empty weak_ptr for parent field
		if (auto ptr = _wParent.lock())
			ptr->removeChild(_id);
		this->setParent(std::weak_ptr<Parent>());
	}
	std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Child>& pChild) {
		if (pChild) {
			os << pChild.get() << ", parent = ";
			if (auto pParent = pChild->_wParent.lock())
				os << pParent.get();
			else
				os << "nullptr";
			os << ", id = " << pChild->_id << ", use_count = " << pChild.use_count() << '\n';
		}
		else
			os << "nullptr\n";
		return os;
	}
	void Parent::addChild(const std::weak_ptr<Parent>& w_parent, const std::shared_ptr<Child>& p_child)
	{
		if (auto pParent = w_parent.lock()) {
			p_child->setParent(w_parent);
			pParent->_childs.push_back(p_child);
		}
	}
	std::shared_ptr<Child> Parent::removeChild(int id)
	{
		//function which removes child with given id
		//first it searches for child with given id
		//if found, method erases that child from a vector of childs
		//and calls cutParent method on child
		//even though cutParent again calls removeChild from parent it doesn't matter
		//such behaviour is useful when we need to cutChild from parent by calling cutParent
		//method on child, not parent
		auto iter = std::find_if(_childs.begin(), _childs.end(), [id](const auto& ch) -> bool {
			return ch->_id == id;
		});
		if (iter != _childs.end()) {
			auto toDeleteChild = *iter;
			_childs.erase(iter);
			toDeleteChild->cutParent();
			return toDeleteChild;
		}
		else
			return std::shared_ptr<Child>(nullptr);
	}
	std::shared_ptr<Child> Parent::findChild(int id)
	{
		auto iter = std::find_if(_childs.begin(), _childs.end(), [id](const auto& ch) -> bool {
			return ch->_id == id;
		});
		return (iter == _childs.end() ? std::shared_ptr<Child>(nullptr) : *iter);
	}

	std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Parent>& pParent) {
		if (pParent) {
			os << "Parent =" << pParent.get() << ":\n";
			for (const std::shared_ptr<Child>& pChild : pParent->_childs)
				os << "Child: " << pChild;
		}
		else
			os << "Parent = nullptr\n";
		return os;
	}
	void Test()
	{
		auto pParent = std::make_shared<Parent>();
		std::weak_ptr<Parent> wParent = pParent;

		std::shared_ptr<Child> pChild1 = std::make_shared<Child>(1);
		Parent::addChild(wParent, pChild1);
		std::cout << "Child1: " << pChild1;
		std::cout << "Parent after adding Child1: " << pParent << "\n";

		std::shared_ptr<Child> pChild2 = std::make_shared<Child>(2);
		std::cout << "Child2 before adding to parent: " << pChild2;
		Parent::addChild(wParent, pChild2);
		std::cout << "Parent after adding Child2: " << pParent << "\n";

		std::shared_ptr<Child> pChild3 = std::make_shared<Child>(3);
		Parent::addChild(wParent, pChild3);
		std::cout << "pParent after three children added:\n" << pParent << "\n";

		std::shared_ptr<Child> pChild4 = pParent->findChild(2);
		std::cout << "pChild4: " << pChild4;
		std::cout << "pParent after findingChild(2): " << pParent << "\n";

		std::shared_ptr<Child> pChild5 = pParent->removeChild(3);
		std::cout << "pChild5: " << pChild5;
		std::cout << "pParent after removeChild(3): " << pParent << "\n";

		pChild2->cutParent();
		std::cout << "child(2) after cutting the parent\n";
		std::cout << "pChild2: " << pChild2;
		std::cout << "pParent: " << pParent << "\n";

		pParent.reset();
		std::cout << "Parent after reset: " << pParent << "\n";
	}
}