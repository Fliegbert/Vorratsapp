#pragma once
#include "supply.h"
#include "meal.h"
#include "dailyplan.h"
#include <string>
#include <vector>
#include <mutex>
#include "../include/rapidxml.hpp"
#include "../include/rapidxml_print.hpp"
#include "../include/rapidxml_utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>

class Pantry {

private:
              Pantry()
              {
                PantryCreated();
              }
              ~Pantry()
              {
              }

              static std::mutex mutex_;
              std::vector<Supply*> SupplyList;
              std::vector<Meal*> MealList;
              std::vector<DailyPlan*> Calendar;
              std::string supplyName;;
              double supplyPrice;
              int supplyKcal;
              int supplyProtein;
              int supplyFat;
              int supplyCarbohydrate;
              int supplyGrammsPerDay;
              int supplyTotalGramms;
public:
              //nicht klonbar
              Pantry(Pantry &other) = delete;
              //nicht zuweisbar
              void operator=(const Pantry &) = delete;

              void PantryCreated()
              {
                std::cout << "Pantry created" << '\n';
              }

              //Functions
              void AddSupply(bool &stateSafed)
              {
                std::cout << "Adding Supply\n";
    						std::cout << "-------------\n";
    						Supply* s = new Supply(supplyName, supplyPrice, supplyKcal, supplyProtein, supplyFat, supplyCarbohydrate, supplyGrammsPerDay, supplyTotalGramms);
    						SupplyList.push_back(s);
    						stateSafed = false;
              }

              void AddMeal(bool &stateSafed)
              {
      						int Helper;
      						std::vector<Supply*> Ingredients;
      						std::string Name;
      						std::cout << "How to call this meal? ";
      						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      						std::getline(std::cin, Name);
      						std::cout << "How many Ingredients do you want to add? ";
      						if (std::cin >> Helper)
      						{
      							for (int i = 0; i < Helper; i++)
      							{
      								Supply* idn = new Supply(supplyName, supplyKcal, supplyProtein, supplyFat, supplyCarbohydrate, supplyPrice, supplyTotalGramms);
      								Ingredients.push_back(idn);
      							}
      							for (Supply* i : Ingredients)
      							{
      								std::cout << i->getKcal() << std::endl;
      							}
      							Meal* m = new Meal(Name, Ingredients);
      							MealList.push_back(m);
      							stateSafed = false;
      						}
      						else
      						{
      							std::cin.clear();
      							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      							std::cout << "Use the amount of Numbers you want to use." << std::endl;
      						}
              }

              bool ModifySupply(bool stateSafed) //////////////////////////////////
              {
                if (SupplyList.size() == 0)
    						{
    							std::cout << "No Supplies available" << std::endl;
    							return stateSafed;
    						}
    						int count = 0;
    						for (Supply* s : SupplyList)
    						{
    							std::cout << s->getName() + ": " + std::to_string(count) << std::endl;
    							++count;
    						}
    						// std::string cs;
    						int cs;
    						std::cout << "Where do you want to change something? Enter number: ";
    						if (std::cin >> cs)
    						{
    							Supply* selectedSupply = SupplyList.at(cs);
    							bool exit = false;
    							while (!exit)
    							{
    								int choice;																																	//Nur Supplies
    								std::cout << "What do you want to do?" << std::endl;
    								std::cout << "                                                                          _ \n";
    								std::cout << "_________________________________________________________________________| |\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "////| *1=Set Gramms Per Day* |//| *2=Show Nutrients* |/| *3=AddGramms* |/|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "////| *4=CalcDaily* |////| *5=SubstractGramms* |////| *6=setPrice* |/////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "///////////////////////////////| *7=Exit* |//////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "-------------------------------------------------------------------------|_|\n";
    								std::cout << "____________________________________________________________________________\n";
    								std::cout << "\n";
    								std::cout << "Enter: ";
    								if (std::cin >> choice)
    								{
    									std::cout << "\n";

    									switch (choice)
    									{
    										case 1: //Mit dezimalstelle problem
    											std::cout << "How many Gramms do you want to eat per day? ";
    											if (std::cin >> choice)
    											{
    												selectedSupply->setGrammsPerDay(choice);
    												stateSafed = false;
    												break;
    											}
    											else
    											{
    												std::cin.clear();
    												std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    												std::cout << "Use Integers for Gramms" << '\n';
    												break;
    											}

    										case 2:
    											selectedSupply->PrintSupplyNutrients();
    											break;

    										case 3:
    											selectedSupply->AddGramms();
    											stateSafed = false;
    											break;

    										case 4:
    											selectedSupply->CalcDaily(); //... days left not calculated probably
    											break;

    										case 5:
    											selectedSupply->SubstractGramms();
    											stateSafed = false;
    											break;

    										case 6:
    											int newPrice;
    											std::cout << "What is the new price?";
    											if (std::cin >> newPrice)
    											{
    												selectedSupply->setPrice(newPrice);
    												stateSafed = true;
    												break;
    											}
    											else
    											{
    												std::cin.clear();
    												std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    												std::cout << "Use Numbers" << '\n';
    												break;
    											}

    										case 7:
    											exit = true;
    											break;
    									}
    								}
    								else
    								{
    									std::cin.clear();
    									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    									std::cout << "Use the Numbers to select one of the Options." << '\n';
    								}
    							}
    						}
                else
    						{
    							std::cin.clear();
    							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    							std::cout << "Use Numbers within the range to select a Supply." << std::endl;
    						}
                return stateSafed;
              }

