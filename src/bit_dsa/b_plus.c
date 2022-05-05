//[程序] B + 树索引的实现(定稿 2 / 1)

/*
作者：  lee
创建时间： 2008-5-13
最后修改： 2008-6-14 14:16:49
联系方式： leeocean2004@163.com
程序说明： b+树结构管理数据
附加说明:
(0)结点数据结构：[流水号,帐号,姓名,金额,附加说明,按不同索引的下一位的指针];
(1)读写数据统一用直接地址而不用单元个数;
(2)全局变量的命名规则是所有首字母大写,其它命名规则是"驼峰命名法";
(3)由于读取的数据的主码是账号都是正整数,所以如果索引中key为负值的话则表示该关键字为空;
(4)插入的方式是首先插入到数据文件中,如果索引启动了再维护索引文件;
(5)流水号说明:由16位组成,前10位用1700年以来的秒数表示,后面5位按流水号1秒钟10万条数据足够了,现实检验1秒最多也不超过1000条
不可能有这么快的速度,最后一位存储'/0';
(6)本程序只实现了帐号字段的索引建立,但是由于时间问题没有给流水号,姓名和金额建立b+树索引,不过道理是一样的,由于它们是字符串,
所以比较不用大于小于号，而用strcmp()函数,有待进一步完善,在数据管理方面只做了数据插入,没有数据删除,同样有待完善。
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define M   51  // M表示b+树的阶数,可以随意修改但是必须大于等于3阶
#define MAX 500000                  // 数据源数据条数,50万条
#define DH  sizeof(dataHead)        // 数据文件头的单位长度
#define DN  sizeof(dataNode)        // 数据结点单位长度
#define AIH sizeof(acctIndexHead)   // 帐号索引文件头单位长度
#define AIN sizeof(acctIndexNode)   // 帐号索引结点单位长度
#define NIH sizeof(nameIndexHead)   // 姓名索引文件头结点长度
#define NIN sizeof(nameIndexNode)   // 姓名索引结点长度
#define SNS sizeof(sourceDataCell)  // 数据源数据结点长度
#define IAN sizeof(indexAdmiNode)   // 索引管理结点长度

//--------------------------------------------------------------------------------
//全局变量(命名规则:所有单词首字母大写)
int DENum;          // 有效数据数
int DANum;          // 总数据数
int AIENum;         // 有效帐号索引结点数
int AIANum;         // 总帐号索引结点数
int ATLayer;        // 帐号索引中b+树的层数
int NIENum;         // 有效姓名索引节点数
int NIANum;         // 总姓名有效结点数
int NTLayer;        // 姓名索引中b+树的层数
int IsAcctIndexOn;  // 是否帐号索引启动
int IsNameIndexOn;  // 是否姓名索引启动
int IsBalaIndexOn;  // 是否金额索引启动
int IsSerlIndexOn;  // 是否流水索引启动
int SerialControl;  // 流水号控制,每一个秒中的开始从0一直往下,最大到99999,再往下就装不下了,不过电脑速度没有那么快,一秒插入10万条记录
time_t PreSec;      // 上一个时间(由秒数来确定)

//--------------------------------------------------------------------------------
//所有数据结构体声明
//---------------------------------------------- 1.1数据头结点
typedef struct {
    int dENum;  // 有效数据数
    int dANum;  // 数据总数
} dataHead;

//---------------------------------------------- 1.2数据结点
typedef struct {
    char serialNum[16];  // 流水号,前10位是时间,后5位是流水号,最后一位是'/0'
    int acct;            // 帐号4b/8b
    char name[16];       // 帐户名32b
    double balance;    // 帐号金额,8b
    char other[432];   // 其它附加信息432b
    int insertTime;    // 插入数据时间,4b/8b
    int nextAcctAddr;  // 下一个相同帐号的地址4b/8b
    int nextNameAddr;  // 下一个相同姓名的地址
    int nextNoAddr;    // 下一个编号地址
    int nextBalAddr;   // 下一个金额地址
} dataNode;

//---------------------------------------------- 2.1帐号索引头结点
typedef struct {
    int tLayer;     // b+树得层数
    int rootP;      // 树的根的指针,用于随机查找
    int leftLeafP;  // 指向最左面的叶子结点,用于连续读取
    int iENum;      // 有效索引结点数
    int iANum;      // 总索引结点数
} acctIndexHead;

//---------------------------------------------- 2.2姓名索引头结点
typedef struct {
    int tLayer;     // b+树得层数
    int rootP;      // 树的根的指针,用于随机查找
    int leftLeafP;  // 指向最左面的叶子结点,用于连续读取
    int iENum;      // 有效索引结点数
    int iANum;      // 总索引结点数
} nameIndexHead;

//---------------------------------------------- 2.3时间索引头结点
typedef struct {
    int tLayer;     // b+树得层数
    int rootP;      // 树的根的指针,用于随机查找
    int leftLeafP;  // 指向最左面的叶子结点,用于连续读取
    int iENum;      // 有效索引结点数
    int iANum;      // 总索引结点数
} timeIndexHead;
//---------------------------------------------- 3.1帐号索引结点
typedef struct {
    int num;            // 本结点中所包含的关键字个数
    int key[M];         // 关键字
    int childP[M + 1];  // 关键字的指针
    int parentP;        // 结点的父结点的位置
    int isMostRight;  // 是否在本层属于最右边的一个结点,因为这样的结点的child[M]总指向下一层,而其他的则指向同层的下一结点
    int isLeaf;
} acctIndexNode;
//---------------------------------------------- 3.2姓名索引结点
typedef struct {
    int num;            // 本结点中所包含的关键字个数
    char name[M][16];   // 关键字,姓名
    int childP[M + 1];  // 关键字的指针
    int parentP;        // 结点的父结点的位置
    int isMostRight;  // 是否在本层属于最右边的一个结点,因为这样的结点的child[M]总指向下一层,而其他的则指向同层的下一结点
    int isLeaf;
} nameIndexNode;

//---------------------------------------------- 3.3时间索引结点
typedef struct {
    int num;            // 本结点中所包含的关键字个数
    int key[M];         // 关键字
    int childP[M + 1];  // 关键字的指针
    int parentP;        // 结点的父结点的位置
    int isMostRight;  // 是否在本层属于最右边的一个结点,因为这样的结点的child[M]总指向下一层,而其他的则指向同层的下一结点
    int isLeaf;
} timeIndexNode;
//---------------------------------------------- 4姓名部分
typedef struct {
    int no;         // 编号
    char name[16];  // 姓名
} nameNode;

//---------------------------------------------- 5说明部分
typedef struct {
    int no;           // 编号
    char other[432];  // 说明
} otherNode;

//---------------------------------------------- 6.1根据帐号在结点中查找结果
typedef struct {
    int n;          // 返回查找结点的中的位数
    int key;        // 查找的最接近查询的值
    int selfAddr;   // 本身结点的地址
    int childAddr;  // 数据地址
} sANRNode;

//---------------------------------------------- 6.2根据姓名在结点中查找结果
typedef struct {
    int n;          // 返回查找结点的中的位数
    char name[16];  // 查找的最接近查询的值
    int selfAddr;   // 本身结点的地址
    int childAddr;  // 数据地址
} sNNRNode;

//---------------------------------------------- 7.1根据帐号在树中查找结果
typedef struct {
    int addr;         // 最后叶子结点的地址
    int orderOfNode;  // 在叶子结点之中的位数
    int nearKey;      // 本节点中最小的>=要查询关键字的关键字
    int flag;         // 查找结果,若成功返回1否则返回0
    int dataAddr;
} sATRNode;

//---------------------------------------------- 7.2根据姓名在树中查找结果
typedef struct {
    int addr;           // 最后叶子结点的地址
    int orderOfNode;    // 在叶子结点之中的位数
    char nearName[16];  // 本节点中最小的>=要查询关键字的关键字
    int flag;           // 查找结果,若成功返回1否则返回0
    int dataAddr;
} sNTRNode;

//---------------------------------------------- 8.1帐号索引单元
typedef struct {
    int child;  // 孩子指针
    int key;    // 关键字
} acctIndexCell;

//---------------------------------------------- 8.2姓名索引单元
typedef struct {
    int child;      // 孩子指针
    char name[16];  // 关键字
} nameIndexCell;

//---------------------------------------------- 9数据源数据单元
typedef struct {
    int acct;         // 帐号4b/8b
    char name[16];    // 帐户名32b
    char other[432];  // 其它附加信息456b
} sourceDataCell;

//---------------------------------------------- 10日志单元
typedef struct {
    int acct;  // 帐号4b/8b
} logNode;

//---------------------------------------------- 11索引管理文件信息单元
typedef struct {
    int isSerialumIndexOn;  // 是激活在流水号索引,唯一索引
    int isAccountIndexOn;   // 是激活在帐号索引,非唯一索引
    int isNameIndexOn;      // 是激活在姓名索引,非唯一索引
    int isBalanceIndexOn;   // 是激活在金额所以,非唯一索引
} indexAdmiNode;

//--------------------------------------------------------------------------------
//函数声明
int enterChoice();                                                            // 00
dataHead getDataHead(FILE *dfP);                                              // 01
acctIndexHead getAcctIndexHead(FILE *aifP);                                   // 02.1
nameIndexHead getNameIndexHead(FILE *nifP);                                   // 02.2
dataNode getData(FILE *dfP, int addr);                                        // 03
acctIndexNode getAcctIndex(FILE *aifP, int addr);                             // 04.1
nameIndexNode getNameIndex(FILE *nifP, int addr);                             // 04.2
dataHead setDataHead(FILE *dfP, dataHead dHead);                              // 05
acctIndexHead setAcctIndexHead(FILE *aifP, acctIndexHead aIHead);             // 06.1
nameIndexHead setNameIndexHead(FILE *nifP, nameIndexHead nIHead);             // 06.2
dataNode setData(FILE *dfP, dataNode dNode, int addr);                        // 07
acctIndexNode setAcctIndex(FILE *aifP, acctIndexNode aINode, int addr);       // 08.1
nameIndexNode setNameIndex(FILE *nifP, nameIndexNode nINode, int addr);       // 08.2
int dataCellToAddr(int cell);                                                 // 09
int acctIndexCellToAddr(int cell);                                            // 10.1
int nameIndexCellToAddr(int cell);                                            // 10.2
void initializeDataFile(FILE *dfP);                                           // 11
void initializeAcctIndexFile(FILE *aifP);                                     // 12.1
void initializeNameIndexFile(FILE *nifP);                                     // 12.2
int doAcctIndex(FILE *aifP, acctIndexCell ic);                                // 13.1
int doNameIndex(FILE *nifP, nameIndexCell ic);                                // 13.2
void insertAcctAtFull(FILE *aifP, int oldAddr, acctIndexCell ic);             // 14.1
void insertNameAtFull(FILE *nifP, int oldAddr, nameIndexCell ic);             // 14.2
int insertAcctAtEmpty(FILE *aifP, int addr, acctIndexCell ic);                // 15.1
int insertNameAtEmpty(FILE *nifP, int addr, nameIndexCell ic);                // 15.2
sATRNode searchInTreeByAcct(FILE *aifP, int acct);                            // 16.1
sNTRNode searchInTreeByName(FILE *aifP, char *name);                          // 16.2
sANRNode searchInNodeByAcct(FILE *aifP, int addr, int acct, int n);           // 17.1
sNNRNode searchInNodeByName(FILE *nifP, int addr, char *name);                // 17.2
int disposeAcctIndex(FILE *dfP, FILE *aifP, dataNode dNode, int insertAddr);  // 18.1
int disposeNameIndex(FILE *dfP, FILE *nifP, dataNode dNode, int insertAddr);  // 18.2
void displayAllData(FILE *dfP);                                               // 19
void displayAllAcctIndex(FILE *aifP);                                         // 20.1
void displayAllNameIndex(FILE *nifP);                                         // 20.2
void clear(FILE *iAFP, FILE *dfP, FILE *aifP, FILE *nifP, FILE *nameTxt, FILE *nameBin,
           FILE *otherTxt, FILE *otherBin,
           FILE *sourceBin);                                                // 21
void orderDisplayByAcct(FILE *aifP, FILE *dfP);                             // 22.1
void orderDisplayByName(FILE *nifP, FILE *dfP);                             // 22.2
dataNode displayData(FILE *dfP, int addr, dataNode dNode, int n);           // 23
void displayAcctIndex(acctIndexNode aINode, int n);                         // 24.1
void displayNameIndex(nameIndexNode nINode, int n);                         // 24.2
void displayAcctIndexHead(acctIndexHead aIHead);                            // 25.1
void displayNameIndexHead(nameIndexHead nIHead);                            // 25.2
void insertAcctCell(FILE *aifP, acctIndexCell ic, int addr);                // 26.1
void insertNameCell(FILE *nifP, nameIndexCell ic, int addr);                // 26.2
void initialize(FILE *iAFP, FILE *dfP, FILE *aifP, FILE *nifP);             // 27
void beginOfRun(FILE *iAFP, FILE *dfP, FILE *aifP, FILE *nifP);             // 28
int displayDFAIndex(FILE *dfP, FILE *aifP, acctIndexNode aINode);           // 29.1
int displayDFNIndex(FILE *dfP, FILE *nifP, nameIndexNode nINode);           // 29.2
int makeNewAcctIndexNode(FILE *aifP, int isMostRight, int isLeaf);          // 30.1
int makeNewNameIndexNode(FILE *nifP, int isMostRight, int isLeaf);          // 30.2
int searchAcctInParent(acctIndexNode parent, int childAddr);                // 31.1
int searchNameInParent(nameIndexNode parent, int childAddr);                // 31.2
void setAcctChildParent(FILE *aifP, int childAddr, int selfAddr);           // 32.1
void setNameChildParent(FILE *nifP, int childAddr, int selfAddr);           // 32.2
acctIndexNode setAcctIndexMostRight(FILE *aifP, int addr, int value);       // 33.1
nameIndexNode setNameIndexMostRight(FILE *nifP, int addr, int value);       // 33.2
void searchBetweenByAcct(FILE *aifP, FILE *dfP, int acct1, int acct2);      // 34.1
void searchBetweenByName(FILE *nifP, FILE *dfP, char *name1, char *name2);  // 34.2
dataNode getDataNode();                                                     // 35
void printLine(int length);                                                 // 36
void secToDate(int sec);                                                    // 37
void goOnInsertByAcct(FILE *dfP, int nDAddr, int oDAddr);                   // 38.1
void goOnInsertByName(FILE *dfP, dataNode nDNode, int oDAddr);              // 38.2
void printDataFileTitle(int i);                                             // 39
void autoInsertByAcct(FILE *dfP, FILE *aifP, FILE *sfP, int autoNum);       // 40.1
void autoInsertByName(FILE *dfP, FILE *nifP, FILE *sfP, int autoNum);       // 40.2
dataNode doSNTDN(sourceDataCell sCell, int seconds, int serial);            // 41
void moveKeyByAcct(acctIndexNode oldNode, acctIndexNode newNode,
                   acctIndexCell ic);  // 42.2
void moveKeyByName(nameIndexNode oldNode, nameIndexNode newNode,
                   nameIndexCell ic);                                       // 42.2
void from1to100(FILE *dfP, FILE *aifP, FILE *logP);                         // 43
void logWrite(FILE *logP, int key, int i);                                  // 44
dataNode getFromDataSourceFile(FILE *sfP, int n);                           // 45
void printAcctIndexTitle();                                                 // 46.1
void printNameIndexTitle();                                                 // 49.2
void displaySearchByAcct(FILE *dfP, int addr);                              // 47
double getNewblance();                                                      // 48
void programmeDoor();                                                       // 49
void printProgrammeEnd();                                                   // 50
int indexMenu(FILE *iAFP);                                                  // 51
void acctIndexChange(FILE *iAFP, FILE *aifP, FILE *dfP, int menu);          // 52.1
void balanceIndexChange(FILE *iAFP, FILE *bifP, FILE *dfP, int menu);       // 52.2
void nameIndexChange(FILE *iAFP, FILE *nifP, FILE *dfP, int menu);          // 52.3
void serialIndexChange(FILE *iAFP, FILE *sifP, FILE *dfP, int menu);        // 52.4
indexAdmiNode getIndexAdmiNode(FILE *iAFP);                                 // 53
int insertWithOutIndex(FILE *dfP, dataNode dNode);                          // 54
void initializeIndexAdmini(FILE *iAFP);                                     // 55
indexAdmiNode printIndexState(FILE *iAFP);                                  // 56
void changeAdminiIndex(FILE *iAFP, int i);                                  // 57
indexAdmiNode setAdminiIndex(FILE *iAFP, indexAdmiNode iaNode);             // 58
void rebulidAcctIndex(FILE *dfP, FILE *aifP);                               // 59.1
void rebulidNameIndex(FILE *dfP, FILE *nifP);                               // 59.2
void deleteAcctIndex(FILE *aifP);                                           // 60.1
void deleteNameIndex(FILE *nifP);                                           // 60.2
int searchWithOutIndexByAcct(FILE *dfP, int acct, int startAddr);           // 61.1
int searchWithOutIndexByName(FILE *dfP, char *name);                        // 61.2
dataNode regressDataNext(FILE *dfP, int dataAddr, dataNode dNode);          // 62
void displaySimpleData(FILE *dfP, int addr, dataNode dNode, int n);         // 63
void intToString(int number, int n, char *s);                               // 64
void getManualInput(FILE *aifP, FILE *dfP, FILE *sfP);                      // 65
void readTxtNameWriteBin(FILE *nameTxt, FILE *nameBin);                     // 66
void readTxtOtherWriteBin(FILE *otherTxt, FILE *otherBin);                  // 67
void composeFile(int num, FILE *nameBin, FILE *otherBin, FILE *sourceBin);  // 68
void timeShow(double t);                                                    // 69
void additionalTime0(int t);                                                // 70

//**********************************************************************************************************************
//                    主函数
//**********************************************************************************************************************
int main() {
    FILE *dfP;        // 指向数据文件的指针
    FILE *aifP;       // 指向帐号索引文件的指针
    FILE *nifP;       // 指向姓名索引文件的指针
    FILE *tifP;       // 指向时间索引文件的指针
    FILE *sfP;        // 数据源文件
    FILE *logP;       // 日志文件
    FILE *iAFP;       // 索引管理文件
    FILE *nameTxt;    // 姓名文本文件
    FILE *otherTxt;   // 其他文本文件
    FILE *nameBin;    // 姓名二进制文件
    FILE *otherBin;   // 其他二进制文件
    FILE *sourceBin;  // 数据源文件

    dataNode dNode;    // 存放数据结点
    dataHead dHead;    // 数据文件头结点
    int choice;        // 菜单选项
    int adminiChoice;  // 索引菜单选项
    int searchNum;     // 要查找帐号
    sATRNode sTR;      // 查询返回值
    acctIndexHead h;
    int acct1, acct2;  // 查找的上下限
    int autoNum;       // 自动生成数据条目数
    clock_t start, finish;
    double duration;     // 相隔时间,单位秒
    char makeSure;       // 确认删除
    int insertAddr;      // 插入数据位置
    int searchDataAddr;  // 找到的数据文件的地址

    programmeDoor();  // 打印程序头信息

    dfP = fopen("dataFile.dat", "rb+");  // 打开数据文件,必须手动建立dataFile.dat文件
    aifP = fopen("indexOfAcct.dat",
                 "rb+");  // 打开帐号索引文件,必须手动建立indexOfAcct.dat文件
    nifP = fopen("indexOfName.dat",
                 "rb+");  // 打开姓名索引文件,必须手动建立indexOfName.dat文件
    tifP = fopen("indexOfTime.dat", "rb+");         //
    sfP = fopen("dataSource.dat", "rb");            // 打开数据源文件
    iAFP = fopen("indexAdministrator.dat", "rb+");  // 打开索引管理文教案
    logP = fopen("log.txt", "w+t");                 // 打开日志文件
    nameTxt = fopen("name.txt", "r");
    nameBin = fopen("name.dat", "rb+");
    otherTxt = fopen("other.txt", "r");
    otherBin = fopen("other.dat", "rb+");
    sourceBin = fopen("dataSource.dat", "ab+");

    dHead = getDataHead(dfP);  // 获取数据头文件

    // 若首次运行,因为首次打开的数据文件无数据,读取到的dHead.dANum是乱码所以小于0
    if (dHead.dANum < 0)
        initialize(iAFP, dfP, aifP, nifP);  // 若第一次运行文件对索引文件和数据文件初始化
    else
        beginOfRun(iAFP, dfP, aifP, nifP);  // 获得有关对本程序必要的数据
    while ((choice = enterChoice()) != 0) {
        switch (choice) {
            case 1:  // 手动插入数据,输入ctrl+z结束输入
                     // 由于在数据源文件中的帐号是从1~MAX,所以帐号不能超过MAX
                printf("说明 : 必须帐号在范围 1 到 %d 之间,当输入ctrl+z时候退出插入./n",
                       MAX);
                printf("请输入用户帐号:");
                scanf("%d", &searchNum);
                if (searchNum < 1 || searchNum > MAX) {
                    printLine(23);
                    printf("插入范围错误!/n");
                    goto end1;  // 跳转语句
                }
                // 由输入的整数获得一条帐号和所输整数一样的数据
                dNode = getFromDataSourceFile(sfP, searchNum);
                while (!feof(stdin)) {
                    start = clock();  // 获取程序开始运行时间start
                    insertAddr =
                        insertWithOutIndex(dfP, dNode);  // 首先向数据文件写一条数据
                    if (IsAcctIndexOn == 1) {
                        disposeAcctIndex(dfP, aifP, dNode, insertAddr);
                    }
                    if (IsNameIndexOn == 1) {
                        disposeNameIndex(dfP, nifP, dNode, insertAddr);
                    }
                    finish = clock();  // 获取程序终止时间finish
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;
                    printf("耗时:");
                    timeShow(duration);
                    printf("/n");

                    printf("请输入用户帐号:");
                    scanf("%d", &searchNum);
                    if (searchNum < 1 || searchNum > MAX) {
                        printf("插入范围错误!/n");
                        goto end1;
                    }
                    dNode = getFromDataSourceFile(sfP, searchNum);
                }
            end1:
                break;

            case 2:  // 按物理路径读取全部数据文件
                printf("按物理路径读取全部数据文件:/n");
                displayAllData(dfP);
                break;

            case 3:  // 从左叶子开始读取,形成一个从小到大的链表
                start = clock();
                orderDisplayByAcct(aifP, dfP);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                printf("耗时:");
                timeShow(duration);
                printf("/n");
                break;

            case 4:  // 读取全部索引文件
                start = clock();
                printf("读取全部索引文件:/n");
                displayAllAcctIndex(aifP);
                h = getAcctIndexHead(aifP);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                printf("耗时:");
                timeShow(duration);
                printf("/n");
                break;

            case 5:  // 索引管理
                adminiChoice = indexMenu(iAFP);
                switch (adminiChoice) {
                    case 1:
                        changeAdminiIndex(iAFP, 1);  // 更改索引存在状态
                        if (IsAcctIndexOn == 1)      // 如果要重新建立索引
                        {
                            rebulidAcctIndex(dfP, aifP);
                        } else
                            deleteAcctIndex(aifP);  // 删除帐号索引
                        IsAcctIndexOn == 1 ? printf("帐号索引创建成功!/n")
                                           : printf("帐号索引已停止!/n");

                        break;
                    case 2:
                        changeAdminiIndex(iAFP, 2);
                        break;
                    case 3:
                        changeAdminiIndex(iAFP, 3);
                        break;
                    case 4:
                        changeAdminiIndex(iAFP, 4);
                        break;
                    default:
                        break;
                }

                break;

            case 6:  // 自动生成数据
                printf("请输入想随机生成的数据条目数/n>>");
                scanf("%d", &autoNum);
                autoInsertByAcct(dfP, aifP, sfP, autoNum);  // 包含了有索引无索引的所有情况
                break;

            case 7:  // 随机查找数据
                printf("查找:/n请输入想要查找的帐号(范围: 1 ~ %d)/n>>", MAX);
                scanf("%d", &searchNum);
                if (searchNum > MAX || searchNum < 1) {
                    printf("随机查询范围错误!/n");
                    goto end7;
                }
                start = clock();
                if (IsAcctIndexOn == 1)  // 如果存在索引按索引进行查找
                {
                    printf("按帐号索引查找:/n");
                    sTR = searchInTreeByAcct(aifP, searchNum);  // 在树中查找
                    if (sTR.flag == 0)
                        printf("未找到!/n");
                    else {
                        printDataFileTitle(1);
                        displaySearchByAcct(dfP, sTR.dataAddr);
                    }
                } else  // 如果不存在索引则从头往尾找
                {
                    printf("无索引查找:/n");
                    printDataFileTitle(1);
                    searchDataAddr = searchWithOutIndexByAcct(
                        dfP, searchNum, DH);  // 从第一个数据开始查找
                    while (searchDataAddr != -1) {
                        dNode = getData(dfP, searchDataAddr);
                        displaySimpleData(dfP, searchDataAddr, dNode,
                                          1);  // 显示找到的数据
                        searchDataAddr = searchWithOutIndexByAcct(
                            dfP, searchNum, searchDataAddr + DN);  // 继续找下一条
                    }
                }
                printLine(24);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                printf("耗时:");
                timeShow(duration);
                printf("/n");
            end7:
                break;

            case 8:  // 清空数据文件和索引文件中数据,但初始化它们
                printf("确实要删除全部数据吗?(Y/N)/n>>");
                fflush(stdin);
                makeSure = getchar();
                if (makeSure - 'y' == 0 || makeSure - 'Y' == 0) {
                    clear(iAFP, dfP, aifP, nifP, nameTxt, nameBin, otherTxt, otherBin,
                          sourceBin);
                    printf("已经把数据文件和索引文件中的所有数据全部清除!/n");
                } else {
                    printf("删除取消!/n");
                }
                break;

            case 9:  // 范围查找,也是B+树的一个优势
                printf("请输入查找范围的下限和上限(范围: 1 ~ %d),中间用空格相隔/n", MAX);
                printf("下限:");
                scanf("%d", &acct1);
                printf("上限:");
                scanf("%d", &acct2);
                if (acct1 > MAX || acct1 < 1 || acct2 > MAX || acct2 < 1) {
                    printf("范围查询范围错误!/n");
                    goto end9;
                }
                start = clock();
                searchBetweenByAcct(aifP, dfP, acct1, acct2);
                finish = clock();
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                if (duration > 0.001) {
                    printf("耗时:");
                    timeShow(duration);
                    printf("/n");
                }
            end9:
                break;

            case 10:  // 范围查找,也是B+树的一个优势
                getManualInput(aifP, dfP, sfP);
                break;
        }
    }
    printf("/n关闭数据文件和索引文件./n");
    fclose(dfP);
    fclose(aifP);
    printProgrammeEnd();

    return 0;
}

//*****************************************函数定义********************************************
//*****************************************函数定义********************************************
//--------------------------------------------------------------------------------
//0用户菜单 用户输入菜单选项#
int enterChoice() {
    int menuChoice;  // 存储用户选项的变量
    printf("/n当前数据文件中有%d条有效数据,总共%d条数据---/n", DENum, DANum);
    IsAcctIndexOn == 1 ? printf("帐号索引: /t  [已启动]/n")
                       : printf("帐号索引: [已停止]/n");
    IsBalaIndexOn == 1 ? printf("金额索引: /t  [已启动]/n")
                       : printf("金额索引: [已停止]/n");
    IsNameIndexOn == 1 ? printf("姓名索引: /t  [已启动]/n")
                       : printf("姓名索引: [已停止]/n");
    IsSerlIndexOn == 1 ? printf("流水索引: /t  [已启动]/n")
                       : printf("流水索引: [已停止]/n");
    printf(
        "/n输入菜单：>>/n"
        "1: 插入数据   "
        "2: 物理读取   "
        "3: 顺序读取   "
        "4: 读取索引   "
        "5: 索引管理/n"
        "6: 自动生成   "
        "7: 数据查找   "
        "8: 清空数据   "
        "9: 范围查询   "
        "10:手动插入   "
        "0: 退出/n请选择>>");
    scanf("%d", &menuChoice);  // 从用户处获得选项
    if (menuChoice >= 1 && menuChoice <= 10) {
        menuChoice = menuChoice;
    } else
        menuChoice = 0;
    return menuChoice;
}

//--------------------------------------------------------------------------------
//1读数据文件头 说明: 读取数据文件头返回头结点
dataHead getDataHead(FILE *dfP) {
    dataHead dHead;  // 头结点

    rewind(dfP);
    fread(&dHead, DH, 1, dfP);
    return dHead;
}

//-------------------------------------------------------------------------------- 2.1读帐号索文件引头
// 说明:读取并返回索引文件头
acctIndexHead getAcctIndexHead(FILE *aifP) {
    acctIndexHead aIHead;

    rewind(aifP);
    fread(&aIHead, AIH, 1, aifP);
    return aIHead;
}

//-------------------------------------------------------------------------------- 2.2读姓名索文件引头
// 说明:读取并返回姓名索引文件头
nameIndexHead getNameIndexHead(FILE *nifP) {
    nameIndexHead nIHead;

    rewind(nifP);
    fread(&nIHead, NIH, 1, nifP);
    return nIHead;
}

//--------------------------------------------------------------------------------
//3读数据结点 说明:在数据文件addr处读取数据项并显示
dataNode getData(FILE *dfP, int addr) {
    dataNode dNode;

    fseek(dfP, addr, SEEK_SET);
    fread(&dNode, DN, 1, dfP);
    return dNode;
}

//-------------------------------------------------------------------------------- 4.1读帐号索引:-)
// 说明:在索引文件addr处读取索引数据并返回
acctIndexNode getAcctIndex(FILE *aifP, int addr) {
    acctIndexNode aINode;

    fseek(aifP, addr, SEEK_SET);
    fread(&aINode, AIN, 1, aifP);
    return aINode;
}
//-------------------------------------------------------------------------------- 4.2读姓名索引
// 说明:在索引文件addr处读取索引数据并返回
nameIndexNode getNameIndex(FILE *nifP, int addr) {
    nameIndexNode nINode;

    fseek(nifP, addr, SEEK_SET);
    fread(&nINode, NIN, 1, nifP);
    return nINode;
}

//--------------------------------------------------------------------------------
//5写数据头 说明:将数据头结点dHead写入数据文件
dataHead setDataHead(FILE *dfP, dataHead dHead) {
    rewind(dfP);
    fwrite(&dHead, DH, 1, dfP);
    return dHead;
}

//-------------------------------------------------------------------------------- 6.1写帐号索引头
// 说明:把帐号索引文件头aIHead写入帐号索引文件
acctIndexHead setAcctIndexHead(FILE *aifP, acctIndexHead aIHead) {
    rewind(aifP);
    fwrite(&aIHead, AIH, 1, aifP);
    return aIHead;
}

//-------------------------------------------------------------------------------- 6.2写姓名索引头
// 说明:把姓名索引文件头nIHead写入姓名索引文件
nameIndexHead setNameIndexHead(FILE *nifP, nameIndexHead nIHead) {
    rewind(nifP);
    fwrite(&nIHead, NIH, 1, nifP);
    return nIHead;
}

//-------------------------------------------------------------------------------- 7写数据
// 说明:把数据dNode写入到文件dfp中addr的位置
dataNode setData(FILE *dfP, dataNode dNode, int addr) {
    fseek(dfP, addr, SEEK_SET);
    fwrite(&dNode, DN, 1, dfP);
    return dNode;
}

//-------------------------------------------------------------------------------- 8.1写帐号索引
// 说明:把帐号索引结点aINode写入到索引文件aifP的addr的位置
acctIndexNode setAcctIndex(FILE *aifP, acctIndexNode aINode, int addr) {
    fseek(aifP, addr, SEEK_SET);
    fwrite(&aINode, AIN, 1, aifP);
    return aINode;
}

//-------------------------------------------------------------------------------- 8.2写姓名索引
// 说明:把姓名索引nINode结点写入到索引文件nifP的addr的位置
nameIndexNode setNameIndex(FILE *nifP, nameIndexNode nINode, int addr) {
    fseek(nifP, addr, SEEK_SET);
    fwrite(&nINode, NIN, 1, nifP);
    return nINode;
}

//--------------------------------------------------------------------------------
//9数据文件单元与地址转换 说明:把数据文件中的单元数转化成的地址,cell>=0
int dataCellToAddr(int cell) {
    int addr;

    addr = cell * DN + DH;
    return addr;
}

//-------------------------------------------------------------------------------- 10.1帐号索引文件单元与地址转换
// 说明:把帐号索引文件中的单元数转化成的地址,cell>=0
int acctIndexCellToAddr(int cell) {
    int addr;

    addr = cell * AIN + AIH;
    return addr;
}

//-------------------------------------------------------------------------------- 10.2姓名索引文件单元与地址转换
// 说明:把姓名索引文件中的单元数转化成的地址,cell>=0
int nameIndexCellToAddr(int cell) {
    int addr;

    addr = cell * NIN + NIH;
    return addr;
}

//--------------------------------------------------------------------------------
//11数据文件初始化 说明:初始化数据文件让其有效数据数和总数据数都=0
void initializeDataFile(FILE *dfP) {
    dataHead dHead;

    dHead.dANum = 0;
    dHead.dENum = 0;
    DENum = 0;  // 0个有效数据,给全局变量赋值
    DANum = 0;  // 0个数据,给全局变量赋值
    setDataHead(dfP, dHead);
}

//-------------------------------------------------------------------------------- 12.1
//帐号索引文件初始化
// 说明:让索引文件头中,层数为1,根指指针和左叶子指针都为AIH,并生成一空的索引结点aINode
void initializeAcctIndexFile(FILE *aifP) {
    int i;                 // 循环变量
    acctIndexHead aIHead;  // 索引头结点
    acctIndexNode aINode;  // 索引节点

    aIHead.tLayer = 1;
    aIHead.rootP = AIH;
    aIHead.leftLeafP = AIH;
    aIHead.iANum = 1;
    aIHead.iENum = 1;
    setAcctIndexHead(aifP, aIHead);  // 写入索引文件
    aINode.num = 0;
    for (i = 0; i < M; i++)  // 无值的全部赋值-1
    {
        aINode.childP[i] = -1;
        aINode.key[i] = -1;
    }
    aINode.childP[M] = -1;            // 给最末的孩子指针赋值-1
    aINode.parentP = 0;               // 指向索引文件的头文件
    aINode.isMostRight = 1;           // 是最右结点
    aINode.isLeaf = 1;                // 是叶子结点
    setAcctIndex(aifP, aINode, AIH);  // 写入索引文件
    AIENum = 1;                       // 1个有效索引结点,给全局变量赋值
    AIANum = 1;                       // 1个索引结点,给全局变量赋值
    ATLayer = 1;                      // 树的层数为1,给全局变量赋值
}

//-------------------------------------------------------------------------------- 12.2姓名索引文件初始化
// 说明:让姓名索引文件头中,层数为1,根指指针和左叶子指针都为NIH,并生成一空的姓名索引结点nINode
void initializeNameIndexFile(FILE *nifP) {
    int i;                 // 循环变量
    nameIndexHead nIHead;  // 索引头结点
    nameIndexNode nINode;  // 索引节点

    nIHead.tLayer = 1;
    nIHead.rootP = NIH;
    nIHead.leftLeafP = NIH;
    nIHead.iANum = 1;
    nIHead.iENum = 1;
    setNameIndexHead(nifP, nIHead);  // 写入索引文件
    nINode.num = 0;
    for (i = 0; i < M; i++)  // 无值的全部赋值-1
    {
        strcpy(nINode.name[i], "");  // 赋空
        nINode.childP[i] = -1;
    }
    nINode.childP[M] = -1;            // 给最末的孩子指针赋值-1
    nINode.parentP = 0;               // 指向索引文件的头文件
    nINode.isMostRight = 1;           // 是最右结点
    nINode.isLeaf = 1;                // 是叶子结点
    setNameIndex(nifP, nINode, NIH);  // 写入索引文件
    NIENum = 1;                       // 1个有效索引结点,给全局变量赋值
    NIANum = 1;                       // 1个索引结点,给全局变量赋值
    NTLayer = 1;                      // 树的层数为1,给全局变量赋值
}

//-------------------------------------------------------------------------------- 13.1调整帐号索引
// 说明:若索引中无这条数据则整理索引文件并返回1,否则返回0,若是有效插入整理索引
int doAcctIndex(FILE *aifP, acctIndexCell ic) {
    acctIndexHead aIHead;
    acctIndexNode aINode;
    sATRNode sTR;  // 在整棵树中查找的返回值
    int addr;      // 下一个要查询地的地址

    aIHead = getAcctIndexHead(aifP);  // 读取索引的头文件,存放在aIHead中
    addr = aIHead.rootP;              // 获取索引中根结点的地址
    sTR = searchInTreeByAcct(
        aifP, ic.key);  // 确定在树中查找要插入关键字ic.key要插入的位置,最终指向叶子结点
    if (sTR.flag == 1)  // 在索引中已经存在则不插入
    {
        return sTR
            .dataAddr;  // 如果已经在数据文件中存在了这条数据,则返回原来已经存在结点的地址以供重新插入
    } else              // 在索引中不存在重复值的情况,正常插入
    {
        aINode = getAcctIndex(aifP, sTR.addr);  // 读取要插入的叶子结点
        if (aINode.num < M)  // 若结点中关键字未满,则直接可以插入无需分裂
            insertAcctAtEmpty(aifP, sTR.addr, ic);
        else  // 若在结点当中已经有了M个关键字了,这个时候需要分裂然后插入
            insertAcctAtFull(aifP, sTR.addr, ic);
        return 0;
    }
}

//-------------------------------------------------------------------------------- 13.2调整姓名索引
// 说明:若索引中无这条数据则整理索引文件并返回1,否则返回0,若是有效插入整理索引
int doNameIndex(FILE *nifP, nameIndexCell ic) {
    return 0;  // 待扩充...
}

//-------------------------------------------------------------------------------- 14.1在帐号满结点中插入
// 在账号索引中,如果账号索引中关键字已经有M个的插入方法,要牵扯分裂,核心代码!
void insertAcctAtFull(FILE *aifP, int oldAddr, acctIndexCell ic) {
    int newAddr;                // 新地址
    int parentAddr;             // 前面一个的地址
    int i, j;                   // 循环变量
    int moveN;                  // 移动次数
    acctIndexCell tempIC;       // 提取旧结点中最大值插入其父结点中
    acctIndexNode oldIndex;     // 待分裂的结点
    acctIndexNode newIndex;     // 用于装新移入的单元
    acctIndexNode parentIndex;  // 待分裂结点的父结点
    acctIndexHead aIHead;

    oldIndex = getAcctIndex(aifP, oldAddr);  // 获取要分裂结点oldIndex

    // 生成新的结点newIndex
    // 如果在最右结点中进行分裂,则必定新结点变为非最右结点,同时新结点取代最右结点*
    if (oldIndex.isMostRight == 1) {
        newAddr = makeNewAcctIndexNode(
            aifP, 1,
            oldIndex
                .isLeaf);  // 新的结点,若old节点是最右节点则它也是最右节点,他和old节点在同一层
    } else {
        newAddr = makeNewAcctIndexNode(aifP, 0, oldIndex.isLeaf);
    }
    newIndex = getAcctIndex(aifP, newAddr);  // 获取新结点newIndex

    // 非最右结点,三个结点建立联系
    if (oldIndex.isMostRight == 0)  // 非最右节点
    {
        newIndex.childP[M] = oldIndex.childP[M];
        oldIndex.childP[M] = newAddr;
        newIndex = setAcctIndex(aifP, newIndex, newAddr);
        oldIndex = setAcctIndex(aifP, oldIndex, oldAddr);
    }

    // 最右结点的最后一个指针总是指向下一层的一个最大值,并不像其它指针一样指向同层的兄弟结点
    else {
        newIndex.childP[(M + 1) / 2] = oldIndex.childP[M];
        if (oldIndex.isLeaf == 0) {
            setAcctChildParent(aifP, oldIndex.childP[M], newAddr);
        }
        oldIndex.childP[M] = newAddr;
        oldIndex = setAcctIndex(aifP, oldIndex, oldAddr);
        oldIndex = setAcctIndexMostRight(aifP, oldAddr, 0);
        newIndex = setAcctIndex(aifP, newIndex, newAddr);
    }

    // 获得oldIndex的父结点
    if (oldIndex.parentP == 0)  // 若头结点就是要分裂结点的父结点,此时需要重新生成父结点
    {
        // 生成一个新的根结点,这个结点最终肯定是最右结点
        parentAddr = makeNewAcctIndexNode(aifP, 1, 0);
        parentIndex = getAcctIndex(aifP, parentAddr);
        parentIndex.parentP = 0;
        parentIndex.childP[0] = oldAddr;
        parentIndex = setAcctIndex(aifP, parentIndex, parentAddr);

        // 修改索引头文件
        aIHead = getAcctIndexHead(aifP);
        aIHead.rootP = parentAddr;  // 索引文件头结点指向这个新的根结点
        aIHead.tLayer = ++ATLayer;
        setAcctIndexHead(aifP, aIHead);  // 每产生一个新的根结点,树就高一层

        // 处理旧结点和新根结点直接的联系
        oldIndex.parentP = parentAddr;
        oldIndex =
            setAcctIndex(aifP, oldIndex, oldAddr);  // 把新的根结点赋值给parentIndex结点
    } else                                          // 父结点不是索引文件头
    {
        parentAddr = oldIndex.parentP;  // 获取分裂结点父结点的地址parentAddr
        parentIndex = getAcctIndex(aifP, parentAddr);  // 获取父结点ParentIndex
    }

    // 把指向旧结点的父结点的指针指向新结点,寻找那个原来指向旧结点的指针,现在指向新结点
    for (i = 0; i <= parentIndex.num && parentIndex.childP[i] != oldAddr; i++) {
    };
    parentIndex.childP[i] = newAddr;
    parentIndex = setAcctIndex(aifP, parentIndex, parentAddr);
    setAcctChildParent(aifP, newAddr, parentAddr);  // 这里肯定得改父结点
    newIndex = getAcctIndex(aifP, newAddr);
    moveN = (M % 2 == 0) ? (M / 2) : (M / 2 + 1);  // 新结点中移进的关键字及其孩子个数

    // 移入新结点个数,这里不用调用直接插入函数效率更高
    for (i = 1, j = 1; i <= moveN; i++, j++) {
        if (oldIndex.key[M - j] >
            ic.key)  // 若老结点中最大值比ic.key大则移动老节点中的最大值 ,M-j是最外层
        {
            newIndex.key[moveN - i] = oldIndex.key[M - j];
            newIndex.childP[moveN - i] = oldIndex.childP[M - j];
            newIndex.num++;
            newIndex = setAcctIndex(aifP, newIndex, newAddr);
            if (oldIndex.isLeaf == 0) {
                setAcctChildParent(aifP, oldIndex.childP[M - j], newAddr);
            }

            oldIndex.key[M - j] = -1;  // 把移走的关键字和孩子都置空
            oldIndex.childP[M - j] = -1;
            oldIndex.num--;
            oldIndex = setAcctIndex(aifP, oldIndex, oldAddr);
        } else  //<ic.key       //若ic.key是当前最大的值则移动ic.key
        {
            newIndex.key[moveN - i] = ic.key;
            newIndex.childP[moveN - i] = ic.child;
            newIndex.num++;
            newIndex = setAcctIndex(aifP, newIndex, newAddr);
            if (newIndex.isLeaf == 0) {
                setAcctChildParent(aifP, ic.child, newAddr);
            }
            j--;  // 控制移动旧结点的次数
            ic.key =
                -1;  // 装入addkey后再把addkey赋一个负值,让所有的结点都大于他,所以再不用装入它
        }
    }
    // 如果ic最终要插入到旧结点中则必须将其再移入其中,因为在循环中并未将其移入
    if (oldIndex.num == M / 2) {
        for (i = oldIndex.num; i >= 0; i--)  // 在循环的过程中要完成插入新值的任务,
        {
            if (oldIndex.key[0] == -1)  // 已经把第一个位置挪空了,只能是ic的位置
            {
                oldIndex.key[0] = ic.key;
                oldIndex.childP[0] = ic.child;
                oldIndex.num++;
                oldIndex = setAcctIndex(aifP, oldIndex, oldAddr);
                if (newIndex.isLeaf == 0) {
                    setAcctChildParent(aifP, ic.child, oldAddr);
                }
                break;
            }

            if (oldIndex.key[i - 1] >
                ic.key)  // 如果比ic大需要往后移动,保留一次循环用于存放新单元
            {
                oldIndex.key[i] = oldIndex.key[i - 1];
                oldIndex.childP[i] = oldIndex.childP[i - 1];
                oldIndex.key[i - 1] = -1;
                oldIndex.childP[i - 1] = -1;
                oldIndex = setAcctIndex(aifP, oldIndex, oldAddr);
            } else {
                oldIndex.key[i] = ic.key;
                oldIndex.childP[i] = ic.child;
                oldIndex.num++;
                oldIndex = setAcctIndex(aifP, oldIndex, oldAddr);
                if (oldIndex.isLeaf == 0) {
                    setAcctChildParent(aifP, ic.child, oldAddr);
                }
                break;
            }
        }
    }
    tempIC.key = oldIndex.key[oldIndex.num - 1];  // 获取旧结点中的最大值
    tempIC.child = oldAddr;                       // tempIC.chile存入旧结点的指针

    setAcctIndex(aifP, oldIndex, oldAddr);  // 首先要把修改过的结点写入文件
    setAcctIndex(aifP, newIndex, newAddr);
    setAcctIndex(aifP, parentIndex, parentAddr);
    insertAcctCell(aifP, tempIC, parentAddr);
}

//-------------------------------------------------------------------------------- 14.2在姓名满结点中插入
// 和账号索引一样,只不过比较的是字符串,使用strcmp函数比较
void insertNameAtFull(FILE *nifP, int oldAddr, nameIndexCell ic) {
    // 待扩充...
}

//-------------------------------------------------------------------------------- 15.1未满结点插值
// 说明:向帐号索引文件aifP的位置addr的结点处插入索引单元ic  关键字acct以及它的孩子child
int insertAcctAtEmpty(FILE *aifP, int addr, acctIndexCell ic) {
    acctIndexNode aINode;
    int i;

    aINode = getAcctIndex(aifP, addr);  // 获取要插入结点
    if (aINode.childP[aINode.num] !=
        -1)  // 如果要移动的单元上最末孩子不为空(每层最右结点的情况),先要将其向后移动,在最右结点中会大量出现这种状况
    {
        aINode.childP[aINode.num + 1] = aINode.childP[aINode.num];
    }
    for (i = aINode.num - 1; i >= 0;
         i--)  // 循环,移动如有必要需要把原来结点中的关键字及其孩子向后移动
    {
        if (aINode.key[i] >
            ic.key)  // 若ic.key比结点中的值aINode.key[i]大要往还要大,原来的节点和指针需要向后移动
        {
            aINode.key[i + 1] = aINode.key[i];
            aINode.childP[i + 1] = aINode.childP[i];
        } else  // 若ic.key是当前最大值则插入,并跳出for循环
        {
            i++;  // 让其定位到要插入的结点顺序
            break;
        }
    }
    i = (i == -1) ? 0 : i;   // i==-1是一直挪到第一个结点的情况
    aINode.key[i] = ic.key;  // 将要插入的值写入腾出来的位置
    aINode.childP[i] = ic.child;
    aINode.num++;
    setAcctIndex(aifP, aINode, addr);  // 写回
    return i;
}

//-------------------------------------------------------------------------------- 15.2未满结点插值
// 说明:向姓名索引文件aifP的位置addr的结点处插入索引单元ic  关键字acct以及它的孩子child
int insertNameAtEmpty(FILE *nifP, int addr, nameIndexCell ic) {
    return 0;  // 待扩充...
}

//-------------------------------------------------------------------------------- 16.1在帐号索引中从根开始的随机查找
// 说明:从根结点开始查找acct,返回一个sATRNode结果,找到下一要查询的位置最终找到要插入新结点的位置
sATRNode searchInTreeByAcct(FILE *aifP, int acct) {
    acctIndexHead aIHead;  // 索引文件头结点
    acctIndexNode aINode;  // 索引结点
    int sAddr;             // 存放下一个要查询的位置
    int i;                 // 循环变量
    sANRNode sNR;          // 在结点中查询的返回值结果
    sATRNode sTR;          // 在整棵树中查找的返回结果

    aIHead = getAcctIndexHead(aifP);  // 读取索引文件的文件头
    sAddr = aIHead.rootP;  // 获得根结点的地址,即下一个要查询的地址
    aINode = getAcctIndex(aifP, sAddr);  // 读取第一个索引到结点aINode中去
    for (i = 0; i < aIHead.tLayer; i++)  // 一直循环读取到叶子结点为止
    {
        sNR = searchInNodeByAcct(aifP, sAddr, acct,
                                 1);  // 主要获取下一层节点的地址,aINode.childP[sNR.n]
        sAddr = sNR.childAddr;  // 获得下一个地址,到最后获得的就是数据在数据文件中的地址
    }
    if (sNR.key == acct)  // 循环到了叶子节点上之后将acct和sNR.key进行比较
    {
        sTR.flag = 1;
        sTR.dataAddr = sNR.childAddr;
    } else {
        sTR.flag = 0;
        sTR.dataAddr = -1;
    }
    sTR.addr = sNR.selfAddr;  // 最后定位叶子节点地址
    sTR.orderOfNode = sNR.n;  // 最后一个查询的关键字的顺序数
    sTR.nearKey = sNR.key;    // 最后一个查询关键字值
    return sTR;
}

//-------------------------------------------------------------------------------- 16.2在姓名索引中从根开始的随机查找
// 说明:从根结点开始查找acct,返回一个sATRNode结果,找到下一要查询的位置最终找到要插入新结点的位置
sNTRNode searchInTreeByName(FILE *nifP, char *name) {
    sNTRNode sntReturn = {0, 0, 0, "", 0};  // 待扩充...
    return sntReturn;
}

//--------------------------------------------------------------------------------- 17.1在帐号索引结点中查找
// 说明:在帐号索引文件的地址为addr处的索引结点中寻找acct,返回查找sNTNode结果,利用折半查找法,效率比逐一查找要高,若n=1用折半查找法
sANRNode searchInNodeByAcct(FILE *aifP, int addr, int acct, int n) {
    int i;                 // 最终返回的位置
    acctIndexNode aINode;  // 要查询的结点
    sANRNode sNR;          // 查找返回结果
    int bigAcct;           // 前一次查到的key的编号
    int smallAcct;
    int preI;

    aINode = getAcctIndex(aifP, addr);  // 获取指定位置索引的结点存入aINode
    if (n == 1) {
        // 折半查找法,效率很好,因为在一个节点中所有的key都是顺序排列的,正好可以加以利用,不然有些浪费
        bigAcct = aINode.num - 1;       // 上线
        smallAcct = 0;                  // 下线
        i = (bigAcct + smallAcct) / 2;  // 初始值正好是索引节点中间的一个值
        do {
            preI = i;                   // 首先赋值给preI
            if (aINode.key[i] == acct)  // 如果中间的key[i]正好就是要查找的值
                break;
            if (aINode.key[i] >
                acct)  // 如果acct比最中间的值小,则说明acct在中间值的左面,上线应该下移
            {
                bigAcct = i;
            } else  // 如果acct比最中间的值大,则说明acct在中间值的右面,下限应该上移
            {
                smallAcct = i;
            }
            i = (bigAcct + smallAcct) / 2;
        } while (preI != i);  // 如果上一次和下一次的中间值一样说明已经停止

    } else {
        i = 0;  // 如果是逐一查找则从第0个关键字开始
    }

    // 现在所要查询的值就在附近,需要逐一排查
    for (i; i < aINode.num; i++) {
        if (aINode.key[i] >= acct)
            break;
    }

    if (i == M)  // 若查询的结果是acct已经超过了查找的范围
    {
        sNR.key = -1;
        sNR.childAddr = -1;
    } else  // 若查询的结果是acct不是结点中的最大值,sNR.key<acct或者=acct
    {
        if (i > aINode.num)  // 如果结点中无值或者查询的值超过了结点中所有的值但是结点未满
        {
            sNR.key = -1;
            sNR.childAddr = -1;
        } else {
            sNR.key = aINode.key[i];
        }
    }
    sNR.n = i;
    sNR.selfAddr = addr;
    sNR.childAddr = aINode.childP[i];
    return sNR;
}

//--------------------------------------------------------------------------------- 17.2在姓名索引结点中查找
// 说明:在帐号索引文件的地址为addr处的索引结点中寻找acct,返回查找sNTNode结果
sNNRNode searchInNodeByName(FILE *nifP, int addr, char *name) {
    sNNRNode snnReturn = {0, 0, "", 0};  // 待扩充...
    return snnReturn;
}

//-------------------------------------------------------------------------------- 18.1插入单条数并处理帐号索引
// 说明:调整帐号索引文件,若无重复值就插入,有重复值则插入后还要修改数据文件后面的地址
int disposeAcctIndex(FILE *dfP, FILE *aifP, dataNode dNode, int insertAddr) {
    int dataAddr;         // 数据文件的位置
    dataHead dHead;       // 数据文件头
    acctIndexCell ic;     // 要插入的索引单元
    int anotherDataAddr;  // 如果已经存在一条数据,它的地址

    dHead = getDataHead(dfP);
    dataAddr =
        insertAddr;  // 转换数据文件的所在地址,也就是将要新插入数据的地址,因已经插入所以-1
    ic.key = dNode.acct;  // 搜集索引单元信息key,数据的关键字
    ic.child = dataAddr;  // 搜集索引单元信息child,即新数据将要存放位置
    anotherDataAddr = doAcctIndex(
        aifP,
        ic);  // 返回0则说明数据文件中没有这条数据,若返回一个正整数则说明原来文件中已经存在这条数据,而且是第一条的地址
    if (anotherDataAddr !=
        0)  // 如果在原来数据文件中已经存在这条数据dNode则在原来值的后面插入,不修改任何索引,仅修改数据的指针
    {
        goOnInsertByAcct(dfP, insertAddr, anotherDataAddr);  // 继续插入
        return 0;
    }
    return 1;
}

//-------------------------------------------------------------------------------- 18.2插入单条数据通过姓名索引
// 说明:调整索引文件,若无重复值就插入,有重复值则插入到原来值的后面
int disposeNameIndex(FILE *dfP, FILE *nifP, dataNode dNode, int insertAddr) {
    return 0;  // 待扩充...
}

//-------------------------------------------------------------------------------- 19
//以物理方式显示数据 说明:不管索引,在数据文件f中一直往下读数据,直到文件最末尾那条数据
void displayAllData(FILE *dfP) {
    int i;  // 循环变量
    dataNode dNode;
    int count = 0;          // 计数器
    clock_t start, finish;  // 运行开始,停止时间
    double duration;        // 间隔的秒数

    printDataFileTitle(0);
    start = clock();
    for (i = 0; i < DANum; i++) {
        dNode = getData(dfP, i * DN + DH);
        if (dNode.acct > 0)
            displaySimpleData(dfP, i * DN + DH, dNode, 0);
    }
    finish = clock();
    duration = (double)(finish - start) / 1000;
    printLine(21);
    printf("总共 %d 条数据  ", DANum);
    printf("耗时:");
    timeShow(duration);
    printf("/n");
    printLine(21);
}

//-------------------------------------------------------------------------------- 20.1
//以物理方式读取帐号索引文件 说明:
void displayAllAcctIndex(FILE *aifP)  // 读取所有的帐号索引
{
    int i;  // 循环变量
    acctIndexHead aIHead;
    acctIndexNode aINode;
    int addr;  // 存放索引结点的地址

    aIHead = getAcctIndexHead(aifP);
    displayAcctIndexHead(aIHead);  // 显示头信息
    printLine(4 * M + 28);
    printAcctIndexTitle();
    printLine(4 * M + 28);
    for (i = 0; i < AIANum; i++)  // 总共AIANum个索引结点
    {
        addr = acctIndexCellToAddr(i);
        aINode = getAcctIndex(aifP, addr);
        displayAcctIndex(aINode, i);
    }
    printLine(4 * M + 28);
    printf("总共 %d 条索引/n", AIENum);
    printLine(4 * M + 28);
}

//-------------------------------------------------------------------------------- 20.2
//以物理方式读取姓名索引文件 说明:
void displayAllNameIndex(FILE *nifP)  // 读取所有姓名的索引
{
    // 待扩充...
}

//--------------------------------------------------------------------------------
//21清除所有文件数据并初始化 说明:清除数据文件和索引文件中所有的数据,但是保留他们的文件头
void clear(FILE *iAFP, FILE *dfP, FILE *aifP, FILE *nifP, FILE *nameTxt, FILE *nameBin,
           FILE *otherTxt, FILE *otherBin, FILE *sourceBin) {
    fclose(dfP);
    fclose(aifP);
    fclose(nifP);
    fclose(iAFP);

    dfP = fopen("dataFile.dat", "w");  // 以w方式打开文件,这种方式会自动清除文件中所有数据
    aifP = fopen("indexOfAcct.dat", "w");
    nifP = fopen("indexOfName.dat", "w");
    iAFP = fopen("indexAdministrator.dat", "w");
    fclose(dfP);  // 再关闭文件
    fclose(aifP);
    fclose(nifP);
    fclose(iAFP);

    dfP = fopen(
        "dataFile.dat",
        "rb+");  // 以rb+的方式打开数据文件,文件会自动添加到指定位置而不会删除其它数据
    aifP = fopen("indexOfAcct.dat", "rb+");
    nifP = fopen("indexOfName.dat", "rb+");
    iAFP = fopen("indexAdministrator.dat", "rb+");
    initialize(iAFP, dfP, aifP, nifP);
    ;  // 初始化
}

//-------------------------------------------------------------------------------- 22.1通过帐号索引顺序读取数据
// 说明:从小到大的顺序按照帐号显示所有数据
void orderDisplayByAcct(FILE *aifP, FILE *dfP) {
    acctIndexNode aINode;
    acctIndexHead aIHead;
    int addr;  // 索引文件中结点的位置
    int count = 0;

    aIHead = getAcctIndexHead(aifP);
    addr = aIHead.leftLeafP;
    printDataFileTitle(0);
    if (IsAcctIndexOn == 0) {
        printf("无帐号索引,暂时不提供此功能!/n");
        printLine(24);
        return;
    }
    do {
        aINode = getAcctIndex(aifP, addr);  // 从最左面叶子开始读起
        count += displayDFAIndex(dfP, aifP, aINode);
        addr = aINode.childP[M];
    } while (addr != -1);
    printLine(21);
    printf("总共 %d 条数据, %d 个用户/n", DENum, count);
    printLine(21);
}

//-------------------------------------------------------------------------------- 22.2按姓名顺序读取数据
// 说明:从小到大的顺序按照姓名显示所有数据
void orderDisplayByName(FILE *nifP, FILE *dfP) {
    nameIndexNode nINode;
    nameIndexHead nIHead;
    int addr;  // 索引文件中结点的位置
    int count = 0;

    nIHead = getNameIndexHead(nifP);
    addr = nIHead.leftLeafP;
    printDataFileTitle(19);
    do {
        nINode = getNameIndex(nifP, addr);  // 从最左面叶子开始读起
        count += displayDFNIndex(dfP, nifP, nINode);
        addr = nINode.childP[M];
    } while (addr != -1);
    printLine(19);
    printf("总共 %d 条数据, %d 个用户/n", DENum, count);
    printLine(19);
}

//--------------------------------------------------------------------------------
//23显示一条数据信息
// 说明:在数据文件addr处读取数据项并显示,这种显示区别于displaySimpleData,如果所查数据还有后节点一并显示出来
dataNode displayData(FILE *dfP, int addr, dataNode dNode, int n) {
    printf("%-20s", dNode.serialNum);  // 流水号
    printf("[%8d] /t/t", addr);
    printf("%-5d/t/t", dNode.acct);
    printf("%-7s/t", dNode.name);
    printf("%-10.2f/t", dNode.balance);
    printf("%-20s/t", dNode.other);
    if (n == 1)  // 将时间已年月日时分秒形式显示
    {
        secToDate(dNode.insertTime);
        printf("/t");
    } else {
        printf("%-15d/t", dNode.insertTime);  // 将时间以秒的形式显示
    }
    printf("[%-d]/n", dNode.nextAcctAddr);
    if (dNode.nextAcctAddr != -1)  // 用迭代算法显示所有关键字和dNode一样的数据结点
    {
        addr = dNode.nextAcctAddr;
        dNode = getData(dfP, addr);
        displayData(dfP, addr, dNode, n);
    }
    return dNode;
}

//-------------------------------------------------------------------------------- 24.1显示帐号索引信息
// 说明:显示帐号索引文件中第n个索引
void displayAcctIndex(acctIndexNode aINode, int n) {
    int i;  // 循环变量

    printf("%-d./t", n + 1);
    printf("[addr=%-10d]/t", acctIndexCellToAddr(n));
    printf("[%d]/t", aINode.num);
    for (i = 0; i < M; i++) {
        printf("[%-10d,", aINode.childP[i]);
        printf("%3d]/t", aINode.key[i]);
    }
    printf("[%d]/t", aINode.childP[M]);  // 显示最后一个指针
    printf("[parent:%d]/t", aINode.parentP);
    printf("[%-3d|%3d]/n", aINode.isLeaf, aINode.isMostRight);
}

//-------------------------------------------------------------------------------- 24.2显示姓名索引信息
// 说明:显示帐号索引文件中第n个索引
void displayNameIndex(nameIndexNode nINode, int n) {
    // 待扩充...
}

//-------------------------------------------------------------------------------- 25.1显示帐号索引头信息
// 说明:在数据文件addr处读取数据项并显示
void displayAcctIndexHead(acctIndexHead aIHead) {
    printf("/n帐号索引文件头: ");
    printf("[层:%d]   ", aIHead.tLayer);
    printf("[根:%d]   ", aIHead.rootP);
    printf("[叶:%d]/n", aIHead.leftLeafP);
}

//-------------------------------------------------------------------------------- 25.2显示姓名索引头信息
// 说明:在数据文件addr处读取数据项并显示
void displayNameIndexHead(nameIndexHead nIHead) {
    printf("/n姓名索引文件头: ");
    printf("[层:%d]   ", nIHead.tLayer);
    printf("[根:%d]   ", nIHead.rootP);
    printf("[叶:%d]/n", nIHead.leftLeafP);
}

//[程序] B + 树索引的实现(定稿 2 / 2)

//-------------------------------------------------------------------------------- 26.1将帐号索引单元插入索引结点
// 说明:在帐号索引文件aifP中位置addr处的结点中插入索引单元ic
void insertAcctCell(FILE *aifP, acctIndexCell ic, int addr) {
    acctIndexNode aINode;

    aINode = getAcctIndex(aifP, addr);
    if (aINode.num < M)  // 若插入的这个结点是未满的
        insertAcctAtEmpty(aifP, addr, ic);
    else  // 插入的结点是已满的,需要分裂
        insertAcctAtFull(aifP, addr, ic);
}

//-------------------------------------------------------------------------------- 26.2将姓名索引单元插入索引结点
// 说明:在姓名索引文件nifP中位置addr处的结点中插入索引单元ic
void insertNameCell(FILE *nifP, nameIndexCell ic, int addr) {
    nameIndexNode nINode;

    nINode = getNameIndex(nifP, addr);
    if (nINode.num < M)  // 若插入的这个结点是未满的
        insertNameAtEmpty(nifP, addr, ic);
    else  // 插入的结点是已满的,需要分裂
        insertNameAtFull(nifP, addr, ic);
}

//--------------------------------------------------------------------------------
//27总初始化 把数据文件,索引文件都初始化
void initialize(FILE *iAFP, FILE *dfP, FILE *aifP, FILE *nifP) {
    FILE *nameTxt, *nameBin;
    FILE *otherTxt, *otherBin;
    FILE *sourceBin;
    nameNode nNode;

    initializeDataFile(dfP);        // 初始化数据文件
    initializeAcctIndexFile(aifP);  // 初始化帐号索引文件
    initializeNameIndexFile(nifP);  // 初始化姓名索引文件
    initializeIndexAdmini(iAFP);    // 初始化索引管理文件

    nameTxt = fopen("name.txt", "r");
    nameBin = fopen("name.dat", "rb+");
    rewind(nameBin);
    fread(&nNode, sizeof(nameNode), 1, nameBin);
    if (nNode.no < 0)  // 如果还没有存在文件则生产
    {
        readTxtNameWriteBin(nameTxt, nameBin);  // 生成二进制姓名信息
        otherTxt = fopen("other.txt", "r");
        otherBin = fopen("other.dat", "rb+");
        readTxtOtherWriteBin(otherTxt, otherBin);  // 生成二进制附加信息
        sourceBin = fopen("dataSource.dat", "ab+");
        composeFile(MAX, nameBin, otherBin, sourceBin);  // 组合数据
    }
}

//--------------------------------------------------------------------------------
//28给全局变量赋值
// 说明:如果程序不是第一次运行则把程序运行的相关的数据复制给文件中的全局变量
void beginOfRun(FILE *iAFP, FILE *dfP, FILE *aifP, FILE *nifP) {
    dataHead dHead;        // 数据文件头结点
    acctIndexHead aIHead;  // 帐号索引文件头结点
    nameIndexHead nIHead;  // 姓名索引文件头结点
    indexAdmiNode iaNode;  // 索引管理接点

    dHead = getDataHead(dfP);         // 获得数据文件头
    aIHead = getAcctIndexHead(aifP);  // 获得帐号索引文件头
    nIHead = getNameIndexHead(nifP);  // 获得姓名索引文件头
    iaNode = getIndexAdmiNode(iAFP);  // 获得索引管理结点

    DENum = dHead.dENum;  // 有效数据数,给全局变量赋值
    DANum = dHead.dANum;  // 总数据数,给全局变量赋值

    AIENum = aIHead.iENum;    // 有效账号索引结点数,给全局变量赋值
    AIANum = aIHead.iANum;    // 总账号索引结点数,给全局变量赋值
    ATLayer = aIHead.tLayer;  // 账号索引b+树的层数,给全局变量赋值

    NIENum = nIHead.iENum;  // 姓名索引得有效结点数
    NIANum = nIHead.iANum;
    NTLayer = nIHead.tLayer;

    IsAcctIndexOn = iaNode.isAccountIndexOn;   // 是否账号索引启动
    IsBalaIndexOn = iaNode.isBalanceIndexOn;   // 是否金额索引启动
    IsNameIndexOn = iaNode.isNameIndexOn;      // 是否姓名索引启动
    IsSerlIndexOn = iaNode.isSerialumIndexOn;  // 是否流水号索引启动
}

//-------------------------------------------------------------------------------- 29.1由帐号索引显示所指数据
// 说明:一次性打印出一个节点中的所有数据
int displayDFAIndex(FILE *dfP, FILE *aifP, acctIndexNode aINode) {
    int i;
    int dataAddr;
    dataNode dNode;

    for (i = 0; i < aINode.num; i++) {
        dataAddr = aINode.childP[i];
        dNode = getData(dfP, dataAddr);
        displayData(dfP, dataAddr, dNode, 0);
    }
    return aINode.num;
}

//-------------------------------------------------------------------------------- 29.2由姓名索引显示所指数据
// 说明:
int displayDFNIndex(FILE *dfP, FILE *nifP, nameIndexNode nINode) {
    return 0;
    // 待扩充...
}

//-------------------------------------------------------------------------------- 30.1生成一个新帐号索引结点
// 说明:在帐号索引文件aifP中位置addr处生成一个新索引,返回该索引结点的地址
int makeNewAcctIndexNode(FILE *aifP, int isMostRight, int isLeaf) {
    acctIndexNode aINode;
    acctIndexHead aIHead;
    int i;
    int addr;

    addr = acctIndexCellToAddr(AIANum);
    aINode.num = 0;
    for (i = 0; i < M; i++) {
        aINode.childP[i] = -1;
        aINode.key[i] = -1;
    }
    aINode.childP[M] = -1;
    aINode.parentP = -1;
    if (isMostRight == 0) {
        aINode.isMostRight = 0;
    } else
        aINode.isMostRight = 1;
    if (isLeaf == 0) {
        aINode.isLeaf = 0;
    } else
        aINode.isLeaf = 1;
    aIHead = getAcctIndexHead(aifP);
    aIHead.iANum = ++AIANum;
    aIHead.iENum = ++AIENum;
    setAcctIndexHead(aifP, aIHead);
    setAcctIndex(aifP, aINode, addr);
    return addr;
}

//-------------------------------------------------------------------------------- 30.2生成一个姓名新索引结点
// 说明:在帐号索引文件aifP中位置addr处生成一个新索引,返回该索引结点的地址
int makeNewNameIndexNode(FILE *nifP, int isMostRight, int isLeaf) {
    return 0;
    // 待扩充...
}

//-------------------------------------------------------------------------------- 31.1获得在父结点中自己的顺序
// 说明:返回本索引节点在父节点中的位置
int searchAcctInParent(acctIndexNode parent, int childAddr) {
    int i = 0;

    while (parent.childP[i] != childAddr && i <= M) {
        i++;
    }
    if (i == M + 1)
        return (-1);
    else
        return i;
}

//-------------------------------------------------------------------------------- 31.2获得在父结点中自己的顺序
// 说明:返回本索引节点在父节点中的位置
int searchNameInParent(nameIndexNode parent, int childAddr) {
    return 0;
    // 待扩充...
}

//-------------------------------------------------------------------------------- 32.1给帐号孩子赋父结点地址
// 说明:给帐号父结点的第n个孩子赋父结点地址selfAddr,也就是新结点的地址
void setAcctChildParent(FILE *aifP, int childAddr, int selfAddr) {
    acctIndexNode child;

    child = getAcctIndex(aifP, childAddr);
    child.parentP = selfAddr;
    setAcctIndex(aifP, child, childAddr);
}

//-------------------------------------------------------------------------------- 32.1给姓名索引结点孩子赋父结点地址
// 说明:给姓名父结点的第n个孩子赋父结点地址selfAddr,也就是新结点的地址
void setNameChildParent(FILE *nifP, int childAddr, int selfAddr) {
    nameIndexNode child;

    child = getNameIndex(nifP, childAddr);
    child.parentP = selfAddr;
    setNameIndex(nifP, child, childAddr);
}

//-------------------------------------------------------------------------------- 33.1设定帐号索引结点的MostRight值
// 说明:将addr处结点修改是否最右结点属性后再返回本结点
acctIndexNode setAcctIndexMostRight(FILE *aifP, int addr, int value) {
    acctIndexNode aINode;

    aINode = getAcctIndex(aifP, addr);
    if (value == 0) {
        aINode.isMostRight = 0;
    } else
        aINode.isMostRight = 1;
    setAcctIndex(aifP, aINode, addr);
    return aINode;
}

//-------------------------------------------------------------------------------- 33.2设定姓名索引结点的MostRight值
// 说明:将addr处结点修改是否最右结点属性后再返回本结点
nameIndexNode setNameIndexMostRight(FILE *nifP, int addr, int value) {
    nameIndexNode niNode = {0, 0, 0, "", 0, 0};

    return niNode;
}

//-------------------------------------------------------------------------------- 34.1帐号范围内搜索
// 说明：输入上限和下线,然后显示这区间的所有数据
void searchBetweenByAcct(FILE *aifP, FILE *dfP, int acct1, int acct2) {
    acctIndexNode aINode;
    sATRNode sTR;
    int indexAddr, dataAddr;
    int i;
    int count = 0;

    printf("帐号从 %d 到 %d 的数据如下:/n", acct1, acct2);
    if (IsAcctIndexOn == 0) {
        printLine(23);
        printf("抱歉,此功能仅在建立索引之后才能使用!/n");
        return;
    }
    if (acct1 > acct2)  // 如果错误把acct1和acct2的顺序弄反了给予容错处理
    {
        i = acct1;
        acct1 = acct2;
        acct2 = i;
    }
    printDataFileTitle(1);
    sTR = searchInTreeByAcct(aifP, acct1);
    indexAddr = sTR.addr;
    aINode = getAcctIndex(aifP, indexAddr);
    do {
        for (i = 0; i < aINode.num; i++)  // 在一个索引节点中循环读取数据文件的地址
        {
            if (aINode.key[i] >= acct1 && aINode.key[i] <= acct2) {
                dataAddr = aINode.childP[i];
                displaySearchByAcct(dfP, dataAddr);
                count++;
            }
        }
        if (aINode.childP[M] > 0) {
            indexAddr = aINode.childP[M];
            aINode = getAcctIndex(aifP, indexAddr);
        } else {
            printLine(24);
            return;
        }

    } while (aINode.key[0] <= acct2);  // 直到要查询的数据超过了要查询的范围则退出
    printLine(24);
    printf("共 %d 条满足条件的数据/n", count);
    printLine(24);
}

//-------------------------------------------------------------------------------- 34.2姓名范围内搜索
// 说明：输入上限和下线,然后显示这区间的所有数据
void searchBetweenByName(FILE *nifP, FILE *dfP, char *name1, char *name2) {
    // 待完善...
}

//--------------------------------------------------------------------------------
//35数据录入 说明:在数据里其中两项,当前时间和后序数据这两项由系统自己处理不要人工输入
dataNode getDataNode() {
    dataNode dNode;
    time_t t;

    t = time(NULL);  // 获取电脑当前时间的秒数,从公元1970年1月1日0时0分0 秒算起

    printf("/n请输入客户的帐号、姓名、金额、用户说明信息(输入ctrl+z则停止输入)/n>>");
    fscanf(stdin, "%d%s%lf%s", &dNode.acct, dNode.name, &dNode.balance, dNode.other);
    dNode.insertTime = t;
    dNode.nextAcctAddr = -1;  // 默认无
    printf("/n");
    return dNode;
}

//--------------------------------------------------------------------------------
//36画一条线 说明:为美观需要，画一条直线，长度由length来控制
void printLine(int length) {
    int i;

    for (i = 0; i < length; i++) {
        printf("------");
    }
    printf("/n");
}

//--------------------------------------------------------------------------------
//37把秒转换为时间 说明:把秒格式的转化为我们可以认识的时间格式显示
void secToDate(int sec) {
    struct tm *local;
    time_t t;

    t = sec;

    local = localtime(&t);
    printf("%d-", local->tm_year + 1900);
    printf("%d-", local->tm_mon + 1);
    printf("%d  ", local->tm_mday);
    printf("%d:%d:%d/t", local->tm_hour, local->tm_min, local->tm_sec);
}

//-------------------------------------------------------------------------------- 38.1把相同关键字的值插入至原值后
// 说明:如果插入的数据在索引文件中已经显示存在,把这条数据接到原来数据的后面,形成单链表结构
void goOnInsertByAcct(FILE *dfP, int nDAddr, int oDAddr) {
    dataNode oDNode;  // 第一条搜索到的和nDNode的关键字相同的数据结点

    oDNode = getData(
        dfP, oDAddr);  // 读取第一条关键字和nDNode的一样的数据结点,目的在于找到最后一条
    while (oDNode.nextAcctAddr != -1)  // 如果没有到最后一个结点就一直循环寻找
    {
        oDAddr = oDNode.nextAcctAddr;
        oDNode = getData(dfP, oDAddr);
    }
    oDNode.nextAcctAddr = nDAddr;  // 把最后一条旧结点的地址改为新结点的地址
    setData(dfP, oDNode, oDAddr);  // 最后把新节点前面的一个节点的指针修改
}

//-------------------------------------------------------------------------------- 38.2把相同关键字的值插入至原值后
// 说明:如果插入的数据在索引文件中已经显示存在,把这条数据接到原来数据的后面,形成单链表结构
void goOnInsertByName(FILE *dfP, dataNode nDNode, int oDAddr) {
    // 待完善...
}

//-------------------------------------------------------------------------------- 39
//显示数据的标题 说明:用于显示数据文件的标题,i用于确定显示的不同类型
void printDataFileTitle(int i) {
    if (i == 1) {
        printLine(24);  // 如果i为时，时间显示方式是吧秒转化为日历时间，所以要长点
    } else
        printLine(21);
    printf("流水号/t/t    ");
    printf("地址/t/t");
    printf("账号/t/t");
    printf("姓名/t");
    printf("金额/t/t");
    printf("说明/t/t/t");
    if (i == 1) {
        printf("时间/t/t/t/t");
    } else
        printf("秒数/t/t");
    printf("NEXT/n");
    if (i == 1) {
        printLine(24);
    } else
        printLine(21);
}

//-------------------------------------------------------------------------------- 40.1自动随机插入数据
// 说明:向数据文件和索引文件随机插入auto次随机抽取的数据
void autoInsertByAcct(FILE *dfP, FILE *aifP, FILE *sfP, int autoNum) {
    dataNode dNode;
    int i;
    int stochasticNum;  // 随机数
    int by, cy;
    clock_t start = 0, finish, tt = 0;
    double duration;      // 相隔时间
    double duration1000;  // 插1000条数据所耗费的时间
    double leaveTime;     // 剩余时间
    int insertAddr;

    start = clock();
    srand(time(NULL));  // 产生随机数因子,随机函数产生的范围是0~32767
    by = (MAX - 1) / 32767;  // 让每一条数据被抽到的可能性是相同的
    cy = (MAX - 1) - (by * 32767);
    printLine(19);
    for (i = 1; i <= autoNum; i++)  // 随机提取一条数据源
    {
        if ((MAX - 1) < 32767) {
            stochasticNum = rand() % (MAX - 1) + 1;
        } else
            stochasticNum =
                1 + rand() * (rand() % (by + 1)) +
                rand() %
                    (cy +
                     1);  // 产生数据源文件中的定位随机数stochasticNum,因为实现生成的数据文件中有,最大rand()=3276
        dNode = getFromDataSourceFile(
            sfP,
            stochasticNum);  // 由随即产生的这个数在数据源文件中提取一个原始数据并加工为完整数据
        insertAddr = insertWithOutIndex(
            dfP, dNode);  // 首先插入数据,然后整理索引,如果帐号索引启动的话
        if (IsAcctIndexOn == 1) {
            disposeAcctIndex(dfP, aifP, dNode, insertAddr);
        }

        if (i % 1000 == 0) {
            finish = clock();
            duration = (double)(finish - start) / CLOCKS_PER_SEC;
            duration1000 = (double)(finish - tt) / CLOCKS_PER_SEC;
            leaveTime = (autoNum - i) * duration / i;
            printf("第 %-7d 条 耗时", i);
            timeShow(duration1000);
            printf(
                "/t/t总耗时: ");  // 在演示时候可以不屏蔽这三条语句,在插入时候如果显示插入速度很慢
            timeShow(duration);
            printf(
                "/t/t预计还剩: ");  // 在演示时候可以不屏蔽这三条语句,在插入时候如果显示插入速度很慢
            timeShow(leaveTime);
            printf("/n");
            tt = finish;
        }
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printLine(19);
    printf("耗时:");
    timeShow(duration);
    printf("/n");
}

//-------------------------------------------------------------------------------- 40.2自动随机插入数据
// 说明:向数据文件和索引文件随机插入auto次随机抽取的数据
void autoInsertByName(FILE *dfP, FILE *nifP, FILE *sfP, int autoNum) {
    // 待完善...
}

//--------------------------------------------------------------------------------
//41数据结点加工
// 说明:把从数据源中读出来数据单元sCell加工成完整数据结点dataNode类型,参数包括时间秒和流水号
dataNode doSNTDN(sourceDataCell sCell, int seconds, int serial) {
    dataNode dNode;        // 数据结点
    char timeString[10];   // 前10位时间
    char serialString[5];  // 后5位流水号,多出一位保存/0

    dNode.serialNum[0] = '/0';  // 意思这个字符串为空没有任何值

    intToString(
        seconds, 10,
        timeString);  // 将时间转换成前10位字符串,其实需要11位来装它,因为还有最后的'/0'
    intToString(
        serial, 5,
        serialString);  // 将流水号转换成后6位字符串,其实需要7位来装它,因为还有最后的'/0'
    strcat(dNode.serialNum, timeString);  // 将时间黏贴到总结点dNode.serialNum之后
    strcat(dNode.serialNum, serialString);
    dNode.acct = sCell.acct;
    dNode.balance = getNewblance();  // 一个随机的金额
    dNode.insertTime = seconds;
    strcpy(dNode.name, sCell.name);  // 复制,后面的复制给前面
    strcpy(dNode.other, sCell.other);
    dNode.nextAcctAddr = -1;
    dNode.nextBalAddr = -1;
    dNode.nextNameAddr = -1;
    dNode.nextNoAddr = -1;
    return dNode;
}

//-------------------------------------------------------------------------------- 42.1新旧结点中关键字的移动
// 说明:在分裂过程中,把旧结点中的值分裂一部分到新结点中,然后把insetIC也插入相应结点中
void moveKeyByAcct(acctIndexNode oldNode, acctIndexNode newNode, acctIndexCell ic) {
    int i;                    // 控制循环次数
    int j;                    // 确定节点的中的位置
    int n = (M - 1) / 2 + 1;  // 循环做动作的次数
    int moveN;                // 移入新结点中的单元个数

    moveN = (M % 2 == 0) ? (M / 2) : (M / 2 + 1);  // 新结点中移进的关键字及其孩子个数
    for (i = 1, j = 1; i <= moveN;
         i++, j++)  // 移入新结点个数,包括ic,这里不用调用直接插入函数效率更高
    {
        if (oldNode.key[M - j] >
            ic.key)  // 若老结点中最大值比ic.key大则移动老节点中的最大值 ,M-j是最外层
        {
            newNode.childP[moveN - i] = oldNode.childP[M - j];
            newNode.key[moveN - i] = oldNode.key[M - j];

            if (oldNode.isLeaf !=
                1)  // 如果移动的不是叶子结点就需要更改索结点的父结点
                    //     setAcctChildParent(aifP,oldNode.childP[M-j],newAddr);//从旧节点中把原来的索引单元移动到新的节点中之后必须把它孩子的父结点修改
                oldNode.key[M - j] = -1;  // 把移走的关键字和孩子都置空
            oldNode.childP[M - j] = -1;
            oldNode.num--;
            newNode.num++;
        } else  // 若ic.key是当前最大的值则移动ic.key
        {
            newNode.key[moveN - i] = ic.key;
            newNode.childP[moveN - i] = ic.child;
            j--;  // 控制移动旧结点的次数
            ic.key =
                -1;  // 装入addkey后再把addkey赋一个负值,让所有的结点都大于他,所以再不用装入它
            newNode.num++;
        }
    }
}

//-------------------------------------------------------------------------------- 42.2新旧结点中关键字的移动
// 说明:在分裂过程中,把旧结点中的值分裂一部分到新结点中,然后把insetIC也插入相应结点中
void moveKeyByName(nameIndexNode oldNode, nameIndexNode newNode, nameIndexCell ic) {
    // 待完善...
}

//--------------------------------------------------------------------------------
//43用于验证某些功能 说明:试验，从1到100随机插入
void from1to100(FILE *aifP, FILE *dfP, FILE *logP) {
    // FILE *sfP;
    // sfP=fopen("dataSource.dat","rb");
    // dataNode dn;
    // int   i;
    // srand(time(NULL));
    // int   maxN;
    // scanf("%d",&maxN);
    //
    // for (i=1;i<=maxN;i++)
    // {
    //  dn.acct=i;/*rand()%3000;*/
    //  dn.balance=i;
    //  dn.insertTime=0;
    //  strcpy(dn.name,"name");
    //  dn.nextAcctAddr=-1;
    //  dn=getFromDataSourceFile(sfP,i);
    //  strcpy(dn.other,"other");
    //  logWrite(logP,dn.acct,i);
    //  disposeAcctIndex(dfP,aifP,dn);
    //  (i%100)==0?printf("%d/n",i):(i==i);
    // }
}

