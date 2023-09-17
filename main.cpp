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
    std::vector<Person*> peoplePtrsFirstName;
    std::vector<Person*> peoplePtrsSSN;
    
    // Fills the vectors of Person Pointers with pointers to each Person in people
    pointPointerVector(peoplePtrsLastName,people);
    pointPointerVector(peoplePtrsFirstName,people);
    pointPointerVector(peoplePtrsSSN,people);

    int menuChoice = 0;
    do{
        displayMenu();
        menuChoice = getMenuOption(1,7);
        if(menuChoice == 1){
            sortByLastName(peoplePtrsLastName);
            displayMultiplePeople(peoplePtrsLastName);
        } else if(menuChoice == 2){
            sortByFirstName(peoplePtrsFirstName);
            displayMultiplePeople(peoplePtrsFirstName);
        } else if(menuChoice == 3){
            sortBySSN(peoplePtrsSSN);
            displayMultiplePeople(peoplePtrsSSN);
        } else if(menuChoice == 4){
            std::string input;
            std::cout << "Enter last name: " << std::flush;
            getline(std::cin,input);
            Person * ptrToPerson = nullptr;
            ptrToPerson = searchByLastName(peoplePtrsLastName,input);
            if(ptrToPerson == nullptr){
                std::cout << "No last name matches \'" << input << "\'." << std::endl;
            } else {
                displayPerson(ptrToPerson);
            }
        } else if(menuChoice == 5){
            std::string input;
            std::cout << "Enter first name: " << std::flush;
            getline(std::cin,input);
            Person * ptrToPerson = nullptr;
            ptrToPerson = searchByFirstName(peoplePtrsFirstName,input);
            if(ptrToPerson == nullptr){
                std::cout << "No first name matches \'" << input << "\'." << std::endl;
            } else {
                displayPerson(ptrToPerson);
            }
        } else if(menuChoice == 6){
            std::string input;
            std::cout << "Enter SSN (with or without dashes): " << std::flush;
            getline(std::cin,input);
            Person * ptrToPerson = nullptr;
            ptrToPerson = searchBySSN(peoplePtrsLastName,input);
            if(ptrToPerson == nullptr){
                std::cout << "No SSN matches \'" << input << "\'." << std::endl;
            } else {
                displayPerson(ptrToPerson);
            }
        } else {exit(1);}
    } while(menuChoice != 7);
    return 0;
}