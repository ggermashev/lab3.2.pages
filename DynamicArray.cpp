#include "DynamicArray.h"
#include <iostream>

template <class T> 
DynamicArray<T>::DynamicArray(T* item, int n) {
	elem = new T[n];
	size = n;
	for (int i = 0; i < size; i++) {
		elem[i] = item[i];
	}
}

template <class T> 
DynamicArray<T>::DynamicArray(int n) {
	elem = new T[n];
	size = n;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynArr) {
	size = dynArr.size;
	elem = new T[size];
	for (int i = 0; i < size; i++) {
		elem[i] = dynArr.elem[i];
	}
}

template  <class T>
T DynamicArray<T>::Get(int i) {
	try {
		return elem[i];
		throw i;
	}
	catch(int i) {
		std::cout << "Out of range in Get: " << i << std::endl;
	}
}

template <class T>
T* DynamicArray<T>::GetIterator(int i)
{
	try
	{
		return &elem[i];
		throw i;
	}
	catch (int i)
	{
		std::cout << "Out of range in GetIterator: " << i << std::endl;
	}
}

template <class T>
int DynamicArray<T>::GetSize() {
	return size;
}

template <class T>
void DynamicArray<T>::Set(T value, int i) {
	if (i >= size) {
		std::cout << "Out of range if Set: " << i << std::endl;
		return;
	}
	elem[i] = value;
}

template <class T>
void DynamicArray<T>::Resize(int newsz) {
	
	T* arr = new T[size];
	for (int i = 0; i < size; i++) {
		arr[i] = elem[i];
	}
	delete[] elem;
	elem = new T[newsz];
	for (int i = 0; i < size && i < newsz; i++) {
		elem[i] = arr[i];
	}
	size = newsz;
	delete[] arr;
}

template <class T>
void DynamicArray<T>::Clear()
{
	if (!elem) return;
	delete[] elem;
	elem = NULL;
	size = 0;
}