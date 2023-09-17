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

void displayMultiplePeople(std::vector <Person> &people, int size){
    if(size < 0){
        for(unsigned i = 0; i < people.size(); ++i){
            displayPerson(&people[i]);
        }
    } else{
        unsigned sizeU = size;
        for(unsigned i = 0; i < sizeU && i < people.size(); ++i){
            displayPerson(&people[i]);
        }
    }
}

void displayMultiplePeople(std::vector <Person*> &people, int size){
    if(size < 0){
        for(unsigned i = 0; i < people.size(); ++i){
            displayPerson(people[i]);
        }
    } else{
        unsigned sizeU = size;
        for(unsigned i = 0; i < sizeU && i < people.size(); ++i){
            displayPerson(people[i]);
        }
    }
}


/**
 * @brief Removes all characters from a string that are not letters
 * 
 * @param str, the string to be converted
 */
void keepOnlyLetters(std::string & str){
    std::string newString = ""; // letters are added to this when they are encountered
    for(unsigned i = 0; i < str.length(); ++i){
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')){ // If the letter is A-Z or a-z
            newString += str[i];
        }
    }
    str = newString; // The original string is then given the value of the string with only letters
}


/**
 * @brief Removes all characters from a string that are not numbers
 * 
 * @param str, the string to be converted
 */
void keepOnlyNumbers(std::string & str){
    std::string newString = ""; // numbers are added to this when they are encountered
    for(unsigned i = 0; i < str.length(); ++i){
        if(str[i] >= '0' && str[i] <= '9'){ // If the character is 0-9
            newString += str[i];
        }
    }
    str = newString; // The original string is then given the value of the string with only letters
}


void convertStringToLower(std::string &str){
    for(unsigned i = 0; i < str.length(); ++i){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] -= 'A';
            str[i] += 'a';
        }
    }
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



/**
 * @brief Prompts the user for a menu option. 
 * 
 * @param min, the minimum value for the menu option
 * @param max, the maximum value for the menu option
 * @return int, value that the user selected
 */
int getMenuOption(unsigned min, unsigned max){
    std::string input;
    unsigned output;
    do {
        std::cout << "Enter a menu option (" << min << "-" << max << "): ";
        input = "";
        std::getline(std::cin,input);
        if(!stringOnlyWhitespace(input)){ // Makes sure that the input was not empty
            output = stringToInt(input);
        }
    } while(output < min || output > max);
    return output;
}


/**
 * @brief Displays the menu
 * 
 */
void displayMenu(){
    std::cout << std::endl << std::endl;
    std::cout << "Person Lookup:" << std::endl;
    std::cout << " 1. Print data in ascending order by last name" << std::endl;
    std::cout << " 2. Print data in ascending order by first name" << std::endl;
    std::cout << " 3. Print data in ascending order by SSN" << std::endl;
    std::cout << " 4. Search by last name" << std::endl;
    std::cout << " 5. Search by first name" << std::endl;
    std::cout << " 6. Search by SSN" << std::endl;
    std::cout << " 7. Exit" << std::endl;
}


void pointPointerVector(std::vector<Person*> &ptrs, std::vector<Person> &people){
    ptrs.clear();
    Person * ptr;
    for(unsigned i = 0; i < people.size(); ++i){
        ptr = &(people[i]);
        ptrs.push_back(ptr);
    }
}

void sortByLastName(std::vector<Person*> &ptrs, bool descending){
    unsigned swapIndex = 0;
    for(unsigned i = 0; i < ptrs.size(); ++i){
        swapIndex = i;
        std::string swapStr = ptrs[swapIndex]->getLastName();
        convertStringToLower(swapStr);
        keepOnlyLetters(swapStr);
        for(unsigned j = i+1; j < ptrs.size(); ++j){
            std::string tempStr = ptrs[j]->getLastName();
            convertStringToLower(tempStr);
            keepOnlyLetters(tempStr);
            if(descending){
                if(tempStr>swapStr){
                    swapIndex = j;
                    swapStr = tempStr;
                }
            } else {
                if(tempStr<swapStr){
                    swapIndex = j;
                    swapStr = tempStr;
                }
            }
        }
        if(swapIndex != i){
            Person * tempPtr = ptrs[i];
            ptrs[i] = ptrs[swapIndex];
            ptrs[swapIndex] = tempPtr;
        }
    }
}

