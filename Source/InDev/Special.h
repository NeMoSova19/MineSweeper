#pragma once

struct MyIterator {
	void* ptr{ nullptr };
	virtual void Next() = 0;
	virtual std::pair<void*, void*> GetPair() { return { nullptr, nullptr }; }
};

struct Variable_C {
	const char* name;
	std::vector<int> type;
	void* ptr{ nullptr };
	MyIterator* iterator{ nullptr };
};

struct MyIterator0 : public MyIterator
{
	MyIterator0() {}
	void Next() {}
};

template<class T>
struct MyIterator1 : public MyIterator
{
	MyIterator1(T i) {
		it = i;
		ptr = &(*it);
		//ptr = &i._Ptr->_Myval;
	};
	void Next() {
		it++;
		ptr = &(*it);
		//ptr = &it._Ptr->_Myval;
	}

	T it;
};

template<class T, class D>
struct MyIterator2 : public MyIterator
{
	MyIterator2(std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<T, D>>>> i) {
		it = i;
		ptr = &(*it);
		//ptr = &i._Ptr->_Myval;
	};
	void Next() {
		it++;
		ptr = &(*it);
		//ptr = &it._Ptr->_Myval;
	}
	std::pair<void*, void*> GetPair() {
		return { (void*)&(*it).first, (void*)&(*it).second };
	}

	std::map<T, D>::iterator it;
};