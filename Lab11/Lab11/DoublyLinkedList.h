#pragma once
#include "cstdarg"
template <class T>
class DoublyLinkedList {
private:
	class DFLT_EQ {
	public:
		static bool compare(T a, T b) { return a == b; }
	};
	class Node {
	public:
		T data;
		Node *pNext;
		Node *pPrev;
		Node(T item, Node *next = nullptr, Node *prev = nullptr) :data(item), pNext(next), pPrev(prev) {}
	};
	unsigned size;
	Node *pHead;
	Node *pTail;
	Node *getNode(unsigned pos) const {
		Node *curr = pHead;
		for (unsigned x = 1; x < pos; x++) curr = curr->pNext;
		return curr;
	}
public:
	DoublyLinkedList() :size(0), pHead(nullptr), pTail(nullptr) {}
	~DoublyLinkedList() {
		Node *next, *curr = pHead;
		while (curr != nullptr) {
			next = curr->pNext;
			delete curr;
			curr = next;
		}
	}
	bool isEmpty() const { return size == 0; }
	unsigned getSize() const { return size; }
	void addHead(T item) {
		//temp ptr obj stores ptr to original head
		Node* oldHead = pHead;
		pHead = new Node(item, pHead);
		if (pTail == nullptr) pTail = pHead;
		if (oldHead != nullptr) { 
			oldHead->pPrev = pHead;
			pHead->pNext = oldHead;
		}
		size++;
	}
	void addTail(T item) {
		Node *oldTail = pTail;
		if (isEmpty()) {
			//addHead(item);
			pHead = pTail = new Node(item);
		}
		else {
			pTail = pTail->pNext = new Node(item);
			pTail->pPrev = oldTail;
		}
		size++;
	}
	void add(unsigned pos, T item) {
		if (pos == 1) {
			addHead(item);
		}
		else {
			if (pos == size + 1) {
				addTail(item);
			}
			else {
				Node *prev = getNode(pos - 1);
				Node *next = prev->pNext;
				prev->pNext = new Node(item, prev->pNext, prev);
				next->pPrev = prev->pNext;
				size++;
			}
		}
	}	
	T retrieveHead() const { return pHead->data; }
	T retrieveTail() const { return pTail->data; }
	T retrieve(unsigned pos) const {
		return
			(pos == size ? retrieveTail() : getNode(pos)->data);
	}
	T removeHead() {
		T ret = pHead->data;
		Node *kill = pHead;
		pHead = pHead->pNext;
		if (pHead == nullptr) pTail = nullptr;
		if (pHead != nullptr ) {
			pHead->pPrev = nullptr;
		}
		size--;
		delete kill;
		return ret;
	}
	T removeTail() {
		if (pTail == pHead) return removeHead();
		T ret = pTail->data;
		Node *prev = getNode(size - 1);
		prev->pNext = nullptr;
		delete pTail;
		pTail = prev;
		size--;
		return ret;
	}
	T remove(unsigned pos) {
		if (pos == 1) return removeHead();
		if (pos == size) return removeTail();
		Node * prev = getNode(pos - 1);
		Node * curr = prev->pNext;
		T ret = curr->data;
		prev->pNext = curr->pNext;
		curr->pNext->pPrev = prev; 
		size--;
		delete curr;
		return ret;
	}
	T replace(unsigned pos, T item) {
		Node *curr = getNode(pos);
		T ret = curr->data;
		curr->data = item;
		return ret;
	}
	template <class EQ = DFLT_EQ>
	int find(T item) {
		Node *curr = pHead;
		int pos = 1;
		while (curr != nullptr) {
			if (EQ::compare(item, curr->data)) return pos;
			curr = curr->pNext;
			pos++;
		}
		return -1;
	}
	class Iterator {
	private:
		Node *m_ptr;
	public:
		Iterator(Node *ptr) :m_ptr(ptr) {}
		void operator++() { m_ptr = m_ptr->pNext; }
		void operator--() { m_ptr = m_ptr->pPrev; }
		bool operator!=(const Iterator &other) { return (m_ptr == other.m_ptr); }
		T getValue() { return m_ptr->data; }
		void setValue(T item) { m_ptr->data = item; }
	};
	Iterator begin() { return Iterator(pHead); }
	Iterator end() { return Iterator(nullptr); }
	Iterator last() { return Iterator(pTail); }
	//Add this method to the DoublyLinkedList class
	bool validate(unsigned count, ...) {
		if (count != size) {
			cout << "validate FAIL:Size does not match!" << count << ":" << size << endl;
			return false;
		}
		//if empty list, verify list variables (head/tail/size)
		if (size == 0 || pHead == nullptr || pTail == nullptr) {
			if (size != 0 || pHead != nullptr || pTail != nullptr) {
				cout << "validate FAIL:List empty/not empty mismatch!" << endl;
				cout << "  Size:" << size << endl;
				cout << "  pHead==nullptr:" << (pHead == nullptr) << endl;
				cout << "  pTail==nullptr:" << (pTail == nullptr) << endl;
				return false;
			}
		}
		else {
			//Not an empty list, verify pHead->pPrev != nullptr and pTail->pNext != nullptr
			if (pHead->pPrev != nullptr) {
				cout << "validate FAIL:pHead->pPrev != nullptr!" << endl;
				return false;
			}
			if (pTail->pNext != nullptr) {
				cout << "validate FAIL:pTail->pNext != nullptr!" << endl;
				return false;
			}
		}
		//copy argument list to array
		T *arr = new T[count];
		va_list arguments;
		va_start(arguments, count);
		for (unsigned x = 0; x < count; x++)
			arr[x] = va_arg(arguments, T);
		va_end(arguments);

		Node *curr;
		//validate next Node pointers
		curr = pHead;
		for (unsigned pos = 1; pos <= size; pos++) {
			if (curr == nullptr) {
				cout << "validate FAIL:Forward traversal-Node " << pos << " is a nullptr!" << endl;
				delete[] arr;
				return false;
			}
			if (curr->data != arr[pos - 1]) {
				cout << "validate FAIL:Forward node data " << curr->data << " does not match arr data " << arr[pos - 1] << endl;
				delete[] arr;
				return false;
			}
			curr = curr->pNext;
		}
		//validate prev Node pointers
		curr = pTail;
		for (unsigned pos = size; pos >= 1; pos--) {
			if (curr == nullptr) {
				cout << "validate FAIL:Backward traversal-Node " << pos << " is a nullptr!" << endl;
				delete[] arr;
				return false;
			}
			if (curr->data != arr[pos - 1]) {
				cout << "validate FAIL:Backward node data " << curr->data << " does not match arr data " << arr[pos - 1] << endl;
				delete[] arr;
				return false;
			}
			curr = curr->pPrev;
		}
		delete[] arr;
		return true;
	}
};