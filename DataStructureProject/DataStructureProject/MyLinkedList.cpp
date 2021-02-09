#include <vector>
#include <exception>
#include <string>

using namespace std;

class MyListException : exception
{
public:

	int code;
	string msg;

	MyListException(int exp)
	{
		code = exp;
		if (exp = 1)
		{
			msg = "Invalid head() call: empty list";
		}
		else if (exp = 2)
		{
			msg = "Invalid end() call: empty list";
		}
		else if (exp = 11)
		{
			msg = "Invalid next() call: hasNext() false";
		}
		else if (exp = 12)
		{
			msg = "Invalid previous() call: hasPrevious() false";
		}
		else if (exp = 13)
		{
			msg = "Invalid set(T v) call: undefined current position";
		}
		else if (exp = 14)
		{
			msg = "Invalid remove() call: undefined current position";
		}
		else
		{
			msg = "Unknown";
		}
	}
};


template <class T> class MyLinkedList;
template <class T> class MyLinkedListIterator;

template <class T> class Node
{

private:

	T data;
	Node<T>* next;
	Node<T>* prev;

	Node()
	{
		next = nullptr;
		prev = nullptr;
	}

	Node(T v)
	{
		data = v;
		next = nullptr;
		prev = nullptr;
	}

	friend class MyLinkedList<T>;
	friend class MyLinkedListIterator<T>;

};
template <class T> class MyLinkedListIterator
{
private:

	Node<T>* itnext;                              // next node 
	Node<T>* current;                             // current node
	MyLinkedList<T> * ch;                         // MyLinkedList object upon which we iterate.

	MyLinkedListIterator(MyLinkedList<T> & a)
	{
		ch = &a;
		current = nullptr;
		itnext = a.first;
	}

	friend class MyLinkedList<T>;

public:

	bool hasNext()
	{
		return itnext != nullptr;
	}

	T next()
	{
		if (itnext != nullptr)
		{
			current = itnext;
			itnext = itnext->next;
			return current->data;
		}
		else
		{
			MyListException e(1);
			throw e;
		}
	}

	bool hasPrevious()
	{
		return current != nullptr;
	}

	T previous()
	{
		if (current != nullptr)
		{
			T w;
			w = current->data;
			itnext = current;
			current = current->prev;
			return w;
		}
		else
		{
			MyListException e(12);
			throw e;
		}
	}

	void goToBegin()                          // sets the iterator to the begin of the list.
	{
		current = nullptr;
		itnext = ch->first;
	}

	void goToEnd()                             // sets the iterator to the end of the list.
	{
		current = ch->last;
		itnext = nullptr;
	}

	void set(T v)                           // assign v as the value of "data" in the node that is at the current position.
	{
		if (current != nullptr)
		{
			current->data = v;
		}
		else
		{
			MyListException e(13);
			throw e;
		}
	}
	void add(T v)                          // adds a node ("data" = v) after the current position.
	{
		Node<T> * temp;
		temp = new Node<T>();
		temp->data = v;
		if (current == nullptr)
		{
			temp->next = ch->first;
			if (ch->first != nullptr)
			{
				ch->first->prev = temp;
			}
			else
			{
				ch->last = temp;
			}
			ch->first = temp;
			current = temp;
		}
		else
		{
			temp->next = current->next;
			if (current->next != nullptr)
			{
				current->next->prev = temp;
			}
			else
			{
				ch->last = temp;
			}
			current->next = temp;
			temp->prev = current;
			current = temp;
		}
	}
	void remove()                       // removes the node that is at current position.
	{
		if (current != nullptr)
		{
			Node<T> *temp;
			temp = current;
			if (itnext != nullptr)
			{
				current = itnext;
				itnext = itnext->next;
				if (temp->prev == nullptr)
				{
					ch->first = current;
					current->prev = nullptr;
				}
				else
				{
					temp->prev->next = current;
					current->prev = temp->prev;
				}
				delete temp;
			}
			else
			{
				current = current->prev;
				ch->last = current;
				if (current != nullptr)
				{
					ch->first = nullptr;
				}
				else
				{
					current->next = nullptr;
				}
				delete temp;
			}
		}
		else
		{
			MyListException e(14);
			throw e;

		}
	}
};

template <class T> class MyLinkedList
{
private:

	Node<T>* first;
	Node<T>* last;

public:

	friend class MyLinkedListIterator<T>;

	MyLinkedList()                         // empty list
	{
		first = nullptr;
		last = nullptr;
	}

	MyLinkedList(T v)                     // list of a single node, whose member "data" is v.
	{
		MyLinkedList();
		append(v);
	}

	MyLinkedList(T v[], int size)        // list whose nodes correspond to the elements of the array v
	{
		MyLinkedList();
		for (int i = 0; i < size; i++)
		{
			append(v[i]);
		}
	}

	MyLinkedList(vector<T> v)
	{
		MyLinkedList();
		for (int i = 0; i < v.size; i++)
		{
			append(v[i]);
		}
	}

	vector<T> toVector()                // return the vector of objects of type T corresponding to MyLinkedList.
	{
		vector<T> w;
		Node<T>* curr = this->first;
		while (curr != nullptr) {
			w.push_back(curr->data);
			curr = curr->next;
		}
		return w;
	}

	T head()						  // return the value of "data" of the first node.	
	{
		if (first != nullptr)
		{
			return first->data;
		}
		else
		{
			MyListException e(1);
			throw e;
		}
	}

	MyLinkedList<T> tail()                // return the MyLinkedList without its first node.
	{
		MyLinkedList<T> w;
		if (first != nullptr)
		{
			w.first = first->next;
		}
		if (w.first != nullptr)
		{
			w.last = last;
		}
		return w;
	}

	T end()	                         // return the value of "data" of the last node.
	{
		if (last != nullptr)
		{
			return last->data;
		}
		else
		{
			MyListException e(2);
			throw e;
		}
	}

	void append(T e)                         // creates a node with "data"=e at the end of the MyLinkedList.
	{
		Node<T> * temp;
		if (last == nullptr)
		{
			first = new Node<T>();
			first->data = e;
			last = first;
		}
		else
		{
			temp = new Node<T>();
			temp->data = e;
			last->next = temp;
			temp->prev = last;
			last = temp;
		}
	}
	void concat(MyLinkedList<T> lc)         // concatenates lc at the end of MyLinkedList.
	{
		if (last == nullptr)
		{
			first = lc.first;
			last = lc.last;
		}
		else
		{
			last->next = lc.first;
			lc.first->prev = last;
			last = lc.last;
		}
	}

	MyLinkedListIterator<T> iterator()        // method to initialise the iterator MyLinkedListIterator for the current LinkedChain.
	{
		return MyLinkedListIterator<T>(*this);
	}

};


