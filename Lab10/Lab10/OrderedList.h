#pragma once
#include <vector>
using namespace std;

template <class T, class O>

class OrderedList {
private:
	vector<T> list;
	unsigned translate(unsigned req) const{
		return req - 1;
	}
public:
	OrderedList(int DeSize = 5) {
		list.reserve(DeSize);
	}
	unsigned getLength() const {
		return list.size();
	}
	void insert(T item) {
		int k;
		for (k = 1; k <= getLength(); k++) {
			if (O::compare(item, retrieve(k)))
				break;
		}
		list.insert(list.begin() + translate(k), item);
	}
	/*template<class EQ> int find(T item) const {
		int i;
		for (i = 1; i <= getLength(); i++) {
			if (EQ::compare(item, retrieve(i)))
				return i;
		}
		return -1;
	}*/

	T retrieve(unsigned pos) const {
		return list[pos];
	}

};