#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    
    string inputPathFile = "../shared_file/useQuery.txt";
    string outputPathFile = "../shared_file/serverRespanse.txt";

    map<string, string> dictionaryRuToTr = {
        {"а", "a"},
        {"б", "b"},
        {"в", "v"},  
        {"г", "g"},
        {"д", "d"},
        {"е", "e"},
        {"ё", "yo"},
        {"ж", "zh"},
        {"з", "z"},
        {"и", "i"},
        {"й", "j"},
        {"к", "k"},
        {"л", "l"},
        {"м", "m"},
        {"н", "n"},
        {"о", "o"},
        {"п", "p"},
        {"р", "r"},
        {"с", "s"},
        {"т", "t"},
        {"у", "u"},
        {"ф", "f"},
        {"х", "x"},
        {"ц", "c"},
        {"ч", "ch"},
        {"ш", "sh"},
        {"щ", "shh"},
        {"ъ", "\""},
        {"ы", "y'"},
        {"ь", "\'"},
        {"э", "eh"},
        {"ю", "ju"},
        {"я", "ja"},
        {" ", " "}
     
    };

    map<char*, string> dictionaryTrToRu = {
        {"a", "а"},
        {"b", "б"},
        {"v", "в"},  
        {"g", "г"},
        {"d", "д"},
        {"e", "е"},
        {"yo", "ё"},
        {"zh", "ж"},
        {"z", "з"},
        {"i", "и"},
        {"j", "й"},
        {"k", "к"},
        {"l", "л"},
        {"m", "м"},
        {"n", "н"},
        {"o", "о"},
        {"p", "п"},
        {"r", "р"},
        {"s", "с"},
        {"t", "т"},
        {"u", "у"},
        {"f", "ф"},
        {"x", "х"},
        {"c", "ц"},
        {"ch", "ч"},
        {"sh", "ш"},
        {"shh", "Щ"},
        {"\"", "ъ"},
        {"y", "ы"},
        {"\'", "ь"},
        {"eh", "э"},
        {"ju", "ю"},
        {"ja", "я"},
        {" ", " "}
        
        

    };

    long int  sizeInputFile = 0;

   
    
    ifstream cheakFile(inputPathFile, ios::binary | ios::ate);
    if(sizeInputFile < cheakFile.tellg()){
        cheakFile.close();
        
        ifstream userFile;
        userFile.open(inputPathFile);
        if(userFile.is_open()){
                      
            ofstream outputData;
            outputData.open(outputPathFile);
            string readUserFile;
            
            while (getline(userFile, readUserFile))
            {
                string transformString = " ";
                for(int i = 0; i < readUserFile.length(); i++){
                
                  char &swp = readUserFile[i];
                  cout <<  dictionaryTrToRu.at(&swp);  
                //transformString.insert(i, dictionaryRuToTr.find(readUserFile[i])) 
               
                }
            }
        }
    } 


   
}