//#pragma once
//
//#include "List.h"
//template <class Item>
//class OrderedList {
//public:
//	OrderedList(unsigned capacity = DEFAULT_LIST); // constructor for
//	// an empty ordered list that can hold up to capacity items; default
//	// size is defined in List.h
//	~OrderedList(); // destructor
//	bool isEmpty() const; // true if list is empty, false otherwise#pragma once
//	int getLength() const; // returns the current size of the list
//	// remove the value at location pos, and return it;
//	// precondition: pos must be a legal list position
//	Item remove(unsigned pos);
//	// return value at pos without modifying the list;
//	// precondition: pos must be a legal list position
//	Item retrieve(unsigned pos) const;
//	// insert item at appropriate pos’n in list and return its index
//	int insert(Item item);
//	// return pos’n of first occurrence of item, or -1 if item isn’t found
//	int find(Item item) const;
//private:
//	List<Item> m_container; // to hold the list of Items
//};
//
//#include <stdlib.h>
//template <class Item>
//OrderedList<Item> ::OrderedList(unsigned capacity)
//	: m_container(capacity)
//{ }
//template <class Item>
//OrderedList<Item> :: ~OrderedList()
//{ }
//template <class Item>
//bool OrderedList<Item> ::isEmpty() const {
//	return m_container.isEmpty();
//}
//template <class Item>
//int OrderedList<Item> ::getLength() const {
//	return m_container.getLength();
//}
//template <class Item>
//Item OrderedList<Item> ::remove(unsigned pos) {
//	return m_container.remove(pos);
//}
//template <class Item>
//Item OrderedList<Item> ::retrieve(unsigned pos) const {
//	return m_container.retrieve(pos);
//}
//template <class Item>
//int OrderedList<Item> ::insert(Item item) {
//	int k;
//	for (k = 1; k <= getLength(); k++)
//		if (item < retrieve(k))
//			break;
//	m_container.insert(k, item);
//	return k;
//}
//template <class Item>
//int OrderedList<Item> ::find(Item item) const {
//	int k;
//	for (k = 1; k <= getLength(); k++)
//		if (item == retrieve(k))
//			return k;
//	return – 1;
//}