//
// Created by AUGUS on 2021/5/28.
// poker 代码剥离
//

#include "poker.hh"



unsigned poker::CommonPart::GetCardValue(unsigned cbCardData) {
    return cbCardData & 0x0F;
}

unsigned poker::CommonPart::GetCardColor(unsigned cbCardData) {
    return cbCardData & 0xF0;
}

bool poker::Poker::isJoker(unsigned cbCardData) {
    return cbCardData == 0x4E || cbCardData == 0x4F;
}


bool poker::Poker::checkData(const unsigned *cardData, unsigned cardCount) {
    unsigned tempHandCardData[108] = {0};
    memcpy(tempHandCardData, cardData, cardCount * sizeof(cardData[0]));
    std::map<unsigned, unsigned> mapChange;
    for (auto data: tempHandCardData) {
        mapChange[data]++;
        //insert 不会更新已存在的值
//    mapChange.insert(pair<unsigned, unsigned>(data, mapChange[data]++));
    }
    // c++ 17
//    for (const auto&[key, value]: mapChange) {
//        std::cout << key << " has value " << value << std::endl;
//    }
    return std::all_of(mapChange.begin(), mapChange.end(), [](std::pair<unsigned, unsigned> val) {
        return val.second <= COUNT_DECK;
    });
}

unsigned poker::Poker::GetCardLogicValue(unsigned cbCardData) {
    unsigned cbCardColor = GetCardColor(cbCardData);
    unsigned cbCardValue = GetCardValue(cbCardData);
    /// 3 4 5 6 7 8 9 10 J Q K
    /// A -> 14 连牌到14就终止
    /// 2 -> 15
    /// Joker -> 16 17
    if (cbCardColor == 0x40) { return cbCardValue + 1; }
    return (cbCardValue == 1) ? (cbCardValue + 13) : cbCardValue;
}

unsigned poker::Poker::GetFirstColor(const unsigned cbCardData[], unsigned cbCardCnt) {
    for (unsigned i = 0; i < cbCardCnt; i++) {
        if (isJoker(cbCardData[i])) { continue; }
        return GetCardColor(cbCardData[i]);
    }
    return 0;
}

bool poker::Poker::IsPrimaryCard(const unsigned cbCardData, const unsigned cbPrimaryColor) {
    bool valid = isValidCard(cbCardData);
    if (!valid) { return false; }
    bool bIsPrimary = defaultPrimaryCard(cbCardData);
    if (GetCardColor(cbCardData) == cbPrimaryColor) { bIsPrimary = true; }
    return bIsPrimary;
}

bool poker::Poker::isValidCard(const unsigned cbCardData) {
    unsigned cbCardColor = GetCardColor(cbCardData);
    unsigned cbCardValue = GetCardValue(cbCardData);
    if ((cbCardData == 0x4E) || (cbCardData == 0x4F)) { return true; }
    if ((cbCardColor <= 0x30) && (cbCardValue >= 0x01) && (cbCardValue <= 0x0D)) { return true; }
    return false;
};

/// 公务员：大王、小王，黑桃A、主2、6个副2；
bool poker::Poker::defaultPrimaryCard(const unsigned cbCardData) {
    return cbCardData == 0x4E || cbCardData == 0x4F || cbCardData == 0x31 || GetCardValue(cbCardData) == 2;
}

void poker::Poker::SortCardList(unsigned cbCardData[], unsigned cbCardCount, enSortCardType SortCardType, bool ori) {

    if (cbCardCount <= 0 || cbCardCount > COUNT_MAX) { return; }

    unsigned cbLogicValue[COUNT_MAX];
    for (unsigned i = 0; i < cbCardCount; i++) { cbLogicValue[i] = GetCardLogicValue(cbCardData[i]); }

    if (enDescend == SortCardType) {
        bool bSorted = true;
        unsigned bTempData, bLast = cbCardCount - 1;
        unsigned m_cbCardCount = 1;
        do {
            bSorted = true;
            for (unsigned i = 0; i < bLast; i++) {
                if ((cbLogicValue[i] < cbLogicValue[i + 1]) ||
                    ((cbLogicValue[i] == cbLogicValue[i + 1]) && (cbCardData[i] < cbCardData[i + 1]))) {
                    bTempData = cbCardData[i];
                    cbCardData[i] = cbCardData[i + 1];
                    cbCardData[i + 1] = bTempData;
                    bTempData = cbLogicValue[i];
                    cbLogicValue[i] = cbLogicValue[i + 1];
                    cbLogicValue[i + 1] = bTempData;
                    bSorted = false;
                }
            }
            bLast--;
        } while (!bSorted);
    } else if (enAscend == SortCardType) {
        bool bSorted = true;
        unsigned bTempData, bLast = cbCardCount - 1;
        unsigned m_cbCardCount = 1;
        do {
            bSorted = true;
            for (unsigned i = 0; i < bLast; i++) {
                if ((cbLogicValue[i] > cbLogicValue[i + 1]) ||
                    ((cbLogicValue[i] == cbLogicValue[i + 1]) && (cbCardData[i] > cbCardData[i + 1]))) {
                    bTempData = cbCardData[i];
                    cbCardData[i] = cbCardData[i + 1];
                    cbCardData[i + 1] = bTempData;
                    bTempData = cbLogicValue[i];
                    cbLogicValue[i] = cbLogicValue[i + 1];
                    cbLogicValue[i + 1] = bTempData;
                    bSorted = false;
                }
            }
            bLast--;
        } while (!bSorted);
    } else if (enColor == SortCardType) {
        bool bSorted = true;
        unsigned bTempData, bLast = cbCardCount - 1;
        unsigned m_cbCardCount = 1;
        unsigned bColor[COUNT_MAX];
        for (unsigned i = 0; i < cbCardCount; i++) { bColor[i] = GetCardColor(cbCardData[i]); }
        do {
            bSorted = true;
            for (unsigned i = 0; i < bLast; i++) {
                if ((bColor[i] < bColor[i + 1]) || ((bColor[i] == bColor[i + 1]) && (GetCardLogicValue(cbCardData[i]) <
                                                                                     GetCardLogicValue(cbCardData[i +
                                                                                                                  1])))) {
                    bTempData = cbCardData[i];
                    cbCardData[i] = cbCardData[i + 1];
                    cbCardData[i + 1] = bTempData;
                    bTempData = bColor[i];
                    bColor[i] = bColor[i + 1];
                    bColor[i + 1] = bTempData;
                    bSorted = false;
                }
            }
            bLast--;
        } while (!bSorted);
    }

}

void poker::Poker::SortCardList(unsigned cbCardData[], unsigned cbCardCount, enSortCardType SortCardType) {
    if (cbCardCount <= 0 || cbCardCount > COUNT_MAX) { return; }
    switch (SortCardType) {
        case enDescend:
            std::sort(cbCardData, cbCardData + cbCardCount, [this](unsigned a, unsigned b) {
                return (a > b && (GetCardLogicValue(a) == GetCardLogicValue(b)) ||
                        (GetCardLogicValue(a) > GetCardLogicValue(b)));
            });
            break;
        case enAscend:
            std::sort(cbCardData, cbCardData + cbCardCount, [this](unsigned a, unsigned b) {
                return (a < b && (GetCardLogicValue(a) == GetCardLogicValue(b)) ||
                        (GetCardLogicValue(a) < GetCardLogicValue(b)));
            });
            break;
        case enColor:
            // color des
            std::sort(cbCardData, cbCardData + cbCardCount, [this](unsigned a, unsigned b) {
                return ((GetCardLogicValue(a) > GetCardLogicValue(b) && GetCardColor(a) == GetCardColor(b))) ||
                       (GetCardColor(a) > GetCardColor(b));
            });
            break;
        default:
            break;
    }
}

