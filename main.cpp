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

#include "index.h"

int main() {

    Person joe("joe","gatto",1,"123-45-6789");
    int scores[5] = {100,100,-100,200,100};
    joe.setTests(scores);
    displayPerson(&joe);



    return 0;
}