Michael Tucholski
Seam Carving

This is a program for Project3 in Algorithms at the University of Akron.
This program is takes in a txt or pgm file, (or any other file that could be space delimited)
with numbers. 

The file must start with this format
P2			   ... start of file 
# Created by IrfanView     ... this is a comment. A line that starts with # is a comment
3 8			   ... the file has 3 columns and 8 rows
255			   ... the bits go from 0 to 255

The goal of this project is to resize an image using seam carving, which removes individual 
seams from the file, which have the least energy. This ensures there will be the least amount 
of visual change on the image. 

To run this program, first compile by typing: g++ seamCarving.cpp -o seamCarving
into a console. 

Next type ./seamCarving example.pgm 1 2 	with example.pgm being the file name, 1 being
the vertical seams to remove, and 2 being the horizontal seams to remove. 

Regarding Source code, this is the flow of operations:
1. parse file
2. put contents into an array called fileContentsArray
3. 
	A. Vertical
		1. find energy function , storing results in energyMatrix
		2. find cumulative energy, storing results in cumulativeEnergyMatrix
		3. find seam to carve, storing results in a binary array called carvedSeam
		4. remove the seam from fileContentsArray, and repeat for however many vertical seams
	B. Horizontal
		1. find energy function , storing results in hEnergyMatrix
		2. find cumulative energy, storing results in hCumulativeEnergyMatrix
		3. find seam to carve, storing results in a binary array called hCarvedSeam
		4. remove the seam from fileContentsArray, and repeat for however many horizontal seams
4. Output to file named fileName_processed.pgm