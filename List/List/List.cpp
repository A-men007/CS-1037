#include <iostream>
#include "List.h"
#include <List>
#include "OrderedList.h"

using namespace std;


int main(int argc, char *argv[]) {
	//instantiated List class...
	//they become intalized like vectors
	List <unsigned> A(10);
	A.insert(5, 10);

	cout << "is empty: " << A.isEmpty() << endl;


	system("PAUSE");
}

