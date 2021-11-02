#pragma once
#include "Dictionary.h"
#include <fstream>
//-----------------------Pair--------------------

template <class K,class T>
Pair<K, T>::Pair(K k, T elem)
{
	key = k;
	element = elem;
	next = nullptr;
	prev = nullptr;
}


//-------------Dictionary------------------------------------
template <class K, class T>
Dictionary<K,T>::Dictionary()
{
	size = 0;
	count = 0;
	head = nullptr;
	tail = nullptr;
}

template <class K, class T>
int Dictionary<K,T>::GetCount()
{
	return count;
}

template <class K, class T>
int Dictionary<K, T>::GetSize()
{
	return size;
}

template <class K, class T>
T Dictionary<K, T>::Get(K k)
{
	Pair<K, T>* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->key == k) return ptr->element;
		ptr = ptr->next;
	}
}

template <class K, class T>
bool Dictionary<K, T>::CheckKey(K k)
{
	Pair<K, T>* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->key == k) return true;
		ptr = ptr->next;
	}
	return false;
}

template <class K, class T>
void Dictionary<K, T>::Add(K k, T elem)
{
	if (!head)
	{
		head = new Pair<K,T>(k,elem);
		tail = head;
		count = 1;
		size = 1;
		return;
	}
	Pair<K, T>* ptr = tail;
	ptr->next = new Pair<K, T>(k, elem);
	ptr = ptr->next;
	ptr->prev = tail;
	tail = ptr;
	count++;
	size++;
	return;
}

template <class K, class T>
void Dictionary<K, T>::Remove(K k)
{
	if (!head) return;
	Pair<K, T>* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->key == k)
		{
			if ((ptr != head) && (ptr != tail))
			{
				ptr->next->prev = ptr->prev;
				ptr->prev->next = ptr->next;
			}
			else if (ptr == head)
			{
				head = ptr->next;
				ptr->next->prev = nullptr;
			}
			else if (ptr == tail)
			{
				tail = ptr->prev;
				ptr->prev->next = nullptr;
			}
			delete ptr;
		}
	}
	count--;
	size--;
	return;
}





//-------------------------------test-------------------------------
