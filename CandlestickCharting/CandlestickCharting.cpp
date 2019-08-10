// CandlestickCharting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//  This file is given as a starting point to help you with your coursework :).
//  You will want to split this single file into multiple classes, objects and methods fairly early on.
//  Author:  Chris Bass
//     SID:  1234567890

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    cout << "Candlestick Charting Program Title!" << endl;
	cout << "Author:  Chris Bass" << endl;
	cout << "SID:  1234567890" << endl << endl;

	// Read input data from .csv file.
	//  Assumes the data is in a particular format:
	//    Date,Open*,High,Low,Close**,Volume,Market Cap
	//    "Jul 28, 2019", 9491.63, 9575.55, 9252.3, 9552.86, 13738687093, 1.70462E+11
	//  First we can read line by line, then we can break the line into multiple values by comma.

	// Note that immediately after reading each field, we simply write them to the console.
	//  For the coursework you will want to change this, so that the values are stored
	//  in some form of temporary data-structure for further processing later on.

	// We should be checking for errors in the input file e.g. formatting at every point after a read.
	//  I.e. read line, check, read line, check...  or read field, check, read field, check.
	//  However, I have only checked for some of the input file reading errors at each point.

	ifstream inputFileStream;
	inputFileStream.open("BTChist.csv"); // hardcoded filename, for now...

	if (inputFileStream.good())
	{
		cout << "Input file is good start processing..." << endl << endl;
		
		cout << right << setw(14) << "Date:" << setw(16) << "Open:" << setw(16) << "High:" << setw(16) << "Low:" << setw(16) << "Close:" << setw(16) << "Volume:" << setw(16) << "Market Cap:" << endl;
		cout.fill(char(196));
		cout << setw(112) << char(191) << endl;
		cout.fill(' ');

		string line;
		getline(inputFileStream, line); // read 1st line, skip 1st line (headers), might fail!
		getline(inputFileStream, line); // read 2nd line, might fail!

		while (!inputFileStream.fail()) // check for failbit
		{
			stringstream ss(line);

			string date1;
			string date2;
			getline(ss, date1, ','); // read first field from line, might fail
			getline(ss, date2, ','); // read second field from line, might fail
			string date = date1 + date2;
			string trimmedDate = date.substr(1, date.size() - 2);

			cout << setw(14) << trimmedDate << " " << char(179);

			cout << fixed;

			for (int i = 0; i < 6; i++) { // loops through the remaining 6 columns
				string field;
				double fieldData;
				getline(ss, field, ','); // read next field, might fail
				stringstream fss(field);
				fss >> fieldData; // try to convert to a double, this might fail !!!
				cout << setw(14) << setprecision(0) << fieldData << " " << char(179);
			}

			cout << endl;

			getline(inputFileStream, line); // read next line
		}

		cout << endl;

		if (inputFileStream.eof()) {
			cout << "Reached the end of file marker.  File data read sucessfully." << endl;
		}
		else {
			cout << "Error in input file." << endl;
		}
	}
	else
	{
		cout << "Error opening input file, ";
		cout << "check 'BTChist.csv' exists in correct directory." << endl;
	}

	inputFileStream.close();


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
