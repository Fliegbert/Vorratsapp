#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

class Supply {
  friend class Meal;

private:
                std::string name;
                double price;
                int kcal100g;
                int protein100g;
                int fat100g;
                int carbohydrate100g;
                int kcalPM;
                int proteinPM;
                int fatPM;
                int carbohydratePM;
                int kcal;
                int protein;
                int fat;
                int carbohydrate;
                int grammsPerDay;
                int totalGramms;

                void RecalculateNutrients()
                {
                  int multiplyer;
                  multiplyer = this->totalGramms / 100;
                  this->kcal = this->kcal100g * multiplyer;
                  this->protein = this->protein100g * multiplyer;
                  this->fat = this->fat100g * multiplyer;
                  this->carbohydrate = this->carbohydrate100g * multiplyer;
                }

                // double CalculateMealPrice(int totalgramms, int grammsperday, double price)
                // {
                //   int intHelper;
                //   intHelper = totalgramms / grammsperday;
                //   price = price/intHelper;
                //   return price;
                // }

public:
                Supply(std::string name, double price, int kcal, int protein, int fat, int carbohydrate, int grammsPerDay, int totalGramms)
                {
                  if (name == "")
                  {
                      std::cout << "Name: ";
                      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              				std::getline(std::cin, name);

              				std::cout << "Price: ";
              				std::cin >> price;
                      if (std::cin.fail())
                      {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      }
              				std::cout << "Kcal/100g: ";
              				std::cin >> kcal;
                      if (std::cin.fail())
                      {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      }
              				std::cout << "Protein/100g: ";
              				std::cin >> protein;
                      if (std::cin.fail())
                      {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      }
              				std::cout << "Fat/100g: ";
              				std::cin >> fat;
                      if (std::cin.fail())
                      {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      }
              				std::cout << "Carbohydrate/100g: ";
              				std::cin >> carbohydrate;
                      if (std::cin.fail())
                      {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      }
              				std::cout << "Gramms per Day: ";
              				std::cin >> grammsPerDay;
                      // if (std::cin.fail())
                      // {
                      //   std::cin.clear();
                      //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      // }
              				std::cout << "Total Gramms: ";
              				std::cin >> totalGramms;
                      // if (std::cin.fail())
                      // {
                      //   std::cin.clear();
                      //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      // }
                  }
                  this->name = name;
                  this->price = price;
                  this->kcal100g = kcal;
                  this->protein100g = protein;
                  this->fat100g = fat;
                  this->carbohydrate100g = carbohydrate;
                  this->grammsPerDay = grammsPerDay;
                  this->totalGramms = totalGramms;
                }

                Supply(std::string name, int kcal, int protein, int fat, int carbohydrate, double price, int totalGramms) // Für Meals , function to calculate this stats
                {
                  if (name == "")
                  {
                      std::cout << "Name: ";
                      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              				std::getline(std::cin, name);
                      if (std::cin.fail())
                      {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                      }
              				std::cout << "Kcal/pM: ";
              				std::cin >> kcal;
              				std::cout << "Protein/pM: ";
              				std::cin >> protein;
              				std::cout << "Fat/pM: ";
              				std::cin >> fat;
              				std::cout << "Carbohydrate/pM: ";
              				std::cin >> carbohydrate;
                      std::cout << "Price: ";
              				std::cin >> price;
                      std::cout << "Total Gramms per Meal: ";
              				std::cin >> totalGramms;
                  }

                  // price = CalculateMealPrice(totalGramms, grammsPerDay, price);
                  // std::out << "Just a small test...";

                  this->name = name;
                  this->kcalPM = kcal;
                  this->proteinPM = protein;
                  this->fatPM = fat;
                  this->carbohydratePM = carbohydrate;
                  this->price = price;
                  this->totalGramms = totalGramms;
                }

