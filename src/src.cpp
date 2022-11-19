#pragma startup loadSafeState

#include <iostream>
#include <string>
#include <vector>
#include "supply.h"
#include "meal.h"
#include "pantry.h"
#include "dailyplan.h"
#include "../include/rapidxml.hpp"
#include "../include/rapidxml_print.hpp"
#include "../include/rapidxml_utils.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <mutex>
#include <ctime>

bool exits = false;
bool stateSafed = false;
std::mutex Pantry::mutex_;

std::string takeDate(time_t Date)
{
	tm *datePointer = localtime(&Date);
	switch (datePointer->tm_mon)
	{
		case 0:
			return std::to_string(datePointer->tm_mday) + ".Januar." + std::to_string(datePointer->tm_year + 1900);
		case 1:
			return std::to_string(datePointer->tm_mday) + ".February." + std::to_string(datePointer->tm_year + 1900);
		case 2:
			return std::to_string(datePointer->tm_mday) + ".March." + std::to_string(datePointer->tm_year + 1900);
		case 3:
			return std::to_string(datePointer->tm_mday) + ".April." + std::to_string(datePointer->tm_year + 1900);
		case 4:
			return std::to_string(datePointer->tm_mday) + ".May." + std::to_string(datePointer->tm_year + 1900);
		case 5:
			return std::to_string(datePointer->tm_mday) + ".Juni." + std::to_string(datePointer->tm_year + 1900);
		case 6:
			return std::to_string(datePointer->tm_mday) + ".July." + std::to_string(datePointer->tm_year + 1900);
		case 7:
			return std::to_string(datePointer->tm_mday) + ".August." + std::to_string(datePointer->tm_year + 1900);
		case 8:
			return std::to_string(datePointer->tm_mday) + ".September." + std::to_string(datePointer->tm_year + 1900);
		case 9:
			return std::to_string(datePointer->tm_mday) + ".October." + std::to_string(datePointer->tm_year + 1900);
		case 10:
			return std::to_string(datePointer->tm_mday) + ".November." + std::to_string(datePointer->tm_year + 1900);
		case 11:
			return std::to_string(datePointer->tm_mday) + ".December." + std::to_string(datePointer->tm_year + 1900);
	}
	return std::to_string(datePointer->tm_mday) + '.' + std::to_string(datePointer->tm_mon + 1) + '.' + std::to_string(datePointer->tm_year + 1900);
};

int main()
{
	time_t date = time(NULL);
	std::string today = takeDate(date);
	Pantry& pinstance = Pantry::GetInstance();
	pinstance.loadSafeState();

	while (!exits)
	{
		{
			int choice;
			std::cout << "                                                                              \n";
			std::cout << "What do you want to do?                                                       \n";
			std::cout << "                                                                            _ \n";
			std::cout << "___________________________________________________________________________| |\n";
			std::cout << "///////////////////////////////////////////////////////////////////////////|/|\n";
			std::cout << "//////| *1=Add Supply* |////| *2=Show Supplies* |////| *3=Supplies* |//////|/|\n";
			std::cout << "///////////////////////////////////////////////////////////////////////////|/|\n";
			std::cout << "///////////////////////////////////////////////////////////////////////////|/|\n";
			std::cout << "//////////| *4=Add Meal* |/////| *5=Show Meals* |////| *6=Meal* |//////////|/|\n";
			std::cout << "///////////////////////////////////////////////////////////////////////////|/|\n";
			std::cout << "///////////////////////////////////////////////////////////////////////////|/|\n";
			std::cout << "/////////////| *7=Save Test* |/////| *8=Exit* |/////| *9=*Daliy*  |////////|/|\n";
			std::cout << "///////////////////////////////////////////////////////////////////////////|/|\n";
			std::cout << "---------------------------------------------------------------------------|_|\n";
			std::cout << "______________________________________________________________________________\n";
			std::cout << "\n";
			std::cout << "Enter: ";
			if (std::cin >> choice)
			{
				std::cout << "\n";

				if (choice == 1)
				{
					pinstance.AddSupply(stateSafed);
				}
				else if (choice == 2)
				{
					pinstance.ShowSupply();
				}
				else if (choice == 3) //Ingredients müssen aus einem vorhandenen Vektor gezogen werden und die nährwerte neu berechnet werden
				{
					stateSafed = pinstance.ModifySupply(stateSafed);
				}
				else if (choice == 4) 																																																													//Edit Meals
				{
					pinstance.AddMeal(stateSafed);
				}
				else if (choice == 5)
				{
					pinstance.ShowMeal();
				}
				else if (choice == 6) //make the buffer so it only takes one character
				{
					pinstance.ModifyMeal(stateSafed);
				}
				else if (choice == 7)
				{
						pinstance.Safe(stateSafed);
				}
				else if (choice == 8)
				{
					if (stateSafed == false)
					{
							std::string choice;
							std::cout << "Your Changes haven't been safed, still exit? [Y/N]: " << std::endl;
							std::cin >> choice;
							if (choice == "N")
							{
								return exits = false;
							}
					}
					exits = true;
				}
				else if (choice == 9)
				{
						pinstance.GetDailyScreen(today);
				}
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid Input, Enter a Number between 1 and 7.";
			}
		}
	}

	// delete s;
	// delete idn;
	// delete m;
	// delete supply;
	return 0;
};
