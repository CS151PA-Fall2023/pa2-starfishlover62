#include "Person.h"

Person::Person(std::string first, std::string last, int id, std::string ssn){
    testScores = nullptr;
    firstName = first;
    lastName = last;
    this->id = id;
    this->ssn = ssn;
    testScores = new int[NUM_TESTS] {0};
    grade = letterGrade();

}


Person::Person(std::string first, std::string last, int id, std::string ssn, int scores[], std::string letter) : Person(first,last,id,ssn) {
    for(int i = 0; i < NUM_TESTS; ++i){
        if(scores[i] >= 0 && scores[i] <= 200){
            *(testScores+i) = scores[i];
        }
    }
}

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

void Person::setTest(int score, unsigned testIndex){
    if((score >= 0 && score <= 200) && (testIndex >= 0 && testIndex < NUM_TESTS)){
        *testScores = score;
    }
    grade = letterGrade();
}


double Person::averageScore(){
    double avg = 0;
    for(int i = 0; i < NUM_TESTS; ++i){
        avg += *(testScores+i);
    }
    return avg/NUM_TESTS;
}

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