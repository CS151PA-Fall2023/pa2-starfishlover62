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
#include <cstdlib>

#include "Person.h"
#include "index.h"

int main() {

    // Creates vector of type Person, then fills it in with data from csv file at path
    std::vector<Person> people;
    std::string path = "grades.csv";
    getPersonsFromCSV(people,path);

    // Creates two vectors of Person pointers that will be sorted via different criteria
    std::vector<Person*> peoplePtrsLastName;
    std::vector<Person*> peoplePtrsSSN;
    
    // Fills the vectors of Person Pointers with pointers to each Person in people
    pointPointerVector(peoplePtrsLastName,people);
    pointPointerVector(peoplePtrsSSN,people);

    int menuChoice = 0;
    do{
        displayMenu();
        menuChoice = getMenuOption(1,5);
        if(menuChoice == 1){
            sortByLastName(peoplePtrsLastName);
            displayMultiplePeople(peoplePtrsLastName);
        } else if(menuChoice == 2){
           
        } else if(menuChoice == 3){

        } else if(menuChoice == 4){
            
        } else {exit(1);}
    } while(menuChoice != 5);
    return 0;
}