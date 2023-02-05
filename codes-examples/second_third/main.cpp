
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <windows.h>
#include <fstream>
#include <thread>
using namespace std;

vector<bool> poly;
vector<bool> rest;
vector<bool> crc;
vector<bool> xorBits;
vector<bool> infoBits;
vector<bool> message;
vector<bool> buffer;

const int order = 8;                       // порядок полінома
unsigned long polynom = 0x7;         // поліном без контрольної одиниці в hex
const string init = "ff";             // початкове значення CRC
const string xorOut = init;                 // кінцеве XOR значення
const bool refIn = 1;                       // звертання кожного байту перед обробкою (інвертування кожного байта)
const bool refOut = refIn;                 // кінцевий вміст регістру звертається перед передачею на наступну стадію обрахунків (відображення CRC перед XOR)

// Функція для виводу динамічного масиву
void printVector(std::vector<bool>& vec)
{
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i];
    cout << endl;
}

// Функція для конвертування даних string -> vector<bool>
vector <bool> boolTransform(string str)
{
    vector <bool> v;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '\0') i++;
        v.push_back(str[i] == '1' ? 1 : 0);
    }
    return v;
}

// Функція для переводу поліному з hex в bin для подальшого modulo-2 division
void getPoly()
{
    string p;
    unsigned long n = polynom;
    for(int i = 0; n > 0; i++)                  // Виконуємо циклічне ділення на 2 з рештою та вставляємо у р
    {
        p += to_string(n%2);
        n = n/2;
    }
    for (unsigned long i = p.size(); i < order; i++) // додаємо 0 для узгодження порядку поліному
        p += to_string(0);
    p += to_string(1);                      // додаємо контрольний біт для 4 мінімальної кодової відстані
    unsigned long v = p.size();
    for (int i = 0; i < v / 2; i++)         // відзеркалюємо наш рядок для правильного виду поліному
        swap(p[i], p[v - i - 1]);
    poly = boolTransform(p);                // конвертуємо у vector<bool>
}

// Функція для ініціалізації RefIn
vector<bool> reverseInfoBits(vector<bool> b)
{
    bool buff;
    int count, pos, c = 7;
    for(int i = 0; i < b.size(); i = i + 8)
    {
        pos = i;
        for(count = 0; count < 4; count++)      // робимо відображення кожного байту
        {
            buff = b[pos];
            b[pos] = b[pos+c];
            b[pos+c] = buff;
            pos++;
            c = c - 2;
        }
        c = 7;
    }
    return b;
}

// Функція для ініціалізації Init
vector<bool> fillXORBits(vector<bool> b, vector<bool> info)
{
    if (init[0] == 'f' || init[0] == 'F')
        for (int i = 0; i < init.size()*4; i++)
            b.push_back(1);
    for (unsigned long i = b.size(); i < info.size(); i++)
        b.push_back(0);

    return b;
}

// XOR для двох векторів(можна було зробити глобальний оператор, але так легше)
vector<bool> countXOR(vector<bool> b, vector<bool> x, unsigned long length)
{
    int i = 0;
    while (i < length)
    {
        if (b[i] == x[i])
            b[i] = 0;
        else
            b[i] = 1;
        i++;
    }
    return b;
}

// Функція розширення вектору
vector<bool> expand(vector<bool> b, unsigned long size)
{
    int i = 0;
    while(i < size*4){
        b.push_back(0);
        i++;
    }
    return b;
}

// Функція Module-2 division для двох vector-ів
void divide(vector <bool> str, vector <bool> bgn = poly, int tmp = 0)
{
    if (str[tmp])
        for (int i = 0; i < bgn.size(); i++)
            str[tmp + i] = str[tmp + i] ^ bgn[i];
    if (tmp + bgn.size() < str.size())
        divide(str, bgn, tmp + 1);
    else
        rest = str;                         // цей залишок має конкретну кількість нулів і залишок CRC в кінці
}
//MARK: функція для повного відображення vector<bool>
vector<bool> reverseVector(vector<bool> b)
{
    unsigned long pos = b.size() - 1;
    bool temp;
    for (unsigned long i = 0; i < pos; i++)
    {
        temp = b[i];
        b[i] = b[pos];
        b[pos] = temp;
        pos = pos - 1;
    }
    return b;
}
// Основна функція для пошуку CRC коду
void findCRC(string myCode) // приймає вже конкретно bin формат полінома
{
    // очищуємо динамічні масиви аби минулі значення не заважали
    rest.clear();
    crc.clear();
    xorBits.clear();
    infoBits.clear();

    //MARK: refIN
    infoBits = boolTransform(myCode);
    message = boolTransform(myCode);
    if (refIn)
        infoBits = reverseInfoBits(infoBits);

    //MARK: init
    // повинні порахувати значення при операції XOR в залежності від параметра Init
    if (init.size() && init[0] != '0')
    {
        xorBits = fillXORBits(xorBits, infoBits);
        infoBits = countXOR(infoBits, xorBits, infoBits.size());
    }

    //MARK: Modulo-2 Division
    infoBits = expand(infoBits, init.size());
    message = expand(message, init.size());
    divide(infoBits);

    // заноcимо залишок в CRC
    for (unsigned long i = myCode.size(); i < rest.size(); i++)
        crc.push_back(rest[i]);

    //MARK: refOUT
    if (refOut)
        crc = reverseVector(crc);

    //MARK: xorOUT
    // 1 = 0, 0 = 1 для CRC
    if(xorOut.size())
        crc.flip();
}