              void ModifyMeal(bool &stateSafed)
              {
    						int count = 0;
    						for (Meal* m : MealList)
    						{
    							std::cout << m->getName() + " " + std::to_string(count) << std::endl;
    							++count;
    						}
    						// std::string cs;
    						int cs;
    						std::cout << "Where do you want to change something? Enter number: ";
    						if (std::cin >> cs)
    						{
    							Meal* selectedMeal = MealList.at(cs);
                  std::string MealName = selectedMeal->getName();
    							bool exit = false;
    							while (!exit)
    							{
    								int choice;																																																													//Meal Menu
    								std::cout << "What do you want to do?" << std::endl;
    								std::cout << "                                                                          _ \n";
    								std::cout << "_________________________________________________________________________| |\n";
                    std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
                    std::cout << "////| *"+MealName+"* |////|/|\n";
                    std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/| *1=Set Description* |/| *2=Show Nutrition* |/| *3=Show Ingredients* |/|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "////| *4=Modify Ingredient* |////| *5=Make Meal* |////| *6=set Price* |//|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "////| *7=Make Recipe* |////| *8=Add Ingredient* |////| *9=*Exit |////////|/|\n";
                    std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
                    std::cout << "////| *10=Show Recipe* |/////////////////////////////////////////////////|/|\n";
                    std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    								std::cout << "-------------------------------------------------------------------------|_|\n";
    								std::cout << "____________________________________________________________________________\n";
    								std::cout << "\n";
    								std::cout << "Enter: ";
    								if (std::cin >> choice)
    								{
    									std::cout << "\n";

    									if (choice == 1)
    									{
    										selectedMeal->SetDescription();
    										stateSafed = false;
    									}
    									else if (choice == 2)
    									{
    										selectedMeal->PrintNutrition();
    									}
    									else if (choice == 3) //shows meal not ingredient, Count zwischen eins und 2 funktioniert nicht richtig
    									{
    										std::vector<Supply*> inLoop;
    										inLoop = selectedMeal->getIngredients();
    										for (Supply* i : inLoop)
    										{
    												std::cout << i->getName() << '\n';
    										}
    									}
    			 						else if (choice == 4) //Modify Ingredients
    									{
    											int count;
    											std::vector<Supply*> Ingr;
    											Ingr = selectedMeal->getIngredients();
    											for (Supply* ingredient : Ingr)
    											{
    												std::cout << ingredient->getName() + " " + std::to_string(count) << std::endl;
    												++count;
    											}
    											int cs;
    											std::cout << "Where do you want to change something? Enter number: ";
    											if (std::cin >> cs)
    											{
    												Supply* selectedSupply = Ingr.at(cs);
    												bool exit2 = false;
    												while (!exit2)
    												{
    													int choice;
    													std::cout << "What do you want to do?" << std::endl;
    													std::cout << "                                                                          _ \n";
    													std::cout << "_________________________________________________________________________| |\n";
    													std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    													std::cout << "////| *1=Set Gramms Per Day* |//| *2=Show Nutrients* |/| *3=addGramms* |/|/|\n";
    													std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    													std::cout << "////| *4=Exit* |/////////////////////////////////////////////////////////|/|\n";
    													std::cout << "/////////////////////////////////////////////////////////////////////////|/|\n";
    													std::cout << "-------------------------------------------------------------------------|_|\n";
    													std::cout << "____________________________________________________________________________\n";
    													std::cout << "\n";
    													std::cout << "Enter: ";
    													if (std::cin >> choice)
    													{
    														std::cout << "\n";

    														if (choice == 1)
    														{
    																std::cout << "How many Gramms do you want to eat per day? ";
    																if (std::cin >> choice)
    																{
    																	selectedSupply->setGrammsPerDay(choice);
    																	stateSafed = false;
    																}
    																else
    																{
    																	std::cin.clear();
    																	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    																	std::cout << "You really should use Integers!\n";
    																}
    														}
    														else if (choice == 2)
    														{
    																selectedSupply->PrintSupplyNutrients();
    														}
    														else if (choice == 3)
    														{
    																selectedSupply->AddGramms();
    																stateSafed = false;
    														}
    														else if (choice == 4)
    														{
    																exit2 = true;
    														}
    													}
    													else
    													{
    														std::cin.clear();
    														std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    														std::cout << "You really should use Integers!\n";
    													}
    												}
    										  }
    											else
    											{
    												std::cin.clear();
    												std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    												std::cout << "You really should use Integers!\n";
    											}
    										}
    										else if (choice == 5)
    										{
                          std::string iName;
                          std::string sName;
                          int iTotalGramms;
                          int sTotalGramms;
                          bool end = false;
                          for (Supply* i : selectedMeal->getIngredients())
                          {
                            if (!end)
                            {
                              iName = i->getName();
                              iTotalGramms = i->getTotalGramms();
                              // std::cout << iName + "\n";
                              // std::cout << "iTotal: " + std::to_string(iTotalGramms) + "\n";
                              for (Supply* s : SupplyList)
                              {
                                sName = s->getName();
                                sTotalGramms = s->getTotalGramms();
                                if (iName == sName)
                                {
                                  if (sTotalGramms - iTotalGramms > 0)
                                  {
                                    s->_SubstractGramms(iTotalGramms);
                                  }
                                  else
                                  {
                                    std::cout << "Not enough Gramms in " + sName + '\n';
                                    end = true;
                                  }
                                }
                              }
                            }
                          }
                          if (!end)
                          {
                            std::cout << "Meal made \n";
                          }
    										}
    										else if (choice == 6)
    										{
    												int newPrice;
    												std::cout << "What is the new price?";
    												std::cin >> newPrice;
    												selectedMeal->setPrice(newPrice);
    												stateSafed = false;
    												break;
    										}
    										else if (choice == 7)
    										{
    												selectedMeal->AddRecipe();
    										}
                        else if (choice == 8)
    										{
    												//Add Ingredients
                            int Helper;
                            std::vector<Supply*> NewIngredients;
                            std::cout << "How many Ingredients do you want to add? ";
                						if (std::cin >> Helper)
                						{
                							for (int i = 0; i < Helper; i++)
                							{
                								Supply* idn = new Supply(supplyName, supplyKcal, supplyProtein, supplyFat, supplyCarbohydrate, supplyPrice, supplyTotalGramms);
                								NewIngredients.push_back(idn);
                							}
                              selectedMeal->AddIngredient(NewIngredients);
                							stateSafed = false;
                						}
                						else
                						{
                							std::cin.clear();
                							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                							std::cout << "Use the amount of Numbers you want to use." << std::endl;
                						}
    										}
                        else if (choice == 9)
    										{
    												exit = true;
    										}
                        else if (choice == 10)
                        {
                          selectedMeal->GetRecipe();
                        }
    									}
    									else
    									{
    										std::cin.clear();
    										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    										std::cout << "You really should use Integers!\n";
    									}
    								}
    							}
    							else
    							{
    								std::cin.clear();
    								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    								std::cout << "You really should use Integers!\n";
    							}
    						// }
    						// else
    						// {
    						// 	std::cin.clear();
    						// 	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    						// 	std::cout << "You really should use Integers!\n";
    						// }
    					}

