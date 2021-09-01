//
// Created by AUGUS on 2021/9/1.
// 如何把random写得优雅
//

#ifndef AUGUS_CPP_AUGUS_RANDOM_H
#define AUGUS_CPP_AUGUS_RANDOM_H

#include <string>
#include <random>
#include <iostream>

class AugusRandom{
    void randomTime(){
        uint32_t timeSeed = time(nullptr);

        std::string aa = "12:13:31";
        time_t tmH, tmM, tmS;
        std::default_random_engine randH, randM, randS;
        randH.seed(timeSeed);
        randM.seed(timeSeed);
        randS.seed(timeSeed);
        std::uniform_int_distribution<time_t> randTimeH{0, 23}, randTimeM(0, 59), randTimeS(0, 59);
        tmH = randTimeH(randH);
        tmM = randTimeM(randM);
        tmS = randTimeS(randS);

        std::string strH = (tmH < 10) ? ("0" + std::to_string(tmH)) : std::to_string(tmH);
        std::string strM = (tmM < 10) ? ("0" + std::to_string(tmM)) : std::to_string(tmM);
        std::string strS = (tmS < 10) ? ("0" + std::to_string(tmS)) : std::to_string(tmS);

        std::cout << strH + strM + strS;
    }
};


#endif //AUGUS_CPP_AUGUS_RANDOM_H
