#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::ofstream; using std::stringstream;

int smallest(int x, int y, int z)
{
    int smallest = std::min(x,y);
    return std::min(smallest,z);
}

int findEnergy( int block, int up, int down, int left , int right)
{
    int x = abs(left - block ) + abs(block - right);
    int y = abs(up - block) + abs(block - down);
    int result = x  + y;
        return result;
}

int findCumulativeEnergy(int block, int left, int above, int right)
{
    int fromLeft = block + left;
    int fromAbove = block + above ;
    int fromRight = block + right;
        return smallest(fromLeft, fromAbove, fromRight);
}

int main(int argc, char *argv[]) {
    std::string filename = argv[1];

    std::string stringVerticalSeams = argv[2];
    int verticalSeams = stoi(stringVerticalSeams);

    std::string stringHorizontalSeams = argv[3];
    int horizontalSeams = stoi(stringHorizontalSeams);

    ifstream myFile;
    string junk;

    myFile.open (filename);
    getline(myFile, junk);
    getline(myFile, junk);
    getline(myFile, junk);
    int columns = stoi(junk.substr(0, junk.find(' ')));
    int rows = stoi(junk.substr(junk.find(' '), junk.find('\n')));
    getline(myFile, junk); // first 255    
    string singleLineOfAllValues;
    while(!myFile.eof()){
        getline(myFile, junk);
        singleLineOfAllValues.append(junk);
    }
    myFile.close();

    int fileContentsArray [rows] [columns];
    stringstream stream(singleLineOfAllValues);

    for (int i = 0; i< rows ; i++){
        for(int j =0; j<columns; j++){
            stream>> fileContentsArray[i][j];
        }
    }

    int energyMatrix [rows][columns];

    for (int i = 0; i< rows; i++) //fill in energy matrix
    {
        for(int j =0; j<columns; j++)
        {   
            if (i == 0 && j == 0)// top left corner
			{
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1], fileContentsArray[i][j], fileContentsArray[i+1][j]);
            }
			else if (i== rows -1 && j ==0)// top right corner
			{
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1], fileContentsArray[i-1][j], fileContentsArray[i][j]);
            }
            else if (i == 0 && j == columns -1) /// bottom left
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i+1][j]);
            }
            else if (i==rows -1 &&  j == columns -1) // bottom right
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j],  fileContentsArray[i-1][j], fileContentsArray[i][j]);
            }
            else if (i == 0)// leftmost column
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1], fileContentsArray[i][j], fileContentsArray[i+1][j]);
            }
            else if (j == 0)// top row
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j], fileContentsArray[i][j+1], fileContentsArray[i-1][j], fileContentsArray[i+1][j]);         
            }
            else if (j == columns -1) // rightmost column
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i+1][j], fileContentsArray[i][j-1], fileContentsArray[i][j]);
            }
            else if (i==rows -1)//bottom row
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i-1][j], fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1]);  
            }
            else // somewhere in the middle 
            {
                energyMatrix [i][j] = findEnergy(fileContentsArray[i][j], fileContentsArray[i][j-1], fileContentsArray[i][j+1], fileContentsArray[i-1][j], fileContentsArray[i+1][j]);    
            }
        }
    }

    int cumulativeEnergyMatrix[rows][columns] ;
    for (int i = 0; i< rows; i++) //fill in energy matrix
    {
        for(int j = 0; j<columns; j++)
        {   
            if (i == 0) // first rows numbers do not change
            {
                cumulativeEnergyMatrix [i][j] = energyMatrix [i][j];
            }
            
            else if (j == 0) // first column does not have a left value
            {
                //cumulativeEnergyMatrix [i][j] = std::min (energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j], energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j+1]);
                //cumulativeEnergyMatrix [i][j] = std::min (energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j], energyMatrix[i][j] + cumulativeEnergyMatrix[i][j+1]);
                cumulativeEnergyMatrix [i][j] = std::min (energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j], energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j+1]);
            }
            else if (j == columns -1) //  last column does not have a right value
            {
                cumulativeEnergyMatrix [i][j] = std::min (energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j], energyMatrix[i][j] + cumulativeEnergyMatrix[i-1][j-1]);
            }
            else
            {
                cumulativeEnergyMatrix [i][j] = findCumulativeEnergy(energyMatrix[i][j], cumulativeEnergyMatrix[i-1][j-1], cumulativeEnergyMatrix[i-1][j], cumulativeEnergyMatrix[i-1][j+1]);
            }
        }
    }

    int carvedSeam[rows][columns];

    for (int i = 0; i<rows; i++) // assign all initial values to zero
    {
        for(int j = 0; j<columns; j++)
        {
            carvedSeam[i][j] = 0;
        }    
    }

    
    int currentSmallest = cumulativeEnergyMatrix[rows-1][0]; // current smallest is initially bottom left corner
    int root = 0; //position of smallest cumulative. energy
    for(int i = 1; i < columns; ++i) // find leftmost smallest number in last row
    {
        if(currentSmallest != std::min(currentSmallest, cumulativeEnergyMatrix[rows-1][i]))
        {
        currentSmallest = std::min(currentSmallest, cumulativeEnergyMatrix[rows-1][i]);
        root = i;
        }
    }
    carvedSeam[rows-1][root] = 1;
    
    for(int i = rows-1; i >= 0 ; i--) // start at bottom , traverse upwards
    {
        if(root == 0) // positioned at leftmost column... can only compare number above and to the top right
        {
            int small = std::min(cumulativeEnergyMatrix[i][root], cumulativeEnergyMatrix[i][root+1]);
            if(small == cumulativeEnergyMatrix[i][root])
            {
                carvedSeam[i][root] = 1;
            }
            else if(small == cumulativeEnergyMatrix[i][root + 1])
            {
                carvedSeam[i][root + 1] = 1;
                root++;
            }
        }
        else if(root == columns) // positioned at far right column... can only compare number above and to the top left
        {
            int small = std::min(cumulativeEnergyMatrix[i][root], cumulativeEnergyMatrix[i][root-1]);
            if(small == cumulativeEnergyMatrix[i][root])
            {
                carvedSeam[i][root] = 1;
            }
            else if(small == cumulativeEnergyMatrix[i][root - 1])
            {
                carvedSeam[i][root - 1] = 1;
                --root;
            }
        }
        else // somewhere in the middle 
        {
            int currentSmallest = smallest(cumulativeEnergyMatrix[i][root], cumulativeEnergyMatrix[i][root-1], cumulativeEnergyMatrix[i][root + 1]);
            if(currentSmallest == cumulativeEnergyMatrix[i][root])
            {
                carvedSeam[i][root] = 1;
            }
            else if(currentSmallest == cumulativeEnergyMatrix[i][root + 1])
            {
                carvedSeam[i][root + 1] = 1;
                ++root;
            }
            else if(currentSmallest == cumulativeEnergyMatrix[i][root-1])
            {
                carvedSeam[i][root-1] = 1;
                --root;
            }
        }      
    }

    string fileNameEdited = filename.substr(0, filename.length()-4); // output the seam to a file
    fileNameEdited = fileNameEdited.append("_processed.pgm");
    ofstream outfile;
    outfile.open(fileNameEdited);

    for (int i = 0; i< rows ; i++)
    {
        for(int j =0; j<columns; j++)
        {
             outfile << carvedSeam [i][j] << " ";
        }
        outfile << endl;
    }

    for(int i = 0; i < rows; i++) // remove the seam from the array and compress the array down to have 1 less column (vertical seam removal)
    {
      for(int j = 0; j < columns; j++)
      {
        if(carvedSeam[i][j] == 1)
        {
          for(int w = j; w < columns - 2; w++)
          {
          cumulativeEnergyMatrix[i][w] = cumulativeEnergyMatrix[i][w + 1];
          fileContentsArray[i][w] = fileContentsArray[i][w + 1];
          }
          cumulativeEnergyMatrix[i][columns -1] = 0;
          fileContentsArray[i][columns -1] = 0;
        }
      }
    }
    --columns;

    return 0;
}
