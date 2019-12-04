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

#include "CSV.h"
#include "Graph.h"

using namespace std;

int main()
{
	CSV csvOutput;
	Graph graph;

	string fileName;

    cout << "Candlestick Charting Program Title!" << endl;
	cout << "Author:  Rodrigo Baeta" << endl;
	cout << "SID:  8789109" << endl << endl;

	while (true)
	{
		cout << "Input the file name to analyze" << endl;
		cin >> fileName;
		cout << endl;
	
		csvOutput.CSVfile(fileName);
	
		char outputTextFile, runAgain;

		cout << "\nBullish -> " << char(219) << endl;
		cout << "Bearish -> " << char(176) << endl;

		//Graph Output
		graph.CandleSticksOutput(csvOutput.open, csvOutput.high, csvOutput.low, csvOutput.close);
		graph.XAxesOutput(csvOutput.dateVector);

		graph.TradingVolumeGraph(csvOutput.open, csvOutput.volume, csvOutput.close);
		graph.XAxesOutput(csvOutput.dateVector);

		graph.MovingAverageGraph(csvOutput.close);
		graph.XAxesOutput(csvOutput.dateVector);

		//cout << "Please type 'Y' or 'y' to output to text file..." << endl;

		cout << "Please type 'Y' or 'y' to run again..." << endl;
		cin >> runAgain;
		cout << endl;

		if (runAgain == 'y' || runAgain == 'Y')
		{}
		else {
			break;
		}
	}
	cout << "Thank you for using the financial candlestick charting program. Goodbye!" << endl;
}