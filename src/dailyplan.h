#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <stdexcept>
#include "meal.h"

class DailyPlan {

private:
                std::string today;
                int kcal;
                int protein;
                int carbohydrate;
                int fat;
                std::vector<Meal*> mealList;
                std::vector<std::string> nameList;
                //DailyPlan dailyplan_;
                double price;

                std::string takeDate()
                {
                  time_t date = time(NULL);
                	tm *datePointer = localtime(&date);
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
public:
                //nicht klonbar
                //DailyPlan(DailyPlan &other) = delete;
                //nicht zuweisbar
                //void operator=(const DailyPlan &) = delete;

                DailyPlan(std::string date)
                {
                  this->today = takeDate();
                  if (this->today != date)
                  {
                    throw std::ObjectCouldNotBeCreatedException();
                  }
                }

                void registerMeal(Meal* meal)
                {
                  this->kcal += meal->getKcal();
                  this->protein += meal->getProtein();
                  this->fat += meal->getFat();
                  this->carbohydrate += meal->getCarbohydrate();
                  this->price += meal->getPrice();
                  nameList.push_back(meal->getName());
                }

                //inline const DailyPlan& getDailyPlanInstance() const { return this-> price; }
};