              void ShowSupply()
              {
                int count = 0;
    						for (Supply* s : SupplyList)
    						{
    							std::cout << "_____________________________________________\n";
    							std::cout << "|/////////////////////////////////////////|/|\n";
    							std::cout << "|////| " + s->getName() + " |////|"  << std::endl;
    							std::cout << "|/////////////////////////////////////////|/|\n";
    							std::cout << "---------------------------------------------\n";
    						}
              }

              void ShowMeal()
              {
                for (Meal* m : MealList)
    						{
    							std::cout << "_____________________________________________\n";
    							std::cout << "|/////////////////////////////////////////|/|\n";
    							std::cout << "|////| " + m->getName() + " |////|\n";
    							std::cout << "|/////////////////////////////////////////|/|\n";
    							std::cout << "---------------------------------------------\n";
    						}
              }

              void GetDailyScreen(std::string date)
              {
                DailyPlan* dailyplan = new DailyPlan(date);
                Calendar.push_back(dailyplan);
              }

              void Safe(bool &stateSafed)
              {
                std::ofstream SafeFile("SafeFile.xml");
  							rapidxml::xml_document<> doc;
  							// xml declaration
  							rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
  							decl->append_attribute(doc.allocate_attribute("version", "1.0"));
  							decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
  							doc.append_node(decl);

  							// root node
  							rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "rootnode");
  							root->append_attribute(doc.allocate_attribute("version", "1.0"));
  							root->append_attribute(doc.allocate_attribute("type", "example"));
  							doc.append_node(root);