//--------------------------------------------------------------------------------
//44写日志文件 说明:将记录以文本格式记录于文本文件中，有待完善，一般主要用语查错之用
void logWrite(FILE *logP, int key, int i) {
    logNode lNode;

    lNode.acct = key;
    fseek(logP, i * 8, SEEK_SET);
    fprintf(logP, "--%d,  %-5d%s", i, lNode.acct, "/n");
}

//--------------------------------------------------------------------------------
//45把整数转换成一条完整的数据 说明:传入一个整数,返回对应的数据源文件中的相同帐号的数据
dataNode getFromDataSourceFile(FILE *sfP, int n) {
    time_t t;
    sourceDataCell sC;
    dataNode dNode;

    t = time(NULL);   // 获取当前时间
    if (t == PreSec)  // 如果执行时间还是在一秒钟之内,则流水号++
    {
        SerialControl++;
    } else {
        SerialControl = 0;  // 流水账号还原到初始位置
    }
    fseek(sfP, (n - 1) * SNS, SEEK_SET);
    fread(&sC, SNS, 1, sfP);  // 在数据源问文件中找到那条原始数据
    dNode = doSNTDN(sC, t, SerialControl);  // 将原始数据加工成完整的数据
    PreSec = t;
    return dNode;
}

//-------------------------------------------------------------------------------- 46.1帐号索引文件标题
// 说明:帐号索引数据的表头
void printAcctIndexTitle() {
    int i;

    printf("编号/t地址/t/t     关键字数/t");
    for (i = 0; i < M; i++) {
        printf("结点%d/t/t/t", i + 1);
    }
    printf("末根/t父结点指针/t叶子|最右/n");
}

