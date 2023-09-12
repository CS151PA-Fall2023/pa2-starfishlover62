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

const int NUM_TESTS = 5;

class Person {

public:
Person() : Person("John","Doe",0,"123-45-6789"){};
Person(std::string first, std::string last, int id, std::string ssn);
Person(std::string first, std::string last, int id, std::string ssn, int scores[]);
Person(const Person & right);
Person& operator=(const Person & right);
bool operator==(const Person & right);
~Person(){
    if(testScores != 0 && testScores != nullptr){
        std::cout << "Array Pointer: " << testScores << std::endl;
        delete [] testScores;
    }
    testScores = nullptr;
}

void setFirstName(std::string first){
    firstName = first;
}
void setLastName(std::string last){
    lastName = last;
}
void setId(int id){
    this->id = id;
}
void setSsn(std::string ssn){
    this->ssn = ssn;
}
void setTests(int scores[]);
void setTest(int score, unsigned testIndex);

std::string getFirstName(){
    return firstName;
}

std::string getLastName(){
    return lastName;
}

int getId(){
    return id;
}

int* getScores(){
    return testScores;
}

double averageScore();

std::string letterGrade();

std::string getSsn(){
    return ssn;
}




private:
std::string firstName, lastName, ssn;
int id;
int * testScores;

};


void displayPerson(Person *obj);


#endif