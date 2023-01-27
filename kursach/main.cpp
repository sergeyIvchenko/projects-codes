#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "functions.hpp"

using namespace std;



void menu()
{
    cout << "����:" << endl;
    cout << "������� ������, ���������� ������� �����, �� ������ Enter" << endl;
    cout << "1 �������� ������\n2 ������� ������(��)\n3 ����� ������(��)\n4 ������� ������������ ���� ������\n";
    cout << "5 ��������� ��������, �� ����������� � ������� �����, �� ������� �� ������\n"
    " ���������� �������� � �����\n0 �����" << endl;
}


void list_create(LinkedList  &newlist)
{
    int secChoose;
    cout << "������� ������:" << endl;
    cout << "�������� �����������:\n1 ������ �� 10 ��-��\n2 ������ �� 100 ��-��" << endl << endl;
    cout << "3 �������� ���������" << endl;
    cin >> secChoose;
    while(secChoose < 0 || secChoose == 0 || secChoose > 3)
    {
        cout << "������� ����������� ��������, ������ �� ���: ";
        cin >> secChoose;
    }
    if(secChoose == 1)
    {
        Data DataArr[10];
        for(int i=0; i<10; i++)
        {
            newlist.lpush_back(DataArr[i]);
        }
    }
    else if(secChoose == 2)
    {
        Data DataArr2[100];
        for(int i=0; i<100; i++)
        {
            newlist.lpush_back(DataArr2[i]);
        }
    }
    else if(secChoose == 3)
    {
        cout << "������ ������� ��������: ";
        int arrSize;
        cin >> arrSize;
        int create_choose;
        cout << "��������� ���������?\n1 ���\n���� ����� ͳ" << endl;
        cin >> create_choose;
        if(create_choose ==1)
        {
            Data tempData;
            char name;
            int number;
            cout << "������ ��������, �������� ��������� ������ �����, ���� ����� �� 1 �� 100:" << endl;
            for(int i=0; i<arrSize; i++)
            {
                cin >> name >> number;
                tempData.name  = name;
                tempData.number = number;
                newlist.lpush_back(tempData);
            }
        }
        else
        {
            Data DataArr[arrSize];
            for(int i=0; i<arrSize; i++)
            {
                newlist.lpush_back(DataArr[i]);
            }
        }
    }
}


