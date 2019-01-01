#include "Temperature.h" // Henter mange ting kan eg fjerne her?
#include "User.h"
#include <iostream> // for input and output stream
#include <iomanip> // for manipulating I/O 
#include <string> // for å bruke std::string
#include <fstream> // for å input og output til fil
#include <chrono> // for tid

User * createNewUser();
inline void introduction();
void showInformation();
void optionsInformation();
int selectOptions();

User * user = new User();
int answer = 6;

std::ofstream fout("CPP_StreamAsText.txt", std::ios_base::out | std::ios_base::app); // STREAMS TO text file CPPtrainingstream.txt! Truncates the content every time the program restarts
std::ifstream fin("CPP_StreamAsText.txt", std::ifstream::in);						 // STREAMS FROM text file CPPtrainingstream.txt! Truncates the content every time the program restarts
std::fstream finout("CPP_StreamAsBinary.txt", std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary);

int main()
{
	introduction();
	do 
	{
		double binaryDouble = 0.0;
		const int WIDTH = 15;

		// Variables used for getting time
		time_t currTime;
		std::string myTime;

		optionsInformation();
		switch (answer = selectOptions())
		{
		case 1: // Celsius to Fahrenheit
			if (!user->changeIteratorPointedObject()) { break; }
			std::cout << (*user->getVectorTempIt())->getCelsius() << " Celsius is " << (*user->getVectorTempIt())->toFahrenheit((*user->getVectorTempIt())->getCelsius()) << " Fahrenheit" << std::endl;
			break;
		case 2: // Fahrenheit to Celsius
			if (!user->changeIteratorPointedObject()) { break; }
			std::cout << (*user->getVectorTempIt())->getFahrenheit() << " Fahrenheit is " << (*user->getVectorTempIt())->toCelsius((*user->getVectorTempIt())->getFahrenheit()) << " Celsius" << std::endl;
			break;
		case 3: // Delete temperature value
			if (!user->changeIteratorPointedObject()) { break; }
			user->removeTemperature((*user->getVectorTempIt()));
			printf_s("Temperature Deleted!\n");
			break;
		case 4: // Create new Temperature Value
			if (!user->addTemperature()) { break; }
			std::cout.setf(std::ios_base::left);

			currTime = (*user->getVectorTempIt())->getCreationTime(); // reduce code on next line;
			myTime = user->getTimeAsString(currTime);

			std::cout << "New Temperature values:\n" << std::setw(WIDTH) << "Celsius: " << std::setw(WIDTH) << (*user->getVectorTempIt())->getCelsius() << std::setw(WIDTH) << "Fahrenheit: " << std::setw(WIDTH) << (*user->getVectorTempIt())->getFahrenheit() << std::setw(WIDTH) << "Creation Time: " << std::setw(26) << myTime << std::endl;
			fout << "Celsius: " << (*user->getVectorTempIt())->getCelsius() << "\tFahrenheit: " << (*user->getVectorTempIt())->getFahrenheit() << "\tTime: " << currTime << std::endl;
			
			binaryDouble = (*user->getVectorTempIt())->getCelsius();
			// Write as binary to fstream
			finout.write((char*)&binaryDouble, sizeof binaryDouble) << std::endl << std::flush; // Flush stream to make sure the buffer is cleared!
			break;
		case 5:  // Change Temperature Values
			if (!user->changeTemperature()) { break; }
			std::cout.setf(std::ios_base::left);

			currTime = (*user->getVectorTempIt())->getCreationTime(); // reduce code on next line;
			myTime = user->getTimeAsString(currTime);

			std::cout << "Changed Temperature values:\n" << std::setw(WIDTH) << "Celsius:" << std::setw(WIDTH) << (*user->getVectorTempIt())->getCelsius() << std::setw(WIDTH) << "Fahrenheit: " << std::setw(WIDTH) << (*user->getVectorTempIt())->getFahrenheit() << std::setw(WIDTH) << "Change Time: " << std::setw(27) << myTime << std::endl;
			fout << "Celsius: " << (*user->getVectorTempIt())->getCelsius() << "\tFahrenheit : " << (*user->getVectorTempIt())->getFahrenheit() << "\tTime: " << currTime << std::endl;
			break;
		case 6: // Print Temperatures
			user->readTemperatureFromFile(fin);
			user->printAllTemperatures();
			user->printAllTemperaturesFromFileAsText(fin);
			//user->printAllTemperaturesFromFileAsBinary(finout);
			break;
		case 7:
			delete user;
		default:
			system("pause");
			return 0;
			break;
		}
	} while (answer > 0 && answer < 7);
	if (user){ delete user; }
	system("pause");
	return 0;
}

void introduction()
{
	std::printf("Welcome to temperature measurement v4.0\nPlease choose one of the options below (anything else will exit the program!)\n");
}

User * createNewUser()
{
	return new User();
}

void showInformation()
{
	std::cout << "You have entered the following information\n" << "Celsius: " << (*user->getVectorTempIt())->getCelsius() << "\tFahrenheit: " << (*user->getVectorTempIt())->getFahrenheit() << "\n";
	return;
}

void optionsInformation()
{
	std::cout << "\nPlease choose from these options below:\n";
	std::cout << "1. Find Fahrenheit from Celsius\t\t2. Find Celsius from Fahrenheit\n3. Delete temperature value\t\t4. New temperature\n5. Change temperature values\t\t6. Print temperatures\n7. Quit\n" << "Choice: ";
	return;
}

int selectOptions()
{
	int tempAnswer;
	std::cin >> tempAnswer;
	std::cout << std::endl;
	return tempAnswer;
}