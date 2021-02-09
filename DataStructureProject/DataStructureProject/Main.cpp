#include <iostream>
#include "MyLinkedList.cpp"

using namespace std;

int main()
{
	MyLinkedList<int> a(5);
	a.append(4);
	a.append(6);
	cout << a.head() << " " << a.end() << endl;       // 1st Line Result -- Display head(5) and end(6). 

	MyLinkedListIterator<int> v = a.iterator();

	v.goToBegin();
	while (v.hasNext())
	{
		cout << v.next() << " ";      // 2nd Line Result -- Display from the beginning head(5), the next value after which is 4, and the last value 6. 
	}
	cout << endl;

	v.goToEnd();
	while (v.hasPrevious())
	{
		cout << v.previous() << " ";    // 3rd Line Result -- Display from the end tail(6), the previous value which is 4, and the head(5).
	}
	cout << endl;


	v.add(3);

	v.next();
	while (v.hasNext())
	{
		cout << v.next() << " ";       // 4th Line Result -- Display from the value next(4), and the value end(6).
	}
	cout << endl;

	v.previous();
	while (v.hasPrevious())
	{
		cout << v.previous() << " ";      // 5th Line Result -- Display from the value next(4), the value of previous(5), and the value already added which is 3.
	}
	cout << endl;

	v.goToBegin();
	v.add(2);
	v.goToEnd();
	v.add(7);
	v.goToBegin();

	while (v.hasNext())
	{
		cout << v.next() << " ";         // 6th Line Result -- Display from the beginning the value just added which is 2, then go back to the end which is 3,
										 // the previous value which is 5, the value before which is 4, then display the value next(6), and the value just added
		                                 // which is 7.
	}
	cout << endl;

	while (v.hasPrevious())
	{
		cout << v.previous() << " ";         // 7th Line Result -- Display the list above in reverse order.
	}
	cout << endl;

	v.goToEnd();
	while (v.hasPrevious())
	{
		cout << v.previous() << " ";       // 8th Line Result -- Verify the result above again.
	}
	cout << endl;


	system("pause");
}

