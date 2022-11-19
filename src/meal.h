#pragma once
#include "supply.h"
#include <string>
#include <vector>

class Meal {
  friend class Supply;

private:
              std::vector<Supply*> ingredients;
              std::string name;
              double price;
              int kcal;
              int protein;
              int fat;
              int carbohydrate;
              std::string description;
              std::string recipe;

public:
              Meal(std::string Name, std::vector<Supply*> Ingredients)
              {
                this->name = Name;
                this->ingredients = Ingredients;
                for (Supply* ms : Ingredients)
      					{
                  this->kcal += ms->getKcalPM();
      						this->protein += ms->getProteinPM();
                  this->fat += ms->getFatPM();
                  this->carbohydrate += ms->getCarbohydratePM();
                  this->price += ms->getPrice();
      					}
              }

              void AddIngredient(std::vector<Supply*> NewIngredient)
              {
                ingredients.insert(ingredients.end(), NewIngredient.begin(), NewIngredient.end());
                for (Supply* ms : NewIngredient)
      					{
                  this->kcal += ms->getKcalPM();
      						this->protein += ms->getProteinPM();
                  this->fat += ms->getFatPM();
                  this->carbohydrate += ms->getCarbohydratePM();
                  this->price += ms->getPrice();
      					}
              }

              /*void GetNutrients(int &kcal, int &protein, int &fat, int &carbohydrate)
              {
                kcal += this->kcal;
                protein += this->protein;
                fat += this->fat;
                carbohydrate += this->carbohydrate;
              }*/

              void AddRecipe()
              {
                std::cout << "Write Your Recipe... \n";
                std::cin >> recipe;
              }

              void GetRecipe()
              {
                std::cout << recipe + '\n';
                std::cout << '\n';
              }

              void PrintNutrition()
              {
                std::cout << getName() << std::endl;
                std::cout << std::to_string(getKcal()) + " Kcal" << std::endl;
                std::cout << std::to_string(getProtein()) + " gramm/s Protein" << std::endl;
                std::cout << std::to_string(getFat()) + " gramm/s Fat" << std::endl;
                std::cout << std::to_string(getCarbohydrate()) + " gramm/s Carbohydrates" << std::endl;
              }

              //Getters
              std::string getName() { return this-> name; }
              std::vector<Supply*> getIngredients() { return this->ingredients; }
              inline const double& getPrice() const { return this-> price; }
              inline const int& getKcal() const { return this-> kcal; }
              inline const int& getProtein() const { return this-> protein; }
              inline const int& getFat() const { return this-> fat; }
              inline const int& getCarbohydrate() const { return this-> carbohydrate; }
              std::string getDescription() { return this-> description; }


              //Setters
              void setName(const std::string name)
              {
                this->name = name;
              }
              void setKcal(const std::string name)
              {
                this->name = name;
              }
              void setPrice(const double newprice)
              {
                this->price = newprice;
              }
              void SetDescription()
              {
                std::string Description;
                std::cout << "Describe your meal." << '\n';
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, Description);
                this->description = Description;
              }
};
