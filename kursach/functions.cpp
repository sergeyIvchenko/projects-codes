#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "functions.hpp"
using namespace std;

Data::Data()
{
        name = rand()%25 + 65;
        number = rand()%100 + 1;
}

bool Data::operator<(Data aData) const
{
        if(number != aData.number)
        {
            return number<aData.number;
        }
        if(name != aData.name)
        {
            return (int)name<(int)aData.name;
        }
        else
        {
            return false;
        }
}

bool Data::operator==(Data aData) const
{
        if(number == aData.number && name == aData.name)
        {
            return true;
        }
        else
        {
            return false;
        }
}

Node::Node()
{
        nextNode = NULL;
        prevNode = NULL;
}

LinkedList::LinkedList()
{
        head = NULL;
        tail = NULL;
}

LinkedList& LinkedList::operator=(LinkedList const& aList)
{
        while(head != tail)
        {
            Node* tmp = head;
            head = head->nextNode;
            head->prevNode = NULL;
            delete tmp;
        }
        head = NULL;
        tail = NULL;
        Node* currNode = aList.head;
        while(currNode!=NULL)
        {
            lpush_back(currNode->newData);
            currNode = currNode->nextNode;
        }
        return *this;
}

LinkedList LinkedList::operator+(LinkedList const& aList)
{
        LinkedList newList;
        Node* currNode = head;
        while(currNode!=NULL)
        {
            newList.lpush_back(currNode->newData);
            currNode = currNode->nextNode;
        }
        currNode = aList.head;
        while(currNode!=NULL)
        {
            newList.lpush_back(currNode->newData);
            currNode = currNode->nextNode;
        }
        return newList;
}

void LinkedList::lpush_back(Data newData)
{
        Node* newNode = new Node();
        newNode->newData = newData;
        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->nextNode = newNode;
            newNode->prevNode = tail;
            tail = newNode;
        }
}

int LinkedList::lsize()
{
        int counter = 0;
        Node* currNode = head;
        while(currNode != NULL)
        {
            currNode = currNode->nextNode;
            counter++;
        }
        return counter;
}

LinkedList& LinkedList::lconcatenate(LinkedList const& aList)
{
        LinkedList newList;
        Node* currNode = head;
        while(currNode!=NULL)
        {
            newList.lpush_back(currNode->newData);
            currNode = currNode->nextNode;
        }
        currNode = aList.head;
        while(currNode!=NULL)
        {
            newList.lpush_back(currNode->newData);
            currNode = currNode->nextNode;
        }
        return newList;
}

void LinkedList::lsort()
{
        if(head == NULL)
        {
            return;
        };
        Node* followNode = head->nextNode;
        while(followNode!=NULL)
        {
            Node* earlyNode = followNode->prevNode;
            Data tempData = followNode->newData;
            Node* tempNode = followNode;
            while(earlyNode!=NULL)
            {
                if(tempData < earlyNode->newData)
                {
                    tempNode->newData = earlyNode->newData;
                    tempNode = tempNode->prevNode;
                }
                earlyNode = earlyNode->prevNode;
            }
            tempNode->newData = tempData;
            followNode = followNode->nextNode;
        }
}

LinkedList LinkedList::lfindInRange2(Data lowerbound, Data upperbound)
{
        lsort();
        Node* currNode = head;
        LinkedList newList;
        while(currNode!=NULL && currNode->newData < lowerbound)
        {
            currNode = currNode->nextNode;
        }
        if(currNode == tail->nextNode)
        {
            return newList;
        }
        Node* tmpNode = tail;
        while(tmpNode!=NULL && upperbound < tmpNode->newData)
        {
            tmpNode = tmpNode->prevNode;
        }
        if(currNode->prevNode != NULL)
        {
            currNode->prevNode->nextNode = tmpNode->nextNode;
        }
        else
        {
            head = tmpNode->nextNode;
        }
        if(tmpNode->nextNode != NULL)
        {
           tmpNode->nextNode->prevNode = currNode->prevNode;
        }
        else
        {
            tail = currNode->prevNode;
        }
        while(currNode!=tmpNode->nextNode)
        {
            newList.lpush_back(currNode->newData);
            delete currNode;
            currNode = currNode->nextNode;
        }
}

LinkedList LinkedList::lfindInRange(Data lowerbound, Data upperbound)
{
        LinkedList tempList;
        Node* currNode = head;
        while(currNode!=tail->nextNode)
        {
            if((lowerbound < currNode->newData && currNode->newData < upperbound) || lowerbound==currNode->newData || upperbound==currNode->newData)
            {
                tempList.lpush_back(currNode->newData);
                if(currNode->prevNode!=NULL)
                {
                   currNode->prevNode->nextNode = currNode->nextNode;
                }
                else
                {
                    head = head->nextNode;
                }
                if(currNode->nextNode!=NULL)
                {
                    currNode->nextNode->prevNode = currNode->prevNode;
                }
                else
                {
                    tail = tail->prevNode;
                }
                Node* tempNode = currNode;
                currNode = currNode->nextNode;
                delete tempNode;
            }
            else currNode = currNode->nextNode;
        }
        return tempList;
}

void LinkedList::lprint()
{
        Node* currNode = head;
        while(currNode != NULL)
        {
            cout << currNode->newData.name <<
             " " << currNode->newData.number << endl;
             currNode = currNode->nextNode;
        }
}

LinkedList::~LinkedList()
{
        Node* currNode = head;
        while(currNode!=NULL)
        {
            Node* tmpNode = currNode;
            currNode = currNode->nextNode;
            delete tmpNode;
        }
}
