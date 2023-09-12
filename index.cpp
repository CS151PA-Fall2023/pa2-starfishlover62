/**
 * @file index.cpp
 * @author Josh Gillum
 * @brief 
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "index.h"

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





void displayPerson(Person *obj){
    std::cout << std::setw(3) << std::right << obj->getId() << std::setw(12) 
        << std::right << obj->getLastName() << std::setw(12)
        << std::right << obj->getFirstName() << std::setw(13) 
        << obj->getSsn() <<  std::setw(4) << obj->getGrade() << std::endl;
   /*
    std::cout << obj->getId() << std::endl;
    std::cout << obj->getLastName() << std::endl;
    std::cout << obj->getFirstName() << std::endl;
    std::cout << obj->getSsn() << std::endl;
    std::cout << obj->getGrade() << std::endl;
    */

}


/**
 * @brief Opens a file for reading
 * 
 * @param file, ifstream object for opening the file
 * @param path, string of the path to the file
 */
void openFile(std::ifstream &file, std::string path){
    file.open(path);
    if(!file){ // Checks if file was opened successfully
        std::cout << "File at path /'" << path << "/' could not be opened."
        << " Terminating program..." << std::endl;
        exit(1);
    }
}


/**
 * @brief Opens a file for writing
 * 
 * @param file, ofstream object for opening the file
 * @param path, string of the path to the file
 */
void openFile(std::ofstream &file, std::string path){
    file.open(path);
    if(!file){ // Checks if file was opened successfully
        std::cout << "File at path /'" << path << "/' could not be opened."
        << " Terminating program..." << std::endl;
        exit(1);
    }
}


/**
 * @brief Converts the string data type into the integer type.
 * Function will skip over any characters that are not a number, or negative sign
 * Once a decimal is encountered, the function stops reading the string
 * 
 * @param str, the string to be converted
 * @return int, the number as an integer
 */
int stringToInt(std::string str){
    int num = 0; // Stores value to be returned
    bool negative = false;
    // Below loop repeats so long as the value at the index is not a decimal, and
    // the index is less than length of the string
    for(unsigned i = 0; str[i] != '.' && (i < str.length()); ++i){
        if(str[i] >= '0' && str[i] <= '9'){
            num *= 10; // Multiplies the working number by 10 to increase its place by one to the left
            num += (str[i] - '0'); // Adds the current number to the working number
        } else if(str[i] == '-'){
            negative = true;
        }
    }
    if(negative){
        num *= -1;
    }
    return num;
}


/**
 * @brief Returns whether a string only contains whitespace characters. Whitespace characters
 * are defined in this function as spaces " ", tabs "\t", vertical tabs "\v", carriage returns "\r", and newlines "\n"
 * 
 * @param str, the string to be checked
 * @return true, the string only contains whitespace
 * @return false, the string has other characters
 */
bool stringOnlyWhitespace(std::string str){
    if(str.length() <= 0){
        return true;
    }
    // Loops through each character and checks if it is one other
    // than the whitespace characters. If it is, returns false
    for(unsigned i = 0; i < str.length(); ++i){
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\v' && str[i] != '\r' && str[i] != '\n'){
            return false;
        }
    }

    // If the loop finishes without finding a non-whitespace character,
    // true will be returned
    return true;
}


void getPersonsFromCSV(std::vector<Person> &vec, std::string path){
    std::ifstream infile;
    openFile(infile,path);
    if(infile){
        std::string line;
        do {
            getline(infile,line);
        } while(stringOnlyWhitespace(line));
        while(infile.peek() != EOF){
            getline(infile,line);
            if(!stringOnlyWhitespace(line)){
                std::string section = "";
                bool inQuotes = false;
                int item = 0;
                Person currentPerson;
                int scores[NUM_TESTS];
                for(unsigned i = 0; i < line.length(); ++i){
                    if(((line[i] == ',' || line[i] == ';') && !inQuotes) || i >= line.length()-1){
                        if(i >= line.length()-1){
                            section += line[i];
                        }
                        if(item == 0){
                            currentPerson.setId(stringToInt(section));
                        } else if(item == 1){
                            currentPerson.setLastName(section);
                        } else if(item == 2){
                            currentPerson.setFirstName(section);
                        } else if(item == 3){
                            currentPerson.setSsn(section);
                        } else if(item == 4){
                            scores[0] = stringToInt(section);
                            currentPerson.setTests(scores);
                        } else if(item == 5){
                            scores[1] = stringToInt(section);
                            currentPerson.setTests(scores);
                        } else if(item == 6){
                            scores[2] = stringToInt(section);
                            currentPerson.setTests(scores);
                        } else if(item == 7){
                            scores[3] = stringToInt(section);
                            currentPerson.setTests(scores);
                        } else if(item == 8){
                            scores[4] = stringToInt(section);
                            currentPerson.setTests(scores);
                        } else if(item == 9){
                            currentPerson.setGrade(section);
                        }

                        section = "";
                        item++;
                    } else {
                        section += line[i];
                    }
                }
                vec.push_back(currentPerson);
            }
        }
    }
}
