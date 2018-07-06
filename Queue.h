#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

template <typename T> class Queue;

template <typename T>
class Queue {
public:
	Queue(int queueCapacity = 10);
	bool IsEmpty()const { return front == rear; }
	T& Front()const {
		try {
			if (IsEmpty())
				throw "Queue is empty. No front element";
			return queue[(front + 1) % capacity];
		}
		catch (char *e) {
			cout << e << endl;
		}
	}
	T& Rear()const {
		try {
			if (IsEmpty())
				throw "Queue is empty. No rear element";
			return queue[rear];
		}
	}
	void Push(const T& item);
	void Pop();
private:
	T *queue;
	int front, rear, capacity;
};

template <typename T>
Queue<T>::Queue(int queueCapacity) :
	capacity(queueCapacity) {
	try {
		if (capacity < 1)
			throw "Queue capacity must be >0";
		queue = new T[capacity];
		front = rear = 0;
	}
	catch (char *e) {
		cout << e << endl;
	}
}

template <typename T>
void Queue<T>::Push(const T& x) {
	if ((rear + 1) % capacity == front) {
		T *newQueue = new T[2 * capacity];
		int start = (front + 1) % capacity;
		if (start < 2)
			copy(queue + start, queue + start + capacity - 1, stdext::checked_array_iterator<T *>(newQueue, capacity - 1));
		else {
			copy(queue + start, queue + capacity, stdext::checked_array_iterator<T *>(newQueue, capacity - start));
			copy(queue, queue + rear + 1, stdext::checked_array_iterator<T *>(newQueue + capacity - start, rear + 1));
		}

		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}
	rear = (rear + 1) % capacity;
	queue[rear] = x;
}

template <typename T>
void Queue<T>::Pop() {
	try {
		if (IsEmpty())
			throw "Queue is empty. Cannot delete.";
		front = (front + 1) % capacity;
		queue[front].~T();
	}
	catch (char* e) {
		cout << e << endl;
	}
}