#include "User.h"
#include "Temperature.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <time.h>

User::User() { }

User::~User() { }

bool User::addTemperature()
{
	double tempCelsius = 0.0;
	double tempFahrenheit = 0.0;
	bool bCorrectType = false;
	std::string trash = "";
	do
	{
		std::cout << "Celsius: ";
		if (!(std::cin >> tempCelsius))
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = false;
		}
		else
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = true;
		}
	} while (!bCorrectType);
	do
	{
		std::cout << "Fahrenheit: ";
		if (!(std::cin >> tempFahrenheit))
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = false;
		}
		else
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = true;
		}
	} while (!bCorrectType);
	std::cout << std::endl;
	Temperature * temp = new Temperature{ tempCelsius, tempFahrenheit };
	
	allTemps.push_back(temp);
	allTempsIt = (std::end(allTemps) - 1);
	return (std::find(allTemps.begin(), allTemps.end(), temp) != allTemps.end());
}

bool User::changeTemperature()
{
	if (!changeIteratorPointedObject()) { return false; }
	this->printAllTemperatures();
	// std::cout << "dereferenced with user class: " << (*user->getVectorTempIt())->getCelsius() << std::endl; BUG TEST LINE
	double tempCelsius = 0.0;
	double tempFahrenheit = 0.0;
	bool bCorrectType = false;
	std::string trash = "";
	do
	{
		std::cout << "Celsius: ";
		if (!(std::cin >> tempCelsius))
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = false;
		}
		else
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = true;
		}
	} while (!bCorrectType);
	do
	{
		std::cout << "Fahrenheit: ";
		if (!(std::cin >> tempFahrenheit))
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = false;
		}
		else
		{
			std::cin.clear();
			std::getline(std::cin, trash);
			bCorrectType = true;
		}
	} while (!bCorrectType);
	std::cout << std::endl;

	(*this->getVectorTempIt())->setCelsius(tempCelsius);
	(*this->getVectorTempIt())->setFahrenheit(tempFahrenheit);

	return true;
}

bool User::changeIteratorPointedObject()
{
	const int end = this->allTemps.size();
	if (end > 0)
	{
		const int start = 1;
		int index = askForIndex(start, end);
		this->setVectorTempIt(index);
		return true;
	}
	std::printf("No temperatures where found on disk. Please create a new one!\n");
	return false;
}

bool User::removeTemperature(Temperature * temp) // TODO Complete removeTemperature
{
	(std::find(begin(allTemps), end(allTemps), temp) != end(allTemps) ? allTemps.erase(allTempsIt) : allTempsIt);
	if (std::find(allTemps.begin(), allTemps.end(), temp) == allTemps.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int User::askForIndex(const int start, const int end)
{
	int index = 0;
	std::cout << "Please select from index: " << start << " - " << end << std::endl << "Choice: ";
	std::cin >> index;
	if ((std::cin.fail()) || (index > end) || (index < start))
	{
		printf_s("Index out of bounds! Try again...");
		std::cin.clear(); // Clears the bitflags of the input stream
		std::cin.ignore(); // Removes the rest of the input stream
		askForIndex(start, end);
	}
	else
	{
		return index;
	}
	return 0;
}

std::string User::getTimeAsString(time_t & mytime)
{
	auto currTime = mytime;
	const int SIZE = 26;
	char buff[SIZE];
	errno_t err = ctime_s(buff, SIZE, &currTime); // used to check for errors. Not sure how
	return (err == 0 ? buff : "error");
}

void User::readTemperatureFromFile(std::ifstream & fin)
{
	fin.seekg(0, std::ios_base::beg);
	if (fin.is_open())
	{
		if (!fin.eof())
		{
			std::string word = "";
			int index = 0;
			while (fin >> word)
			{
				if (index % 2)
				{
					std::cout << word;
				}
				else 
				{ 
					std::cout << word; 
				}
				++index;
			}
			fin.clear();
		}
		else
		{
			std::cout << "end of file bit set!" << std::endl;
			fin.clear();
		}

	}
	else
	{
		return;
	}
}

void User::readTemperatureFromBinaryFile()
{

}

std::vector<Temperature*> User::getVectorTemp()
{
	return this->allTemps;
}

std::vector<Temperature*>::iterator User::getVectorTempIt()
{
	return this->allTempsIt;
}

void User::setVectorTempIt(int x) // TODO rewrite!
{
	x = (x - 1);
	allTempsIt = (allTemps.begin() + x);
	return;
}

void User::printAllTemperatures()
{
	const int n = allTemps.size();
	if (n < 1) { return; }
	std::cout << "Vector:" << std::endl;
	int count = 0;

	std::for_each
	(
		allTemps.begin(), 
		allTemps.end(), 
		[&](Temperature * t)  // USING LAMBA TO LOOP THROUGH! TODO ONLY USE VARIABLES NEEDED NOT ALL IN USER.CPP -> [&] use all
		{ 
		count++;
		auto currTime = t->getCreationTime();
		printf_s("%*d: Celsius: %.*f Fahrenheit: %.*f Time: %s\n", WIDTH, (count), PRECISION, t->getCelsius(), PRECISION, t->getFahrenheit(), this->getTimeAsString(currTime).c_str());
		}
	); {}
	
		  
		  // Another way of getting the same result
/* 
	for (int x = 0; x < n; x++)
	{
		printf_s("%*d: Celsius: %.*f Fahrenheit: %.*f\n", WIDTH, (x + 1), PRECISION, allTemps[x]->getCelsius(), PRECISION, allTemps[x]->getFahrenheit());
	}
*/ 
	std::cout << std::endl;
}

void User::printAllTemperaturesFromFileAsText(std::ifstream & fin)
{
	fin.seekg(0, std::ios_base::beg);
	if (fin.is_open())
	{
		if (!fin.eof())
		{
			std::cout << "File-Text: " << std::endl;
			std::string l;
			int index = 0;
			unsigned int timeIndex = 1;
			std::vector<Temperature*>::iterator tempIT = allTemps.begin(); // TODO: MAKE SURE THE VALUES FROM THE FILE IS ADDED IN THE VECTOR AT START
			/*
			while (std::getline(fin, l))
			{
				++index;
				printf_s("%*d: %s\n", WIDTH, index, l.c_str());
			}
			*/
			while (fin >> l)
			{
				if (!(index % 5))
				{
					std::cout << (timeIndex) << ": ";
				}
				++index;
				if (index % 2) // word
				{
					std::cout << l << " ";
				}
				else // value
				{
					std::cout << l << "\t";
				}
				if (!(index % 5))
				{
					fin >> l;
					time_t creationTime = (*tempIT)->getCreationTime();
					std::cout << this->getTimeAsString(creationTime);
					(tempIT < (allTemps.end() - 1) ? tempIT++ : tempIT);
					timeIndex++;
					index = 0;
				}
			}
			fin.clear(); // remember to clear flags! When file comes to the end it will set the flat for end-of-file, and you would not be able to read the 2nd time without clearing this flag.
			std::cout << std::endl;
		}
		else
		{
			fin.clear();
			std::cout << std::endl;
		}
	}
	else
		std::cout << "File-Text failed" << std::endl;
}

void User::printAllTemperaturesFromFileAsBinary(std::fstream & finout)
{
	std::cout << "File-Binary: " << std::endl;
	std::cout << std::endl;
	return;
}
