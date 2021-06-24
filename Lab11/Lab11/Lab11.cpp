#include <iostream>
#include <string>
using namespace std;
#include "DoublyLinkedList.h"

void quit(string msg = "") {
	cout << msg << endl;
	char z;
	cin >> z;
	exit(0);
}

int main(int argc, char *argv[]) {
	DoublyLinkedList<int> dll;
	//Instruction 10
		cout << "Constructor" << endl;
		if (!dll.validate(0)) quit();

	//Instruction 11
		cout << "Add head to empty list" << endl;
		dll.addHead(1);
		if (!dll.validate(1,1)) quit();
		cout << "Add head to non-empty list" << endl;
		dll.addHead(2);
		if (!dll.validate(2,2,1)) quit();

	//Instruction 12
		cout << "Remove head from 2 node list" << endl;
		if (dll.removeHead()!=2) quit("Failed to return correct value");
		if (!dll.validate(1,1)) quit();
		cout << "Remove head from 1 node list" << endl;
		if (dll.removeHead()!=1) quit("Failed to return correct value");
		if (!dll.validate(0)) quit();

	//Instruction 13
		cout << "Add tail to empty list" << endl;
		dll.addTail(1);
		if (!dll.validate(1,1)) quit();
		cout << "Add tail to non-empty list" << endl;
		dll.addTail(2);
		if (!dll.validate(2,1,2)) quit();
		cout << "Remove tail from 2 node list" << endl;
		if (dll.removeTail()!=2) quit("Failed to return correct value");
		if (!dll.validate(1,1)) quit();
		cout << "Remove tail from 1 node list" << endl;
		if (dll.removeTail()!=1) quit("Failed to return correct value");
		if (!dll.validate(0)) quit();

	//Instruction 14
		cout << "Replace middle node value" << endl;
		dll.addTail(2);
		dll.addTail(4);
		dll.addTail(6);
		if (dll.replace(2,9)!=4) quit("Failed to return correct value");
		if (!dll.validate(3,2,9,6)) quit();

	//Instruction 15
		cout << "test retrieve methods" << endl;
		dll.addTail(10);
		dll.addTail(11);
		if (dll.retrieveHead()!=2) quit("Failed to retrieve head value");
		if (dll.retrieveTail()!=11) quit("Failed to retrieve tail value");
		int tarr[]={2,9,6,10,11};
		for (unsigned x=0;x<5;x++)
			if (dll.retrieve(x+1)!=tarr[x]) quit("Failed to retrieve pos value");

	//Instruction 16
		cout << "test remove methods" << endl;
		if (dll.remove(2)!=9) quit("Failed to remove pos 2 value");
		if (!dll.validate(4,2,6,10,11)) quit();
		if (dll.remove(3)!=10) quit("Failed to remove pos 3 value");
		if (!dll.validate(3,2,6,11)) quit();

	//Instruction 17
		cout << "test add methods" << endl;
		dll.add(2,88);
		if (!dll.validate(4,2,88,6,11)) quit();
		dll.add(4,99);
		if (!dll.validate(5,2,88,6,99,11)) quit();

	//Instruction 18
		cout << "test find method" << endl;
		if (dll.find(88)!=2) quit("Failed to find 88 value");
		if (dll.find(2)!=1) quit("Failed to find 2 value");
		if (dll.find(11)!=5) quit("Failed to find 11 value");

	//Instruction 21
		int x,farr[]={2,88,6,99,11};
		cout << "test iterators" << endl;
		DoublyLinkedList<int>::Iterator start=dll.begin(),last=dll.last();
		for (x=0;x<5;x++){
			if (start.getValue()!=farr[x]) quit("Failed forward iterator");
			++start;
		}
		for (x=4;x>=0;x--){
			if (last.getValue()!=farr[x]) quit("Failed backward iterator");
			--last;
		}
		x=0;
		for (DoublyLinkedList<int>::Iterator curr=dll.begin();curr!=dll.end();++curr){
			if (curr.getValue()!=farr[x]) quit("Failed forloop iterator");
			x++;
		}
		x=4;
		for (DoublyLinkedList<int>::Iterator curr=dll.last();curr!=dll.end();--curr){
			if (curr.getValue()!=farr[x]) quit("Failed forloop-reverse iterator");
			x--;
		}

		cout << "test unchanged" << endl;
		if (!dll.validate(5,2,88,6,99,11)) quit();

	cout << "PASS!!!";
	char z;
	cin >> z;
	return(0);
}
