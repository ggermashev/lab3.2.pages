#include "Sequance.h"
#include <iostream>
#include <math.h>



template <class T>
ArrayVector<T>::ArrayVector(T* item, int n) {
	items = new DynamicArray<T> (item,n);
 }

template <class T> 
ArrayVector<T>::ArrayVector() {
	items = new DynamicArray<T>(0);
}

template <class T>
ArrayVector<T>::ArrayVector(int n) {
	items = new DynamicArray<T>(n);
}

template <class T> 
ArrayVector<T>::ArrayVector(const ArrayVector<T>& arrVec) {
	items = new DynamicArray<T>(*(arrVec.items)) ;
}


//декомпозиция
template <class T>
T  ArrayVector<T>::GetFirst() {
	return items->Get(0);
}

template <class T> 
T ArrayVector<T>::GetLast() {
	return items->Get(items->GetSize() - 1);
}

template <class T> 
T ArrayVector<T>::Get(int i) {
	return items->Get(i);
}

template <class T>
void ArrayVector<T>::Set(T elem, int i) {
	items->Set(elem, i);
}

template <class T>
T* ArrayVector<T>::GetIterator(int i)
{
	return items->GetIterator(i);
}

template <class T> 
ArrayVector<T>* ArrayVector<T>::GetSubVector(int i, int j) {
	try {
		ArrayVector<T>* newVec = new ArrayVector<T>;
		for (int k = 0; k < j - i + 1; k++) {
			newVec->Append(items->Get(i + k));
		}
		return newVec;
		throw ;
	}
	catch(int i)  {
		std::cout << "Out of range in GetSubLVector\n" << std::endl;
	}
}

template <class T> 
int ArrayVector<T>::GetLength() {
	return items->GetSize();
}


//операции
template <class T> 
void ArrayVector<T>::Append(T item) {
	items->Resize(items->GetSize() + 1);
	items->Set(item, items->GetSize() - 1);
}

template <class T> 
void ArrayVector<T>::Prepend(T item) {
	items->Resize(items->GetSize() + 1);
	for (int i = items->GetSize() - 1; i > 0; i--) {
		items->Set(items->Get(i - 1), i);
	}
	items->Set(item, 0);
}

template <class T> 
void ArrayVector<T>::InsertAt(T item, int i) {
	try {
		items->Resize(items->GetSize() + 1);
		for (int k = items->GetSize() - 1; k >= i; k--) {
			items->Set(items->Get(k - 1), k);
		}
		items->Set(item, i);
		throw i;
	}
	catch (int i) {
		std::cout << "Out of range in InsertAt: " << i << std::endl;
	}
}

template <class T>
void ArrayVector<T>::PopBack()
{
	items->Resize(GetLength() - 1);
}

template <class T>
void ArrayVector<T>::Clear()
{
	if (!items) return;
	items->Clear();
	items = nullptr;
}

template <class T>
ArrayVector<T>* ArrayVector<T>::Concat(ArrayVector<T>* arrVec) {
	ArrayVector<T>* newVec = new ArrayVector<T>;
	for (int i = 0; i < this->items->GetSize(); i++) {
		newVec->Append(this->Get(i));
	}
	for (int i = 0; i < arrVec->GetLength(); i++) {
		newVec->Append(arrVec->Get(i));
	}
	return newVec;
}

template <class T>
void ArrayVector<T>::Sum(ArrayVector<T>* vec) {
	if (vec->GetLength() != this->GetLength()) {
		std::cout << "different sizes in Sum\n";
		return;
	}
	for (int i = 0; i < this->GetLength(); i++) {
		this->items->Set(vec->Get(i) + this->Get(i), i);
	}
}

template <class T>
void ArrayVector<T>::MultOnScal(int k) {
	for (int i = 0; i < this->GetLength(); i++) {
		items->Set(this->Get(i) * k, i);
	}
}

template <class T>
T ArrayVector<T>::Norm() {
	T norm = 0;
	for (int i = 0; i < this->GetLength(); i++) {
		norm += this->Get(i) * this->Get(i);
	}
	return sqrt(norm);
}

template <class T> 
T ArrayVector<T>::ScalMult(ArrayVector<T>* vec) {
	if (this->GetLength() != vec->GetLength()) {
		std::cout << "different sizes if ScalMult\n";
		return 0;
	}
	T scal = 0;
	for (int i = 0; i < this->GetLength(); i++) {
		scal += this->Get(i) * vec->Get(i);
	}
	return scal;
}

template <class T>
void ArrayVector<T>::Output() {
	if (!items) return;
	for (int i = 0; i < this->GetLength(); i++) {
		std::cout << this->Get(i) << " ";
	}
	std::cout << std::endl;
}

