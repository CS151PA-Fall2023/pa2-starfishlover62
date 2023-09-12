/**
 * @file main.cpp
 * @author Josh Gillum
 * @brief 
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>

#include "Person.h"
#include "index.h"

int main() {

    std::vector<Person> people;
    std::string path = "grades.csv";
    getPersonsFromCSV(people,path);
    displayMultiplePeople(people);


    return 0;
}