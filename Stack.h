#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

template <typename T> class Stack;
template <typename T> void ChangeSize1D(T*& a, const int oldSize, const int newSize);

template <typename T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;

	T& Top()const;
	void Push(const T& item);
	void Pop();
private:
	T *stack;
	int top;
	int capacity;
};

template <typename T>
Stack<T>::Stack(int stackCapacity) :
	capacity(stackCapacity) {
	try {
		if (capacity < 1)
			throw "Stack capacity must be>0";
	}
	catch (const string e) {
		cout << e.data() << endl;
	}
	stack = new T[capacity];
	top = -1;
}

template <typename T>
inline bool Stack<T>::IsEmpty()const { return top == -1; }

template <typename T>
inline T& Stack<T>::Top()const {
	try {
		if (IsEmpty())
			throw "Stack is empty";
		return stack[top];
	}
	catch (char *e) {
		cout << e << endl;
	}
}

template <typename T>
void Stack<T>::Push(const T& x) {
	if (top == capacity - 1) {
		ChangeSize1D(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template <typename T>
void Stack<T>::Pop() {
	try {
		if (IsEmpty())
			throw "Stack is empty. Cannot delete";
		stack[top--].~T();
	}
	catch (char *e) {
		cout << e << endl;
	}
}

template <typename T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
	try {
		if (newSize < 0)
			throw "New length must be >= 0";
		T* temp = new T[newSize];
		int number = min(oldSize, newSize);
		copy(a, a + number, stdext::checked_array_iterator<T *>(temp, number));
		delete[] a;
		a = temp;
	}
	catch (char *e) {
		cout << e << endl;
	}
}