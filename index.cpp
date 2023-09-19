/**
 * @file index.cpp
 * @author Josh Gillum
 * @brief Function definitions
 * @version 1.0
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "index.h"


/**
 * @brief Displays column headers for information
 * 
 */
void displayHeader(){
    std::cout << std::endl << std::setw(3) << std::right << "ID" << std::setw(12) 
        << std::right << "Last Name" << std::setw(12)
        << std::right << "First Name" << std::setw(13) 
        << "SSN    " <<  std::setw(4) << "Grade" << std::endl;
}


/**
 * @brief Displays the id, last name, first name, ssn, and grade of a person object
 * 
 * @param obj, the object whose information is to be displayed
 */
void displayPerson(Person *obj){
    std::cout << std::setw(3) << std::right << obj->getId() << std::setw(12) 
        << std::right << obj->getLastName() << std::setw(12)
        << std::right << obj->getFirstName() << std::setw(13) 
        << obj->getSsn() <<  std::setw(4) << obj->getGrade() << std::endl;
}


/**
 * @brief Displays multiple person objects in a column
 * 
 * @param people, a vector containing person objects
 * @param size, the number of objects out of the vector to be displayed. If a
 * value less than 0 is passed, all objects of the vector will be displayed
 */
void displayMultiplePeople(std::vector <Person> &people, int size){
    displayHeader();
    if(size < 0){ // Displays entire vector
        for(unsigned i = 0; i < people.size(); ++i){
            displayPerson(&people[i]);
        }
    } else{ // Displays number of elements equal to size
        unsigned sizeU = size; 
        for(unsigned i = 0; i < sizeU && i < people.size(); ++i){
            displayPerson(&people[i]);
        }
    }
}


/**
 * @brief Displays multiple person objects in a column
 * 
 * @param people, the vector containing pointers to person objects
 * @param size, the number of objects to be displayed. If a value less than 0 is passed,
 * all objects in the vector will be displayed
 */
