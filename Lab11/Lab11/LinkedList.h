#pragma once

template <class T>
class LinkedList {
private:
	class Node {
	public:
		T data;
		Node *pNext;
		Node(T item, Node *next = nullptr) :data(item), pNext(next) {}
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
	LinkedList() :size(0), pHead(nullptr), pTail(nullptr) {}
	~LinkedList() {
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
		pHead = new Node(item, pHead);
		if (pTail == nullptr) pTail = pHead;
		size++;
	}
	void addTail(T item) {
		if (isEmpty()) {
			//addHead(item);
			pHead = pTail = new Node(item);
		}
		else {
			pTail = pTail->pNext = new Node(item);
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
				prev->pNext = new Node(item, prev->pNext);
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
	template <class EQ>
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
		bool operator!=(const Iterator &other) { return (m_ptr == other.m_ptr); }
		T getValue() { return m_ptr->data; }
		void setValue(T item) { m_ptr->data = item; }
	};
	Iterator begin() { return Iterator(pHead); }
	Iterator end() { return Iterator(nullptr); }
};