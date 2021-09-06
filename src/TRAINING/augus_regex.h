//
// Created by AUGUS on 2021/9/1.
//

#ifndef AUGUS_CPP_AUGUS_REGEX_H
#define AUGUS_CPP_AUGUS_REGEX_H

#include <regex>
#include <iostream>

class AugusRegex {
    void regexTime() {
        try {
            std::regex rex("^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$");
            //        std::regex  rex("([0-9]+):([0-9]+):([0-9]+)");
            //        std::regex rex("([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2})");
            std::string input = "11:23:12";

            std::smatch smatch1;
            while (std::cin >> input) {
                if (std::regex_search(input, smatch1, rex)) {
                    if (!smatch1.empty()) { std::cout << "match\n"; }
                    else { std::cout << "err\n"; }
                } else {
                    std::cout << "no ma\n";
                }
            }
        } catch (const std::regex_error &err) {
            std::cout << "There is an error. The error is: " << err.what() << '\n';
            if (err.code() == std::regex_constants::error_brack) {
                std::cout << "This is the code of error_brack\n";
            }
        }
    }
};

#endif //AUGUS_CPP_AUGUS_REGEX_H
