#pragma once
#include <vector>
#include <ctime>

class Temperature
{
public:
	// Constructor
	explicit Temperature();
	explicit Temperature(double cf = 0.0);
	explicit Temperature(double c = 0.0, double f = 0.0);
	
	// Copy-Constructor
	// NOT A DEEP COPY CONSTRUCTOR !! Only shallow copy
	Temperature(const Temperature & t) { celsius = t.celsius; fahrenheit = t.fahrenheit; };

	//Destructor
	~Temperature();

	// Setters
	void setFahrenheit(const double f = 0.0);
	void setCelsius(const double c = 0.0);

	// Getters
	const double getFahrenheit();
	const double getCelsius();
	time_t getCreationTime();

	// Functions
	double toFahrenheit(const double c);
	double toCelsius(const double f);

	// Templates
	template <class T> T toFahrenheit_T(const T & c);

private:
	double celsius;
	double fahrenheit;
	std::time_t creationTime;
};


