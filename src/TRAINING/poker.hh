//
// Created by AUGUS on 2021/5/28.
//

#ifndef AUGUSTEST_CSWL_HH
#define AUGUSTEST_CSWL_HH

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <cstring>

#include "augus/augus.h"

namespace poker {


struct CommonPart
{
    CommonPart() = default;
    ~CommonPart() = default;
    static unsigned GetCardValue(unsigned cbCardData);
    static unsigned GetCardColor(unsigned cbCardData);
};

class Poker: public CommonPart
{
public:
    Poker() = default;
    ~Poker() = default;
public:
    constexpr const static unsigned CARD_DATA[54] =
        {
            0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,    //方块 A - K
            0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,    //梅花 A - K
            0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,    //红桃 A - K
            0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,    //黑桃 A - K
            0x4E, 0x4F,
        };

    enum enSortCardType
    {
        enDescend,
        enAscend,
        enColor,
        enCount,
    };

    const static unsigned COUNT_POKER = 54;
    const static unsigned COUNT_POKER_NO_JOKER = 52;
    const static unsigned COUNT_DECK = 2;
    const static unsigned COUNT_MAX = 33;
    static bool isJoker(unsigned cbCardData);
    virtual bool checkData(const unsigned *cardData, unsigned cardCount);
    virtual unsigned GetCardLogicValue(unsigned cbCardData);
    unsigned GetFirstColor(const unsigned cbCardData[], unsigned cbCardCnt);

    bool IsPrimaryCard(unsigned cbCardData, unsigned cbPrimaryColor);

    virtual inline bool isValidCard(unsigned cbCardData);

    // 公务员：大王、小王，黑桃A、主2、6个副2；
    inline bool defaultPrimaryCard(unsigned cbCardData);

    void SortCardList(unsigned cbCardData[], unsigned cbCardCount, enSortCardType SortCardType, bool ori);

    void SortCardList(unsigned cbCardData[], unsigned cbCardCount, enSortCardType SortCardType);

};

class Mahjong: public CommonPart
{
public:
    Mahjong() = default;
    ~Mahjong() = default;
};

class Thirteen: public Poker
{
public:
    Thirteen() = default;
    ~Thirteen() = default;
};

class ThreeAgainstOne: public Poker
{
public:
    ThreeAgainstOne() = default;
    ~ThreeAgainstOne() = default;
public:
    const static unsigned COUNT_MAX_SAME = 8;
    const static unsigned COUNT_MAX = 33;
    const static unsigned ERROR_COLOR = 0xff;
    const static unsigned PRIMARY_COLOR = 0x50;

    enum CARD_TYPE
    {
        CT_ERROR = 0,                                    //错误类型
        CT_SINGLE,                                    //单牌类型
        CT_DOUBLE,                                    //对牌类型
        CT_THREE,                                    //三条类型
        CT_SINGLE_LINE,                                    //单连类型
        CT_DOUBLE_LINE,                                    //对连类型
        CT_THREE_LINE,                                    //三连类型
        CT_THREE_LINE_TAKE_ONE,                                    //三带一单
        CT_THREE_LINE_TAKE_TWO,                                    //三带一对
        CT_FOUR_LINE_TAKE_ONE,                                    //四带两单
        CT_FOUR_LINE_TAKE_TWO,                                    //四带两对
        CT_BOMB_CARD,                                    //炸弹类型
        CT_MISSILE_CARD,                                //火箭类型
        CT_SPECIAL,                                    //八龙
    };

    struct tagSameAnalyseResult
    {
        unsigned cbKingCount;
        unsigned cbBlockCount[COUNT_MAX_SAME];
        unsigned cbCardData[COUNT_MAX_SAME][COUNT_MAX];
    };

    struct tagSearchCardResult
    {
        unsigned cbSearchCount;                    //扑克数目
        unsigned cbCardCount[COUNT_MAX];                    //扑克数目
        unsigned cbResultCard[COUNT_MAX][COUNT_MAX];                        //扑克数据
    };

    struct tagDistributing
    {
        unsigned cbCardCount;                    //扑克数目
        unsigned cbDistributing[15][6];                        //扑克数据
    };

