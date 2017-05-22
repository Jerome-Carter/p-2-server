//
//  id_gen.cpp
//  p²-server
//
//  Created by James Carter on 3/2/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

// Code from https://gist.github.com/shabinesh/2403356

#include "id_gen.h"

namespace App {
    id_gen::id_gen() : m_Index(0) {
        for (int i = 0; i < LIMIT; i++) {
            m_IdList.push_back(i);
        }
        std::srand((unsigned)std::time(0));
        for (int k = 0; k < m_IdList.size(); k++) {
            int r = k + rand() % (m_IdList.size() - k); // careful here!
            std::swap(m_IdList[k], m_IdList[r]);
        }
    }
    unsigned long id_gen::getIdentifier() {
        if (m_Index == m_IdList.size()) {
            std::cout << "Max ID assignment reached!" << std::endl;
            return m_IdList.size() + 1;
        }
        return m_IdList.at(m_Index++);
    }
}