template <class T>
void ArrayVector<T>::InsertSort(bool direct, int start, int end, bool (*cmp)(T el1, T el2))
{
	if (!items) return;
	if (this->GetLength() < 2) return;
	for (int i = 1; i < this->GetLength(); i++)
	{
		int j = i;
		while (!(cmp(Get(j-1) , Get(j))^direct) && j > 0)
		{
			T swap = Get(j - 1);
			items->Set(Get(j), j - 1);
			items->Set(swap, j);
			j--;
		}
	}
	return;
}

template <class T>
void ArrayVector<T>::FastSort(bool direct, int start, int end, bool (*cmp)(T el1, T el2))
{
	if (!items) return;
	if (start == end) return;
	int l = start;
	int r = end;
	int ind = (start + end) / 2;
	T comp = this->Get(ind);
	 
	while (l <= r)
	{
		
		while  (!( cmp(comp, this->Get(l)) ^ direct ))
		{
			if ( (!direct) && (l == ind)) break;
			l++;
		}
		
		while  (!( cmp(this->Get(r) , comp) ^ direct)) 
		{
			if ( (!direct) && (r == ind)) break;
			r--;
		}
		
		if  (l <= r)  
		{
			T save = this->Get(l);
			items->Set(this->Get(r), l);
			items->Set(save, r);
			l++;
			r--;
		}
		
		
	}
	
	if (l < end) this->FastSort(direct, l, end, cmp);
	
	if (r > start) this->FastSort(direct, start, r, cmp);
	return;
}

template <class T>
void ArrayVector<T>::ShellSort(bool direct, int start, int end, bool (*cmp)(T el1, T el2)) {
	if (!items) return;
	int size = end - start + 1;
	int sr = size / 2;
	while (sr > 0)
	{
		for (int i = start; i < size - sr; i++)
		{
			int j = i;
			while ((j >= start) && !( cmp(this->Get(j) , this->Get(j + sr)) ^ direct) )
			{
				T swap = this->Get(j);
				items->Set(this->Get(j + sr), j);
				items->Set(swap, j + sr);
				j--;
			}
		}
		sr = sr / 2;
	}
}

template <class T>
void ArrayVector<T>::Merge(bool direct, int first, int last, bool (*cmp)(T el1, T el2))
{
	int middle, start;
	T* mas = new T[this->GetLength()];
	middle = (first + last) / 2; 
	start = first; 
	int final = middle + 1;
	int ind = first;
	
	while ((start <= middle) && (final <= last))
	{
		if (!( cmp(this->Get(final), this->Get(start)) ^ direct))
		{
			mas[ind] = this->Get(start);
			ind++;
			start++;
		}
		else
		{
			mas[ind] = this->Get(final);
			ind++;
			final++;
		}
	}
	while (start <= middle)
	{
		mas[ind] = this->Get(start);
		ind++;
		start++;
	}
	while (final <= last)
	{
		mas[ind] = this->Get(final);
		ind++;
		final++;
	}
	for (int j = first; j <= last; j++)
	{
		items->Set(mas[j], j);
	}
	
	delete[] mas;
	return;
}



template <class T>
void ArrayVector<T>::MergeSort(bool direct, int first, int last, bool (*cmp)(T el1, T el2))
{
	
	if (!items) return;
	if (first < last )
	{
		
		MergeSort(direct, first, (first + last) / 2, cmp); 
		MergeSort(direct, (first + last) / 2 + 1, last, cmp); 
		Merge(direct, first, last, cmp); 
		
	}
	return;
}


template <class T>
void ArrayVector<T>::SiftDown(bool direct, int ind, int length, bool (*cmp)(T el1, T el2))
{
	while ((2 * ind + 1) < length)
	{
		int left = 2 * ind + 1;
		int right = 2 * ind + 2;
		int j = left;
		if ((right < length) && !(cmp(Get(right), Get(left)) ^ direct))
			j = right;
		if (!(cmp(Get(ind), Get(j)) ^ direct))
			return;
		else
		{
			T swap = Get(ind);
			items->Set(Get(j), ind);
			items->Set(swap, j);
			ind = j;
		}
	}
	return;
}


template <class T>
void ArrayVector<T>::HeapSort(bool direct, int first, int last, bool (*cmp)(T el1, T el2))
{
	int length = last - first + 1;
	for (int i = length / 2 - 1; i >= first; i--)
	{
		SiftDown(direct,i,length,cmp);
	}
	for (int i = last; i >= first; i--)
	{
		T swap = Get(first);
		items->Set(Get(i), first);
		items->Set(swap, i);
		SiftDown(direct,first,i,cmp);
	}
	return;
}

//list-----------------------------

template <class T>
ListVector<T>::ListVector(T* item, int n) {
	items = new LinkedList<T>(item, n);
}

template <class T>
ListVector<T>::ListVector() {
	items = new LinkedList<T>;
}