/// 此函数入参花色必须为 形如黑桃0x30



unsigned poker::ThreeAgainstOne::GetCardLogicValue(unsigned cbCardData, unsigned byPrimaryColor) {
    //扑克属性
    unsigned cbCardColor = GetCardColor(cbCardData);
    unsigned cbCardValue = GetCardValue(cbCardData);

#ifdef _DEBUG
    if (!isValidCard(cbCardData))
          return 0;
#endif

    // 3 4 5 6 8 9 10 J Q K
    // A -> 14
    // 副2 -> 15
    // 主2 -> 16
    // 0x31 -> 17
    // Joker -> 18 19
    // primary 5 -> 20
    if (cbCardValue == 5 && cbCardColor == byPrimaryColor) { return 20; }
    if (cbCardData == 0x31) { return 17; }
    if (cbCardColor == 0x40) { return cbCardValue + 4; }
    if (cbCardColor == byPrimaryColor && cbCardValue == 2) { return 16; }

    return (cbCardValue <= 2) ? (cbCardValue + 13) : cbCardValue;
}

bool poker::ThreeAgainstOne::isPrimaryCard(const unsigned cbCardData, const unsigned cbPrimaryColor) {
    bool valid = isValidCard(cbCardData);
    if (!valid) { return false; }
    auto value = GetCardValue(cbCardData);
    bool bIsPrimary = defaultPrimaryCard(cbCardData);
    if (GetCardColor(cbCardData) == cbPrimaryColor) { bIsPrimary = true; }

    return bIsPrimary;
}

poker::ThreeAgainstOne::CARD_TYPE poker::ThreeAgainstOne::GetCardType(const unsigned cbCardData[], unsigned cbCardCount, unsigned cbPrimaryColor) {

    //简单牌型
    switch (cbCardCount) {
        case 0: {
            return CT_ERROR;
        }
        case 1: {
            return CT_SINGLE;
        }
        case 2: {
            bool sameLogic = GetCardLogicValue(cbCardData[0], cbPrimaryColor) ==
                             GetCardLogicValue(cbCardData[1], cbPrimaryColor);
            bool isPrimaryColorFirst = isPrimaryCard(cbCardData[0], cbPrimaryColor);
            bool isPrimaryColorSecond = isPrimaryCard(cbCardData[1], cbPrimaryColor);
            bool sameColor = GetCardColor(cbCardData[0]) == GetCardColor(cbCardData[1]);
            if (sameColor && sameLogic) {
                return CT_DOUBLE;
            }

            return CT_ERROR;
        }
        default:
            break;
    }

    unsigned TempCard[COUNT_MAX];
    memcpy(TempCard, cbCardData, cbCardCount);
    SortCardList(TempCard, cbCardCount, enDescend);

    //分析扑克
    tagSameAnalyseResult AnalyseResult = {0};
    if (!analyseCardData(TempCard, cbCardCount, AnalyseResult, cbPrimaryColor)) {
        return CT_ERROR;
    }

    //两张类型
    if (AnalyseResult.cbBlockCount[1] >= 2) {
        //变量定义
        unsigned cbFirstCardData = AnalyseResult.cbCardData[1][0];
        unsigned cbFirstLogicValue = GetCardLogicValue(cbFirstCardData, cbPrimaryColor);
        ///错误过滤
        if (cbFirstLogicValue >= 20) { return CT_ERROR; }
        //连牌判断
        for (unsigned i = 1; i < AnalyseResult.cbBlockCount[1]; i++) {
            unsigned cbNextCardData = AnalyseResult.cbCardData[1][i * 2];
            if (cbFirstLogicValue != (GetCardLogicValue(cbNextCardData, cbPrimaryColor) + i)) { return CT_ERROR; }
        }
        //二连判断
        if ((AnalyseResult.cbBlockCount[1] * 2) == cbCardCount) { return CT_DOUBLE_LINE; }

        return CT_ERROR;
    }

    //auto checkLine = [&](unsigned data[], unsigned std::count, unsigned primary, unsigned line) {
    //	if (std::count % line) return false;
    //	auto firstVal = GetCardLogicValue(data[0], primary);
    //	auto firstColor = GetCardColor(data[0]);
    //	auto isPrimary = isPrimaryCard(data[0], primary);
    //	//不连主5
    //	if (firstVal >= 19) return false;
    //	for (auto i = 1; i < std::count / line; i++) {
    //		auto nextIsPrimary = isPrimaryCard(data[i], primary);
    //		//不为同花色不可组连对
    //		if (nextIsPrimary != isPrimary) return false;
    //		//非主花色 再次校验 不为同花色不可组连对
    //		if (!isPrimary) if (firstColor != GetCardColor(data[i])) return false;
    //		//逻辑值不递减 不可组连
    //		// 对于主副连对的组成模式 目前仅依照 GetCardLogicValue 即可组成正确的连对
    //		auto nextVal = GetCardLogicValue(data[i * line], primary);
    //		if (firstVal != nextVal + i) return false;
    //	}
    //	return true;
    //};

    //if (checkLine(_TempCard, cbCardCount, cbPrimaryColor, 2)) return CT_DOUBLE_LINE;

    return CT_ERROR;

}

void poker::ThreeAgainstOne::SortHandCardListByPrimary(unsigned cbCardData[], unsigned cbCardCount, const bool bDragonData[], unsigned specificColor) {
    SortCardList(cbCardData, cbCardCount, enColor);


    unsigned temp[30];
    memcpy(temp, cbCardData, cbCardCount * sizeof(unsigned));

    std::vector<unsigned> primaryDragonData;
    std::vector<unsigned> primary5Data;
    std::vector<unsigned> primaryJokerData;
    std::vector<unsigned> primaryAceData;
    std::vector<unsigned> primary2Data; /// dont forget fix
    std::vector<unsigned> primaryData;

    /// 公务员：(主5) 大王、小王，黑桃A、主2、6个副2；
    for (auto index = 0; index < cbCardCount; index++) {
        auto dragonIndex = GetCardValue(cbCardData[index]) - 1;
        //(dragonIndex >= 0 && dragonIndex < 13)排除王牌
        if ((dragonIndex >= 0 && dragonIndex < 13) && bDragonData[dragonIndex]) {
            primaryDragonData.push_back(cbCardData[index]);
            cbCardData[index] = 0;
        } else {
            if (isPrimaryCard(cbCardData[index], specificColor)) {
                if (GetCardValue(cbCardData[index]) == 0x05) { primary5Data.push_back(cbCardData[index]); }
                else if (GetCardColor(cbCardData[index]) == 0x40) { primaryJokerData.push_back(cbCardData[index]); }
                else if (cbCardData[index] == 0x31) { primaryAceData.push_back(cbCardData[index]); }
                else if (GetCardValue(cbCardData[index]) == 0x02) { primary2Data.push_back(cbCardData[index]); }
                else { primaryData.push_back(cbCardData[index]); }

                cbCardData[index] = 0;
            }
        }
    }

    std::vector<unsigned> fixPrimary2Data;
    for (auto &fix: primary2Data) {
        if (GetCardColor(fix) == specificColor) {
            fixPrimary2Data.push_back(fix);
            fix = 0;
        }
    }
    for (auto data: primary2Data) {
        if (data) { fixPrimary2Data.push_back(data); }
    }

    std::vector<unsigned> otherData;
    for (auto index = 0; index < cbCardCount; index++) {
        if (cbCardData[index]) { otherData.push_back(cbCardData[index]); }
    }

    std::vector<unsigned> result;

    auto fn = [&](const std::vector<unsigned> &arr, std::vector<unsigned> &res) {
        for (auto data: arr) { res.push_back(data); }
    };
    fn(primaryDragonData, result);
    fn(primary5Data, result);
    fn(primaryJokerData, result);
    fn(primaryAceData, result);
    fn(fixPrimary2Data, result);
    fn(primaryData, result);
    fn(otherData, result);

    if (!result.empty()) {
        memcpy(cbCardData, &result[0], result.size() * sizeof(result[0])); /// copy all
    }

}


