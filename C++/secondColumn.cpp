#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int BUFSIZE = 1024;
const int ARRAYSIZE = 50;

int main(int argc, char* argv[])
{
	char buffer[BUFSIZE];
	char* startPtr;
	char* endPtr;
	char myArray[ARRAYSIZE][ARRAYSIZE][BUFSIZE];
	
	for(int i = 0; i < ARRAYSIZE; i++)
		for(int j = 0; j < ARRAYSIZE; j++)
			*myArray[i][j] = '\0';
	
	ifstream myStream(argv[1]);
	bool isEndLine = false;
	bool isSpace = false;
	int row, col, maxRow, maxCol;
	
	while(!myStream.eof())
	{
		myStream.getline(buffer, BUFSIZE-1);
		startPtr = buffer;
		endPtr = startPtr;
		isEndLine = false;
		
		while(!isEndLine)
		{
			endPtr++;
			isSpace = false;
			if(*endPtr == ' ')
			{
				*endPtr = '\0';
				isSpace = true;
			}
			if(*endPtr == '\0')
			{
				isEndLine = true;
				strncpy(myArray[row][col], startPtr, BUFSIZE-1);
				col++;
			}
			if(isSpace)
			{
				*endPtr = ' ';
				while(*endPtr == ' ') endPtr++;
				startPtr = endPtr;
				isEndLine = false;
			}
		}
		if(col > maxCol) maxCol = col;
		row++;
		col = 0;
	}
	
	maxRow = row;
	double sum = 0;
	for(int i = 0; i < maxRow; i++) sum += atof(myArray[i][1]);
	cout << sum << endl;
	
	return 0;
}

			
