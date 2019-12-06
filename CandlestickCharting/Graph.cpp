#include "Graph.h"

Graph::Graph()
{}


void Graph::XAxesOutput(vector<string> dateVector)
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

	int vectorSize = (int)dateVector.size();

	cout << setw(9) << char(192);

	//Output the x axes bar

	for (int i = 0; i < vectorSize; i = i++)
	{
		cout << char(194);
	}

	cout << "-Date-" << endl;

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

	cout << endl << endl;
}


void Graph::CandleSticksOutput(vector<float> open, vector<float> high, vector<float> low, vector<float> close)
{
	//Starting to figure out the graph
	float maxHigh = *max_element(high.begin(), high.end()); //maxHigh is the maximum value from the high vector
	float minLow = *min_element(low.begin(), low.end()); //minLow is the minimum value from the low vector

	//scale the y axes to half of the data size
	int scale = (int)high.size() / 2;
	float priceScale = (maxHigh - minLow) / (scale - 1);
	float outputRange = priceScale / 2; //devide by 2 so that we output on the same line a value 50% above and under the y axes value
	float yAxesPrice = maxHigh;
	int prevSpace = 0;
	int spacing = 0;

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
					spacing = (i + 1) - prevSpace;
					cout << setw(spacing) << char(219); //Output the candleSticks
					prevSpace = i + 1;
					continue;
				}
				if (close[i] > (yAxesPrice - outputRange) && open[i] < (yAxesPrice - outputRange))
				{
					spacing = (i + 1) - prevSpace;
					cout << setw(spacing) << char(219); //Output the candleSticks
					prevSpace = i + 1;
					continue;
				}
			}

			if ((open[i] - close[i]) > 0)
			{
				if (open[i] > (yAxesPrice - outputRange) && close[i] < (yAxesPrice - outputRange))
				{
					spacing = (i + 1) - prevSpace;
					cout << setw(spacing) << char(176); //Output the candleSticks
					prevSpace = i + 1;
					continue;
				}
				if (close[i] < (yAxesPrice + outputRange) && close[i] > (yAxesPrice - outputRange))
				{
					spacing = (i + 1) - prevSpace;
					cout << setw(spacing) << char(176); //Output the candleSticks
					prevSpace = i + 1;
					continue;
				}
			}

			if (high[i] > (yAxesPrice - outputRange) && close[i] < (yAxesPrice - outputRange) && open[i] < (yAxesPrice - outputRange))
			{
				spacing = (i + 1) - prevSpace;
				cout << setw(spacing) << char(179); //Output the candleSticks
				prevSpace = i + 1;
				continue;
			}
			if (low[i] < (yAxesPrice + outputRange) && close[i] > (yAxesPrice - outputRange) && open[i] > (yAxesPrice - outputRange))
			{
				spacing = (i + 1) - prevSpace;
				cout << setw(spacing) << char(179); //Output the candleSticks
				prevSpace = i + 1;
				continue;
			}
		}


		cout << endl;
		yAxesPrice = yAxesPrice - priceScale;
	}
}


void Graph::TradingVolumeGraph(vector<float> open, vector<float> volume, vector<float> close)
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


void Graph::MovingAverageGraph(vector<float> close)
{
	//MA Graph
	int prevSpace = 0;
	float movingAverageValue = 0;
	vector<float> movingAverage9Period, movingAverage18Period;
	reverse(close.begin(), close.end());
	int spacing = 0;

	cout << setw(9) << "-Price-" << setw(65) << "Period-9 MA chart" << endl;

	for (size_t i = 1; i < (close.size() - 8); i++)
	{

		for (size_t x = i; x < (i + 9); x++)
		{
			movingAverageValue = movingAverageValue + close[x];
		}

		movingAverage9Period.emplace_back(movingAverageValue / 9);

		movingAverageValue = 0;
	}

	for (size_t i = 1; i < (close.size() - 17); i++)
	{

		for (size_t x = i; x < (i + 18); x++)
		{
			movingAverageValue = movingAverageValue + close[x];
		}

		movingAverage18Period.emplace_back(movingAverageValue / 18);

		movingAverageValue = 0;
	}

	//Starting to figure out the graph
	float maxMovingAverage = *max_element(movingAverage9Period.begin(), movingAverage9Period.end());
	float minMovingAverage = *min_element(movingAverage9Period.begin(), movingAverage9Period.end());

	//scale the y axes to half of the size of the movingAverage9Period vector
	int scale = (int)movingAverage9Period.size() / 2;
	float priceScale = (maxMovingAverage - minMovingAverage) / (scale - 1);
	float yAxesPrice = maxMovingAverage;
	float outputRange = priceScale / 2; //devide by 2 so that we output on the same line a value 50% above and under the y axes value

	for (int i = 0; i < scale; i++)
	{
		prevSpace = 0;

		cout << setw(8) << yAxesPrice << char(180); //Output the maximum value on the y axes

		for (size_t x = 0; x < movingAverage9Period.size(); x++)
		{
			
			if (movingAverage9Period[x] < (yAxesPrice + outputRange) && movingAverage9Period[x] > (yAxesPrice - outputRange))
			{
				spacing = ((int)x + 10) - prevSpace;
				cout << setw(spacing) << char(43);
				prevSpace = (int)x + 10;
			}
			
			/*
			if (x >= movingAverage18Period.size())
			{
				if (movingAverage9Period[x] < (yAxesPrice + outputRange) && movingAverage9Period[x] > (yAxesPrice - outputRange))
				{
					spacing = ((int)x + 10) - prevSpace;
					cout << setw(spacing) << char(43);
					prevSpace = (int)x + 10;
				}
			}
			else
			{
				if (movingAverage9Period[x] < (yAxesPrice + outputRange) && movingAverage9Period[x] > (yAxesPrice - outputRange))
				{
					spacing = ((int)x + 10) - prevSpace;
					cout << setw(spacing) << char(43);
					prevSpace = (int)x + 10;
					continue;
				}
				
				if (movingAverage18Period[x] < (yAxesPrice + outputRange) && movingAverage18Period[x] > (yAxesPrice - outputRange))
				{
					spacing = ((int)x + 19) - prevSpace;
					cout << setw(spacing) << char(111);
					prevSpace = (int)x + 19;
					continue;
				}
				
			}
			*/
		}
		cout << endl;
		yAxesPrice = yAxesPrice - priceScale;
	}
}