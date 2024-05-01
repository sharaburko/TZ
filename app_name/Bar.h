#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include "Logs.h"

namespace fs = std::filesystem;

class Bar
{
private:
	std::string exchangeRates;
	std::string sign;
	std::string time;
	double price;
	int size;

	std::string path;

public:
	Bar(Logs &logs, SYSTEMTIME& time);
	Bar(std::string exchangeRates, double price, int size);

	void setExchangeRates(std::string exchangeRates);
	void setPrice(double price);

	std::string& getExchangeRates();
	double& getPrice();

	friend std::istream& operator >> (std::istream& stream, Bar &bar);
};
