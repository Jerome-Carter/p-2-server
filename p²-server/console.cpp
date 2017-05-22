//
//  console.cpp
//  p²
//
//  Created by James Carter on 2/23/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "console.h"

namespace App {
    void Console::in(std::string& input) {
        std::getline (std::cin, input);
    }
    void Console::out(std::string message) {
        std::cout << message << std::endl;
    }
    void Console::prompt(std::string question, std::string& answer, bool printValue, const std::string& msgPrefix, bool hasSuffix, const std::string& msgSuffix) {
        std::cout << question;
        in(answer);
        if (printValue != false) {
            std::cout << msgPrefix;
            std::cout << answer;
            if (hasSuffix != false) std::cout << msgSuffix << std::endl; else std::cout << std::endl;
        }
    }
}
