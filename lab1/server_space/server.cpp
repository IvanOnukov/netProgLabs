#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

long int cheakSize(string inputPathFile)
{
    long int sizeInputFile;

    ifstream cheakFile(inputPathFile, ios::binary | ios::ate);
    sizeInputFile = cheakFile.tellg();
    cheakFile.close();
    return sizeInputFile;
}

double arithmeticAverg(uint sized, int mas[])
{

    long int sum = 0;
    for (int i = 0; i < sized; i++)
    {
        sum += mas[i];
    }
    return sum / sized;
}

void clearFile(string pathFile)
{
    ofstream clearFile;
    clearFile.open(pathFile, ios_base::trunc);
    clearFile.close();
}

int main()
{
    setlocale(LC_ALL, "rus");

    string inputPathFile = "../shared_file/useQuery.txt";
    string outputPathFile = "../shared_file/serverRespanse.txt";

    clearFile(outputPathFile);
    long int sizeInputFile = 0;
    ifstream userFile(inputPathFile);

    while (1)
    {
        if (sizeInputFile < cheakSize(inputPathFile))
        {

            sizeInputFile = cheakSize(inputPathFile);

            uint sized = 0;
            userFile >> sized;

            int *mas = new int[sized]();
            for (int i = 0; i < sized; i++)
            {
                userFile >> mas[i];
            }

            // cout << arithmeticAverg(sized, mas) << endl;

            if (userFile.is_open())
            {
                double result = arithmeticAverg(sized, mas);
                cout << result << endl;
                ofstream outputData(outputPathFile, ios_base::app);
                outputData << result;
                outputData << "\n";
                outputData.close();
                result = 0;
            }

            delete (mas);
        }
    }
    //userFile.close();
    return 0;
}