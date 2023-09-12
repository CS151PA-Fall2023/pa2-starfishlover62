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