//-------------------------------------------------------------------------------- 46.2姓名索引文件标题
// 说明:姓名索引数据的表头
void printNameIndexTitle() {
    int i;

    printf("编号/t地址/t/t     关键字数/t");
    for (i = 0; i < M; i++) {
        printf("结点%d/t/t/t", i + 1);
    }
    printf("末根/t父结点指针/t叶子|最右/n");
}

//--------------------------------------------------------------------------------
//47显示数据结点查找结果 说明:显示一个结点的所有数据,包括后面所跟的数据结点
void displaySearchByAcct(FILE *dfP, int addr) {
    int dataFileAddr;
    dataNode dNode;

    dataFileAddr = addr;                 // 获取数据文件存放的地址
    dNode = getData(dfP, dataFileAddr);  // 3从数据文件中读取数据项并放入dNode
    displayData(dfP, dataFileAddr, dNode, 1);  // 23显示dNode
}

//--------------------------------------------------------------------------------
//48随机获得金额
// 说明:在函数之内不能设立随机因子,必须在调用本函数以外设置,否则每次获得相同的值
double getNewblance() {
    double balance;  // 金额,随机合成
    int b1;          // 金额证书部分
    double b2;       // 金额小数部分

    b1 = rand() - rand();  // 为了从一个最小的负值到最大的正值之间是对称的,而且是等概率的
    b2 = rand() % 100 - rand() % 100;
    b2 /= 100;
    balance = b1 + b2;  // 合成金额
    return balance;
}

