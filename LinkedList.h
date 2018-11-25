//Author: Justin Cain @AffinityForFun
//11/22/2018
/*
README:
If a T value is allocated from memory it is up to the user to delete/store it before the list is destroyed.
Since this is using templates, all code that should be in a .cpp file is included here.
*/

#include <iostream>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// <summary>
// A simple doubly linked node
// </summary>
template <class T>
struct Node {
	T value; //Value
    struct Node<T>* next; //The next node in the structure.
	struct Node<T>* prev; //The previous node in the structure.
};

// <summary>
// A generic doubly linked list, with special case for char* comparison
// </summary>
template <class T>
class LinkedList {
private:
	//Pointer to the head node of this list 
	Node<T>* head = 0;
	//Intenrnal size count
	unsigned int size;
public:
	unsigned int GetSize();
	void Add(T value);
	void Remove(Node<T>* node);
	Node<T>*  Find(T value);
	bool Contains(T value);
	T* GetValueArray();
	Node<T>* Peek();
	~LinkedList();
};

// <summary>
// Returns the size of the linked list
// </summary>
template <class T>
unsigned int LinkedList<T>::GetSize() {
	return size;
}

// <summary>
// Adds a value to the list at the front
// </summary>
template <class T>
void LinkedList<T>::Add(T value) {
	Node<T>* newNode = new Node<T>(); // Create a new node
	newNode->value = value; //Set its value
	//New node will now take position at the head of the list
	//Create the links with the current head if there is one
	if (size > 0) {
		newNode->next = head;
		head->prev = newNode;
	}
	head = newNode;
	//Increase size
	size++;
}

// <summary>
// Removes a node from the list
// </summary>
template <class T>
void LinkedList<T>::Remove(Node<T>* node){
	//If the list is empty we cannot remove anything
	if (size == 0)
		return;
	
	//If the node has something following it
	if(node->next && node->prev) {
		//We are in the middle of the listWe link the two other nodes together and delete this one.
		
		//Store the previous and next
		Node<T>* prev = node->prev;
		Node<T>* next = node->next;
		
		//Link them together
		prev->next = next;
		next->prev = prev;
	}
	else if (node->next) {
		//We are at the beginning of the list (head)
		//Move our next to the head
		head = node->next;
		//Set our next's previous to null
		node->next->prev = 0;
	}
	else if (node->prev) {
		//We are at the end of the list (tail)
		//Set our prev's next to null
		node->prev->next = 0;
	}
	else {
		//Otherwise, we are the only element in this list so we remove the reference to the tail.
		head = 0;
	}
	
	//We have modified the list, now delete the node
	size--;
	delete node;
}

// <summary>
// Finds a node containing the appropriate value.
// </summary>
template <class T>
Node<T>*  LinkedList<T>::Find(T value){ 
	if (size == 0)
		return 0;
	//Track the current node we are looking at
	Node<T>* cNode = head;
	//Loop through all nodes
	for (int i = 0; i < size; i++) {
		//Check if this node has the value we are looking for (with special case of matching char*)
		if (cNode->value == value)
			return cNode;
		//Advance our node 
		cNode = cNode->next;
	}
	return 0; 
}

// <summary>
// Returns if the list contains the value
// </summary>
template <class T>
bool LinkedList<T>::Contains(T value){
	if (size == 0)
		return false;
	//Track the current node we are looking at
	Node<T>* cNode = head;
	//Loop through all nodes
	for (int i = 0; i < size; i++) {
		//Check if this node has the value we are looking for (with special case of matching char*)
		if (cNode->value == value)
			return true;
		//Advance our node 
		cNode = cNode->next;

	}
	//We have not found a node, so return false.
	return false; 
}

// <summary>
// Returns an array of all contained values. Array space is allocated, remember to delete.
// </summary>
template <class T>
T* LinkedList<T>::GetValueArray() {
	//Create an array of value pointers equal to the size of the list
	T* values = new T[size];
	//Track the current node we are looking at
	Node<T>* cNode = head;
	//Loop through all nodes
	for (int i = 0; i < size; i++) {
		//Asign value
		values[i] = cNode->value;
		//Advance our node 
		cNode = cNode->next;
	}
	
	return values;
}

// <summary>
// Returns the current head of the list
// </summary>
template <class T>
Node<T>* LinkedList<T>::Peek() {
	//If we have a head, return a pointer to it, otherwise return null pointer
	if (head)
		return head;
	else
		return 0;
}

// <summary>
// Deletes all nodes created by the linked list
// </summary>
template <class T>
LinkedList<T>::~LinkedList(){
	//Delete all of our nodes.
	while (head != 0) {
		//Store the current head
		Node<T>* cNode = head;
		//Move the head forward
		head = cNode->next;
		//Deleted the stored node
		delete cNode;
	}
}
#endif