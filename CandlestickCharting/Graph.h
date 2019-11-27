#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
	Graph();

	void XAxesOutput(vector<string> dateVector);
	void CandleSticksOutput(vector<float> open, vector<float> high, vector<float> low, vector<float> close);
	void TradingVolumeGraph(vector<float> open, vector<float> volume, vector<float> close);
	void MovingAverageGraph(vector<float> close);
};

#endif // !GRAPH_H