//--------------------------------------------------------------------------------
//49程序头 说明:显示系统相关信息以及当前时间等等信息
void programmeDoor() {
    FILE *dfP;   // 指向数据文件的指针
    FILE *aifP;  // 指向帐号索引文件的指针
    FILE *nifP;  // 指向姓名索引文件的指针
    FILE *tifP;  //
    FILE *iAFP;  // 索引管理文件
    FILE *nameTxt, *nameBin;
    FILE *otherTxt, *otherBin;
    FILE *sourceBin;
    dataHead dHead;  // 数据文件头结点
    acctIndexHead aiHead;
    nameIndexHead niHead;
    timeIndexHead tiHead;
    indexAdmiNode iaNode;
    time_t t;

    t = time(NULL);  // 获得当前时间
                     // 数据文件
    if ((dfP = fopen("dataFile.dat", "rb+")) ==
        NULL)  // 打开数据文件,如果不存在数据文件自动创建文件
    {
        dfP = fopen("dataFile.dat", "w");
        fclose(dfP);
    }
    // 账号索引文件
    if ((aifP = fopen("indexOfAcct.dat", "rb+")) ==
        NULL)  // 打开数据文件,如果不存在账号索引文件文件自动创建文件
    {
        aifP = fopen("indexOfAcct.dat", "w");
        fclose(aifP);
    }
    // 姓名索引文件
    if ((nifP = fopen("indexOfName.dat", "rb+")) ==
        NULL)  // 打开数据文件,如果不存在账号索引文件文件自动创建文
    {
        nifP = fopen("indexOfName.dat", "w");
        fclose(nifP);
    }
    // 时间索引文件
    if ((tifP = fopen("timeOfAcct.dat", "rb+")) ==
        NULL)  // 打开数据文件,如果不存在账号索引文件文件自动创建文件
    {
        tifP = fopen("timeOfAcct.dat", "w");
        fclose(tifP);
    }
    // 账号管理文件
    if ((iAFP = fopen("indexAdministrator.dat", "rb+")) ==
        NULL)  // 如果文件不存在自动创建
    {
        iAFP = fopen("indexAdministrator.dat", "w");
        fclose(iAFP);
    }
    // 姓名文本文件
    if ((nameTxt = fopen("name.txt", "r")) == NULL)  // 如果文件不存在自动创建
    {
        printf("无姓名文件!/n");
        exit(0);
    }
    // 姓名二进制文件
    if ((nameBin = fopen("name.dat", "rb")) == NULL)  // 如果文件不存在自动创建
    {
        nameBin = fopen("name.dat", "w");
        fclose(nameBin);
    }

    // 附加信息文本文件
    if ((otherTxt = fopen("other.txt", "r")) == NULL)  // 如果文件不存在自动创建
    {
        printf("无附加信息文件!/n");
        exit(0);
    }
    // 附加信息二进制文件
    if ((otherBin = fopen("other.dat", "rb")) == NULL)  // 如果文件不存在自动创建
    {
        otherBin = fopen("other.dat", "w");
        fclose(otherBin);
    }

    // 数据源文件

    if ((sourceBin = fopen("dataSource.dat", "ab+")) == NULL)  // 如果文件不存在自动创建
    {
        sourceBin = fopen("dataSource.dat", "w");
        sourceBin = fopen("dataSource.dat", "ab+");
    }

    dfP = fopen("dataFile.dat", "rb+");
    dHead = getDataHead(dfP);
    aiHead = getAcctIndexHead(aifP);

    aifP = fopen("indexOfAcct.dat", "rb+");
    niHead = getNameIndexHead(nifP);

    iAFP = fopen("indexAdministrator.dat", "rb+");
    iaNode = getIndexAdmiNode(iAFP);
    if (dHead.dANum < 0)  // 数据
    {
        dHead.dANum = 0;
        dHead.dENum = 0;
    }
    if (aiHead.iANum < 0)  // 账号索引头
    {
        aiHead.iANum = 0;
        aiHead.iENum = 0;
        aiHead.tLayer = 0;
    }
    if (niHead.iANum < 0)  // 姓名索引头
    {
        niHead.iANum = 0;
        niHead.iENum = 0;
        niHead.tLayer = 0;
    }
    if (tiHead.iANum < 0)  // 时间索引头
    {
        tiHead.iANum = 0;
        tiHead.iENum = 0;
        tiHead.tLayer = 0;
    }
    if (iaNode.isAccountIndexOn < 0) {
        iaNode.isAccountIndexOn = 0;
        iaNode.isBalanceIndexOn = 0;
        iaNode.isNameIndexOn = 0;
        iaNode.isSerialumIndexOn = 0;
    }

    printf("======================================================================/n");
    printf("                 *** %d RANKS B+TREE START  ***/n", M);
    printf("======================================================================/n");
    printf("帐号范围: 1 ~ %d/t/t/t/t    ", MAX);
    secToDate(t);  // 显示系统时间
    printf("/n数据文件中:有效数据结点数:%-d/t总数据结点数%-d/n", dHead.dENum,
           dHead.dANum);
    printf("帐号索引中:有效索引结点数:%-d/t总索引结点数%-d/t树的层数:%d/n", aiHead.iENum,
           aiHead.iANum, aiHead.tLayer);
    printf(
        "=============================== "
        "索引状态===============================/n帐号索引:%s /n",
        iaNode.isAccountIndexOn == 0 ? "[关闭]" : "/t[启动]");
    printf("金额索引:%s/n", iaNode.isBalanceIndexOn == 0 ? "[关闭]" : "/t[启动]");
    printf("姓名索引:%s/n", iaNode.isNameIndexOn == 0 ? "[关闭]" : "/t[启动]");
    printf("流水索引:%s", iaNode.isSerialumIndexOn == 0 ? "[关闭]" : "/t[启动]");
    printf("/n======================================================================/n");
}