int main()
{
    // рядок input, в яку у нас заносяться дані
    // рядок code, який ми конвертуємо в bin
    SetConsoleOutputCP(CP_UTF8);
    string input, code;
    int way;
    cout << "Уведіть опцію: " << endl;
    cout << "1 - Зчитання з консолі" << endl;
    cout << "2 - Зчитання з файлу" << endl;
    cin >> way;
    cin.ignore();
    if(way == 1){
        cout << "Уведіть повідомлення:" << endl;
        getline(cin, input);
    }else if(way == 2){
        cout << "Зчитую повідомлення з файлу..."<< endl;
        ifstream file("text.txt");
        while(getline(file,input));
        this_thread::sleep_for(chrono::milliseconds(20));
        cout << "Зчитування завершено"<< endl;
        file.close();
    }else{
        cout << "Уведено неправильне число"; return 0;
    }

    // перевеcти cтроку в бинарный вид
    for (size_t i = 0; i < input.size(); ++i)
    {
        bitset<8> b(input.c_str()[i]);
        code += b.to_string();
    }

    // підрахунок поліному в vector<bool>
    getPoly();

    // шукаємо CRC код
    findCRC(code);

    // доповнення нашого повідомлення CRC-кодами в кінець
    int j = 0;
    for (unsigned long i = code.size(); i < rest.size(); i++)
    {
        message[i] = crc[j];
        j++;
    }

    // меню для виводу виконуваних параметрів
    cout << endl << "Параметри CRC-" << order << " коду:" << endl;
    cout << "   Представлення поліному:  0x" << hex << polynom << endl;
    cout << "   Init: \t  0x" <<  hex << init << endl;
    cout << "   RefIn: \t  " << refIn << endl;
    cout << "   RefOut: \t  " << refOut << endl;
    cout << "   XorOut:\t  0x" << hex << xorOut << endl << endl;
    cout << dec <<"Повідомлення:  '" << input << "' (" << input.size() << " байт)" <<  endl;
    cout << "CRC: ";
    printVector(crc);
    cout << "Закодоване повідомлення: ";
    printVector(message);

    char answer;
    cout  << endl << "Перевірити на наявність помилок? ? (1/0): ";
    cin >> answer;
    if (answer != '1')
        exit(1);

    int n = 1;
    while (n)
    {
        cout << endl;
        cout << "Закодоване повідомлення: ";
        printVector(message); // наше повідомлення без помилки
        cout << "1 - Вибрати помилки" << endl;
        cout << "2 - Знайти помилки" << endl;
        cout << "0 - Вихід" << endl;
        cin >> n ;
        cout << endl;
        switch (n) {
            case 1:{
                int bit = -1, num = 0;
                cout << "Уведіть кількість помилок: ";
                cin >> num;
                while(num != 0)
                {
                    cout << "Уведіть позицію помилки: ";
                    cin >> bit;

                    while (bit < 0 || bit > message.size() - 1)
                    {
                        cout << "кількість повинна бути в діапазоні [0," << message.size() - 1 << "]!" << endl;
                        cin >> bit;
                    }
                    message[bit] = !message[bit];
                    num--;
                }
            }
            case 2:{
                int j = 0;
                // ще раз рахуємо наше повідомлення, якщо ввели помилки
                for (unsigned long i = code.size(); i < code.size(); i++)
                {
                    crc[j] = message[i];
                    j++;
                }

                // зберігаємо значення CRC в буфер
                // якщо буде помилка, то вони будуть не рівними
                buffer = crc;

                // підраховуємо нове значення нашого рядка в bin вигляді
                string newCode;

                for (unsigned long i = 0; i < code.size(); i++)
                    newCode += to_string(message[i]);
                //пошук CRC

                findCRC(newCode);
                cout << "Перевірочний CRС: " ;
                printVector(crc);

                // перевірка на рівність двох CRC
                // також це можно зробити за допомогою XOR
                // якщо після XOR синдром = 0, помилок немає
                if (buffer == crc)
                    cout << "Помилок немає !" << endl;
                else
                    cout << "Помилка є ! " <<endl;

                // Робимо нове заповнення аби отримати нове невірне повідомлення
                j = 0;
                for (unsigned long i = code.size(); i < rest.size(); i++)
                {
                    message[i] = crc[j];
                    j++;
                }
            }
            default: cout << "Спробуйте знову..." << endl;
        }
    }
    //system("pause");
    return(0);
}
