//
//  id_gen.h
//  p²-server
//
//  Created by James Carter on 3/2/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

// Inspired by: Cherno

#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

#define LIMIT 1000

namespace App {
    struct id_gen {
    private:
        std::vector<unsigned int> m_IdList;
        unsigned int m_Index;
    public:
        id_gen();
        unsigned long getIdentifier();
    };
}