template <class T>
ListVector<T>::ListVector(const ListVector<T>& listVec) {
	items = new LinkedList<T>(*(listVec.items));
}

//декомпозиция
template <class T>
T ListVector<T>::GetFirst() {
	return items->GetFirst();
}

template <class T>
T ListVector<T>::GetLast() {
	return items->GetLast();
}

template <class T>
T ListVector<T>::Get(int i) {

	return items->Get(i);
}


template <class T>
ListVector<T>* ListVector<T>::GetSubVector(int i, int j) {
	 LinkedList<T>* ptr = items->GetSubList(i, j);
	 items = ptr;
	 return this;
}

template <class T>
int ListVector<T>::GetLength() {
	return items->GetLength();
}


//операции
template <class T>
void ListVector<T>::Append(T item) {
	items->Append(item);
}

template <class T>
void ListVector<T>::Prepend(T item) {
	items->Prepend(item);
}

template <class T>
void ListVector<T>::InsertAt(T item, int i) {
	items->InsertAt(item, i);
}

template <class T>
ListVector<T>* ListVector<T>::Concat(ListVector<T>* arrVec) {
	LinkedList<T> ptr = items->Concat(arrVec->items);
	*items = ptr;
	return this;
}






template <class T>
void ListVector<T>::Clear()
{
	if (!items) return;
	items->Clear();
	items = nullptr;
}
//доп операции

template <class T>
void ListVector<T>::Sum(ListVector<T>* vec) {
	if (this->GetLength() != vec->GetLength()) {
		std::cout << "different sizez in sum\n";
		return;
	}
	for (int i = 0; i < this->GetLength(); i++) {
		this->items->Set(this->Get(i) + vec->Get(i), i);
	}
}

template <class T>
void ListVector<T>::MultOnScal(int k) {
	for (int i = 0; i < this->GetLength(); i++) {
		this->items->Set(this->Get(i) * k, i);
	}
}

template <class T>
T ListVector<T>::Norm() {
	T norm = 0;
	for (int i = 0; i < this->GetLength(); i++) {
		norm += this->Get(i) * this->Get(i);
	}
	return sqrt(norm);
}

template <class T>
T ListVector<T>::ScalMult(ListVector<T>* vec) {
	if (this->GetLength() != vec->GetLength()) {
		std::cout << "Differen Sizes in ScalMult\n";
		return 0;
	}
	T scal = 0;
	for (int i = 0; i < this->GetLength(); i++) {
		scal += this->Get(i) * vec->Get(i);
	}
	return scal;
}

template <class T>
void ListVector<T>::Output() {
	if (!items) return;
	items->Output(items);
	/*
	for (int i = 0; i < this->GetLength(); i++) {
		std::cout << this->Get(i) << " ";
	}
	std::cout << std::endl;
	*/
	return;
}

template <class T>
void ListVector<T>::InsertSort(bool direct, int start, int end, bool (*cmp)(T el1, T el2))
{
	if (!items) return;
	if (this->GetLength() < 2) return;
	Node<T>* ptr = items->GetNode(1);
	Node<T>* curptr = nullptr;
	while (ptr != nullptr)
	{
		curptr = ptr;
		while ( (curptr != items->GetNode(0)) && !(cmp(curptr->prev->data,curptr->data) ^ direct ) )
		{
			T swap = curptr->prev->data;
			curptr->prev->data = curptr->data;
			curptr->data = swap;
			curptr = curptr->prev;
		}
		ptr = ptr->next;
	}
	return;
}

template <class T>
void ListVector<T>::FastSort(bool direct, int start, int end, bool (*cmp)(T el1, T el2))
{
	if (!items) return;
	if (start == end) return;
	int l = start;
	int r = end;
	int ind = (start + end) / 2;
	T comp = this->Get(ind);
	Node<T>* left = items->GetNode(l);
	Node<T>* right = items->GetNode(r);
	while (l <= r)
	{

		while ( !( cmp(comp, left->data) ^ direct))
		{
			if ((!direct) && (l == ind)) break;
			left = left->next;
			l++;
			if (left == nullptr) break;
		}

		while ( !( cmp(right->data , comp) ^ direct))
		{
			if ((!direct) && (r == ind)) break;
			right = right->prev;	
			r--;
			if (right == nullptr) break;
		}

		if ( (l <= r) && (left != nullptr) && (right != nullptr) )
		{
			T save = left->data;
			left->data = right->data;
			right->data = save;
			left = left->next;
			right = right->prev;
			l++;
			r--;

		}

	}

	if (l < end) this->FastSort(direct, l, end, cmp);

	if (r > start) this->FastSort(direct, start, r, cmp);
	return;
}

