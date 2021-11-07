#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

/*
    подсчет среднее арефметического значения
*/

void clearFile(string pathFile)
{
    ofstream clearFile;
    clearFile.open(pathFile, ios_base::trunc);
    clearFile.close();
}

int main()
{
    setlocale(LC_ALL, "rus");

    string pathFile = "../shared_file/useQuery.txt";

    // очистка файла
    clearFile(pathFile);

    //файл с ответом от сервера
    string outputPathFile = "../shared_file/serverRespanse.txt";
    ifstream result(outputPathFile);
    
    cout << "подсчет среднее арефметическог значения \n\n";
    cout << "1) ввод значений\n";
    cout << "2) выход\n > ";

    int arg;
    cin >> arg;

    while (arg == 1)
    {
        ofstream query;
        uint numElement;
        cout << "ввведите количество эдиментов\n > ";

        cin >> numElement;
        int arrElemrnt[numElement];

        cout << "Введите значение через ENTER" << endl;
        for (int i = 0; i < numElement; i++)
            cin >> arrElemrnt[i];

        //запись в файл
        query.open(pathFile, ios_base::app);

        query << numElement;
        query << "\n";

        for (int i = 0; i < numElement; i++)
        {
            query << arrElemrnt[i];
            query << "\n";
        }

        query.close();

        sleep(1);

        string resultNam;
        result >> resultNam;
        cout << "ответ от сервера - " << resultNam << endl;

        cout << "1) продолжить\n";
        cout << "2) выход\n > ";
        cin >> arg;
    }
    result.close();
    return 0;
}