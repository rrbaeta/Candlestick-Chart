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
void candleSticksOutput(vector<float> open, vector<float> high, vector<float> low, vector<float> close);
void tradingVolumeGraph(vector<float> open, vector<float> volume, vector<float> close);

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

	//Graph Output

	candleSticksOutput(open, high, low, close);
	xAxesOutput(dateVector);

	tradingVolumeGraph(open, volume, close);
	xAxesOutput(dateVector);

	//MA Graph

	//Starting to figure out the graph
	float maxHigh = *max_element(high.begin(), high.end()); //maxHigh is the maximum value from the high vector
	float minLow = *min_element(low.begin(), low.end()); //minLow is the minimum value from the low vector

	//scale the y axes to 40 values
	int scale = 40;
	float priceScale = (maxHigh - minLow) / scale;
	//float outputRange = priceScale / 2; //devide by 2 so that we output on the same line a value 50% above and under the y axes value
	float yAxesPrice = maxHigh;

	cout << setw(9) << "-Price-" << setw(65) << "Period-9 and period-18 MA chart" << endl;

	for (int i = 0; i < scale; i++)
	{
		int prevSpace = 0;

		cout << setw(8) << yAxesPrice << char(180); //Output the maximum value on the y axes

		cout << endl;
		yAxesPrice = yAxesPrice - priceScale;
	}

	xAxesOutput(dateVector);

	cout << "Please type ‘Y’ or ‘y’ to output to text file..." << endl;

	cout << "Please type ‘Y’ or ‘y’ to run again..." << endl;
}



void xAxesOutput(vector<string> dateVector)
{
	vector<pair<char, char>> date;
	reverse(dateVector.begin(), dateVector.end());

	for (size_t i = 0; i < dateVector.size(); i++)
	{
		if (dateVector[i].length() == 2)
		{
			date.emplace_back(make_pair<char, char>((char)dateVector[i].c_str()[0], (char)dateVector[i].c_str()[1]));
		}
		else
		{
			date.emplace_back(make_pair<char, char>('0', (char)dateVector[i].c_str()[0]));
		}
	}
	
	int vectorSize = dateVector.size();

	cout << setw(9) << char(192);

	//Output the x axes bar

	for (int i = 0; i < vectorSize; i = i++)
	{
		cout << char(194);
	}

	cout << endl;

	//Output the dates
	cout << setw(10);

	for (int i = 0; i < vectorSize; i = i++)
	{
		cout << date[i].first;
	}
	
	cout << endl;
	cout << setw(10);

	for (int i = 0; i < vectorSize; i = i++)
	{
		cout << date[i].second;
	}

	cout << endl;
	cout << setw(60) << "-Date-" << endl;
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


void candleSticksOutput(vector<float> open, vector<float> high, vector<float> low, vector<float> close)
{
	//Starting to figure out the graph
	float maxHigh = *max_element(high.begin(), high.end()); //maxHigh is the maximum value from the high vector
	float minLow = *min_element(low.begin(), low.end()); //minLow is the minimum value from the low vector

	//scale the y axes to 50 values
	int scale = high.size() / 1.5;
	float priceScale = (maxHigh - minLow) / (scale - 1);
	float outputRange = priceScale / 2; //devide by 2 so that we output on the same line a value 50% above and under the y axes value
	float yAxesPrice = maxHigh;
	int prevSpace = 0;


	//Create a Vector of pairs
	reverse(open.begin(), open.end());
	reverse(high.begin(), high.end());
	reverse(low.begin(), low.end());
	reverse(close.begin(), close.end());


	cout << "\n- Price -" << setw(75) << "Candlestick chart showing the last 3 months' data" << endl;

	//output the y axis
	for (int i = 0; i < scale; i++)
	{
		prevSpace = 0;

		cout << setw(8) << yAxesPrice << char(180); //Output the maximum value on the y axes

		//check if there are values in the vector between a range of values
		for (int i = 0; i < high.size(); i++)
		{
			//if the result is negative the market closed with a higher value then what it opened with
			if ((open[i] - close[i]) < 0)
			{
				if (open[i] < (yAxesPrice + outputRange) && open[i] > (yAxesPrice - outputRange))
				{
					cout << setw(i - prevSpace) << char(219); //Output the candleSticks
					prevSpace = i;
					continue;
				}
				if (close[i] > (yAxesPrice - outputRange) && open[i] < (yAxesPrice - outputRange))
				{
					cout << setw(i - prevSpace) << char(219); //Output the candleSticks
					prevSpace = i;
					continue;
				}
			}

			if ((open[i] - close[i]) > 0)
			{
				if (open[i] > (yAxesPrice - outputRange) && close[i] < (yAxesPrice - outputRange))
				{
					cout << setw(i - prevSpace) << char(176); //Output the candleSticks
					prevSpace = i;
					continue;
				}
				if (close[i] < (yAxesPrice + outputRange) && close[i] > (yAxesPrice - outputRange))
				{
					cout << setw(i - prevSpace) << char(176); //Output the candleSticks
					prevSpace = i;
					continue;
				}
			}

			if (high[i] > (yAxesPrice - outputRange) && close[i] < (yAxesPrice - outputRange) && open[i] < (yAxesPrice - outputRange))
			{
				cout << setw(i - prevSpace) << char(179); //Output the candleSticks
				prevSpace = i;
				continue;
			}
			if (low[i] < (yAxesPrice + outputRange) && close[i] > (yAxesPrice - outputRange) && open[i] > (yAxesPrice - outputRange))
			{
				cout << setw(i - prevSpace) << char(179); //Output the candleSticks
				prevSpace = i;
				continue;
			}
		}


		cout << endl;
		yAxesPrice = yAxesPrice - priceScale;
	}
}


void tradingVolumeGraph(vector<float> open, vector<float> volume, vector<float> close)
{
	//Output Trading Volume Graph

	//scale the y axes to 5 values
	reverse(volume.begin(), volume.end());
	reverse(open.begin(), open.end());
	reverse(close.begin(), close.end());
	float maxVolume = *max_element(volume.begin(), volume.end()); //maxHigh is the maximum value from the high vector
	float minVolume = *min_element(volume.begin(), volume.end()); //minLow is the minimum value from the low vector
	int scale = 5;
	float volumeScale = (maxVolume - minVolume) / (scale - 1);
	float outputRange = volumeScale / 2; //devide by 2 so that we output on the same line a value 50% above and under the y axes value
	float yAxesVolume = maxVolume;
	int prevSpace = 0;
	int spacing = 0;

	cout << setw(9) << "-Volume-" << setw(65) << "Bargraph showing trading volume" << endl;

	for (int i = 0; i < scale; i++)
	{
		cout << setw(4) << (yAxesVolume / 1000000000) << " Bil" << char(180); //Output the maximum value on the y axes

		prevSpace = 0;
		/*
		if (i == scale)
		{
			outputRange = outputRange * 1000000;
		}
		*/
		for (int x = 0; x < volume.size(); x++)
		{
			if (volume[x] >= (yAxesVolume - outputRange))
			{
				if ((open[x] - close[x]) < 0)
				{
					spacing = (x + 1) - prevSpace;
					cout << setw(spacing) << char(219);
					prevSpace = x + 1;
				}

				if ((open[x] - close[x]) >= 0)
				{
					spacing = (x + 1) - prevSpace;
					cout << setw(spacing) << char(176);
					prevSpace = x + 1;
				}
			}
		}

		yAxesVolume = yAxesVolume - volumeScale;
		cout << endl;
	}
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