//--------------------------------------------------------------------------------
//50程序尾 说明:打印程序结束
void printProgrammeEnd() {
    time_t t;

    t = time(NULL);
    printf("======================================================================/n");
    printf("                  *** %d RANKS B+TREE END ***/n/t/t/t/t/t/t    ", M);
    secToDate(t);
    printf("/n======================================================================/n");
    printf("程序关闭!/n");
    system("pause");  // 程序结束时候暂停一下
}

//--------------------------------------------------------------------------------
//51索引管理
// 说明:索引修改管理，如果已经打开则运行之后关闭索引，如果关闭则打开，返回选择情况
int indexMenu(FILE *iAFP) {
    indexAdmiNode iaNode;
    int menuChoice;
    int intChoice;
    char makeSure;

    iaNode = printIndexState(iAFP);  // 打印并获得索引管理文件
    printf("更改索引状态:/n");
    printf("1: 帐号   ");
    printf("2: 金额   ");
    printf("3: 姓名   ");
    printf("4: 流水   ");
    printf("0: 取消/n>>");
    scanf("%d", &menuChoice);

    if (menuChoice == 1) {
        printf("确认要 %s 帐号索引? 是(Y) , 否(N)  /n>>",
               iaNode.isAccountIndexOn == 1 ? "<停止>" : "<启动>");
        fflush(stdin);
        makeSure = getchar();
        if (makeSure == 'Y' || makeSure == 'y') {
            intChoice = 1;
        } else
            intChoice = 0;
        menuChoice = intChoice;
    } else if (menuChoice == 2) {
        printf("确认要 %s 金额索引? 是(Y) , 否(N)  /n>>",
               iaNode.isBalanceIndexOn == 1 ? "<停止>" : "<启动>");
        fflush(stdin);
        makeSure = getchar();
        if (makeSure == 'Y' || makeSure == 'y') {
            intChoice = 2;
        } else
            intChoice = 0;
        menuChoice = (intChoice == 1 ? 2 : 0);
    } else if (menuChoice == 3) {
        printf("确认要 %s 姓名索引? 是(Y) , 否(N)  /n>>",
               iaNode.isNameIndexOn == 1 ? "<停止>" : "<启动>");
        fflush(stdin);
        makeSure = getchar();
        if (makeSure == 'Y' || makeSure == 'y') {
            intChoice = 3;
        } else
            intChoice = 0;
        menuChoice = (intChoice == 1 ? 3 : 0);
    } else if (menuChoice == 4) {
        printf("确认要 %s 流水号索引? 是(Y) , 否(N)  /n>>",
               iaNode.isSerialumIndexOn == 1 ? "<停止>" : "<启动>");
        fflush(stdin);
        makeSure = getchar();
        if (makeSure == 'Y' || makeSure == 'y') {
            intChoice = 4;
        } else
            intChoice = 0;
        menuChoice = (intChoice == 1 ? 4 : 0);
    }
    if (menuChoice >= 0 && menuChoice <= 4) {
        return menuChoice;
    } else
        return 0;
}

