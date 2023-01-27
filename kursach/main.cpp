#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "functions.hpp"

using namespace std;



void menu()
{
    cout << "Меню:" << endl;
    cout << "Виберіть варіант, натиснувши потрібну цифру, та нажміть Enter" << endl;
    cout << "1 Створити список\n2 Вивести список(ки)\n3 Розмір списку(ків)\n4 Зробити конкатенацію двох списків\n";
    cout << "5 Виключити елементи, що знаходяться в заданих межах, та вивести їх список\n"
    " виключення елементів в межах\n0 Вихід" << endl;
}


void list_create(LinkedList  &newlist)
{
    int secChoose;
    cout << "Виберіть варіант:" << endl;
    cout << "Створити автоматично:\n1 Список на 10 ел-ів\n2 Список на 100 ел-ів" << endl << endl;
    cout << "3 Створити самостійно" << endl;
    cin >> secChoose;
    while(secChoose < 0 || secChoose == 0 || secChoose > 3)
    {
        cout << "Введено неправильне значення, введіть ще раз: ";
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
        cout << "Уведіть кількість елементів: ";
        int arrSize;
        cin >> arrSize;
        int create_choose;
        cout << "Заповнити самостійно?\n1 Так\nінше число Ні" << endl;
        cin >> create_choose;
        if(create_choose ==1)
        {
            Data tempData;
            char name;
            int number;
            cout << "Уведіть елементи, спочатку англійську велику букву, потім цифру від 1 до 100:" << endl;
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
            cout << "Введено неправильне значення, введіть ще раз: ";
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
                            cout << "Перший список, заданий в пункті 1:" << endl;
                            newlist.lprint();
                        }
                        if(secondlist.lsize()!=0)
                        {
                            cout << "Другий список, створений в пункті 4 для конкатенації:" << endl;
                            secondlist.lprint();
                        }
                        else if(newlist.lsize() == 0 && secondlist.lsize()==0)
                        {
                            cout << "Списків не створено" << endl;
                        }
                        break;
                    }
                case 3:
                    {
                        cout << "Розмір першого списку: " << newlist.lsize() << endl;
                        cout << "Розмір другого(для 4 пункту) списку: " << secondlist.lsize() << endl;
                        cout << "Розмір третьго списку(результат конкатенації): " << conlist.lsize() << endl;
                        break;
                    }
                case 4:
                    {
                        cout << "Створіть другий список, щоб зробити конкатенацію:" << endl;
                        list_create(secondlist);
                        if(newlist.lsize() == 0 && secondlist.lsize() == 0)
                        {
                            cout << "Списків не створено" << endl;
                            break;
                        }
                        conlist  = newlist + secondlist;
                        int print_choose;
                        cout << "Друкувати сконкатенований список?\n1 Так\nінше число Ні" << endl;
                        cin >> print_choose;
                        if(print_choose == 1)
                        {
                            cout << "Конкатенація списків:" << endl;
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
                            cout << "Списків не створено" << endl;
                            break;
                        }
                        cout << "Введіть межі або залишіть автоматично створеними:\n1 Ввести\nІнше число Залишити" << endl;
                        cin >> bound_choose;
                        if(bound_choose == 1)
                        {
                            cout << "Уведіть дані таким же чином, як і в пункті 1(спочатку велика англійська літера, потім цифра від 1 до 100):" << endl;
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
                        cout << "Уведіть, у якому списку шукати ел-ти в межах:" << endl;
                        if(newlist.lsize()!=0)
                        {
                            cout << "1 Перший список" << endl;
                        }
                        if(secondlist.lsize()!=0)
                        {
                            cout << "2 Другий список" << endl;
                        }
                        if(conlist.lsize()!=0)
                        {
                            cout << "3 Третій список" << endl;
                        }
                        cin >> bound_choose;
                        LinkedList tmplist;
                        cout << lowerbound.name << " " << lowerbound.number << endl;
                        cout << upperbound.name << " " << upperbound.number << endl << endl;
                        while(bound_choose <0 || bound_choose ==0 || bound_choose >3)
                        {
                            cout << "Введено неправильне значення" << endl;
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
                                    cout << "Список ел-тів, що входять у межі: " << endl;
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
                                    cout << "Список ел-тів, що входять у межі: " << endl;
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
                                    cout << "Список ел-тів, що входять у межі: " << endl;
                                    found_list.lprint();
                                }
                                break;
                            }
                        }
                        cout << "Зробити аналіз двох алгоритмів пошуку в межах?\n1 Так\nінша цифра Ні" << endl;
                        cin >> bound_choose;
                        if(bound_choose == 1)
                        {
                            clock_t start3 = clock();
                            found_list = tmplist.lfindInRange2(lowerbound, upperbound);
                            clock_t end3 = clock();
                            cout << "Час алгоритмів:" << endl;
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
