/*************************************
*Modified by Gizem Gezici
*Date: 05.03.2012
*Modified by Gizem Gezici on 13.03.2012 (Bug fix on addToEnd member function)
*************************************/

#include <iostream>
#include "linkedList.h"

using namespace std;

linkedlist::linkedlist()
{
	head=NULL;
}

void linkedlist::printList()
{	
	node * ptr = head;
	//List is empty
	if(head == NULL)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		while(ptr != NULL)
		{
			cout << ptr->data << endl;
			ptr = ptr->next;
		}
	}
}

void linkedlist::addToEnd(string n)
{
	node *ptr = head;
	node *temp = new node(n, NULL);
	//List is empty
	if(head == NULL)
	{
		head = temp;
	}
	else
	{
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
	}
}

void linkedlist::addToBeginning(string n)
{
	//List is empty
	if(head == NULL)
	{
		node *ptr = new node(n, NULL);
		head = ptr;
		head->next = NULL;
	}
	else
	{
		node *ptr = new node(n, head);
		head = ptr;
	}
}

/*
Delete Function could be implemented here.
*/

void linkedlist::printListInverse()
{
	if(head != NULL)
	{
		printListInverse(head);
	}
}

void linkedlist::printListInverse(node *n)
{
	if(n->next != NULL)
	{
		printListInverse(n->next);
	}
	cout << n->data << endl;
}