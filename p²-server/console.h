//
//  console.h
//  p²
//
//  Created by James Carter on 2/23/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <iostream>

namespace App {
    class Console {
    public:
        static void in(std::string& input);
        static void out(std::string message);
        static void prompt(std::string question, std::string& answer, const bool printValue, const std::string& msgPrefix, bool hasSuffix, const std::string& msgSuffix);
    };
}
