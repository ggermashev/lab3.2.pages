#pragma once

template <class K, class T>
class Pair
{
public:
	K key;
	T element;
	Pair<K,T>* next;
	Pair<K,T>* prev;
	Pair(K k, T elem);
};

template <class K, class T>
class Dictionary
{
private:
	int size;
	int count;
	Pair<K,T>* head;
	Pair<K,T>* tail;
public:
	Dictionary();
	int GetCount();
	int GetSize();
	T Get(K key);
	bool CheckKey(K key);
	void Add(K key, T elem);
	void Remove(K key);
};

void Test();