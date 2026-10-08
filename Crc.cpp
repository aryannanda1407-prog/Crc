#include <iostream>
#include <string>
using namespace std;

bool isBinary(const string &s)
{
    for (char c : s)
        if (c != '0' && c != '1')
            return false;
    return !s.empty();
}

string divideCRC(const string &data, const string &gen)
{
    size_t n = gen.length();
    string temp = data.substr(0, n);

    for (size_t i = n; i <= data.length(); i++)
    {
        char lead = temp[0];
        for (size_t j = 0; j < n; j++)
            if (lead == '1')
                temp[j] = (temp[j] == gen[j]) ? '0' : '1';
        temp = temp.substr(1);
        if (i < data.length())
            temp += data[i];
    }
    return temp;
}

bool validInput(const string &a, const string &g)
{
    if (!isBinary(a) || !isBinary(g) || g.length() < 2 || g[0] != '1' || a.length() < g.length())
    {
        cout << "Invalid input! Use only 0/1; generator must start with 1 and not exceed data length.\n";
        return false;
    }
    return true;
}

void generate()
{
    string data, gen;
    cout << "\nEnter data: ";
    cin >> data;
    cout << "Enter generator: ";
    cin >> gen;
    if (!validInput(data, gen))
        return;
    string crc = divideCRC(data + string(gen.length() - 1, '0'), gen);
    cout << "\nOriginal Data    : " << data;
    cout << "\nGenerator        : " << gen;
    cout << "\nCRC Remainder    : " << crc;
    cout << "\nTransmitted Data : " << data + crc << endl;
}

void verify()
{
    string received, gen;
    cout << "\nEnter received data: ";
    cin >> received;
    cout << "Enter generator: ";
    cin >> gen;
    if (!validInput(received, gen))
        return;
    string rem = divideCRC(received, gen);
    cout << "\nReceived Data : " << received;
    cout << "\nRemainder     : " << rem << endl;
    if (rem.find('1') != string::npos)
        cout << "Result: ERROR DETECTED!\n";
    else
        cout << "Result: NO ERROR DETECTED.\n";
}

void information()
{
    cout << "\nCRC = Cyclic Redundancy Check, an error detection technique.\n";
    cout << "It uses modulo-2 division (XOR) and is used in computer networks.\n";
}

int main()
{
    int choice = 0;ṇ
    cout << "===== CRC CALCULATOR - C++ =====\n";
    do
    {
        cout << "\n1. Generate CRC\n2. Verify Received Data\n3. Project Information\n4. Exit\nEnter choice: ";
        if (!(cin >> choice))
            return 0;
        if (choice == 1)
            generate();
        else if (choice == 2)
            verify();
        else if (choice == 3)
            information();
        else if (choice == 4)
            cout << "\nProgram ended.\n";
        else
            cout << "\nInvalid choice!\n";
    } while (choice != 4);
    return 0;
}