//-------------------------------------------------------------------------------- 52.1更改帐号索引状态
// 说明:未使用
void acctIndexChange(FILE *iAFP, FILE *aifP, FILE *dfP, int menu) {
    indexAdmiNode iaNode;

    iaNode = getIndexAdmiNode(iAFP);
    if (iaNode.isAccountIndexOn == 1)  // 如果已经开启了帐号索引,现在想取消
    {
    } else  // 如果没有索引现在想建立帐号索引,并以后插入删除自动维护索引
    {
    }
}
//-------------------------------------------------------------------------------- 52.2更改金额索引状态
// 说明:
void balanceIndexChange(FILE *iAFP, FILE *aifP, FILE *dfP, int menu) {
    // 待完善...
}
//-------------------------------------------------------------------------------- 52.3更改姓名索引状态
// 说明:
void nameIndexChange(FILE *iAFP, FILE *aifP, FILE *dfP, int menu) {
    // 待完善...
}
//-------------------------------------------------------------------------------- 52.4更改流水号索引状态
// 说明:
void serialIndexChange(FILE *iAFP, FILE *aifP, FILE *dfP, int menu) {
    // 待完善...
}

//-------------------------------------------------------------------------------- 53
//获得索引管理结点 说明:得到并返回当前索引管理文件数据
indexAdmiNode getIndexAdmiNode(FILE *iAFP) {
    indexAdmiNode iaNode;

    rewind(iAFP);
    fread(&iaNode, IAN, 1, iAFP);
    return iaNode;
}

