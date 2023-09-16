/**
 * @file index.h
 * @author Josh Gillum
 * @brief 
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INDEX_H
#define INDEX_H
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Person.h"




void openFile(std::ifstream &file, std::string path);
void openFile(std::ofstream &file, std::string path);
int stringToInt(std::string str);
bool stringOnlyWhitespace(std::string str);
void keepOnlyLetters(std::string &str);
void keepOnlyNumbers(std::string &str);
void convertStringToLower(std::string &str);

void getPersonsFromCSV(std::vector<Person> &vec, std::string path);
void displayPerson(Person *obj);
void displayMultiplePeople(std::vector <Person> &people, int size = -1);
void displayMultiplePeople(std::vector <Person*> &people, int size = -1);

int getMenuOption(unsigned min, unsigned max);
void displayMenu();

void pointPointerVector(std::vector<Person*> &ptrs, std::vector<Person> &people);
void sortByLastName(std::vector<Person*> &ptrs, bool descending = false);
void sortBySSN(std::vector<Person*> &ptrs, bool descending = false);

bool searchByLastName(std::vector<Person*> &ptrs, std::string lastName);

#endif