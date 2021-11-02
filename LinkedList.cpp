#include "LinkedList.h"
#include <iostream>

template <class T>
LinkedList<T>::LinkedList(T* item, int n) {
	head = new Node<T>;
	tail = new Node<T>;
	size = n;
	head->data = item[0];
	Node<T>* ptr = head;
	ptr->prev = NULL;
	for (int i = 1; i < n; i++) {
		ptr->next = new Node<T>;
		ptr->next->prev = ptr;
		ptr = ptr->next;
		ptr->data = item[i];
	}
	tail = ptr;
	tail->next = nullptr;
}

template <class T> 
LinkedList<T>::LinkedList() { 
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	head = new Node<T>;
	tail = new Node<T>;
	size = 0;

	Node<T>* ptr1 = head;
	Node<T>* ptr2 = list.head;

	while (ptr2 != list.tail) {
		ptr1->data = ptr2->data;
		ptr1->next = new Node<T>;
		ptr1->next->prev = ptr1;
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		size++;
	}
	ptr1->data = ptr2->data;
	tail = ptr1;
	tail->next = nullptr;
	size++;
}

template <class T>
T LinkedList<T>::GetFirst() {
	return head->data;
}

template <class T> 
T LinkedList<T>::GetLast() {
	return tail->data;
}

template <class T> 
T LinkedList<T>::Get(int i) {
	try {
		int j = 0;
		Node<T>* ptr = head;
		while (j != i) {
			ptr = ptr->next;
			j++;
		}
		return ptr->data;
		throw i;
	}
	catch (int i) {
		std::cout << "Out of range in Get: " << i << std::endl;
	}
}

template <class T>
Node<T>* LinkedList<T>::GetNode(int i)
{
	try {
		int j = 0;
		Node<T>* ptr = head;
		while (j != i) {
			ptr = ptr->next;
			j++;
		}
		return ptr;
		throw i;
	}
	catch (int i) {
		std::cout << "Out of range in Get: " << i << std::endl;
	}
}

template <class T>
void LinkedList<T>::Input(T* mas, int start, int end)
{
	int j = start;
	Node<T>* ptr = this->GetNode(j);
	while (j <= end)
	{
		ptr->data = mas[j];
		ptr = ptr->next;
		j++;
	}
	return;
}


template <class T>
void LinkedList<T>::Set(T item, int i) {
	if (i >= size) {
		std::cout << "Out of range: " << i << std::endl;
		return;
	}

	int j = 0;
	Node<T>* ptr = head;
	while (j != i) {
		ptr = ptr->next;
		j++;
	}
	ptr->data = item;

}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int i, int j) {
	try {
		LinkedList<T>* list = new LinkedList<T>;
		Node<T>* ptr = head;
		int k = 0;
		while (k != i) {
			ptr = ptr->next;
			k++;
		}

		for (int k = 0; k < j - i + 1; k++) {
			list->Append(ptr->data);
			ptr = ptr->next;
		}
		list->Append(ptr->data);
		return list;
		throw ;
	}
	catch(int i)  {
		std::cout << "Out of range in GetSubList\n" << std::endl;
	}
} 

template <class T>
int LinkedList<T>::GetLength() {
	return size;
}

template <class T>
void LinkedList<T>::Append(T item) {
	if (!head) {
		Node<T>* ptr = new Node<T>;
		ptr->data = item;
		head = ptr;
		tail = ptr;
		size++;
		ptr->next = nullptr;
		ptr->prev = nullptr;
		return;
	}

	tail->next = new Node<T>;
	tail->next->prev = tail;
	Node<T>* ptr = tail->next;
	ptr->data = item;
	size++;
	tail = ptr;
	tail->next = nullptr;
}

template <class T>
void LinkedList<T>::Prepend(T item) {
	if (!head) {
		Node<T>* ptr = new Node<T>;
		ptr->data = item;
		head = ptr;
		tail = ptr;
		size++;
		return;
	}
	Node<T>* ptr = new Node<T>;
	ptr->data = item;
	ptr->next = head;
	head->prev = ptr;
	head = ptr;
	size++;
}

template <class T>
void LinkedList<T>::InsertAt(T item, int i) {

	try {
		int k = 0;
		Node<T>* ptr = head;

		if (i == 0) {
			Prepend(item);
			return;
		}

		while (k != i - 1) {
			ptr = ptr->next;
			k++;
		}

		Node<T>* newptr = new Node<T>;
		newptr->data = item;
		newptr->next = ptr->next;
		newptr->prev = ptr;
		ptr->next = newptr;
		size++;
		throw i;
	}
	catch (int i) {
		std::cout << "Out of range in InsertAt: " << i << std::endl;
	}
}

template <class T> 
LinkedList<T> LinkedList<T>::Concat(LinkedList<T>* list) {
	LinkedList<T> newlist(*this) ;
	Node<T>* ptr1 = newlist.tail;
	Node<T>* ptr2 = list->head;
	while (ptr2 != list->tail) {
		ptr1->next = new Node<T>;
		ptr1->next->prev = ptr1;
		ptr1 = ptr1->next;
		ptr1->data = ptr2->data;
		ptr2 = ptr2->next;
	}

	ptr1->next = new Node<T>;
	ptr1->next->prev = ptr1;
	ptr1 = ptr1->next;
	ptr1->data = ptr2->data;
	newlist.tail = ptr1;
	newlist.size = size + list->size;
	return newlist;
}

template <class T>
void LinkedList<T>::Clear()
{
	Node<T>* ptr = head;
	while (ptr != tail)
	{
		Node<T>* last = ptr;
		ptr = ptr->next;
		delete last;
	}
	return;
}

template <class T>
void LinkedList<T>::Output(LinkedList<T>* list)
{
	if (!list->head) return;
	Node<T>* ptr = list->head;
	while (ptr != list->tail)
	{
		std::cout << ptr->data << " ";
		ptr = ptr->next;
	}
	std::cout << ptr->data << "\n";
	//delete ptr;
	return;
}