//--------------------------------------------------------------------------------
//54无索引插入单条数据
// 说明:在不建立任何索引的时候直接往数据文中插入数据,返回插入数据的地址
int insertWithOutIndex(FILE *dfP, dataNode dNode) {
    int dataAddr;    // 数据文件的位置
    dataHead dHead;  // 数据文件头

    dHead = getDataHead(dfP);
    dataAddr =
        dataCellToAddr(dHead.dANum);  // 转换数据文件的所在地址,也就是将要新插入数据的地址
    setData(dfP, dNode, dataAddr);  // 将数据写入数据文件
    dHead.dENum = ++DENum;  // 全局变量DENum增加,说明已经写入了一条数据
    dHead.dANum = ++DANum;  // 全局变量DANum也增加,说明已经写入了一条数据
    setDataHead(dfP, dHead);  // 写回数据头结点
    return dataAddr;          // 返回插入数据结点的地址
}

//--------------------------------------------------------------------------------
//55初始化索引管理文件 说明:开始时候默认所有索引都已停止，即为0
void initializeIndexAdmini(FILE *iAFP) {
    indexAdmiNode iaNode;

    iaNode = getIndexAdmiNode(iAFP);
    IsAcctIndexOn = iaNode.isAccountIndexOn = 0;  // 初始化并赋值给全局变量
    IsBalaIndexOn = iaNode.isBalanceIndexOn = 0;
    IsNameIndexOn = iaNode.isNameIndexOn = 0;
    IsSerlIndexOn = iaNode.isSerialumIndexOn = 0;
    setAdminiIndex(iAFP, iaNode);  // 将修改之后的值写回文件
}

//--------------------------------------------------------------------------------
//56打印索引状态 说明:
indexAdmiNode printIndexState(FILE *iAFP) {
    indexAdmiNode iaNode;

    iaNode = getIndexAdmiNode(iAFP);
    iaNode.isAccountIndexOn == 1 ? printf("帐号索引: /t  [已启动]/n")
                                 : printf("帐号索引: [已停止]/n");
    iaNode.isBalanceIndexOn == 1 ? printf("金额索引: /t  [已启动]/n")
                                 : printf("金额索引: [已停止]/n");
    iaNode.isNameIndexOn == 1 ? printf("姓名索引: /t  [已启动]/n")
                              : printf("姓名索引: [已停止]/n");
    iaNode.isSerialumIndexOn == 1 ? printf("流水索引: /t  [已启动]/n")
                                  : printf("流水索引: [已停止]/n");
    return iaNode;
}