    unsigned GetCardLogicValue(unsigned cbCardData, unsigned byPrimaryColor);
    bool isPrimaryCard(unsigned cbCardData, unsigned cbPrimaryColor);
    CARD_TYPE GetCardType(const unsigned cbCardData[], unsigned cbCardCount, unsigned cbPrimaryColor);

    // 此函数入参花色必须为 形如黑桃0x30
    void SortHandCardListByPrimary(unsigned cbCardData[],
                                   unsigned cbCardCount,
                                   const bool bDragonData[],
                                   unsigned specificColor);
    bool findStraightType(const unsigned byHandCardData[],
                          unsigned byHandCardCount,
                          unsigned &byReferCard,
                          unsigned countType,
                          unsigned countMaxStraight,
                          unsigned byPrimaryColor);
    //甩牌分析模块
public:

    unsigned findMaxLogicValue(const unsigned *cbCardData,
                               unsigned cbCardCount,
                               unsigned cbPrimaryColor,
                               unsigned cbCurrentColor);
    bool analyseCardData(const unsigned *cbCardData, unsigned cbCardCount,
                         tagSameAnalyseResult &AnalyseResult, unsigned cbPrimaryColor);
    bool compareThrowCard(const unsigned cbFirstCard[], const unsigned cbNextCard[],
                          unsigned cbFirstCount, unsigned cbNextCount,
                          unsigned cbPrimaryColor, unsigned cbCurrentColor);
    //searchSameCard searchLineCardType 方法里的 cbCurrentColor 无须过虑 只用花色判断即可
    unsigned searchSameCard(const unsigned *cbHandCardData,
                            unsigned cbHandCardCount,
                            unsigned cbReferCard,
                            unsigned cbSameCardCount,
                            tagSearchCardResult &pSearchCardResult,
                            unsigned cbPrimaryColor,
                            unsigned cbCurrentColor);
    unsigned searchLineCardType(const unsigned *cbHandCardData, unsigned cbHandCardCount,
                                unsigned cbReferCard, unsigned cbBlockCount, unsigned cbLineCount,
                                tagSearchCardResult &pSearchCardResult,
                                unsigned cbPrimaryColor, unsigned cbCurrentColor);
    bool analyseDistributing(const unsigned *cbCardData, unsigned cbCardCount, tagDistributing &Distributing);
    unsigned MakeCardData(unsigned cbValueIndex, unsigned cbColorIndex);
    bool searchOutCard(const unsigned *cbHandCardData, unsigned cbHandCardCount,
                       const unsigned *cbTurnCardData, unsigned cbTurnCardCount,
                       tagSearchCardResult &pSearchCardResult,
                       unsigned cbPrimaryColor, unsigned cbCurrentColor);
    unsigned findSameCards(unsigned wChairID, const unsigned byCardData[], unsigned byCardCount);

};

class CompanyTest: public Poker, public Mahjong
{
public:
    CompanyTest();
    ~CompanyTest();

    std::vector<unsigned> RemoveZero(unsigned source_arr[], unsigned source_length, bool just_test);

    bool
    RemoveExist(std::vector<unsigned> &source_arr,
                unsigned source_length,
                std::vector<unsigned> delete_arr,
                unsigned delete_length);

    bool RemoveExist(unsigned source_arr[], unsigned source_length, unsigned delete_arr[], unsigned delete_length);

    std::vector<unsigned> RemoveZero(std::vector<unsigned> source_arr, unsigned source_length);

    std::vector<unsigned> RemoveZero(unsigned source_arr[], unsigned source_length);

    void InsertToMap(unsigned *a, unsigned n, std::map<unsigned, unsigned> &out_map);

    void SprintMap(std::map<unsigned, unsigned> &count_map);

    bool IsSameColorCard(const std::vector<unsigned> &cbCardData, unsigned cbCardCount);

    bool Test();

    bool Test1123();

    bool testPrimary();

    void testFirstBack(bool &first, bool &back, unsigned noJokerCard[]);

    unsigned mapChange();

    unsigned CountJoker(unsigned cbCardData[], unsigned cbCardCount);

    bool IsLinkCard(const unsigned cbCardData[], unsigned cbCardCount);

    bool IsLinkCard(const std::vector<unsigned> &cbCardData);
};
}//namespace poker

#endif //AUGUSTEST_CSWL_HH