void sortByFirstName(std::vector<Person*> &ptrs, bool descending){
    unsigned swapIndex = 0;
    for(unsigned i = 0; i < ptrs.size(); ++i){
        swapIndex = i;
        std::string swapStr = ptrs[swapIndex]->getFirstName();
        convertStringToLower(swapStr);
        keepOnlyLetters(swapStr);
        for(unsigned j = i+1; j < ptrs.size(); ++j){
            std::string tempStr = ptrs[j]->getFirstName();
            convertStringToLower(tempStr);
            keepOnlyLetters(tempStr);
            if(descending){
                if(tempStr>swapStr){
                    swapIndex = j;
                    swapStr = tempStr;
                }
            } else {
                if(tempStr<swapStr){
                    swapIndex = j;
                    swapStr = tempStr;
                }
            }
        }
        if(swapIndex != i){
            Person * tempPtr = ptrs[i];
            ptrs[i] = ptrs[swapIndex];
            ptrs[swapIndex] = tempPtr;
        }
    }
}

void sortBySSN(std::vector<Person*> &ptrs, bool descending){
    unsigned swapIndex = 0;
    for(unsigned i = 0; i < ptrs.size(); ++i){
        swapIndex = i;
        std::string swapStr = ptrs[swapIndex]->getSsn();
        keepOnlyNumbers(swapStr);
        for(unsigned j = i+1; j < ptrs.size(); ++j){
            std::string tempStr = ptrs[j]->getSsn();
            keepOnlyNumbers(tempStr);
            if(descending){
                if(tempStr>swapStr){
                    swapIndex = j;
                    swapStr = tempStr;
                }
            } else {
                if(tempStr<swapStr){
                    swapIndex = j;
                    swapStr = tempStr;
                }
            }
        }
        if(swapIndex != i){
            Person * tempPtr = ptrs[i];
            ptrs[i] = ptrs[swapIndex];
            ptrs[swapIndex] = tempPtr;
        }
    }
}


Person * searchByLastName(std::vector<Person*> &ptrs, std::string lastName){
    keepOnlyLetters(lastName);
    convertStringToLower(lastName);
    if(ptrs.size() > 0 && lastName.size() > 0){
        sortByLastName(ptrs);
        std::string checkName;
        int low = 0;
        int high = (ptrs.size()) - 1;
        int mid = 0;
        while (low <= high){
            mid = (low + high) / 2;
            checkName = ptrs[mid]->getLastName();
            keepOnlyLetters(checkName);
            convertStringToLower(checkName);
            if(lastName == checkName){
                Person * ptrReturn = ptrs[mid];
                return ptrReturn;
            } else if(lastName < checkName){
                high = mid + -1;
            } else if(lastName > checkName){
                low = mid + 1;
            }
        }
    }
    return nullptr;
}

Person * searchByFirstName(std::vector<Person*> &ptrs, std::string firstName){
    keepOnlyLetters(firstName);
    convertStringToLower(firstName);
    if(ptrs.size() > 0 && firstName.size() > 0){
        sortByFirstName(ptrs);
        std::string checkName;
        int low = 0;
        int high = (ptrs.size()) - 1;
        int mid = 0;
        while (low <= high){
            mid = (low + high) / 2;
            checkName = ptrs[mid]->getFirstName();
            keepOnlyLetters(checkName);
            convertStringToLower(checkName);
            if(firstName == checkName){
                Person * ptrReturn = ptrs[mid];
                return ptrReturn;
            } else if(firstName < checkName){
                high = mid + -1;
            } else if(firstName > checkName){
                low = mid + 1;
            }
        }
    }
    return nullptr;
}

Person * searchBySSN(std::vector<Person*> &ptrs, std::string ssn){
    keepOnlyNumbers(ssn);
    if(ptrs.size() > 0 && ssn.size() > 0){
        sortBySSN(ptrs);
        std::string checkSSN;
        int low = 0;
        int high = (ptrs.size()) - 1;
        int mid = 0;
        while (low <= high){
            mid = (low + high) / 2;
            checkSSN = ptrs[mid]->getSsn();
            keepOnlyNumbers(checkSSN);
            if(ssn == checkSSN){
                Person * ptrReturn = ptrs[mid];
                return ptrReturn;
            } else if(ssn < checkSSN){
                high = mid + -1;
            } else if(ssn > checkSSN){
                low = mid + 1;
            }
        }
    }
    return nullptr;
}
