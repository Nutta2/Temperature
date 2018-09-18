#pragma once
#include <vector>
#include "Temperature.h"

typedef std::vector<Temperature*> tVec; // use typedef to stop having to write whole declaration.
typedef std::vector<Temperature*>::iterator tVecIT;

class User
{
private:
	std::vector<Temperature*> allTemps;
	std::vector<Temperature*>::iterator allTempsIt = allTemps.begin();
	const int WIDTH = 5;
	const int PRECISION = 2;

public:
	User();
	~User();

	// Getters
	tVec getVectorTemp();
	tVecIT getVectorTempIt();

	// Setters
	void setVectorTempIt(int x);

	// Functions
	bool addTemperature();
	bool changeTemperature();
	bool changeIteratorPointedObject();
	bool removeTemperature(Temperature * temp);
	int askForIndex(const int start, const int end);
	std::string getTimeAsString(time_t &mytime);

	void readTemperatureFromFile(std::ifstream & fin);
	void readTemperatureFromBinaryFile();

	void printAllTemperatures();
	void printAllTemperaturesFromFileAsText(std::ifstream & fin);
	void printAllTemperaturesFromFileAsBinary(std::fstream & finout);

};