template <class T>
void ListVector<T>::ShellSort(bool direct, int start, int end, bool (*cmp)(T el1, T el2)) {
	if (!items) return;
	int size = end - start + 1;
	int sr = size / 2;
	while (sr > 0)
	{
		Node<T>* ptrj = items->GetNode(start);
		Node<T>* ptrjsr = items->GetNode(start + sr);
		Node<T>* savej = ptrj;
		Node<T>* savejsr = ptrjsr;
		for (int i = start; i < size - sr; i++)
		{
			int j = i;
			ptrj = savej;
			ptrjsr = savejsr;
			while ((j >= start) && !(cmp(ptrj->data , ptrjsr->data) ^ direct))
			{
				T swap = ptrj->data;
				items->Set(ptrjsr->data, j);
				items->Set(swap, j + sr);
				j--;
				ptrj = ptrj->prev;
				ptrjsr = ptrjsr->prev;
			}
			if (i < size - sr  - 1) savej = savej->next;
			if (i < size - sr  - 1) savejsr = savejsr->next;
		}
		sr = sr / 2;
	}
}

template <class T>
void ListVector<T>::Merge(bool direct, int first, int last, bool (*cmp)(T el1, T el2))
{
	
	int middle, start, final, j = first;
	T* mas = new T[GetLength()];
	middle = (first + last) / 2;
	start = first;
	final = middle + 1;
	Node<T>* strt = items->GetNode(start);
	Node<T>* fnl = items->GetNode(final);
	while ((start <= middle) && (final <= last))
	{
		if (!(cmp(fnl->data ,strt->data ) ^ direct))
		{
			mas[j] = strt->data;
			j++;
			start++;
			if (strt->next) strt = strt->next;
		}
		else
		{
			mas[j] = fnl->data;
			j++;
			final++;
			if (fnl->next) fnl = fnl->next;
		}
	}
	while (start <= middle)
	{
		if (strt) mas[j] = strt->data;
		j++;
		start++;
		if (strt->next) strt = strt->next;
	}
	while (final <= last)
	{
		if (fnl) mas[j] = fnl->data;
		j++;
		final++;
		if (fnl->next) fnl = fnl->next;
	}
	items->Input(mas, first, last);
	delete[]mas;
	return;
	
}

template <class T>
void ListVector<T>::MergeSort(bool direct, int first, int last, bool (*cmp)(T el1, T el2))
{
	if (!items) return;
	if (first < last)
	{
		MergeSort(direct, first, (first + last) / 2, cmp); 
		MergeSort(direct, (first + last) / 2 + 1, last, cmp); 
		Merge(direct, first, last, cmp); 
	}
}

//stek array

template <class T>
ArrayStek<T>::ArrayStek(T* item, int n) {
	items = new DynamicArray<T>(item, n);
}

template <class T>
ArrayStek<T>::ArrayStek() {
	items = new DynamicArray<T>(0);
}

template <class T>
ArrayStek<T>::ArrayStek(const ArrayVector<T>& arrVec) {
	items = new DynamicArray<T>(*(arrVec.items));
}

template <class T>
T ArrayStek<T>::GetLast() {
	return items->Get(items->GetSize() - 1);
}

template <class T>
void ArrayStek<T>::Append(T item) {
	items->Resize(items->GetSize() + 1);
	items->Set(item, items->GetSize() - 1);
}

template <class T>
int ArrayStek<T>::GetLength() {
	return items->GetSize();
}

template <class T>
void ArrayStek<T>::Output() {
	for (int i = 0; i < this->GetLength(); i++) {
		std::cout << this->Get(i) << " ";
	}
	std::cout << std::endl;
}

template <class T>
void ArrayStek<T>::Pop()
{
	items->Resize(items->GetSize() - 1);
}

template <class T>
T ArrayStek<T>::Get(int i) {
	return items->Get(i);
}

//stek list

template <class T>
ListStek<T>::ListStek(T* item, int n) {
	items = new LinkedList<T>(item, n);
}

template <class T>
ListStek<T>::ListStek() {
	items = new LinkedList<T>;
}

template <class T>
ListStek<T>::ListStek(const ListVector<T>& listVec) {
	items = new LinkedList<T>(*(listVec.items));
}

template <class T>
T ListStek<T>::GetLast() {
	return items->GetLast();
}

template <class T>
void ListStek<T>::Append(T item) {
	items->Append(item);
}

template <class T>
int ListStek<T>::GetLength() {
	return items->GetLength();
}

template <class T>
void ListStek<T>::Output() {
	for (int i = 0; i < this->GetLength(); i++) {
		std::cout << this->Get(i) << " ";
	}
	std::cout << std::endl;
}

template <class T>
void ListStek<T>::Pop()
{
	LinkedList<T>* ptr = new LinkedList<T>;
	for (int i = 0; i < items->GetLength() - 1; i++)
	{
		ptr->Append(items->Get(i));
	}
	delete[] items;
	items = ptr;
	return;
}

template <class T>
T ListStek<T>::Get(int i) {
	return items->Get(i);
}




