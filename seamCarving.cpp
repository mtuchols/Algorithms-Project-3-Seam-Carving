#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::ofstream; using std::vector; using std::stringstream;

int findEnergy( int block, int up, int down, int left , int right)
{
    int x = abs(left - block ) + abs(block - right);
    int y = abs(up - block) + abs(block - down);
    int result = x  + y;
        return result;
}

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
    int fileContentsArray [columns] [rows];
    stringstream stream(singleLineOfAllValues);

    for (int i = 0; i< columns; i++)
    {
        for(int j =0; j<rows; j++)
        {
            stream>> fileContentsArray[i][j];
            //cout << fileContentsArray[i][j] << " ";
        }
        //cout << endl;
    }
    int energyMatrix [columns][rows];

    //int findEnergy( int block, int up, int down, int left , int right)

    for (int i = 0; i< columns; i++) //fill in energy matrix
    {
        for(int j =0; j<rows; j++)
        {   
            if (i == 0 && j == 0)// top left corner
			{
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1], fileContentsArray[i][j], fileContentsArray[i+1][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i+1][j], fileContentsArray[i][j], fileContentsArray[i][j+1]); 
                // cout << "TOP LEFT" << endl;
                // cout << "BLOCK" << fileContentsArray[i][j] << endl;
                // cout << "UP:" << fileContentsArray[i][j] << endl;
                // cout << "DOWN:"<<fileContentsArray[i+1][j]<< endl;
                // cout << "LEFT:"<<fileContentsArray[i][j]<<endl;
                // cout << "RIGHT"<<fileContentsArray[i][j+1]<<endl;
            }
			else if (i==0 && j == rows -1)// top right corner
			{
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1], fileContentsArray[i-1][j], fileContentsArray[i][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i+1][j], fileContentsArray[i][j-1], fileContentsArray[i][j]);
            }
            else if (i== columns -1 && j == 0) /// bottom left
            {
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i+1][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1]);
            }
            else if (i==columns -1 &&  j == rows -1) // bottom right
            {
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j],  fileContentsArray[i-1][j], fileContentsArray[i][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i][j],  fileContentsArray[i][j-1], fileContentsArray[i][j]);
            }
            else if (j == 0)// leftmost column
            {
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1], fileContentsArray[i][j], fileContentsArray[i+1][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i+1][j], fileContentsArray[i][j], fileContentsArray[i][j+1]);
            }
            else if (i == 0)// top row
            {
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1], fileContentsArray[i-1][j], fileContentsArray[i+1][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i+1][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1]);            
            }
            else if (j == rows -1) // rightmost column
            {
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1], fileContentsArray[i-1][j], fileContentsArray[i][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i+1][j], fileContentsArray[i][j-1], fileContentsArray[i][j]);
            }
            else if (i==columns -1)//bottom row
            {
                //energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i+1][j]);
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1]);  
            }
            else // somewhere in the middle 
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i+1][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1]);      
            }
        }
    }


    // for (int i = 0; i< rows; i++) //fill in energy matrix
    // {
    //     for(int j =0; j<columns; j++)
    //     {   
    //         cout << energyMatrix [i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
