/**
 * @file Person.cpp
 * @author Josh Gillum
 * @brief Function definitions for Person class
 * @version 1.0
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Person.h"


/**
 * @brief Construct a new Person:: Person object
 * 
 * @param first, first name
 * @param last, last name
 * @param id, id number
 * @param ssn, ssn number
 */
Person::Person(std::string first, std::string last, int id, std::string ssn){
    testScores = nullptr;
    firstName = first;
    lastName = last;
    this->id = id;
    this->ssn = ssn;
    testScores = new int[NUM_TESTS] {0};
    grade = letterGrade();

}


/**
 * @brief Construct a new Person:: Person object
 * 
 * @param first, first name
 * @param last, last name
 * @param id, id number
 * @param ssn, ssn number
 * @param scores, array of scores
 * @param letter, letter grade
 */
Person::Person(std::string first, std::string last, int id, std::string ssn, int scores[], std::string letter) : Person(first,last,id,ssn) {
    for(int i = 0; i < NUM_TESTS; ++i){
        if(scores[i] >= 0 && scores[i] <= 200){
            *(testScores+i) = scores[i];
        }
    }
}


/**
 * @brief Construct a new Person:: Person object
 * 
 * @param right, person object being copied
 */
Person::Person(const Person & right){
    this->testScores = right.testScores;
    this->firstName = right.firstName;
    this->lastName = right.lastName;
    this->id = right.id;
    this->ssn = right.ssn;
    testScores = new int[NUM_TESTS] {0};
    for(int i = 0; i < NUM_TESTS; ++i){
        *(testScores + i) = *(right.testScores+i);
    }
    this->grade = right.grade;
}


Person::~Person(){
    if(testScores != 0 && testScores != nullptr){
        delete [] testScores;
    }
    testScores = nullptr;
}

/**
 * @brief Assignment operator overload
 * 
 * @param right, person object on the right side of the operator
 * @return Person&, pointer to this object
 */
Person& Person::operator=(const Person & right){
    delete [] testScores;
    this->testScores = right.testScores;
    this->firstName = right.firstName;
    this->lastName = right.lastName;
    this->id = right.id;
    this->ssn = right.ssn;
    testScores = new int[NUM_TESTS] {0};
    for(int i = 0; i < NUM_TESTS; ++i){
        *(testScores + i) = *(right.testScores+i);
    }
    this->grade = right.grade;
    return *this;
}


/**
 * @brief Comparison operator overloard
 * 
 * @param right, object on the right side of the operator
 * @return true, the objects are equal
 * @return false, the objects are not equal
 */
bool Person::operator==(const Person & right){
    if(this->firstName != right.firstName){return false;}
    if(this->lastName != right.lastName){return false;}
    if(this->id != right.id){return false;}
    if(this->ssn != right.ssn){return false;}
    if(this->grade != right.grade){return false;}
    for(int i = 0; i < NUM_TESTS; ++i){
        if(*(testScores + i) != *(right.testScores+i)){return false;}
    }
    return true;
}


/**
 * @brief Sets the test scores array
 * 
 * @param scores, the scores
 */
void Person::setTests(int scores[]){
    for(int i = 0; i < NUM_TESTS; ++i){
        if(scores[i] >= 0 && scores[i] <= 200){
            *(testScores+i) = scores[i];
        } else {
            *(testScores+i) = 0;
        }
    }
    grade = letterGrade();
}


/**
 * @brief Sets the value of a specific test
 * 
 * @param score, the test score
 * @param testIndex, the test number
 */
void Person::setTest(int score, unsigned testIndex){
    if((score >= 0 && score <= 200) && (testIndex >= 0 && testIndex < NUM_TESTS)){
        *testScores = score;
    }
    grade = letterGrade();
}


/**
 * @brief Returns the average of the scores array
 * 
 * @return double, the average score
 */
double Person::averageScore(){
    double avg = 0;
    for(int i = 0; i < NUM_TESTS; ++i){
        avg += *(testScores+i);
    }
    return avg/NUM_TESTS;
}


/**
 * @brief Calculates a letter grade based off of the average test score
 * 
 * @return std::string, the letter grade
 */
std::string Person::letterGrade(){
    std::string grade;
    double score = averageScore();
    if(score >= 96){
        return "A+";
    } else if(score >= 93){
        return "A";
    } else if(score >= 90){
        return "A-";
    } else if(score >= 86){
        return "B+";
    } else if(score >= 83){
        return "B";
    } else if(score >= 80){
        return "B-";
    } else if(score >= 76){
        return "C+";
    } else if(score >= 73){
        return "C";
    } else if(score >= 70){
        return "C-";
    } else if(score >= 66){
        return "D+";
    } else if(score >= 63){
        return "D";
    } else if(score >= 60){
        return "D-";
    } else {
        return "F";
    }
}