                void CalcDaily() //benötigt berichtigung
                {
                        double sumDays = this->totalGramms/this->grammsPerDay;
                        double dailyProteins;
                        double dailyFats;
                        double dailyCarbohydrates;
                        double intHelper;

                        double P100g = this->protein100g;
                        double F100g = this->fat100g;
                        double C100g = this->carbohydrate100g;
                        double ForIntHelper = this->grammsPerDay;

                        sumDays = this->totalGramms / this->grammsPerDay;
                        intHelper = ForIntHelper / 100;
                        dailyProteins = ((double)P100g) * intHelper;
                        dailyFats = ((double)F100g) * intHelper;
                        dailyCarbohydrates = ((double)C100g) * intHelper;

                        std::cout << std::setprecision(2) << sumDays << " days left." << std::endl;
                        std::cout << std::setprecision(2) << dailyProteins << " Proteins per day." << std::endl;
                        std::cout << std::setprecision(2) << dailyFats << " Fats per day." << std::endl;
                        std::cout << std::setprecision(2) << dailyCarbohydrates << " Carbohydrates per day." << std::endl;
                }

                void AddGramms()
                {
                  int gramms;
                  std::cout << "How much Gramms do you have to add?: ";
                  std::cin >> gramms;
                  if (std::cin.fail())
                  {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You really should use Integers!\n";
                  }
                  else
                  {
                    this->totalGramms += gramms;
                    RecalculateNutrients();
                  }
                }

                void SubstractGramms()
                {
                  int gramms;
                  std::cout << "How much to substract?: ";
                  std::cin >> gramms;
                  if (std::cin.fail())
                  {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You really should use Integers!\n";
                  }
                  else
                  {
                    this->totalGramms -= gramms;
                    RecalculateNutrients();
                  }
                }

                void _SubstractGramms(int grammsToSubstract)
                {
                    this->totalGramms = this->totalGramms - grammsToSubstract;
                    RecalculateNutrients();
                }

                void PrintSupplyNutrients()
                {
                  std::cout << "|~" + getName() << std::endl;
                  std::cout << "|~" + std::to_string(getKcal100g()) + " Kcal" << std::endl;
                  std::cout << "|~" + std::to_string(getProtein100g()) + " gramm/s Protein" << std::endl;
                  std::cout << "|~" + std::to_string(getFat100g()) + " gramm/s Fat" << std::endl;
                  std::cout << "|~" + std::to_string(getCarbohydrate100g()) + " gramm/s Carbohydrates" << std::endl;
                  // std::cout << "|~" + std::to_string(getGrammsPerDay()) + " gramms per Day" << std::endl;
                  std::cout << "|~" + std::to_string(getTotalGramms()) + " Total gramms available." << std::endl;
                  std::cout << "|~" + std::to_string(getPrice()) + " Total Price." << std::endl;
                }



                //Getters
                std::string getName() { return this-> name; }
                inline const double& getPrice() const { return this-> price; }
                inline const int& getKcal() const { return this-> kcal; }
                inline const int& getProtein() const { return this-> protein; }
                inline const int& getFat() const { return this-> fat; }
                inline const int& getCarbohydrate() const { return this-> carbohydrate; }
                inline const int& getKcal100g() const { return this-> kcal100g; }
                inline const int& getProtein100g() const { return this-> protein100g; }
                inline const int& getFat100g() const { return this-> fat100g; }
                inline const int& getCarbohydrate100g() const { return this-> carbohydrate100g; }
                inline const int& getKcalPM() const { return this-> kcalPM; }
                inline const int& getProteinPM() const { return this-> proteinPM; }
                inline const int& getFatPM() const { return this-> fatPM; }
                inline const int& getCarbohydratePM() const { return this-> carbohydratePM; }
                inline const int& getGrammsPerDay() const { return this-> grammsPerDay; }
                inline const int& getTotalGramms() const { return this-> totalGramms; }

                //Setters
                void setName(const std::string name)
                {
                  this->name = name;
                }

                void setPrice(const int price) //funktioniert auch nicht
                {
                  this->price = price;
                }

                void setGrammsPerDay(const int grammsPerDay)
                {
                  this->grammsPerDay = grammsPerDay;
                }
};
