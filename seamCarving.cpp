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
    int fileContentsArray[rows] [columns];
    int energyMatrix[rows][columns];
    //for vertical seams
    int cumulativeEnergyMatrix[rows][columns] ;
    int hCumulativeEnergyMatrix[columns][rows] ;
    int carvedSeam[rows][columns];

    stringstream stream(singleLineOfAllValues);

    for (int i = 0; i< rows ; i++){ // put file contents into an array
        for(int j =0; j<columns; j++){
            stream>> fileContentsArray[i][j];
            cumulativeEnergyMatrix [i][j]  = 0;
            hCumulativeEnergyMatrix[j][i] = 0;
        }
    }

    for(int verticalSeamRemovals = 0; verticalSeamRemovals<verticalSeams; verticalSeamRemovals++)
    {
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
        
        for(int i = rows-2; i >= 0 ; i--) // start at bottom , traverse upwards
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
            else if (root != columns) // somewhere in the middle 
            {
                int currentSmallest = smallest(cumulativeEnergyMatrix[i][root], cumulativeEnergyMatrix[i][root-1], cumulativeEnergyMatrix[i][root + 1]);
                if(currentSmallest == cumulativeEnergyMatrix[i][root-1])
                {
                    carvedSeam[i][root-1] = 1;
                    --root;
                }
                else if(currentSmallest == cumulativeEnergyMatrix[i][root])
                {
                    carvedSeam[i][root] = 1;
                }
                else if(currentSmallest == cumulativeEnergyMatrix[i][root + 1])
                {
                    carvedSeam[i][root + 1] = 1;
                    ++root;
                }
            }             
            else if(root == columns) // positioned at far right column... can only compare number above and to the top left
            {
                int small = std::min(cumulativeEnergyMatrix[i][root], cumulativeEnergyMatrix[i][root-1]);
                if(small == cumulativeEnergyMatrix[i][root - 1])
                {
                    carvedSeam[i][root - 1] = 1;
                    --root;
                }
                else if(small == cumulativeEnergyMatrix[i][root])
                {
                    carvedSeam[i][root] = 1;
                }
            }   
        }

        for(int i = 0; i < rows; i++) // remove the seam from the array and compress the array down to have 1 less column (vertical seam removal)
        {
            for(int j = 0; j < columns; j++)
            {
                if(carvedSeam[i][j] == 1)
                {
                    for (int x = j; x < columns -1; x++) // translate the columns over one to remove the seam
                    {
                        carvedSeam[i][x] = carvedSeam[i][ x + 1 ];
                        cumulativeEnergyMatrix[i][x] = cumulativeEnergyMatrix[i][ x + 1 ];
                        fileContentsArray[i][x] = fileContentsArray[i][ x + 1 ];
                    }
                }
            }
            carvedSeam[i][ columns - 1 ] = -1;              //make the last column a -1, to show everything has translated and is removed
            cumulativeEnergyMatrix[i][ columns - 1 ] = -1;
            fileContentsArray[i][ columns - 1 ] = -1;
        }
        --columns;
    }

    int horizontalContentsArray[columns][rows]; // horizontal, transposed version of fileContentsArray
    for (int i = 0; i< columns; i++)
    {
        for (int j = 0; j< rows; j++)
        {
            horizontalContentsArray[i][j] = fileContentsArray[j][i];
        }
    }

    for(int horizontalSeamRemovals = 0; horizontalSeamRemovals < horizontalSeams; horizontalSeamRemovals++)
    {
        int hEnergyMatrix[columns][rows];

        for (int i = 0; i< columns; i++) //fill in energy matrix
        {
            for(int j =0; j<rows; j++)
            {
                if (i == 0 && j == 0)// top left corner
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j], horizontalContentsArray[i][j+1], horizontalContentsArray[i][j], horizontalContentsArray[i+1][j]);
                }
                else if (i==0 && j == rows - 1)// top right corner
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j], horizontalContentsArray[i][j+1], horizontalContentsArray[i-1][j], horizontalContentsArray[i][j]);
                }
                else if (i == columns - 1 && j == 0) /// bottom left
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j-1], horizontalContentsArray[i][j], horizontalContentsArray[i][j], horizontalContentsArray[i+1][j]);
                }
                else if (i==columns -1 &&  j == rows -1) // bottom right
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j-1], horizontalContentsArray[i][j],  horizontalContentsArray[i-1][j], horizontalContentsArray[i][j]);
                }
                else if (i == 0)// leftmost column
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j-1], horizontalContentsArray[i][j+1], horizontalContentsArray[i][j], horizontalContentsArray[i+1][j]);
                }
                else if (j == 0)// top row
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j], horizontalContentsArray[i][j+1], horizontalContentsArray[i-1][j], horizontalContentsArray[i+1][j]);
                }
                else if (j == rows - 1) // rightmost column
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i-1][j], horizontalContentsArray[i+1][j], horizontalContentsArray[i][j-1], horizontalContentsArray[i][j]);
                }
                else if (i==columns - 1)//bottom row
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i-1][j], horizontalContentsArray[i][j], horizontalContentsArray[i][j-1], horizontalContentsArray[i][j+1]);
                }
                else // somewhere in the middle
                {
                    hEnergyMatrix [i][j] = findEnergy(horizontalContentsArray[i][j], horizontalContentsArray[i][j-1], horizontalContentsArray[i][j+1], horizontalContentsArray[i-1][j], horizontalContentsArray[i+1][j]);
                }
            }
        }

        // int hCumulativeEnergyMatrix[columns][rows] ;
        for (int i = 0; i< columns; i++)
        {
            for(int j = 0; j<rows; j++)
            {
                if (i == 0) // first rows numbers do not change
                {
                    hCumulativeEnergyMatrix [i][j] = hEnergyMatrix [i][j];
                }
                else if (j == 0) // first row does not have a left value
                {
                    hCumulativeEnergyMatrix [i][j] = std::min (hEnergyMatrix[i][j] + hCumulativeEnergyMatrix[i-1][j], hEnergyMatrix[i][j] + hCumulativeEnergyMatrix[i-1][j+1]);
                }
                else if (j == rows -1) //  last row does not have a right value
                {
                    hCumulativeEnergyMatrix [i][j] = std::min (hEnergyMatrix[i][j] + hCumulativeEnergyMatrix[i-1][j], hEnergyMatrix[i][j] + hCumulativeEnergyMatrix[i-1][j-1]);
                }
                else
                {
                    hCumulativeEnergyMatrix [i][j] = findCumulativeEnergy(hEnergyMatrix[i][j], hCumulativeEnergyMatrix[i-1][j-1], hCumulativeEnergyMatrix[i-1][j], hCumulativeEnergyMatrix[i-1][j+1]);
                }
            }
        }
        int hCarvedSeam[columns][rows];
        for (int i = 0; i< columns; i++) 
        {
            for (int j = 0; j< rows; j++)
            {
                hCarvedSeam[i][j] = 0;
            }
        }
        int currentSmallest = hCumulativeEnergyMatrix[columns-1][0]; // current smallest is initially bottom left corner
        int root = 0; //position of smallest cumulative. energy

        for(int i = 1; i <rows; ++i) // find leftmost smallest number in last row
        {
            if(currentSmallest != std::min(currentSmallest, hCumulativeEnergyMatrix[columns-1][i]))
            {
                currentSmallest = std::min(currentSmallest, hCumulativeEnergyMatrix[columns-1][i]);
                root = i;
            }
        }
        hCarvedSeam[columns -1][root] = 1;

        for(int i = columns -2; i >= 0 ; --i) // start at bottom , traverse upwards
        {
            if(root == 0) // positioned at leftmost column... can only compare number above and to the top right
            {
                int small = std::min(hCumulativeEnergyMatrix[i][root], hCumulativeEnergyMatrix[i][root+1]);
                if(small == hCumulativeEnergyMatrix[i][root])
                {
                    hCarvedSeam[i][root] = 1;
                }
                else if(small == hCumulativeEnergyMatrix[i][root + 1])
                {
                    hCarvedSeam[i][root + 1] = 1;
                    ++root;
                }
            }
            else if(root != rows-1)// somewhere in the middle 
            {
                int currentSmallest = smallest(hCumulativeEnergyMatrix[i][root], hCumulativeEnergyMatrix[i][root-1], hCumulativeEnergyMatrix[i][root + 1]);
                if(currentSmallest == hCumulativeEnergyMatrix[i][root-1])
                {
                    hCarvedSeam[i][root - 1] = 1;
                    --root;
                }
                else if(currentSmallest == hCumulativeEnergyMatrix[i][root])
                {
                    hCarvedSeam[i][root] = 1;
                }
                else if(currentSmallest == hCumulativeEnergyMatrix[i][root + 1])
                {
                    hCarvedSeam[i][root + 1] = 1;
                    ++root;
                }
            }
            else if(root == rows-1) // positioned at far right column... can only compare number above and to the top left
            {
                int small = std::min(hCumulativeEnergyMatrix[i][root], hCumulativeEnergyMatrix[i][root-1]);
                if(small == hCumulativeEnergyMatrix[i][root - 1])
                {
                    hCarvedSeam[i][root - 1] = 1;
                    --root;
                }
                else if(small == hCumulativeEnergyMatrix[i][root])
                {
                    hCarvedSeam[i][root] = 1;
                }
            }
        }

        for(int i = 0; i < columns; i++) // remove the seam from the array and compress the array down to have 1 less column (vertical seam removal)
        {
            for(int j = 0; j < rows; j++)
            {
                if(hCarvedSeam[i][j] == 1)
                {
                    for (int x = j; x < rows -1; x++) // translate the columns over one to remove the seam
                    {
                        hCarvedSeam[i][x] = hCarvedSeam[i][ x + 1 ];
                        hCumulativeEnergyMatrix[i][x] = hCumulativeEnergyMatrix[i][ x + 1 ];
                        horizontalContentsArray[i][x] = horizontalContentsArray[i][ x + 1 ];
                    }
                }
            }
            hCarvedSeam[i][ rows - 1 ] = -1;              //make the last column a -1, to show everything has translated and is removed
            hCumulativeEnergyMatrix[i][ rows - 1 ] = -1;
            horizontalContentsArray[i][ rows - 1 ] = -1;
        }
        --rows;
    }

    for (int i = 0; i< rows; i++) // transpose back to original 
    {
        for (int j = 0; j< columns; j++)
        {
            fileContentsArray[i][j] = horizontalContentsArray[j][i];
        }
    }

    string fileNameEdited = filename.substr(0, filename.length()-4); // output the seam to a file
    fileNameEdited = fileNameEdited.append("_processed.pgm");
    ofstream outfile;
    outfile.open(fileNameEdited);
    outfile << "P2" << endl;
    outfile << "# Created by IrfanView" << endl;
    outfile << columns << " " << rows << endl;
    outfile << "255" << endl;
    for (int i = 0; i< rows ; i++)
    {
        for(int j =0; j<columns; j++)
        {
            outfile << fileContentsArray [i][j] << " ";
        }
        outfile << endl;
    }
    return 0;
}