//--------------------------------------------------------------------------------
//57修改索引管理信息 说明:修改并显示索引修改情况
void changeAdminiIndex(FILE *iAFP, int i) {
    indexAdmiNode iaNode;

    iaNode = getIndexAdmiNode(iAFP);
    switch (i) {
        case 1:
            iaNode.isAccountIndexOn = (iaNode.isAccountIndexOn == 1 ? 0 : 1);
            IsAcctIndexOn = iaNode.isAccountIndexOn;
            break;
        case 2:
            iaNode.isBalanceIndexOn = (iaNode.isBalanceIndexOn == 1 ? 0 : 1);
            break;
        case 3:
            iaNode.isNameIndexOn = (iaNode.isNameIndexOn == 1 ? 0 : 1);
            IsNameIndexOn = iaNode.isNameIndexOn;
            break;
        case 4:
            iaNode.isSerialumIndexOn = (iaNode.isSerialumIndexOn == 1 ? 0 : 1);
            break;
        default:
            break;
    }
    setAdminiIndex(iAFP, iaNode);  // 将更改之后的值写回文件
}

//--------------------------------------------------------------------------------
//58写入索引管理信息 说明:
indexAdmiNode setAdminiIndex(FILE *iAFP, indexAdmiNode iaNode) {
    rewind(iAFP);
    fwrite(&iaNode, IAN, 1, iAFP);
    return iaNode;
}

//-------------------------------------------------------------------------------- 59.1重建帐号索引
// 说明:根据数据生成帐号索引,把所有的索引全清除然后重新生成
void rebulidAcctIndex(FILE *dfP, FILE *aifP) {
    int i;  // 循环变量
    dataNode dNode;
    int count = 0;
    clock_t start = 0, finish;  // 计时
    clock_t finish1, tt = 0;
    double duration;
    double duration1;
    double duration2;
    double leaveTime;

    start = clock();
    initializeAcctIndexFile(aifP);  // 首先初始化帐号索引文件
    printLine(19);
    for (i = 0; i < DANum; i++) {
        dNode = getData(dfP, i * DN + DH);
        dNode = regressDataNext(dfP, i * DN + DH,
                                dNode);  // 让数据的所有next全部回复到初始的-1状态
        if (dNode.acct > 0)
            disposeAcctIndex(dfP, aifP, dNode, i * DN + DH);  // 建立帐号索引
        if (i % 1000 == 0 && i != 0) {
            finish1 = clock();
            duration1 = (double)(finish1 - start) / CLOCKS_PER_SEC;
            duration2 = (double)(finish1 - tt) / CLOCKS_PER_SEC;
            leaveTime = (DENum - i) * duration1 / i;
            printf("第 %-7d 条 耗时: ", i);
            timeShow(duration2);
            printf("/t/t总耗时: ");
            timeShow(duration1);
            printf("/t/t预计剩余:");
            timeShow(leaveTime);
            printf("/n");
            tt = finish1;
        }
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;

    printLine(19);
    printf("耗时:");
    timeShow(duration);
    printf("/n");
}

//-------------------------------------------------------------------------------- 59.2重建姓名索引
// 说明:根据数据生成姓名索引,
void rebulidNameIndex(FILE *dfP, FILE *nifP) {
    // 待完善...
}

//-------------------------------------------------------------------------------- 60.1删除帐号索引
// 说明:删除所有的帐号索引
void deleteAcctIndex(FILE *aifP) {
    fclose(aifP);
    aifP = fopen("indexOfAcct.dat", "w");  // 清空其中数据
    fclose(aifP);
    aifP = fopen("indexOfAcct.dat", "rb+");  // 重新打开
    initializeAcctIndexFile(aifP);
}

//-------------------------------------------------------------------------------- 60.2删除姓名索引
// 说明:删除所有的帐号索引
void deleteNameIndex(FILE *nifP) {
    fclose(nifP);
    nifP = fopen("indexOfName.dat", "w");  // 清空其中数据
    fclose(nifP);
    nifP = fopen("indexOfName.dat", "rb+");  // 重新打开
    initializeNameIndexFile(nifP);
}

//-------------------------------------------------------------------------------- 61.1按帐号无索引查找
// 说明:在数据文件中从开始往后查找,找到返回找到的地址
int searchWithOutIndexByAcct(FILE *dfP, int acct, int startAddr) {
    dataNode dNode;
    int i;
    int dataAddr;

    i = (startAddr - DH) / DN;  // 获得startAddr处地址是第多少个数据
    for (; i < DANum; i++) {
        dataAddr = dataCellToAddr(i);
        fseek(dfP, dataAddr, SEEK_SET);
        fread(&dNode, DN, 1, dfP);
        if (dNode.acct == acct) {
            return dataAddr;  // 这个地址既可以做找到数据的地址,又可以做下一次的开始地址
        }
    }
    return -1;  // 如果循环出来了说明没有找到
}

//-------------------------------------------------------------------------------- 61.2按姓名无索引查找
// 说明:
int searchWithOutIndexByName(FILE *dfP, char *name) {
    return -1;
    // 待完善...
}

//--------------------------------------------------------------------------------
//62将帐号的acctNext置空 说明:
dataNode regressDataNext(FILE *dfP, int dataAddr, dataNode dNode) {
    dNode.nextAcctAddr = -1;
    dNode.nextBalAddr = -1;
    dNode.nextNameAddr = -1;
    dNode.nextNoAddr = -1;
    setData(dfP, dNode, dataAddr);
    return dNode;
}

//--------------------------------------------------------------------------------
//63简单显示物理数据
// 说明:以物理方式从头到尾显示数据，n代表时间显示格式，若0则秒，否则是日历显示方式
void displaySimpleData(FILE *dfP, int addr, dataNode dNode, int n) {
    printf("%-20s", dNode.serialNum);  // 流水号
    printf("[%8d] /t/t", addr);
    printf("%-5d/t/t", dNode.acct);
    printf("%-7s/t", dNode.name);
    printf("%-10.2f/t", dNode.balance);
    printf("%-20s/t", dNode.other);
    if (n == 1)  // 将时间已年月日时分秒形式显示
    {
        secToDate(dNode.insertTime);
        printf("/t");
    } else {
        printf("%-15d/t", dNode.insertTime);  // 将时间以秒的形式显示
    }
    printf("[%-d]/n", dNode.nextAcctAddr);
}

//--------------------------------------------------------------------------------
//64将一个整数转换成一个字符串
// 说明:将n位整数number转换成字符串,其实生成的n位最后一位是'/0'
void intToString(int number, int n, char *s) {
    int base = 1;
    int i;

    if (n == 0) {
        *s = 0;
        return;
    }

    for (i = 0; i < n - 1; i++) base *= 10;
    intToString(number - number / base * base, n - 1, s + 1);
    *s = number / base + '0';  // 跌代算法
}

//--------------------------------------------------------------------------------
//65获得全手工输入信息
// 说明：首先获取手工输入信息,再转换成数据源样子的数据,再转换成真正的数据,本来如果输入的账号和信息和源数据文件中姓名账号不符不予返回
void getManualInput(FILE *aifP, FILE *dfP, FILE *sfP) {
    time_t t, PreSec;
    dataNode dNode;
    dataNode dNode1;
    sourceDataCell sdC;
    double balance;    // 帐号金额,8b
    int insertAddres;  // 插入的地方
    clock_t start, finish;
    double duration;

    printf("手工输入信息,帐号为正整数,金额必须是数值,范围从1到 %d (当输入 0 退出插入.)/n",
           MAX);
    printf("请输入用户<账号> <金额> 以及 <附加信息>/n");
    printf("账号:");
    if (!scanf("%d", &sdC.acct) || sdC.acct < 0)  // 如果输入非正整数或者字符则返回
    {
        printf("帐号必须为正整数!/n");
        return;
    }
    if (sdC.acct > MAX) {
        printf("输入账号范围错误!/n");
        return;
    }
    if (sdC.acct == 0)  // 如果输入0则退出插入
    {
        printf("退出插入!/n");
        goto r;
    }
    dNode1 = getFromDataSourceFile(sfP, sdC.acct);
    strcpy(sdC.name, dNode1.name);  // 根据账号自动寻找姓名插入
    printf("金额:");
    if (!scanf("%lf", &balance))  // 输入得必须是数值,正负均可,负代表从银行贷出去
    {
        printf("金额必须为数值形!/n");
        goto r;
    }
    printf("附加信息:");
    scanf("%s", sdC.other);

r:
    while (sdC.acct > 0) {
        start = clock();
        t = time(NULL);   // 获取当前时间
        if (t == PreSec)  // 如果执行时间还是在一秒钟之内,则流水号++
        {
            SerialControl++;  // 全局变量
        } else {
            SerialControl = 0;  // 流水账号还原到初始位置
        }
        dNode = doSNTDN(sdC, t, SerialControl);  // 将原始数据加工成完整的数据
        dNode.balance = balance;                 // 这个钱来自用户自己的输入
        PreSec = t;
        printf("正在插入数据请稍等.../n");
        insertAddres = insertWithOutIndex(dfP, dNode);  // 首先向数据文件写一条数据
        if (IsAcctIndexOn == 1)                         // 如果建立索引则维护之
        {
            disposeAcctIndex(dfP, aifP, dNode, insertAddres);
        }
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("插入成功!/n");
        printLine(23);
        printf("耗时:");
        timeShow(duration);
        printf("/n");
        printf("账号:");
        if (!scanf("%d", &sdC.acct) || sdC.acct < 0)  // 如果输入非正整数或者字符则返回
        {
            printf("帐号必须为正整数!/n");
            return;
        }
        if (sdC.acct > MAX) {
            printf("输入账号范围错误!/n");
            return;
        }
        if (sdC.acct == 0)  // 如果输入0则退出插入
        {
            printf("退出插入!/n");
            goto r;
        }
        dNode1 = getFromDataSourceFile(sfP, sdC.acct);
        strcpy(sdC.name, dNode1.name);  // 根据账号自动寻找姓名插入
        printf("金额:");
        if (!scanf("%lf", &balance))  // 输入得必须是数值,正负均可,负代表从银行贷出去
        {
            printf("金额必须为数值形!/n");
            goto r;
        }
        printf("附加信息:");
        scanf("%s", sdC.other);
    }
}

//--------------------------------------------------------------------------------
//66把姓名文本数据存入二进制文件
void readTxtNameWriteBin(FILE *nameTxt, FILE *nameBin) {
    nameNode nNode = {0, ""};

    printf("正在将姓名文从本文件转换为2进制文件,请稍后.../n");
    fscanf(nameTxt, "%d%s", &nNode.no,
           nNode.name);  // 从 txt 文件指针所指向的文件中读取输入，存入到默认结构体中
    while (!feof(nameTxt))  // 如果未到文件结尾
    {
        fseek(nameBin, (nNode.no - 1) * sizeof(nameNode),
              SEEK_SET);  // 将文件的指针定位到文件的正确记录
        fwrite(&nNode, sizeof(nameNode), 1, nameBin);    // 将记录插入文件
        fscanf(nameTxt, "%d%s", &nNode.no, nNode.name);  // 继续读取下一条记录
    }
    printf("姓名数据转换成功!/n/n");
}

//--------------------------------------------------------------------------------
//67把附加信息文本数据以二进制存入
void readTxtOtherWriteBin(FILE *otherTxt, FILE *otherBin) {
    otherNode oNode = {0, ""};

    printf("正在将附加信息从文本文件转换为2进制文件,请稍后.../n");
    fscanf(
        otherTxt, "%d%s", &oNode.no,
        oNode.other);  // 从 otherTxt 文件指针所指向的文件中读取输入，存入到默认结构体中
    while (!feof(otherTxt))  // 如果未到文件结尾
    {
        fseek(otherBin, (oNode.no - 1) * sizeof(otherNode),
              SEEK_SET);  // 将文件的指针定位到文件的正确记录
        fwrite(&oNode, sizeof(otherNode), 1, otherBin);    // 将记录插入文件
        fscanf(otherTxt, "%d%s", &oNode.no, oNode.other);  // 继续读取下一条记录
    }
    printf("附加信息转换成功!/n/n");
}

//--------------------------------------------------------------------------------
//68把原始数据随即组成数据源
void composeFile(int num, FILE *nameBin, FILE *otherBin, FILE *sourceBin) {
    int i;
    int nameNo, otherNo;
    nameNode nNode;
    otherNode oNode;
    sourceDataCell sdC;

    printf("正在合成 %d 条数据源,请稍后.../n", num);
    if (nameBin == NULL || sourceBin == NULL) {
        printf("文件打开失败!");
        exit(0);
    }
    srand(time(NULL));
    for (i = 1; i <= num + 1; i++) {
        // 产生随机数，用于定位各自文件中的位置
        nameNo = rand() % 22093;  // 有22093条姓名数据
        otherNo = rand() % 3888;  // 有3888条网址记录

        // 定位并读取姓名中的一条数据
        fseek(nameBin, nameNo * sizeof(nameNode), SEEK_SET);
        fread(&nNode, sizeof(nameNode), 1, nameBin);

        fseek(otherBin, otherNo * sizeof(otherNode), SEEK_SET);
        fread(&oNode, sizeof(otherNode), 1, otherBin);
        // 生成一条数据
        sdC.acct = i;
        strcpy(sdC.name, nNode.name);  // 复制,后面的复制给前面
        strcpy(sdC.other, oNode.other);
        fseek(sourceBin, (i - 1) * sizeof(sourceDataCell), SEEK_SET);
        fwrite(&sdC, sizeof(sourceDataCell), 1,
               sourceBin);  // 顺序写入到数据文件data.dat中
        if (i % 1000 == 0) {
            printf("/r");
            printf("完成第 %d 条", i);
        }
    }
    printf("/n合成数据源文件成功!/n");
}
//--------------------------------------------------------------------------------
//69时间显示 说明：把秒数已hh:mm:ss mmm格式显示，最后的三个m表示三位毫秒
void timeShow(double t) {
    int h;
    int m;
    int s;
    double ms;
    double tempT = t;

    h = (int)(t / 3600);
    t -= h * 3600;
    m = (int)(t / 60);
    t -= m * 60;
    s = (int)(t);
    t -= s * 60;
    additionalTime0(h);
    printf(":");
    additionalTime0(m);
    printf(":");
    additionalTime0(s);
    printf(" ");
    s = tempT / 1;
    ms = tempT - s;
    printf("%-3.0f", ms * 1000);
}
//--------------------------------------------------------------------------------
//70美观时间格式
void additionalTime0(int t) {
    if (t == 0)
        printf("00");
    else if (t < 10)
        printf("0%d", t);
    else
        printf("%d", t);
}
//----------------------------------------------------END-------------------------------------------