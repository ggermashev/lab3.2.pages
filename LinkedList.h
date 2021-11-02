#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
struct Node {
	T data;
	Node* next;
	Node* prev;
};

template <class T> class LinkedList {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

	
public:
	Node<T>* GetNode(int i);
	//создание
	LinkedList(T* item, int n);
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	//декомпозиция
	T GetFirst();
	T GetLast();
	T Get(int i);
	LinkedList<T>* GetSubList(int i, int j);
	int GetLength();
	//операции
	void Input(T* mas, int start, int end);
	void Append(T item);
	void Prepend( T item );
	void InsertAt(T item, int i);
	LinkedList<T> Concat(LinkedList<T>* list);
	void Clear();

	void Set(T item, int i);
	void Output(LinkedList<T>* list);
};


#endif // !LINKEDLIST_H





