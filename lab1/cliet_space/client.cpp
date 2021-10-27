#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
Транслитизация  
*/


int main()
{
    setlocale(LC_ALL, "rus");
    
    string pathFile = "../shared_file/useQuery.txt";

    // очистка файла 
    ofstream clearFile;
    clearFile.open(pathFile, ios_base::trunc); 
    clearFile.close();


        cout << "Транслитор <-> Translitor\n\n";
        cout << "1) прирейти к воду текста\n";
        cout << "2) выход\n > ";
      
        int arg;
        cin >> arg;

    while (arg == 1)
    {
    ofstream query;
    string text;
    cout << "ввведите текст (конец ввода ENTER)\n > ";

        cin.ignore();
        getline(cin, text);
        
        //запись в файл
        query.open(pathFile, ios_base::app); 
        query << "\n";
        query << text;

        query.close();
        
        cout << "1) продолжить\n";
        cout << "2) выход\n > ";
        cin  >> arg;
    }
   
    return 0;
}