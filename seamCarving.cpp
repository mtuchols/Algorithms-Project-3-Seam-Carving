#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::ofstream; using std::vector; using std::stringstream;

int main(int argc, char *argv[]) {
    string stringTemp;
    std::string filename = argv[1];

    std::string stringVerticalSeams = argv[2];
    int verticalSeams = stoi(stringVerticalSeams);

    std::string stringHorizontalSeams = argv[3];
    int horizontalSeams = stoi(stringHorizontalSeams);

    ifstream myFile;
    string junk; 
    myFile.open (filename);
    getline(myFile, junk);
        cout << junk << endl;
    getline(myFile, junk);
        cout << junk << endl;
    getline(myFile, junk);
    int columns = stoi(junk.substr(0, junk.find(' ')));
        cout <<"columns: " <<columns << endl;
    int rows = stoi(junk.substr(junk.find(' '), junk.find('\n')));
        cout << "rows: "<< rows << endl;
    getline(myFile, junk); // first 255    
    string singleLineOfAllValues;
    while(!myFile.eof())
    {
        getline(myFile, junk);
        singleLineOfAllValues.append(junk);
    }
    //cout << singleLineOfAllValues ;

    myFile.close();
    int fileContentsArray [rows] [columns];
    stringstream stream(singleLineOfAllValues);

    for (int i = 0; i< rows; i++)
    {
        for(int j =0; j<columns; j++)
        {
            stream>> fileContentsArray[i][j];
            //cout << fileContentsArray[i][j] << " ";
        }
        //cout << endl;
    }



    return 0;
}