bool poker::ThreeAgainstOne::findStraightType(const unsigned byHandCardData[], unsigned byHandCardCount, unsigned &byReferCard, unsigned countType, unsigned countMaxStraight, unsigned byPrimaryColor) {
    bool res = false;
    unsigned tempHandCardData[COUNT_MAX] = {0};
    memcpy(tempHandCardData, byHandCardData, byHandCardCount * sizeof(byHandCardData[0]));
    //change to logic index
    for (auto &changeToLogic: tempHandCardData) {
        changeToLogic = GetCardLogicValue(changeToLogic, byPrimaryColor);
    }
    //change map
    std::map<unsigned, unsigned> mapLogic;
    //无须考虑八龙 故最大逻辑值为20即可
    const unsigned maxLogicIndex = 20;
    for (auto logicIndex: tempHandCardData) {
        mapLogic.insert(std::pair<unsigned, unsigned>(logicIndex, mapLogic[logicIndex]++));
    }
    unsigned beginLogicIndex = byReferCard;
    if (!beginLogicIndex) { beginLogicIndex = 1; }
    try {
        for (unsigned i = beginLogicIndex; i <= maxLogicIndex; i++) {
            for (unsigned j = 0; j < countMaxStraight; j++) {
                if (mapLogic[i + j] != countType) { break; }

                //countType 1单 2对 3三 4 ...
                //countStraight 1连 2连 3连 ...
                //单张超过1连即跳过 本游戏没顺子
                if (countType == 1 && countMaxStraight > 1) { break; }
                //两张及以上 无要求

                if (countMaxStraight == 1 || j + 1 == countMaxStraight) {
                    res = true;
                    byReferCard = i;
                }
            }
        }
    } catch (const std::exception &) {

        return false;
    }

    return res;
}

unsigned poker::ThreeAgainstOne::findMaxLogicValue(const unsigned *cbCardData, unsigned cbCardCount, unsigned cbPrimaryColor, unsigned cbCurrentColor) {
    unsigned tempHandCardData[COUNT_MAX];
    memset(tempHandCardData, 0, sizeof(tempHandCardData));
    memcpy(tempHandCardData, cbCardData, cbCardCount * sizeof(cbCardData[0]));
    for (auto &changeData: tempHandCardData) {
        if (cbCurrentColor == PRIMARY_COLOR) {
            if (!isPrimaryCard(changeData, cbPrimaryColor)) { continue; }
        } else {
            if (GetCardColor(changeData) != cbCurrentColor) { continue; }
        }
        if (!changeData) { continue; }
        changeData = GetCardLogicValue(changeData, cbPrimaryColor);
    }
    auto pMax = std::max_element(tempHandCardData, tempHandCardData + COUNT_MAX);
    return *pMax;
}

bool poker::ThreeAgainstOne::analyseCardData(const unsigned *cbCardData, unsigned cbCardCount, tagSameAnalyseResult &AnalyseResult, unsigned cbPrimaryColor) {
    //设置结果
    AnalyseResult = {};
    //扑克分析
    for (unsigned i = 0; i < cbCardCount; i++) {
        //跳过错误
        if (!cbCardData[i]) { continue; }
        //变量定义
        unsigned cbSameCount = 1;
        unsigned cbLogicValue = GetCardLogicValue(cbCardData[i], cbPrimaryColor);
        unsigned firstColor = GetCardColor(cbCardData[i]);
        auto isPrimary = isPrimaryCard(cbCardData[i], cbPrimaryColor);
        if (GetCardColor(cbCardData[i]) == 0x40) { AnalyseResult.cbKingCount++; }
        //搜索同牌
        for (unsigned j = i + 1; j < cbCardCount; j++) {
            auto nextIsPrimary = isPrimaryCard(cbCardData[j], cbPrimaryColor);
            //不为同花色不可组连对
            if (nextIsPrimary != isPrimary) { break; }
            //非主花色 或 主 都需要 再次校验 不为同花色不可组连对
            if (firstColor != GetCardColor(cbCardData[j])) { break; }
            //获取扑克
            if (GetCardLogicValue(cbCardData[j], cbPrimaryColor) != cbLogicValue) { break; }
            //设置变量
            cbSameCount++;
        }
        //设置结果
        unsigned cbIndex = AnalyseResult.cbBlockCount[cbSameCount - 1]++;
        for (unsigned j = 0; j < cbSameCount; j++) {
            AnalyseResult.cbCardData[cbSameCount - 1][cbIndex * cbSameCount + j] = cbCardData[i + j];
        }
        //设置索引
        i += cbSameCount - 1;
    }
    return true;
}


