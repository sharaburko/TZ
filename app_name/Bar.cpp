#include "Bar.h"

Bar::Bar(Logs& logs, SYSTEMTIME& time)
{
	path = fs::current_path().string() + "\\" + "Bars";

	if (fs::is_directory(path)) {
		std::uintmax_t n{ fs::remove_all(path + "\\") };
		logs.AddAnEvent("Bars folder cleared", time);
	}

	fs::create_directory(path);
	logs.AddAnEvent("Bars folder create", time);
}

void Bar::setExchangeRates(std::string exchangeRates)
{
	this->exchangeRates = exchangeRates;
}

void Bar::setPrice(double price)
{
	this->price = price;
}

std::string& Bar::getExchangeRates()
{
	return exchangeRates;
}

double& Bar::getPrice()
{
	return price;
}

Bar::Bar(std::string exchangeRates, double price, int size)
{
	setExchangeRates(exchangeRates);
	setPrice(price);
}

std::istream& operator >> (std::istream& stream, Bar& bar) {
	std::string price;
	std::string size;
	std::getline(stream, bar.exchangeRates, ',');
	std::cout << bar.exchangeRates << " ";
	std::getline(stream, bar.sign, ',');
	std::cout << bar.sign << " ";
	std::getline(stream, price, ',');
	std::cout << price << " ";
	bar.price = std::stod(price);
	std::cout << bar.price << " ";
	std::getline(stream, size, '\n');
	std::cout << size << " ";
	bar.size = std::stod(size);
	std::cout << bar.size << "\n";

	return stream;
}