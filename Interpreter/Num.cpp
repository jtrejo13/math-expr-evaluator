//
//  Num.cpp
//  Interpreter
//
//  Created by Juan Trejo on 10/8/17.
//  Copyright © 2017 PocketMatlab. All rights reserved.
//

#include "Num.hpp"

Num::Num() {
    _token = Token();
}

Num::Num(Token t) {
    _token = t;
}
