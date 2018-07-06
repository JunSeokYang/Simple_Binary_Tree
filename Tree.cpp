#include <iostream>
#include "Stack.h"
#include "Queue.h"

using namespace std;

template <typename T> class Tree;
template <typename T> class TreeNode;

template <typename T>
class TreeNode {
public:
	friend class Tree<T>;
	TreeNode();
private:
	TreeNode<T> *leftchild;
	TreeNode<T> *rightchild;
	T data;
};

template <typename T>
class Tree {
public:
	Tree();
	void Inorder() { Inorder(root); }
	void Preorder() { Preorder(root); }
	void Postorder() { Postorder(root); }
	void LevelOrder();
	class InorderIterator {
	public:
		InorderIterator() { currentNode = root; }
		T* Next();
	private:
		Stack<TreeNode<T>*>s;
		TreeNode<T> *currentNode;
	};
private:
	TreeNode<T> *root;
	void Inorder(TreeNode<T> *currentNode);
	void Preorder(TreeNode<T> *currentNode);
	void Postorder(TreeNode<T> *currentNode);
	void Visit(TreeNode<T> *currentNode) { cout << currentNode->data; }
};

template <typename T>
void Tree<T>::Inorder(TreeNode<T> *currentNode) {
	if (currentNode) {
		Inorder(currentNode->leftchild);
		Visit(currentNode);
		Inorder(currentNode->rightchild);
	}
}

template <typename T>
void Tree<T>::Preorder(TreeNode<T> *currentNode) {
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->leftchild);
		Preorder(currentNode->rightchild);
	}
}

template <typename T>
void Tree<T>::Postorder(TreeNode<T> *currentNode) {
	if (currentNode) {
		Postorder(currentNode->leftchild);
		Postorder(currentNode->rightchild);
		Visit(currentNode);
	}
}

template <typename T>
T* Tree<T>::InorderIterator::Next(){
	while (currentNode) {
		s.Push(currentNode);
		currentNode = currentNode->leftchild;
	}
	if (s.IsEmpty())
		return 0;
	currentNode = s.Top();
	s.Pop();
	T& temp = currentNode->data;
	currentNode = currentNode->rightchild;
	return &temp;
}

template <typename T>
void Tree<T>::LevelOrder() {
	Queue<TreeNode<T>*> q;
	TreeNode<T>* currentNode = root;
	while (currentNode) {
		Visit(currentNode);
		if (currentNode->leftchild)
			q.Push(currentNode->leftchild);
		if (currentNode->rightchild)
			q.Push(currentNode->rightchild);
		if (q.IsEmpty())
			return;
		currentNode = q.Front();
		q.Pop();
	}
}

void main(void) {
}