  							// child node
  							rapidxml::xml_node<>* objects = doc.allocate_node(rapidxml::node_element, "Objects");
  							root->append_node(objects);

  							for (Supply* s: SupplyList)
  							{
  									std::string name;
  									std::string NameString = s->getName();
  									const char* NameChar = NameString.c_str();
  									char *node_NameChar = doc.allocate_string(NameChar);

  									double PriceDouble;
  									PriceDouble = s->getPrice();
  									std::string PriceString = std::to_string(PriceDouble);
  									const char* DoubleChar = PriceString.c_str();
  									char *node_DoubleChar = doc.allocate_string(DoubleChar);

  									int KCal100Int;
  									KCal100Int = s->getKcal100g();
  									std::string KCal100String = std::to_string(KCal100Int);
  									const char* KCal100Char = KCal100String.c_str();
  									char *node_KCal100Char = doc.allocate_string(KCal100Char);

  									int Protein100Int;
  									Protein100Int = s->getProtein100g();
  									std::string Protein100String = std::to_string(Protein100Int);
  									const char* Protein100Char = Protein100String.c_str();
  									char *node_Protein100Char = doc.allocate_string(Protein100Char);

  									int Fat100Int;
  									Fat100Int = s->getFat100g();
  									std::string Fat100String = std::to_string(Fat100Int);
  									const char* Fat100Char = Fat100String.c_str();
  									char *node_Fat100Char = doc.allocate_string(Fat100Char);

  									int Carbohydrate100Int;
  									Carbohydrate100Int = s->getCarbohydrate100g();
  									std::string Carbohydrate100String = std::to_string(Carbohydrate100Int);
  									const char* Carbohydrate100Char = Carbohydrate100String.c_str();
  									char *node_Carbohydrate100Char = doc.allocate_string(Carbohydrate100Char);

  									int grammsPerDayInt;
  									grammsPerDayInt = s->getGrammsPerDay();
  									std::string grammsPerDayString = std::to_string(grammsPerDayInt);
  									const char* grammsPerDayChar = grammsPerDayString.c_str();
  									char *node_grammsPerDayChar = doc.allocate_string(grammsPerDayChar);

  									int totalGrammsInt;
  									totalGrammsInt = s->getTotalGramms();
  									std::string totalGrammsString = std::to_string(totalGrammsInt);
  									const char* totalGrammsChar = totalGrammsString.c_str();
  									char *node_totalGrammsChar = doc.allocate_string(totalGrammsChar);

  									rapidxml::xml_node<>* object = doc.allocate_node(rapidxml::node_element, "Supply");
  									object->append_attribute(doc.allocate_attribute("Name", node_NameChar));
  									object->append_attribute(doc.allocate_attribute("Price", node_DoubleChar));
  									object->append_attribute(doc.allocate_attribute("KCalP100", node_KCal100Char));
  									object->append_attribute(doc.allocate_attribute("ProteinP100g", node_Protein100Char));
  									object->append_attribute(doc.allocate_attribute("FatP100g", node_Fat100Char));
  									object->append_attribute(doc.allocate_attribute("CarbohydrateP100g", node_Carbohydrate100Char));
  									object->append_attribute(doc.allocate_attribute("GrammsPDay", node_grammsPerDayChar));
  									object->append_attribute(doc.allocate_attribute("totalGramms", node_totalGrammsChar));
  									objects->append_node(object);
  							}
  							for (Meal* m: MealList)//meals
  							{
  									std::string name;
  									std::string NameString = m->getName();
  									const char* NameChar = NameString.c_str();
  									char *node_NameChar = doc.allocate_string(NameChar);

  									std::string description;
  									std::string descriptionString = m->getDescription();
  									const char* descriptionChar = descriptionString.c_str();
  									char *node_descriptionChar = doc.allocate_string(descriptionChar);

  									double PriceDouble;
  									PriceDouble = m->getPrice();
  									std::string PriceString = std::to_string(PriceDouble);
  									const char* DoubleChar = PriceString.c_str();
  									char *node_DoubleChar = doc.allocate_string(DoubleChar);

  									int KCal;
  									KCal = m->getKcal();
  									std::string KCalString = std::to_string(KCal);
  									const char* KCalChar = KCalString.c_str();
  									char *node_KCalChar = doc.allocate_string(KCalChar);

  									int ProteinInt;
  									ProteinInt = m->getProtein();
  									std::string ProteinString = std::to_string(ProteinInt);
  									const char* ProteinChar = ProteinString.c_str();
  									char *node_ProteinChar = doc.allocate_string(ProteinChar);

  									int FatInt;
  									FatInt = m->getFat();
  									std::string FatString = std::to_string(FatInt);
  									const char* FatChar = FatString.c_str();
  									char *node_FatChar = doc.allocate_string(FatChar);

  									int CarbohydrateInt;
  									CarbohydrateInt = m->getCarbohydrate();
  									std::string CarbohydrateString = std::to_string(CarbohydrateInt);
  									const char* CarbohydrateChar = CarbohydrateString.c_str();
  									char *node_CarbohydrateChar = doc.allocate_string(CarbohydrateChar);

  									std::vector<Supply*> Ingredients = m->getIngredients();

  									rapidxml::xml_node<>* object = doc.allocate_node(rapidxml::node_element, "Meal");
  									object->append_attribute(doc.allocate_attribute("Name", node_NameChar));
  									object->append_attribute(doc.allocate_attribute("Description", node_descriptionChar));
  									object->append_attribute(doc.allocate_attribute("Price", node_DoubleChar));
  									object->append_attribute(doc.allocate_attribute("KCal", node_KCalChar));
  									object->append_attribute(doc.allocate_attribute("Protein", node_ProteinChar));
  									object->append_attribute(doc.allocate_attribute("Fat", node_FatChar));
  									object->append_attribute(doc.allocate_attribute("Carbohydrate", node_CarbohydrateChar));
  									objects->append_node(object);

  									for (Supply* i: Ingredients)
  									{
  										std::string name;
  										std::string NameString = i->getName();
  										const char* NameChar = NameString.c_str();
  										char *node_NameChar = doc.allocate_string(NameChar);

  										double PriceDouble;
  										PriceDouble = i->getPrice();
  										std::string PriceString = std::to_string(PriceDouble);
  										const char* DoubleChar = PriceString.c_str();
  										char *node_DoubleChar = doc.allocate_string(DoubleChar);

  										int KCalPMInt;
  										KCalPMInt = i->getKcalPM();
  										std::string KCalPMString = std::to_string(KCalPMInt);
  										const char* KCalPMChar = KCalPMString.c_str();
  										char *node_KCalPMChar = doc.allocate_string(KCalPMChar);

  										int ProteinPMInt;
  										ProteinPMInt = i->getProteinPM();
  										std::string ProteinPMString = std::to_string(ProteinPMInt);
  										const char* ProteinPMChar = ProteinPMString.c_str();
  										char *node_ProteinPMChar = doc.allocate_string(ProteinPMChar);

  										int FatPMInt;
  										FatPMInt = i->getFatPM();
  										std::string FatPMString = std::to_string(FatPMInt);
  										const char* FatPMChar = FatPMString.c_str();
  										char *node_FatPMChar = doc.allocate_string(FatPMChar);

  										int CarbohydratePMInt;
  										CarbohydratePMInt = i->getCarbohydratePM();
  										std::string CarbohydratePMString = std::to_string(CarbohydratePMInt);
  										const char* CarbohydratePMChar = CarbohydratePMString.c_str();
  										char *node_CarbohydratePMChar = doc.allocate_string(CarbohydratePMChar);

  										int totalGrammsInt;
  										totalGrammsInt = i->getTotalGramms();
  										std::string totalGrammsString = std::to_string(totalGrammsInt);
  										const char* totalGrammsChar = totalGrammsString.c_str();
  										char *node_totalGrammsChar = doc.allocate_string(totalGrammsChar);

  										rapidxml::xml_node<>* objectchild = doc.allocate_node(rapidxml::node_element, "Ingredients");
  										objectchild->append_attribute(doc.allocate_attribute("Name", node_NameChar));
  										objectchild->append_attribute(doc.allocate_attribute("Price", node_DoubleChar));
  										objectchild->append_attribute(doc.allocate_attribute("KCal", node_KCalPMChar));
  										objectchild->append_attribute(doc.allocate_attribute("Protein", node_ProteinPMChar));
  										objectchild->append_attribute(doc.allocate_attribute("Fat", node_FatPMChar));
  										objectchild->append_attribute(doc.allocate_attribute("Carbohydrate", node_CarbohydratePMChar));
  										objectchild->append_attribute(doc.allocate_attribute("TotalGramms", node_totalGrammsChar));
  										object->append_node(objectchild);
  									}
  							}
  							std::string xml_Doc;
  							rapidxml::print(std::back_inserter(xml_Doc), doc);

