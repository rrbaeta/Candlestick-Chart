#include "CSV.h"

CSV::CSV()
{
}

vector < pair<float, string> > CSV::CSVfile()
{
	string dateDay;

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

			//Inserting the dates into the vector dateVector
			stringstream dd(date1);
			getline(dd, dateDay, ' ');
			getline(dd, dateDay, ' ');

			dateVector.emplace_back(dateDay);


			cout << setw(14) << trimmedDate << " " << char(179);

			cout << fixed;

			for (int i = 0; i < 6; i++) { // loops through the remaining 6 columns
				string field;
				double fieldData;
				getline(ss, field, ','); // read next field, might fail
				stringstream fss(field);
				fss >> fieldData; // try to convert to a double, this might fail !!!
				cout << setw(14) << setprecision(0) << fieldData << " " << char(179);

				//Inserting the values to their respective vectors
				switch (i)
				{
				case 0:
					open.emplace_back(std::stof(field));
					break;
				case 1:
					high.emplace_back(std::stof(field));
					break;
				case 2:
					low.emplace_back(std::stof(field));
					break;
				case 3:
					close.emplace_back(std::stof(field));
					break;
				case 4:
					volume.emplace_back(std::stof(field));
					break;
				case 5:
					marketCap.emplace_back(std::stof(field));
					break;
				default:
					break;
				}

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

	return open, high, low, close, volume, marketCap, dateVector;
}