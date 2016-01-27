#include "stdafx.h"
#include <iostream>
#include <cstddef>
#include "Vector3.h"


using namespace std;
class Node
{
	friend class LinkedList;
private:
	Vector3 val; /* data, can be any data type, but use integer for easiness */
	Node *next; /* pointer to the next node */

public:
	/* Constructors with No Arguments */
	Node(void)
		: next(NULL)
	{ }

	/* Constructors with a given value */
	Node(Vector3 value)
		: val(value), next(NULL)
	{ }

	/* Constructors with a given value and a link of the next node */
	Node(Vector3 value, Node* nextNode)
		: val(value), next(nextNode)
	{}

	/* Getters */
	Vector3 getValue(void)
	{
		return val;
	}

	Node* getNext(void)
	{
		return next;
	}
};

/* definition of the linked list class */
class LinkedList
{
private:
	/* pointer of head node */
	Node *head;
	/* pointer of tail node */
	Node *tail;

public:
	/* Constructors with No Arguments */
	inline LinkedList(void);
	/* Constructors with a given value of a list node */
	inline LinkedList(Vector3 val);
	/* Destructor */
	inline ~LinkedList(void);

	/* Traversing the list and printing the value of each node */
	void traverse_and_print();


};

LinkedList::LinkedList()
{
	/* Initialize the head and tail node */
	head = tail = NULL;
}

LinkedList::LinkedList(Vector3 val)
{
	/* Create a new node, acting as both the head and tail node */
	head = new Node(val);
	tail = head;
}

LinkedList::~LinkedList()
{
	/*
	* Leave it empty temporarily.
	* It will be described in detail in the example "How to delete a linkedlist".
	*/
}

/*void LinkedList::traverse_and_print()
{
	Node *p = head;

	// The list is empty? 
	if (head == NULL) {
		cout << "The list is empty" << endl;
		return;
	}

	cout << "LinkedList: ";
	// A basic way of traversing a linked list 
	while (p != NULL) { /* while there are some more nodes left */
						/* output the value */
		//std::cout << p->val;
		/* The pointer moves along to the next one 
		p = p->next;
	}
	cout << endl;
}*/