#pragma once

const int DEFAULT_LIST = 200;

template <class Item>
class List {
public:
	List(unsigned capacity = DEFAULT_LIST); // constructor for
	// an empty list that can hold up to capacity items; if capacity
	// is not supplied, the default size is used
	~List(); // destructor
	bool isEmpty() const;
	// returns true if the list is empty, and false otherwise
	bool isFull() const;
	// returns true if the list is full, and false otherwise
	unsigned getLength() const;
	// returns the number of items currently in the list
	void insert(unsigned pos, Item item);
	// inserts item into the list at location pos;
	// PRECONDITION: pos must be be a valid position
	// and the bag should not be full
	Item remove(unsigned pos);
	// removes the element at location pos from the list, and returns it;
	// PRECONDITION: pos must be a valid position
	Item retrieve(unsigned pos) const;
	// find the element stored at location pos in the list, and
	// return it; PRECONDITION: pos must be a valid list position
	Item replace(unsigned pos, Item item);
	// replace the element at location pos in the list with item,
	// and return the element that was displaced;
	// PRECONDITION: pos must be a valid list position
	void swap(unsigned i, unsigned j);
	// swaps Item values stored in 2 specified positions
	// PRECONDITION: i and j must be valid list positions
private:
	Item * m_container; // pointer to array to hold the list
	unsigned m_max_capacity; // maximum capacity of the list
	unsigned m_size; // number of items currently in the list
	inline unsigned translate(unsigned pos) const { return pos - 1; }
	// converts a list position to the corresponding array index


	void replaceContainer();
	// private function replaces the underlying array with one that holds
	// the same values as the original, but has double the capacity
};

template <class Item>
List<Item> ::List(unsigned capacity) {
	m_max_capacity = capacity;
	m_container = new Item[m_max_capacity];
	m_size = 0;
}
template <class Item>
List <Item> :: ~List() {
	delete[] m_container;
}
template <class Item>
bool List <Item> ::isEmpty() const {
	return (m_size == 0);
}
//template <class Item>
//bool List <Item> ::isFull() const {
//	return (m_size == m_max_capacity);
//}
// replace earlier implementation of isFull with:
template <class Item>
bool List<Item> ::isFull() const {
	//b/c it can always get bigger with replacecontainer().....
	return false;
}
template <class Item>
unsigned List<Item> ::getLength() const {
	return m_size;
}
//template <class Item>
//void List <Item> ::insert(unsigned pos, Item item) {
//	// PRECONDITION: pos must be between 1 and m_size+1
//	// and the bag should not be at full capacity
//	for (unsigned k = m_size; k >= pos; k--)
//		m_container[translate(k + 1)] = m_container[translate(k)];
//	m_container[translate(pos)] = item;
//	m_size++;
//}
// replace earlier implementation of insert with:
template <class Item>
void List<Item> ::insert(unsigned pos, Item item) {
	// PRECONDITION: pos must be between 1 and m_size+1
	if (m_size == m_max_capacity) replaceContainer();
	for (int k = m_size; k >= pos; k--) {
		m_container[translate(k + 1)] = m_container[translate(k)];
	}
	m_container[translate(pos)] = item;
	m_size++;
}
template <class Item>
Item List<Item> ::remove(unsigned pos) {
	// PRECONDITION: the list is not empty,
	// and pos is between 1 and m_size
	Item returnValue = m_container[translate(pos)];
	for (int k = pos + 1; k <= m_size; k++)
		m_container[translate(k - 1)] = m_container[translate(k)];
	m_size--;
	return returnValue;
}
template <class Item>
Item List<Item> ::replace(unsigned pos, Item item) {
	// PRECONDITION: the list is not empty,
	// and pos is between 1 and m_size
	Item returnVal = m_container[translate(pos)];
	m_container[translate(pos)] = item;
	return returnVal;
}
template <class Item>
Item List<Item> ::retrieve(unsigned pos) const {
	// PRECONDITION: the list is not empty,
	// and pos is between 1 and m_size
	return m_container[translate(pos)];
}
template <class Item>
void List<Item>::swap(unsigned i, unsigned j) {
	// PRECONDITION: indexes i and j should be within list range
	if (i == j) return;
	Item temp = m_container[translate(i)];
	m_container[translate(i)] = m_container[translate(j)];
	m_container[translate(j)] = temp;
}
template <class Item>
void List<Item> ::replaceContainer() {
	Item * newList;
	newList = new Item[2 * m_max_capacity];
	for (int k = 0; k < m_size; k++)
		newList[k] = m_container[k];
	m_max_capacity = 2 * m_max_capacity;
	delete[] m_container;
	m_container = newList;
}