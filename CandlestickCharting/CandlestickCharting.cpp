// CandlestickCharting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//  This file is given as a starting point to help you with your coursework :).
//  You will want to split this single file into multiple classes, objects and methods fairly early on.
//  Author:  Rodrigo Baeta
//     SID:  8789109

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void xAxesOutput(vector<string> dateVector);
vector < pair<float, int> > createVectorPairs(vector<float> vectorReceived);

int main()
{
    cout << "Candlestick Charting Program Title!" << endl;
	cout << "Author:  Rodrigo Baeta" << endl;
	cout << "SID:  8789109" << endl << endl;

	vector<float> open, high, low, close, volume, marketCap;
	vector<float> posOrNegative;
	vector<string> dateVector;

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



	//Starting to figure out the graph
	float maxHigh = *max_element(high.begin(), high.end()); //maxHigh is the maximum value from the high vector
	float minLow = *min_element(low.begin(), low.end()); //minLow is the minimum value from the low vector

	//scale the y axes to 45 values
	float priceScale = (maxHigh - minLow) / 45;
	float outputRange = priceScale / 2; //devide by 2 so that we output on the same line a value 50% above and under the y axes value
	float yAxesPrice = maxHigh;

	//Create a Vector of pairs
	reverse(open.begin(), open.end());
	reverse(high.begin(), high.end());
	reverse(low.begin(), low.end());
	reverse(close.begin(), close.end());


	cout << "\n- Price -" << setw(80) << "Candlestick chart showing the last 3 months' data" << endl;

	//output the y axis
	for (int i = 0; i < 45; i++)
	{
		int prevSpace = 0;

		cout << setw(8) << yAxesPrice << char(180); //Output the maximum value on the y axes

		//check if there are values in the vector between a range of values
		for (int i = 0; i < high.size(); i++)
		{
			if (high[i] < (yAxesPrice + outputRange) && high[i] > (yAxesPrice - outputRange))
			{
				cout << setw(((i + 1) * 2) - prevSpace) << char(179); //Output the candleSticks
				prevSpace = ((i + 1 )* 2);
			}
			if (low[i] < (yAxesPrice + outputRange) && low[i] > (yAxesPrice - outputRange))
			{
				cout << setw(((i + 1) * 2) - prevSpace) << char(179); //Output the candleSticks
				prevSpace = ((i + 1) * 2);
			}

			//if the result is negative the market closed with a higher value then what it opened with
			if ((open[i] - close[i]) < 0)
			{
				if (open[i] < (yAxesPrice + outputRange) && open[i] > (yAxesPrice - outputRange))
				{
					cout << setw(((i + 1) * 2) - prevSpace) << char(219); //Output the candleSticks
					prevSpace = ((i + 1) * 2);
				}
				if (close[i] < (yAxesPrice + outputRange) && close[i] > (yAxesPrice - outputRange))
				{
					cout << setw(((i + 1) * 2) - prevSpace) << char(219); //Output the candleSticks
					prevSpace = ((i + 1) * 2);
				}
			}
			if ((open[i] - close[i]) > 0)
			{
				if (open[i] < (yAxesPrice + outputRange) && open[i] > (yAxesPrice - outputRange))
				{
					cout << setw(((i + 1) * 2) - prevSpace) << char(176); //Output the candleSticks
					prevSpace = ((i + 1) * 2);
				}
				if (close[i] < (yAxesPrice + outputRange) && close[i] > (yAxesPrice - outputRange))
				{
					cout << setw(((i + 1) * 2) - prevSpace) << char(176); //Output the candleSticks
					prevSpace = ((i + 1) * 2);
				}
			}
		}


		cout << endl;
		yAxesPrice = yAxesPrice - priceScale;
	}

	xAxesOutput(dateVector);


	/*
	vectorSize = open.size();

	//Reverse all the vectors so that they are on the right date order
	reverse(dateVector.begin(), dateVector.end());
	reverse(open.begin(), open.end());
	reverse(high.begin(), high.end());
	reverse(low.begin(), low.end());
	reverse(close.begin(), close.end());
	reverse(volume.begin(), volume.end());
	reverse(marketCap.begin(), marketCap.end());

	for(int i = 0; i < vectorSize; i++)
	{

		float result;

		result = open[i] - close[i];

		posOrNegative.emplace_back(result);

		//if the result is negative the market closed with a higher value then what it opened with

	}

	//This for outputs the high bars

	float maxHigh = *max_element(high.begin(), high.end()); //maxHigh is the maximum value from the high vector
	float maxLow = *max_element(low.begin(), low.end()); //maxLow is the maximum value from the low vector

	float oldMaxHigh = 0;
	float oldMaxLow = 0;

	vector<float>::iterator itHigh;
	vector<float>::iterator itLow;

	//for (int i = 0; i < vectorSize; i++)
	while(maxHigh != 0)
	{

		//Need to find the index of the maximum value in the vector
		itHigh = find(high.begin(), high.end(), maxHigh);

		cout << setw(8) << maxHigh << char(180); //Output the maximum value on the y axes

		cout << setw((itHigh - high.begin() + 1)*2) << char(179); //Output the candleSticks

		high[itHigh - high.begin()] = 0;

		oldMaxHigh = maxHigh;

		maxHigh = *max_element(high.begin(), high.end());


		while(oldMaxHigh == maxHigh)
		{

			itHigh = find(high.begin(), high.end(), maxHigh);

			cout << setw((itHigh - high.begin() + 1)*2) << char(179); //Output the candleSticks

			high[itHigh - high.begin()] = 0;

			oldMaxHigh = maxHigh;

			maxHigh = *max_element(high.begin(), high.end());

		}
		
		
		while (maxHigh == maxLow)
		{

			itLow = find(low.begin(), low.end(), maxLow);

			cout << setw((itLow - low.begin() + 1) * 2) << char(179); //Output the candleSticks

			low[itLow - low.begin()] = 0;

			oldMaxLow = maxLow;

			maxLow = *max_element(low.begin(), low.end());

		}

		cout << endl;

	}

	
	if (maxHigh < maxLow)
	{
		while (maxLow != 0)
		{

			itLow = find(low.begin(), low.end(), maxLow);

			cout << setw(8) << maxLow << char(180); //Output the maximum value on the y axes

			cout << setw((itLow - low.begin() + 1) * 2) << char(179); //Output the candleSticks

			low[itLow - low.begin()] = 0;

			oldMaxLow = maxLow;

			maxLow = *max_element(low.begin(), low.end());

			while (oldMaxHigh == maxLow)
			{

				itLow = find(low.begin(), low.end(), maxLow);

				cout << setw((itLow - low.begin() + 1) * 2) << char(179); //Output the candleSticks

				low[itLow - low.begin()] = 0;

				oldMaxLow = maxLow;

				maxLow = *max_element(low.begin(), low.end());

			}

			cout << endl;

		}
	}
	*/

}

void xAxesOutput(vector<string> dateVector)
{
	reverse(dateVector.begin(), dateVector.end());

	int vectorSize = dateVector.size();

	cout << setw(9) << char(192);

	//Output the x axes bar
	for (int i = 0; i < vectorSize; i++)
	{
		cout << char(196) << char(194);
	}

	cout << endl;

	//Output the dates
	cout << setw(11);

	for (int i = 0; i < vectorSize; i++)
	{
		cout << dateVector[i] << setw(2);
	}

	cout << endl;
}



vector < pair<float, int> > createVectorPairs(vector<float> vectorReceived)
{
	reverse(vectorReceived.begin(), vectorReceived.end());

	vector < pair<float, int> > vectorToPair;

	for (int i = 0; i < vectorReceived.size(); i++)
	{
		vectorToPair.push_back(make_pair(vectorReceived[i], i + 1));
	}

	//sort(vectorToPair.begin(), vectorToPair.end());

	for (int i = 0; i < vectorReceived.size(); i++)
	{
		cout << vectorToPair[i].first << " " << vectorToPair[i].second << endl;
	}

	return vectorToPair;
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