int main()
{
    LinkedList newlist;
    LinkedList secondlist;
    LinkedList conlist;
    int choose;
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    cin >> choose;
    while(choose!=0)
    {
        if(choose < 0)
        {
            cout << "������� ����������� ��������, ������ �� ���: ";
            cin >> choose;
        }
        else
        {
            switch(choose)
            {
                case 1:
                    {
                        list_create(newlist);
                        break;
                    }
                case 2:
                    {
                        if(newlist.lsize()!=0)
                        {
                            cout << "������ ������, ������� � ����� 1:" << endl;
                            newlist.lprint();
                        }
                        if(secondlist.lsize()!=0)
                        {
                            cout << "������ ������, ��������� � ����� 4 ��� ������������:" << endl;
                            secondlist.lprint();
                        }
                        else if(newlist.lsize() == 0 && secondlist.lsize()==0)
                        {
                            cout << "������ �� ��������" << endl;
                        }
                        break;
                    }
                case 3:
                    {
                        cout << "����� ������� ������: " << newlist.lsize() << endl;
                        cout << "����� �������(��� 4 ������) ������: " << secondlist.lsize() << endl;
                        cout << "����� ������� ������(��������� ������������): " << conlist.lsize() << endl;
                        break;
                    }
                case 4:
                    {
                        cout << "������� ������ ������, ��� ������� ������������:" << endl;
                        list_create(secondlist);
                        if(newlist.lsize() == 0 && secondlist.lsize() == 0)
                        {
                            cout << "������ �� ��������" << endl;
                            break;
                        }
                        conlist  = newlist + secondlist;
                        int print_choose;
                        cout << "��������� ��������������� ������?\n1 ���\n���� ����� ͳ" << endl;
                        cin >> print_choose;
                        if(print_choose == 1)
                        {
                            cout << "������������ ������:" << endl;
                            conlist.lprint();
                        }
                        break;
                    }
                case 5:
                    {
                        Data lowerbound, upperbound;
                        int bound_choose;
                        if(newlist.lsize() == 0 && secondlist.lsize()==0)
                        {
                            cout << "������ �� ��������" << endl;
                            break;
                        }
                        cout << "������ ��� ��� �������� ����������� ����������:\n1 ������\n���� ����� ��������" << endl;
                        cin >> bound_choose;
                        if(bound_choose == 1)
                        {
                            cout << "������ ��� ����� �� �����, �� � � ����� 1(�������� ������ ��������� �����, ���� ����� �� 1 �� 100):" << endl;
                            cin >> lowerbound.name >> lowerbound.number;
                            cin >> upperbound.name >> upperbound.number;
                        }
                        if(upperbound<lowerbound)
                        {
                            Data tmpData = upperbound;
                            upperbound = lowerbound;
                            lowerbound = tmpData;
                        }
                        LinkedList found_list;
                        cout << "������, � ����� ������ ������ ��-�� � �����:" << endl;
                        if(newlist.lsize()!=0)
                        {
                            cout << "1 ������ ������" << endl;
                        }
                        if(secondlist.lsize()!=0)
                        {
                            cout << "2 ������ ������" << endl;
                        }
                        if(conlist.lsize()!=0)
                        {
                            cout << "3 ����� ������" << endl;
                        }
                        cin >> bound_choose;
                        LinkedList tmplist;
                        cout << lowerbound.name << " " << lowerbound.number << endl;
                        cout << upperbound.name << " " << upperbound.number << endl << endl;
                        while(bound_choose <0 || bound_choose ==0 || bound_choose >3)
                        {
                            cout << "������� ����������� ��������" << endl;
                            cin >> bound_choose;
                        }
                        float time;
                        switch(bound_choose)
                        {
                            case 1:
                            {
                                tmplist = newlist;
                                clock_t start = clock();
                                found_list = newlist.lfindInRange(lowerbound, upperbound);
                                clock_t end = clock();
                                time = (end-start)/CLOCKS_PER_SEC;
                                if(found_list.lsize()!=0)
                                {
                                    cout << "������ ��-��, �� ������� � ���: " << endl;
                                    found_list.lprint();
                                }
                                break;
                            }
                            case 2:
                            {
                                tmplist = secondlist;
                                clock_t start1 = clock();
                                found_list = secondlist.lfindInRange(lowerbound, upperbound);
                                clock_t end1 = clock();
                                time = (end1-start1)/CLOCKS_PER_SEC;
                                if(found_list.lsize()!=0)
                                {
                                    cout << "������ ��-��, �� ������� � ���: " << endl;
                                    found_list.lprint();
                                }
                                break;
                            }
                            case 3:
                            {
                                tmplist = conlist;
                                clock_t start2 = clock();
                                found_list = conlist.lfindInRange(lowerbound, upperbound);
                                clock_t end2 = clock();
                                time = (end2-start2)/CLOCKS_PER_SEC;
                                if(found_list.lsize()!=0)
                                {
                                    cout << "������ ��-��, �� ������� � ���: " << endl;
                                    found_list.lprint();
                                }
                                break;
                            }
                        }
                        cout << "������� ����� ���� ��������� ������ � �����?\n1 ���\n���� ����� ͳ" << endl;
                        cin >> bound_choose;
                        if(bound_choose == 1)
                        {
                            clock_t start3 = clock();
                            found_list = tmplist.lfindInRange2(lowerbound, upperbound);
                            clock_t end3 = clock();
                            cout << "��� ���������:" << endl;
                            cout << time*100000 << endl;
                            cout << (end3-start3)*100000/CLOCKS_PER_SEC << endl;
                        }
                        break;
                    }
            }
            cout << endl;
            menu();
            cin >> choose;
        }
    }
    return 0;
}