bool poker::ThreeAgainstOne::compareThrowCard(const unsigned cbFirstCard[], const unsigned cbNextCard[], unsigned cbFirstCount, unsigned cbNextCount, unsigned cbPrimaryColor, unsigned cbCurrentColor) {
    //目前只完成了连对 对子 单牌的逻辑处理
    using RECORD_HANDLE = unsigned;
    CARD_TYPE cbThrowCardType = GetCardType(cbFirstCard, cbFirstCount, cbPrimaryColor);

    switch (cbThrowCardType) {
        case CT_ERROR: {
            tagSearchCardResult tagSearchFirstCardResult = {0}, tagSearchNextCardResult = {0};
            RECORD_HANDLE resSearchFirst = searchLineCardType(cbFirstCard, cbFirstCount, 0, 2, 0, tagSearchFirstCardResult, cbPrimaryColor, cbCurrentColor);
            if (resSearchFirst) {
                RECORD_HANDLE maxLineCount = tagSearchFirstCardResult.cbCardCount[0];
                RECORD_HANDLE referCard = tagSearchFirstCardResult.cbResultCard[0][maxLineCount - 1];
                RECORD_HANDLE resSearchNext = searchLineCardType(cbNextCard, cbNextCount, referCard, 2, maxLineCount, tagSearchNextCardResult, cbPrimaryColor, cbCurrentColor);
                if (resSearchNext) { return true; }
            }
            tagSearchFirstCardResult = {0}, tagSearchNextCardResult = {0};
            resSearchFirst = searchSameCard(cbFirstCard, cbFirstCount, 0, 2, tagSearchFirstCardResult, cbPrimaryColor, cbCurrentColor);
            if (resSearchFirst) {
                RECORD_HANDLE referCard = tagSearchFirstCardResult.cbResultCard[0][1];
                RECORD_HANDLE resSearchNext = searchSameCard(cbNextCard, cbNextCount, referCard, 2, tagSearchNextCardResult, cbPrimaryColor, cbCurrentColor);
                if (resSearchNext) { return true; }
            }
            unsigned firstMaxLogicElement = findMaxLogicValue(cbFirstCard, cbFirstCount, cbPrimaryColor, cbCurrentColor);
            unsigned nextMaxLogicElement = findMaxLogicValue(cbNextCard, cbNextCount, cbPrimaryColor, cbCurrentColor);
            if (nextMaxLogicElement > firstMaxLogicElement) {
                return true;
            }
            return false;
        }
        case CT_SINGLE: {
            RECORD_HANDLE firstLogicValue = GetCardLogicValue(cbFirstCard[0], cbPrimaryColor);
            unsigned nextMaxLogicElement = findMaxLogicValue(cbNextCard, cbNextCount, cbPrimaryColor, cbCurrentColor);
            if (nextMaxLogicElement > firstLogicValue) {
                return true;
            }
            return false;
        }
        case CT_DOUBLE: {
            RECORD_HANDLE firstLogicValue = GetCardLogicValue(cbFirstCard[0], cbPrimaryColor);
            RECORD_HANDLE referCard = cbFirstCard[0];
            tagSearchCardResult tagSearchNextCardResult = {0};
            RECORD_HANDLE resSearchNext = searchSameCard(cbNextCard, cbNextCount, referCard, 2, tagSearchNextCardResult, cbPrimaryColor, cbCurrentColor);
            RECORD_HANDLE maxNext = 0;
            for (int i = 0; i < tagSearchNextCardResult.cbSearchCount; i++) {
                if (tagSearchNextCardResult.cbResultCard[i][0] > maxNext) {
                    maxNext = tagSearchNextCardResult.cbResultCard[i][0];
                }
            }
            RECORD_HANDLE nextLogicValue = GetCardLogicValue(maxNext, cbPrimaryColor);
            if (nextLogicValue > firstLogicValue) { return true; }
            return false;
        }
        case CT_THREE:
        case CT_SINGLE_LINE:
            break;
        case CT_DOUBLE_LINE: {
            tagSearchCardResult tagSearchNextCardResult = {0};
            unsigned firstMaxLogicElement = 0;
            for (int i = 0; i < cbFirstCount; i++) {
                if (GetCardLogicValue(cbFirstCard[i], cbPrimaryColor) > firstMaxLogicElement) {
                    firstMaxLogicElement = cbFirstCard[i];
                }
            }
            RECORD_HANDLE referCard = firstMaxLogicElement;
            RECORD_HANDLE maxLineCount = cbFirstCount / 2;
            RECORD_HANDLE resSearchNext = searchLineCardType(cbNextCard, cbNextCount, referCard, 2, maxLineCount, tagSearchNextCardResult, cbPrimaryColor, cbCurrentColor);
            if (resSearchNext) { return true; }
            return false;
        }
        case CT_THREE_LINE:
        case CT_THREE_LINE_TAKE_ONE:
        case CT_THREE_LINE_TAKE_TWO:
        case CT_FOUR_LINE_TAKE_ONE:
        case CT_FOUR_LINE_TAKE_TWO:
        case CT_BOMB_CARD:
        case CT_MISSILE_CARD:
        case CT_SPECIAL:
            break;
    }


    return false;
}

unsigned poker::ThreeAgainstOne::searchSameCard(const unsigned *cbHandCardData, unsigned cbHandCardCount, unsigned cbReferCard, unsigned cbSameCardCount, tagSearchCardResult &pSearchCardResult, unsigned cbPrimaryColor, unsigned cbCurrentColor) {
    //设置结果
    pSearchCardResult = {};
    unsigned cbResultCount = 0;
    //构造扑克
    unsigned cbCardData[COUNT_MAX] = {0};
    unsigned cbCardCount = cbHandCardCount;
    for (unsigned i = 0; i < cbHandCardCount; i++) {
        cbCardData[i] = cbHandCardData[i];
    }
    //排列扑克
    SortCardList(cbCardData, cbCardCount, enDescend);
    //分析扑克
    tagSameAnalyseResult analyseResult = {0};
    analyseCardData(cbCardData, cbCardCount, analyseResult, cbPrimaryColor);

    unsigned cbReferLogicValue = cbReferCard == 0 ? 0 : GetCardLogicValue(cbReferCard, cbPrimaryColor);
    unsigned cbReferCardColor = GetCardColor(cbReferCard);
    unsigned indexBlock = cbSameCardCount - 1;
    for (int i = analyseResult.cbBlockCount[indexBlock] - 1; i >= 0; i--) {
        unsigned tempCard = analyseResult.cbCardData[indexBlock][cbSameCardCount * i];
        if (GetCardColor(tempCard) == cbCurrentColor &&
            GetCardLogicValue(tempCard, cbPrimaryColor) > cbReferLogicValue) {
            //复制扑克
            for (unsigned j = 0; j < cbSameCardCount; ++j) {
                pSearchCardResult.cbResultCard[cbResultCount][j] = analyseResult.cbCardData[indexBlock][
                        cbSameCardCount * i + j];
            }
            pSearchCardResult.cbCardCount[cbResultCount] = cbSameCardCount;
            cbResultCount++;
        }
    }
    pSearchCardResult.cbSearchCount = cbResultCount;
    return cbResultCount;
}

