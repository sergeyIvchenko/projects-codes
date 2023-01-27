#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>
using namespace std;

struct Data
{
    char name;
    int number;

    Data();


    bool operator<(Data aData) const;

    bool operator==(Data aData) const;
};


struct Node
{
    Data newData;
    Node* nextNode;
    Node* prevNode;
    Node();
};


struct LinkedList
{
    Node* head;
    Node* tail;
    LinkedList();


    LinkedList& operator=(LinkedList const& aList);


    LinkedList operator+(LinkedList const& aList);


    void lpush_back(Data newData);


    int lsize();


    LinkedList& lconcatenate(LinkedList const& aList);


    void lsort();


    LinkedList lfindInRange2(Data lowerbound, Data upperbound);


    LinkedList lfindInRange(Data lowerbound, Data upperbound);

    void lprint();


    ~LinkedList();
};


