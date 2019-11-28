#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef CSV_H
#define CSV_H

class CSV
{
public:
	CSV();

	vector<float> open, high, low, close, volume, marketCap;
	vector<string> dateVector;

	void CSVfile(string fileName);
};

#endif // !CSV_H