unsigned poker::ThreeAgainstOne::searchLineCardType(const unsigned *cbHandCardData, unsigned cbHandCardCount, unsigned cbReferCard, unsigned cbBlockCount, unsigned cbLineCount, tagSearchCardResult &pSearchCardResult, unsigned cbPrimaryColor, unsigned cbCurrentColor) {
    //常量
    const unsigned maxLogicIndex = 20;
    const unsigned minBeginIndex = 3;
    //设置结果
    pSearchCardResult = {};
    unsigned cbResultCount = 0;
    //定义变量
    unsigned cbLessLineCount = 0;
    if (cbLineCount == 0) {
        if (cbBlockCount == 1) {
            cbLessLineCount = 5;
        } else if (cbBlockCount == 2) {
            cbLessLineCount = 3;
        } else { cbLessLineCount = 2; }
    } else { cbLessLineCount = cbLineCount; }
    unsigned cbReferIndex = minBeginIndex;
    if (cbReferCard != 0) {
        if (GetCardLogicValue(cbReferCard, cbPrimaryColor) - cbLessLineCount < 2) { return 0; }
        cbReferIndex = GetCardLogicValue(cbReferCard, cbPrimaryColor) - cbLessLineCount + 1;
    }
    //超过20
    if (cbReferIndex + cbLessLineCount > maxLogicIndex) { return cbResultCount; }
    //长度判断
    if (cbHandCardCount < cbLessLineCount * cbBlockCount) { return cbResultCount; }
    //构造扑克
    unsigned cbCardData[COUNT_MAX] = {0};
    unsigned cbCardCount = cbHandCardCount;
    for (unsigned i = 0; i < cbHandCardCount; i++) {
        cbCardData[i] = cbHandCardData[i];
    }
    //排列扑克
    SortCardList(cbCardData, cbCardCount, enDescend);
    //分析扑克
    tagDistributing Distributing = {0};
    analyseDistributing(cbCardData, cbCardCount, Distributing);
    //搜索顺子
    unsigned cbIndexCount = 5;
    int tmpLinkCount = 0;
    for (int i = cbReferIndex; i < 13; i++) {
        //继续判断
        if (Distributing.cbDistributing[i][cbIndexCount] < cbBlockCount) {
            if (tmpLinkCount < cbLessLineCount) {
                tmpLinkCount = 0;
                continue;
            } else {
                i--;
            }
        } else {
            tmpLinkCount++;
            //寻找最长连
            if (cbLineCount == 0) {
                continue;
            }
        }

        if (tmpLinkCount >= cbLessLineCount) {
            //复制扑克
            unsigned cbCount = 0;
            for (int cbIndex = i + 1 - tmpLinkCount; cbIndex <= i; cbIndex++) {
                unsigned cbTmpCount = 0;
                if (cbCurrentColor != ERROR_COLOR) {
                    unsigned cbColorIndex = cbCurrentColor >> 4;
                    for (unsigned cbColorCount = 0;
                         cbColorCount < Distributing.cbDistributing[cbIndex][cbColorIndex]; cbColorCount++) {
                        pSearchCardResult.cbResultCard[cbResultCount][cbCount++] = MakeCardData(cbIndex, cbColorIndex);
                        if (++cbTmpCount == cbBlockCount) { break; }
                    }
                } else {
                    for (unsigned cbColorIndex = 0; cbColorIndex < 4; cbColorIndex++) {
                        for (unsigned cbColorCount = 0;
                             cbColorCount < Distributing.cbDistributing[cbIndex][3 - cbColorIndex]; cbColorCount++) {
                            pSearchCardResult.cbResultCard[cbResultCount][cbCount++] = MakeCardData(cbIndex,
                                                                                                    3 - cbColorIndex);
                            if (++cbTmpCount == cbBlockCount) { break; }
                        }
                        if (cbTmpCount == cbBlockCount) { break; }
                    }
                }
            }
            //设置变量
            pSearchCardResult.cbCardCount[cbResultCount] = cbCount;
            cbResultCount++;

            if (cbLineCount != 0) {
                tmpLinkCount--;
            } else {
                tmpLinkCount = 0;
            }
        }
    }

    pSearchCardResult.cbSearchCount = cbResultCount;
    return cbResultCount;
}

bool poker::ThreeAgainstOne::analyseDistributing(const unsigned *cbCardData, unsigned cbCardCount, tagDistributing &Distributing) {
    Distributing = {};
    unsigned cbIndexCount = 5;
    //设置变量
    for (unsigned i = 0; i < cbCardCount; i++) {
        if (cbCardData[i] == 0) { continue; }
        //获取属性
        unsigned cbCardColor = GetCardColor(cbCardData[i]);
        unsigned cbCardValue = GetCardValue(cbCardData[i]);
        //分布信息
        Distributing.cbCardCount++;
        Distributing.cbDistributing[cbCardValue - 1][cbIndexCount]++;
        Distributing.cbDistributing[cbCardValue - 1][cbCardColor >> 4]++;
    }
    return true;
}

unsigned poker::ThreeAgainstOne::MakeCardData(unsigned cbValueIndex, unsigned cbColorIndex) {
    return (cbColorIndex << 4) | (cbValueIndex + 1);
}