void displayMultiplePeople(std::vector <Person*> &people, int size){
    displayHeader();
    if(size < 0){ // Displays entire vector
        for(unsigned i = 0; i < people.size(); ++i){
            displayPerson(people[i]);
        } 
    } else{ // Displays number of elements equal to size
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


/**
 * @brief Converts an entire string to lowercase. All none uppercase characters
 * are left as is
 * 
 * @param str, the string to be converted. Directly modifies the string passed to it
 */
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


/**
 * @brief Creates and fills out person objects from a csv file
 * 
 * @param vec, the vector that will hold the Person objects
 * @param path, the path to the csv file, as a string
 */
void getPersonsFromCSV(std::vector<Person> &vec, std::string path){
    // Opens file for reading, and makes sure it was successfully opened
    std::ifstream infile;
    openFile(infile,path);
    if(infile){
        std::string line;

        // Reads all blank lines at the beginning of the file,
        // as well as the first non-blank line. Does not save
        // any of these lines
        do {
            getline(infile,line);
        } while(stringOnlyWhitespace(line));

        while(infile.peek() != EOF){
            // Reads the line, then makes sure that it is not blank
            getline(infile,line);
            if(!stringOnlyWhitespace(line)){
                std::string section = ""; // Section of the line being worked with (one data piece)
                bool inQuotes = false; // If the section is enclosed in quotes (allows spaces in names)
                int item = 0; // Data piece being read, allows function to know which piece of information it is
                Person currentPerson; // Person object to be filled with read data
                int scores[NUM_TESTS]; // Array to temporarily hold all the test scores of the person

                // Loops through entire line, character-by-character
                for(unsigned i = 0; i < line.length(); ++i){
                    // Checks if a comma or semicolon is reached and it is not enclosed in quotes. Also
                    // checks if the end if the line has been reached
                    if(((line[i] == ',' || line[i] == ';') && !inQuotes) || i >= line.length()-1){
                        // If at the end of the line, adds the last character to the section string
                        if(i >= line.length()-1){
                            section += line[i];
                        }
                        
                        // Adds information to the object, based off of the value of item
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

                        // Resets the section string for the next data piece and moves to the next data item
                        section = "";
                        item++;
                    } else { // If not at the point of adding data to object, adds character to section string
                        section += line[i];
                    }
                }
                // Adds the filled out object to the vector
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


/**
 * @brief Points pointers to each Person object in a vector
 * 
 * @param ptrs, the vector to be filled with the pointers
 * @param people, the vector containing person objects to be pointed to
 */
void pointPointerVector(std::vector<Person*> &ptrs, std::vector<Person> &people){
    ptrs.clear();
    Person * ptr;
    for(unsigned i = 0; i < people.size(); ++i){
        ptr = &(people[i]);
        ptrs.push_back(ptr);
    }
}


/**
 * @brief Sorts a vector of pointers to person objects by last name
 * 
 * @param ptrs, the vector of pointers
 * @param descending, whether to sort in descending order, default is false,
 * so default is ascending order
 */
void sortByLastName(std::vector<Person*> &ptrs, bool descending){
    unsigned swapIndex = 0; // Index of the string that comes first alphabetically
    for(unsigned i = 0; i < ptrs.size(); ++i){
        // All names will be compared without spaces and in all lowercase letters
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
        // Swaps the two pointers
        if(swapIndex != i){
            Person * tempPtr = ptrs[i];
            ptrs[i] = ptrs[swapIndex];
            ptrs[swapIndex] = tempPtr;
        }
    }
}

/**
 * @brief Sorts of vector of pointers to person objects by first name
 * 
 * @param ptrs, the vector of pointers to person objects to be sorter
 * @param descending, true if the objects are to be sorted in descending order,
 * defualt is false, which is ascending order
 */
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


/**
 * @brief Sorts a vector of pointers to person objects by ssn
 * 
 * @param ptrs, the vector of pointers to person objects to be sorted
 * @param descending, true to sort in descending order. Default is false, which is ascending order
 */
void sortBySSN(std::vector<Person*> &ptrs, bool descending){
    unsigned swapIndex = 0;
    for(unsigned i = 0; i < ptrs.size(); ++i){
        swapIndex = i;
        std::string swapStr = ptrs[swapIndex]->getSsn();
        keepOnlyNumbers(swapStr); // Removes all non-digit characters from the string
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


/**
 * @brief Searched a vector of pointers to person objects for a specified last name
 * 
 * @param ptrs, the vector to be searched
 * @param lastName, the name being searched for
 * @return Person*, a pointer to the object containing the name. In the case
 * of multiple objects sharing the same name, the object first encountered with this name
 * will be returned
 */
Person * searchByLastName(std::vector<Person*> &ptrs, std::string lastName){
    // Removes all non alphabetic characters, and converts all of them to lowercase for comparison
    keepOnlyLetters(lastName);
    convertStringToLower(lastName);
    if(ptrs.size() > 0 && lastName.size() > 0){
        sortByLastName(ptrs); // Sorts the vector for binary search
        std::string checkName;
        int low = 0;
        int high = (ptrs.size()) - 1;
        int mid = 0;
        while (low <= high){ // Binary search
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


/**
 * @brief Searched a vector of pointers to person objects for a specified first name
 * 
 * @param ptrs, the vector to be searched
 * @param lastName, the name being searched for
 * @return Person*, a pointer to the object containing the name. In the case
 * of multiple objects sharing the same name, the object first encountered with this name
 * will be returned
 */
Person * searchByFirstName(std::vector<Person*> &ptrs, std::string firstName){
    keepOnlyLetters(firstName);
    convertStringToLower(firstName);
    if(ptrs.size() > 0 && firstName.size() > 0){
        sortByFirstName(ptrs); // Sorts for binary search
        std::string checkName;
        int low = 0;
        int high = (ptrs.size()) - 1;
        int mid = 0;
        while (low <= high){ // Binary search
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


/**
 * @brief Searched a vector of pointers to person objects for a specified ssn
 * 
 * @param ptrs, the vector to be searched
 * @param lastName, the ssn being searched for
 * @return Person*, a pointer to the object containing the ssn. In the case
 * of multiple objects sharing the same name, the object first encountered with this name
 * will be returned
 */
Person * searchBySSN(std::vector<Person*> &ptrs, std::string ssn){
    keepOnlyNumbers(ssn); // Removes all non-digit characters (ex: dashes)
    if(ptrs.size() > 0 && ssn.size() > 0){
        sortBySSN(ptrs); // Sorts for binary search
        std::string checkSSN;
        int low = 0;
        int high = (ptrs.size()) - 1;
        int mid = 0;
        while (low <= high){ // Binary search
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
