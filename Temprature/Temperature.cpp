#include "Temperature.h"
#include <ios>
#include <iostream>
#include <algorithm>

Temperature::Temperature() { celsius = 0.0; fahrenheit = 0.0; creationTime = time(0); }
Temperature::Temperature(double cf) : celsius(cf), fahrenheit(cf), creationTime(time(0)) {}
Temperature::Temperature(double c, double f) : celsius(c), fahrenheit(f), creationTime(time(0)) {}
Temperature::~Temperature() {};

void Temperature::setCelsius(const double c)
{
	celsius = c;
}

void Temperature::setFahrenheit(const double f)
{
	fahrenheit = f;
}

const double Temperature::getCelsius() { return this->celsius; }
time_t Temperature::getCreationTime() { return this->creationTime; }
const double Temperature::getFahrenheit() { return this->fahrenheit; }

double Temperature::toFahrenheit(const double c)
{
	double temp = 0.0;
	temp = c * (9.0 / 5.0) + 32.0;
	return temp;
}

double Temperature::toCelsius(const double f)
{
	double temp = 0.0;
	temp = (f - 32.0) * (5.0 / 9.0);
	return temp;
}

template<class T>
inline T Temperature::toFahrenheit_T(const T & c)
{
	if (std::is_same<c, double>::value)
	{
		double temp { 0.0 };
		temp = c * (9.0 / 5.0) + 32.0;
		return temp;
	}
	else
	{
		return 0.0;
	}
}