//还未修改
bool poker::ThreeAgainstOne::searchOutCard(const unsigned *cbHandCardData, unsigned cbHandCardCount, const unsigned *cbTurnCardData, unsigned cbTurnCardCount, tagSearchCardResult &pSearchCardResult, unsigned cbPrimaryColor, unsigned cbCurrentColor) {
    //设置结果
    pSearchCardResult = {};
    //变量定义
    unsigned cbResultCount = 0;
    tagSearchCardResult tmpSearchCardResult = {0};
    //构造扑克
    unsigned cbCardData[COUNT_MAX];
    unsigned cbCardCount = cbHandCardCount;
    memcpy(cbCardData, cbHandCardData, sizeof(unsigned) * cbHandCardCount);
    //排列扑克
    SortCardList(cbCardData, cbCardCount, enDescend);
    //获取类型
    unsigned cbTurnOutType = GetCardType(cbTurnCardData, cbTurnCardCount, cbPrimaryColor);
    //出牌分析
    switch (cbTurnOutType) {
        case CT_ERROR:                    //错误类型
        {
            //提取各种牌型一组
            //if (!pSearchCardResult) return false;

            //是否一手出完
            if (GetCardType(cbCardData, cbCardCount, cbPrimaryColor) != CT_ERROR) {
                pSearchCardResult.cbCardCount[cbResultCount] = cbCardCount;
                for (unsigned i = 0; i < cbCardCount; i++) {
                    pSearchCardResult.cbResultCard[cbResultCount][i] = cbCardData[i];
                }
                cbResultCount++;
            }

            //如果最小牌不是单牌，则提取
            unsigned cbSameCount = 0;
            if (cbCardCount > 1 &&
                GetCardValue(cbCardData[cbCardCount - 1]) == GetCardValue(cbCardData[cbCardCount - 2])) {
                cbSameCount = 1;
                pSearchCardResult.cbResultCard[cbResultCount][0] = cbCardData[cbCardCount - 1];
                unsigned cbCardValue = GetCardValue(cbCardData[cbCardCount - 1]);
                for (int i = cbCardCount - 2; i >= 0; i--) {
                    if (GetCardValue(cbCardData[i]) == cbCardValue) {
                        pSearchCardResult.cbResultCard[cbResultCount][cbSameCount++] = cbCardData[i];
                    } else { break; }
                }

                pSearchCardResult.cbCardCount[cbResultCount] = cbSameCount;
                cbResultCount++;
            }

            //单牌
            unsigned cbTmpCount = 0;
            if (cbSameCount != 1) {
                cbTmpCount = searchSameCard(cbCardData, cbCardCount, 0, 1, tmpSearchCardResult, cbPrimaryColor, cbCurrentColor);
                if (cbTmpCount > 0) {
                    pSearchCardResult.cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
                    for (unsigned i = 0; i < tmpSearchCardResult.cbCardCount[0]; i++) {
                        pSearchCardResult.cbResultCard[cbResultCount][i] = tmpSearchCardResult.cbResultCard[0][i];
                    }
                    cbResultCount++;
                }
            }

            //对牌
            if (cbSameCount != 2) {
                cbTmpCount = searchSameCard(cbCardData, cbCardCount, 0, 2, tmpSearchCardResult, cbPrimaryColor, cbCurrentColor);
                if (cbTmpCount > 0) {
                    pSearchCardResult.cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
                    for (unsigned i = 0; i < tmpSearchCardResult.cbCardCount[0]; i++) {
                        pSearchCardResult.cbResultCard[cbResultCount][i] = tmpSearchCardResult.cbResultCard[0][i];
                    }
                    cbResultCount++;
                }
            }

            //三条
            if (cbSameCount != 3) {
                cbTmpCount = searchSameCard(cbCardData, cbCardCount, 0, 3, tmpSearchCardResult, cbPrimaryColor, cbCurrentColor);
                if (cbTmpCount > 0) {
                    pSearchCardResult.cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
                    for (unsigned i = 0; i < tmpSearchCardResult.cbCardCount[0]; i++) {
                        pSearchCardResult.cbResultCard[cbResultCount][i] = tmpSearchCardResult.cbResultCard[0][i];
                    }
                    cbResultCount++;
                }
            }

            //单连
            cbTmpCount = searchLineCardType(cbCardData, cbCardCount, 0, 1, 0, tmpSearchCardResult, cbPrimaryColor, cbCurrentColor);
            if (cbTmpCount > 0) {
                pSearchCardResult.cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
                for (unsigned i = 0; i < tmpSearchCardResult.cbCardCount[0]; i++) {
                    pSearchCardResult.cbResultCard[cbResultCount][i] = tmpSearchCardResult.cbResultCard[0][i];
                }
                cbResultCount++;
            }

            //连对
            cbTmpCount = searchLineCardType(cbCardData, cbCardCount, 0, 2, 0, tmpSearchCardResult, cbPrimaryColor, cbCurrentColor);
            if (cbTmpCount > 0) {
                pSearchCardResult.cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
                for (unsigned i = 0; i < tmpSearchCardResult.cbCardCount[0]; i++) {
                    pSearchCardResult.cbResultCard[cbResultCount][i] = tmpSearchCardResult.cbResultCard[0][i];
                }
                cbResultCount++;
            }

            //三连
            cbTmpCount = searchLineCardType(cbCardData, cbCardCount, 0, 3, 0, tmpSearchCardResult, cbPrimaryColor, cbCurrentColor);
            if (cbTmpCount > 0) {
                pSearchCardResult.cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
                for (unsigned i = 0; i < tmpSearchCardResult.cbCardCount[0]; i++) {
                    pSearchCardResult.cbResultCard[cbResultCount][i] = tmpSearchCardResult.cbResultCard[0][i];
                }
                cbResultCount++;
            }

            pSearchCardResult.cbSearchCount = cbResultCount;
            return cbResultCount;
        }
        case CT_SINGLE:                    //单牌类型
        case CT_DOUBLE:                    //对牌类型
        case CT_THREE:                    //三条类型
        {
            //变量定义
            unsigned cbReferCard = cbTurnCardData[0];
            unsigned cbSameCount = 1;
            if (cbTurnOutType == CT_DOUBLE) { cbSameCount = 2; }
            else if (cbTurnOutType == CT_THREE) { cbSameCount = 3; }
            //搜索相同牌
            cbResultCount = searchSameCard(cbCardData, cbCardCount, cbReferCard, cbSameCount, pSearchCardResult, cbPrimaryColor, cbCurrentColor);

            break;
        }
        case CT_SINGLE_LINE:        //单连类型
        case CT_DOUBLE_LINE:        //对连类型
        case CT_THREE_LINE:                //三连类型
        {
            //变量定义
            unsigned cbBlockCount = 1;
            if (cbTurnOutType == CT_DOUBLE_LINE) { cbBlockCount = 2; }
            else if (cbTurnOutType == CT_THREE_LINE) { cbBlockCount = 3; }
            unsigned cbLineCount = cbTurnCardCount / cbBlockCount;
            //搜索边牌
            cbResultCount = searchLineCardType(cbCardData, cbCardCount, cbTurnCardData[0], cbBlockCount, cbLineCount, pSearchCardResult, cbPrimaryColor, cbCurrentColor);
            break;
        }
        default:
            break;
    }

    pSearchCardResult.cbSearchCount = cbResultCount;
    return cbResultCount;

}


unsigned poker::ThreeAgainstOne::findSameCards(unsigned wChairID, const unsigned byCardData[], unsigned byCardCount) {
    // 方法一
    // 可以直接用 AnalyseCardData 分析
    //
    // 方法二
    int count = 1;
    unsigned res = 0;
    unsigned data = 0;
    for (auto i = 0; i < byCardCount; i++) {
        if (isJoker(byCardData[i])) { continue; }
        for (auto j = i + 1; j < byCardCount; j++) {
            if (GetCardValue(byCardData[i]) == GetCardValue(byCardData[j])) {
                data = GetCardValue(byCardData[i]);
                std::cout << " " << std::hex << data;
                count++;
            }
        }
        if (count == COUNT_MAX_SAME) {
//        ASSERT(data >= 1 && data <= 13);
//        m_bySameCardData[wChairID][data - 1] = true;
            res++;
        }
        count = 1;
        data = 0;
    }
//    m_bHave8SameCard[wChairID] = !res ? false : true;
    return res;
}

poker::CompanyTest::CompanyTest() = default;

poker::CompanyTest::~CompanyTest() = default;

std::vector<unsigned> poker::CompanyTest::RemoveZero(unsigned source_arr[], unsigned source_length, bool just_test) {

    std::cout << "source arr" << std::endl;
    for (auto i = 0; i < source_length; i++) {
        std::cout << source_arr[i] << " ";
    }
    std::cout << std::endl;

    std::sort(source_arr, source_arr + source_length, [this](unsigned a, unsigned b) { return a - b; });

    std::cout << "return a - b " << std::endl;
    for (auto i = 0; i < source_length; i++) {
        std::cout << source_arr[i] << " ";
    }
    std::cout << std::endl;


    std::sort(source_arr, source_arr + source_length, [this](unsigned a, unsigned b) { return a > b; });

    std::cout << "return a > b " << std::endl;
    for (auto i = 0; i < source_length; i++) {
        std::cout << source_arr[i] << " ";
    }
    std::cout << std::endl;

    unsigned end_index = 0;
    for (unsigned i = 0; i < source_length; i++) {
        if (!source_arr[i]) {
            end_index = i;
            break;
        }
    }

    if (end_index) {
        std::vector<unsigned> res(source_arr, source_arr + end_index);
        return res;
    } else {
        std::vector<unsigned> res(source_arr, source_arr + source_length);
        return res;
    }

}

bool poker::CompanyTest::RemoveExist(std::vector<unsigned> &source_arr, unsigned source_length, std::vector<unsigned> delete_arr, unsigned delete_length) {

    for (auto i: delete_arr) {
        for (unsigned &j: source_arr) {
            if (i == j) {
                j = 0;
                break;
            }
        }
    }

    std::sort(source_arr.rbegin(), source_arr.rend());
    return true;
}

bool poker::CompanyTest::RemoveExist(unsigned source_arr[], unsigned source_length, unsigned delete_arr[], unsigned delete_length) {
    for (unsigned i = 0; i < delete_length; i++) {
        for (unsigned j = 0; j < source_length; j++) {
            if (source_arr[j] == delete_arr[i]) {
                source_arr[j] = 0;
                break;
            }
        }
    }
    std::sort(source_arr, source_arr + source_length, [this](unsigned a, unsigned b) { return a > b; });
    return true;
}