  							SafeFile << doc;
  							SafeFile.close();
  							doc.clear();
  							// rapidxml::xml_document<> doc;
  							std::ifstream file("SafeFile.xml");
  							std::stringstream buffer;
  							buffer << file.rdbuf();
  							std::string content(buffer.str());
  							// doc.parse<0>(&content[0]);
  							stateSafed = true;
              }

              void loadSafeState(void)
            	{
            			rapidxml::xml_document<> doc;
            			rapidxml::xml_node<> * root_node = NULL;
            			rapidxml::xml_node<> * objects_node = NULL;
            			rapidxml::xml_node<> * object_node = NULL;
            			rapidxml::xml_node<> * objectSub_node = NULL;
            			//READING THE SAFESTATE
            			std::ifstream SafeFile("SafeFile.xml");
            			std::vector<char> buffer((std::istreambuf_iterator<char>(SafeFile)), std::istreambuf_iterator<char>());
            			buffer.push_back('\0');

            			//PARSE buffer
            			doc.parse<0>(&buffer[0]);

            			//FIND ROOTNODE
            			root_node = doc.first_node("rootnode");
            			objects_node = root_node->first_node();
            			object_node = objects_node->first_node();
            			for (object_node = objects_node->first_node(); object_node; object_node = object_node->next_sibling())
            			{
            					std::string SupplyName = object_node->name();
            					if (SupplyName == "Supply")
            					{
            							std::string SupplyAttributeNameString = object_node->first_attribute("Name")->value();
            							std::string SupplyAttributePriceString = object_node->first_attribute("Price")->value();
            							double SupplyAttributePriceDouble = std::stod(SupplyAttributePriceString);
            							std::string SupplyAttributeKcalString = object_node->first_attribute("KCalP100")->value();
            							int SupplyAttributeKcalInt = std::stoi(SupplyAttributeKcalString);
            							std::string SupplyAttributeProteinString = object_node->first_attribute("ProteinP100g")->value();
            							int SupplyAttributeProteinInt = std::stoi(SupplyAttributeProteinString);
            							std::string SupplyAttributeFatString = object_node->first_attribute("FatP100g")->value();
            							int SupplyAttributeFatInt = std::stoi(SupplyAttributeFatString);
            							std::string SupplyAttributeCarbohydrateString = object_node->first_attribute("CarbohydrateP100g")->value();
            							int SupplyAttributeCarbohydrateInt = std::stoi(SupplyAttributeCarbohydrateString);
            							std::string SupplyAttributeGrammsPDayString = object_node->first_attribute("GrammsPDay")->value();
            							int SupplyAttributeGrammsPDayInt = std::stoi(SupplyAttributeGrammsPDayString);
            							std::string SupplyAttributeTotalGrammsString = object_node->first_attribute("totalGramms")->value();
            							int SupplyAttributeTotalGrammsInt = std::stoi(SupplyAttributeTotalGrammsString);

            							Supply* s = new Supply(SupplyAttributeNameString, SupplyAttributePriceDouble, SupplyAttributeKcalInt, SupplyAttributeProteinInt, SupplyAttributeFatInt, SupplyAttributeCarbohydrateInt, SupplyAttributeGrammsPDayInt, SupplyAttributeTotalGrammsInt);
            							SupplyList.push_back(s);
            					}
            					else if (SupplyName == "Meal")
            					{
            							std::string MealAttributeNameString = object_node->first_attribute("Name")->value();
            							std::string MealAttributeDescriptionString = object_node->first_attribute("Description")->value();
            							std::string MealAttributePriceString = object_node->first_attribute("Price")->value();
            							double MealAttributePriceDouble = std::stod(MealAttributePriceString);
            							std::string MealAttributeKcalString = object_node->first_attribute("KCal")->value();
            							int MealAttributeKcalInt = std::stoi(MealAttributeKcalString);
            							std::string MealAttributeProteinString = object_node->first_attribute("Protein")->value();
            							int MealAttributeProteinInt = std::stoi(MealAttributeProteinString);
            							std::string MealAttributeFatString = object_node->first_attribute("Fat")->value();
            							int MealAttributeFatInt = std::stoi(MealAttributeFatString);
            							std::string MealAttributeCarbohydrateString = object_node->first_attribute("Carbohydrate")->value();
            							int MealAttributeCarbohydrateInt = std::stoi(MealAttributeCarbohydrateString);
            							std::vector<Supply*> Ingredients;

            							objectSub_node = object_node->first_node();
            							for (objectSub_node = object_node->first_node(); objectSub_node; objectSub_node = objectSub_node->next_sibling())
            							{
            									std::string IngredientAttributeNameString = objectSub_node->first_attribute("Name")->value();
            									std::string IngredientAttributePriceString = objectSub_node->first_attribute("Price")->value();
            									double IngredientAttributePriceDouble = std::stod(IngredientAttributePriceString);
            									std::string IngredientAttributeKcalString = objectSub_node->first_attribute("KCal")->value();
            									int IngredientAttributeKcalInt = std::stoi(IngredientAttributeKcalString);
            									std::string IngredientAttributeProteinString = objectSub_node->first_attribute("Protein")->value();
            									int IngredientAttributeProteinInt = std::stoi(IngredientAttributeProteinString);
            									std::string IngredientAttributeFatString = objectSub_node->first_attribute("Fat")->value();
            									int IngredientAttributeFatInt = std::stoi(IngredientAttributeFatString);
            									std::string IngredientAttributeCarbohydrateString = objectSub_node->first_attribute("Carbohydrate")->value();
            									int IngredientAttributeCarbohydrateInt = std::stoi(IngredientAttributeCarbohydrateString);
            									std::string IngredientAttributeTotalGrammsString = objectSub_node->first_attribute("TotalGramms")->value();
            									int IngredientAttributeTotalGrammsInt = std::stoi(IngredientAttributeTotalGrammsString);

            									Supply* i = new Supply(IngredientAttributeNameString, IngredientAttributeKcalInt, IngredientAttributeProteinInt, IngredientAttributeFatInt, IngredientAttributeCarbohydrateInt, IngredientAttributePriceDouble, IngredientAttributeTotalGrammsInt);
            									Ingredients.push_back(i);
            							}
            							Meal* m = new Meal(MealAttributeNameString, Ingredients);
            							MealList.push_back(m);
            					}
            			}
            	}

              //Getters
              static Pantry& GetInstance()
              {
                static Pantry pantry_;
              	return pantry_;
              }

              std::vector<Supply*> getSupplyList() { return SupplyList; }
              std::vector<Meal*> getCreatedMeals() { return this->MealList; }
              //Setters
              // void SetSupplyList(const vector<Supply*> Supplies)
              // {
              //   SupplyList = Supplies;
              // }
};