std::vector<unsigned> poker::CompanyTest::RemoveZero(std::vector<unsigned> source_arr, unsigned source_length) {
    std::sort(source_arr.rbegin(), source_arr.rend());
    unsigned end_index = 0;
    for (unsigned i = 0; i < source_length; i++) {
        if (!source_arr[i]) {
            end_index = i;
            break;
        }
    }

    if (end_index) {
        std::vector<unsigned> res(source_arr.begin(), source_arr.begin() + end_index);
        return res;
    } else {
        std::vector<unsigned> res;
        res = source_arr;
        return res;
    }

}

std::vector<unsigned> poker::CompanyTest::RemoveZero(unsigned source_arr[], unsigned source_length) {
    std::sort(source_arr, source_arr + source_length, [this](unsigned a, unsigned b) { return a > b; });
    unsigned end_index = 0;
    for (unsigned i = 0; i < source_length; i++) {
        if (!source_arr[i]) {
            end_index = i;
            break;
        }
    }

    if (end_index) {
        std::vector<unsigned> res(source_arr, source_arr + end_index);
        return res;
    } else {
        std::vector<unsigned> res(source_arr, source_arr + source_length);
        return res;
    }

}

void poker::CompanyTest::InsertToMap(unsigned *a, unsigned n, std::map<unsigned, unsigned> &out_map) {
    std::map<unsigned, unsigned> temp_map;
    std::pair<std::map<unsigned, unsigned>::iterator, bool> ret;
    for (unsigned i = 0; i < n; i++) {
        ret = temp_map.insert({a[i], 1});
        if (!ret.second) {
            ++temp_map[a[i]];
        }
    }
    out_map = temp_map;
}

void poker::CompanyTest::SprintMap(std::map<unsigned, unsigned> &count_map) {
    auto map_it = count_map.cbegin();
    while (map_it != count_map.cend()) {
        std::cout << "value " << map_it->first << " appear " << map_it->second << " times\n";
        ++map_it;
    }
}


bool poker::CompanyTest::IsSameColorCard(const std::vector<unsigned> &cbCardData, unsigned cbCardCount) {

//  ASSERT(cbCardCount > 0);
    if (cbCardCount <= 0) { return false; }

    bool bRet = true;

    unsigned *tempCard = new unsigned[cbCardData.size() * sizeof(unsigned)];

    memcpy(tempCard, &cbCardData[0], cbCardData.size() * sizeof(cbCardData[0]));

    unsigned cbFirstCard = GetFirstColor(tempCard, cbCardCount);
    for (unsigned i = 1; i < cbCardCount; i++) {
        if (isJoker(cbCardData[i])) { continue; }
        unsigned cbNextCard = GetCardColor(cbCardData[i]);
        if (cbNextCard != cbFirstCard) { bRet = false; }
    }

    return bRet;
}

bool poker::CompanyTest::Test() {

    unsigned test0826[108] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,    //方块 A - K
                              0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,    //梅花 A - K
                              0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,    //红桃 A - K
                              0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,    //黑桃 A - K
                              0x4e, 0x4f, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,    //方块 A - K
                              0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,    //梅花 A - K
                              0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,    //红桃 A - K
                              0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,    //黑桃 A - K
                              0x4e, 0x4f};

    std::sort(test0826, test0826 + 108, [this](unsigned a, unsigned b) {
        return (a > b && GetCardLogicValue(a) == GetCardLogicValue(b)) || (GetCardLogicValue(a) > GetCardLogicValue(b));
    });

    std::vector<unsigned> res0826(test0826, test0826 + 108);
    augus::PrintTest(res0826);

//  return true;

    unsigned a[53] = {1, 1, 2, 3, 4, 4, 5, 6, 6, 8, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,    //梅花 A - K
                      0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,    //红桃 A - K
                      0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,    //黑桃 A - K
                      0x4E, 0x4F, 0x4F,};
    std::cout << "source arr is \n";
    std::vector<unsigned> vec_0825(a, a + 53);
    augus::PrintTest(vec_0825);
    std::map<unsigned, unsigned> result_map;
    InsertToMap(a, 53, result_map);
    SprintMap(result_map);

    auto map_it = result_map.cbegin();
    std::vector<unsigned> res0825;
    while (map_it != result_map.cend()) {
        if (map_it->second == 1 && map_it->first != 0x4e && map_it->first != 0x4f) {
            res0825.push_back(map_it->first);
        }
        ++map_it;
    }

    std::cout << " \nsize vec->" << res0825.size();

    unsigned cbChickenCard = res0825[rand() % res0825.size()];

    augus::PrintTest(res0825);


    std::cout << "\n got chicken ->" << cbChickenCard;

//  system("pause");

    unsigned test1_1[10] = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    unsigned test1_2[10] = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    unsigned test1_3[10] = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    unsigned test1_4[10] = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    unsigned test2_1[3] = {2, 5, 6};
    unsigned test2_2[3] = {2, 5, 6};
    unsigned test2_3[3] = {2, 5, 6};
    unsigned test2_4[3] = {2, 5, 6};
    std::vector<unsigned> vec_test1_1 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    std::vector<unsigned> vec_test1_2 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    std::vector<unsigned> vec_test1_3 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    std::vector<unsigned> vec_test1_4 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    std::vector<unsigned> vec_test1_5 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 71};
    std::vector<unsigned> vec_test2_1 = {2, 5, 6};
    std::vector<unsigned> vec_test2_2 = {2, 5, 6};
    std::vector<unsigned> vec_test2_3 = {2, 5, 6};
    std::vector<unsigned> vec_test2_4 = {2, 5, 6};
    std::vector<unsigned> vec_test2_5 = {2, 5, 6};


    auto res = RemoveZero(test1_1, 10);
    std::cout << "\n RemoveZero Test1 Arr->\n";
    for (auto i: res) {
        std::cout << i << " ";
    }

    auto res2 = RemoveZero(vec_test1_1, 10);
    std::cout << "\n RemoveZero Test2 Vec->\n";
    for (auto i: res2) {
        std::cout << i << " ";
    }

    auto res3 = RemoveExist(test1_2, 10, test2_1, 3);
    std::cout << "\n RemoveExist Test3 Arr->\n";
    for (auto i: test1_2) {
        std::cout << i << " ";
    }

    auto res4 = RemoveExist(vec_test1_2, 10, vec_test2_1, 3);
    std::cout << "\n RemoveExist Test4 Vec->\n";
    for (auto i: vec_test1_2) {
        std::cout << i << " ";
    }

    std::cout << "\n ********* COMPANY FUNC TEST END ********* \n";

    return true;
}

bool poker::CompanyTest::Test1123() {

    std::vector<unsigned> a = {1, 2, 3, 4, 5, 6, 7, 0x4e, 0x4f, 0x4e, 0x39};
    unsigned a1124[] = {1, 2, 3, 4, 5, 6, 7, 0x4e, 0x4f, 0x4e, 0x39};

    auto res = IsLinkCard(a);
    if (res) { std::cout << "is link "; }

    return true;

}

bool poker::CompanyTest::testPrimary() {
    unsigned tempCard[] = {0x01, 0x09, 0x03, 0x04, 0x05, 0x06, 0x08, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x03, 0x04, 0x05, 0x06}, count = 17;

    auto isPrimary = [&](unsigned value) {
        return (GetCardColor(value) == 0x40 || GetCardColor(value) == 0x00 || GetCardValue(value) == 0x02 ||
                GetCardValue(value) == 0x07);
    };
    auto allPrimary = std::all_of(tempCard, tempCard + count, [&](unsigned value) {
        return isPrimary(value);
    });

    /// 关于 all_of 直接入参数组 进行判定 也不会出错

    std::cout << "allPrimary-> " << allPrimary << std::endl;

    if (allPrimary) { std::cout << "nb"; }
    else { std::cout << "oh-------"; }


    unsigned res1112[] = {3, 3, 3, 1, 1};
    unsigned rescopy[5] = {0};
    memcpy(rescopy, res1112, 2 * sizeof(unsigned));
    for (auto i: rescopy) {
        std::cout << "  " << i;
    }
    std::cout << std::endl << std::endl;

//  auto f = [&](unsigned a,unsigned b){ return  a== b;};
    unsigned valueFirst = res1112[0];
    auto fiveSame = std::all_of(res1112, res1112 + 5 - 2, [&](unsigned value) { return value == valueFirst; });
    std::cout << "put->" << fiveSame << std::endl;

    unsigned card[5] = {3, 4, 5, 2, 0};
    bool first = true, back = true;
    testFirstBack(first, back, card);
    std::cout << first << " " << back << std::endl;

    return allPrimary;

}

void poker::CompanyTest::testFirstBack(bool &first, bool &back, unsigned noJokerCard[]) {
    first = true;
    back = true;
    unsigned cbBackA[5] = {10, 11, 12, 13, 1};
    unsigned cbFirstA[5] = {1, 2, 3, 4, 5};
    unsigned temp[5] = {0};
    memcpy(temp, noJokerCard, sizeof(temp));

    for (auto value: temp) {
        if (!value) { continue; }
        auto countBackValue = std::count(cbBackA, cbBackA + 5, GetCardValue(value));
        auto countFirstValue = std::count(cbFirstA, cbFirstA + 5, GetCardValue(value));
        if (!countBackValue) { back = false; }
        if (!countFirstValue) { first = false; }
    }
}

unsigned poker::CompanyTest::mapChange() {

    unsigned bTempCardData[] = {0x21, 0x35, 0x03, 0x12, 0};

    unsigned cbBackA[5] = {10, 11, 12, 13, 1};
    unsigned cbFirstA[5] = {1, 2, 3, 4, 5};
    unsigned cbColor = GetCardColor(bTempCardData[0]) >> 4;
    bool bBackA = true, bFirstA = true;
    for (auto value: bTempCardData) {
        if (!value) { continue; }
        auto countBackValue = std::count(cbBackA, cbBackA + 5, GetCardValue(value));
        auto countFirstValue = std::count(cbFirstA, cbFirstA + 5, GetCardValue(value));
        if (!countBackValue) { bBackA = false; }
        if (!countFirstValue) { bFirstA = false; }
    }
    if (bBackA) {
        for (auto &back: cbBackA) {
            auto haveValue = std::any_of(bTempCardData, bTempCardData + 5, [&](unsigned value) {
                return GetCardValue(value) == back;
            });
            if (!haveValue) {
                back = (cbColor << 4) + back;
            }
        }


        return 2;
    }
    if (bFirstA) {
        for (auto &first: cbFirstA) {
            auto haveValue = std::any_of(bTempCardData, bTempCardData + 5, [&](unsigned value) {
                return GetCardValue(value) == first;
            });
            if (!haveValue) {
                first = (cbColor) + first;
            }
        }


        return 1;
    }
    return 0;
}

unsigned poker::CompanyTest::CountJoker(unsigned cbCardData[], unsigned cbCardCount) {
    return std::count_if(cbCardData,
                         cbCardData + cbCardCount, [&](unsigned value) { return value == 0x4e || value == 0x4f; });
}

bool poker::CompanyTest::IsLinkCard(const unsigned cbCardData[], unsigned cbCardCount) {

    if (cbCardCount <= 0) { return false; }

    unsigned cbCardBuffer[COUNT_MAX] = {0};
    memcpy(cbCardBuffer, cbCardData, cbCardCount * sizeof(unsigned));

    unsigned countJoker = CountJoker(cbCardBuffer, cbCardCount);
    if (countJoker >= cbCardCount - 1) { return true; }

    unsigned noJokerCardData[COUNT_MAX] = {0};
    memcpy(noJokerCardData, &cbCardBuffer[0], cbCardCount * sizeof(unsigned));
    for (unsigned &value: noJokerCardData) {
        if (value == 0x4e || value == 0x4f) { value = 0; }
    }
    SortCardList(noJokerCardData, COUNT_MAX, enDescend);

    for (unsigned &value: noJokerCardData) {
        /// 遇王或空值直接退出
        if (!value) { break; }
        /// noJokerCardData 转化为纯 value
        value = GetCardValue(value);
        if (std::count(noJokerCardData, noJokerCardData + COUNT_MAX, value) > 1) {
            return false;
        }
    }

    unsigned cbFirstCard = noJokerCardData[0];
    if (cbFirstCard == 1) {
        if (noJokerCardData[1] == cbCardCount) { cbFirstCard = cbCardCount + 1; }
    }

    return cbFirstCard - noJokerCardData[cbCardCount - countJoker - 1] < cbCardCount;
}

bool poker::CompanyTest::IsLinkCard(const std::vector<unsigned> &cbCardData) {
    if (cbCardData.empty()) { return false; }
    unsigned cbCardCount = cbCardData.size();

    unsigned *cbCardBuffer = new unsigned[cbCardData.size()];
    memcpy(cbCardBuffer, &cbCardData[0], cbCardData.size() * sizeof(cbCardData[0]));

    unsigned countJoker = CountJoker(cbCardBuffer, cbCardCount);
    if (countJoker >= cbCardCount - 1) { return true; }

    unsigned noJokerCardData[COUNT_MAX] = {0};
    memcpy(noJokerCardData, &cbCardBuffer[0], cbCardData.size() * sizeof(cbCardData[0]));
    for (unsigned &value: noJokerCardData) {
        if (value == 0x4e || value == 0x4f) { value = 0; }
    }
    SortCardList(noJokerCardData, COUNT_MAX, enDescend);

    for (unsigned &value: noJokerCardData) {
        /// 遇王或空值直接退出
        if (!value) { break; }
        /// noJokerCardData 转化为纯 value
        value = GetCardValue(value);
        if (std::count(noJokerCardData, noJokerCardData + COUNT_MAX, value) > 1) {
            return false;
        }
    }

    unsigned cbFirstCard = noJokerCardData[0];
    if (cbFirstCard == 1) {
        if (noJokerCardData[1] == cbCardCount) { cbFirstCard = cbCardCount + 1; }
    }

    return cbFirstCard - noJokerCardData[cbCardCount - countJoker - 1] < cbCardCount;
}
