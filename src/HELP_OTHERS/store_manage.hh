//
// Created by AUGUS on 2021/7/6.
//

#ifndef AUGUSTEST_STORE_MANAGE_HH
#define AUGUSTEST_STORE_MANAGE_HH

#include<iostream>
#include<fstream>
#include<string>
#include <cstring>
#include<iomanip>
#include<vector>
#include<algorithm>

#include "gtest/gtest.h"

std::string menuMain =
    "|-----------------------------------------|\n"
    "|            请输入选项编号（0-5）:          |\n"
    "|-----------------------------------------|\n"
    "|              1--创建商品档案              |\n"
    "|              2--编辑商品信息              |\n"
    "|              3--统计销售情况              |\n"
    "|              4--查询商品信息              |\n"
    "|              5--显示商品信息              |\n"
    "|              0--退出系统                 |\n"
    "|-----------------------------------------|\n";

std::string menuSub1 =
    "|*****************************************|\n"
    "|            请输入选项编号（0-4）:          |\n"
    "|*****************************************|\n"
    "|              1--添加新商品                |\n"
    "|              2--删除原有商品              |\n"
    "|              3--修改原有商品信息           |\n"
    "|              4--返回                     |\n"
    "|              0--退出                     |\n"
    "|*****************************************|\n";

std::string menuSub2 =
    "|*****************************************|\n"
    "|            请输入选项编号（0-4）:          |\n"
    "|*****************************************|\n"
    "|              1--添加新商品                |\n"
    "|              2--删除原有商品              |\n"
    "|              3--修改原有商品信息           |\n"
    "|              4--返回                     |\n"
    "|              0--退出                     |\n"
    "|*****************************************|\n";

std::string menuSub3 =
    "|*****************************************|\n"
    "|            请输入选项编号（0-4）:          |\n"
    "|*****************************************|\n"
    "|              1--添加新商品                |\n"
    "|              2--删除原有商品              |\n"
    "|              3--修改原有商品信息           |\n"
    "|              4--返回                     |\n"
    "|              0--退出                     |\n"
    "|*****************************************|\n";

std::string menuSub4 =
    "|*****************************************|\n"
    "|            请输入选项编号（0-4）:          |\n"
    "|*****************************************|\n"
    "|              1--添加新商品                |\n"
    "|              2--删除原有商品              |\n"
    "|              3--修改原有商品信息           |\n"
    "|              4--返回                     |\n"
    "|              0--退出                     |\n"
    "|*****************************************|\n";

std::string menuSub5 =
    "|*****************************************|\n"
    "|            请输入选项编号（0-4）:          |\n"
    "|*****************************************|\n"
    "|              1--添加新商品                |\n"
    "|              2--删除原有商品              |\n"
    "|              3--修改原有商品信息           |\n"
    "|              4--返回                     |\n"
    "|              0--退出                     |\n"
    "|*****************************************|\n";

int testp()
{
    int in_menu_main;
    std::cout << menuMain;

    std::cin >> in_menu_main;
    switch (in_menu_main) {
        case 1:
            std::cout << menuSub1;
            break;
        case 2:
            std::cout << menuSub2;
            break;
        case 3:
            std::cout << menuSub3;
            break;
        case 4:
            std::cout << menuSub4;
            break;
        case 5:
            std::cout << menuSub5;
            break;
        case 0:
            return 0;
        default:
            std::cout << "您输入的有误，请重新输入！\n";
            std::cout << menuMain;
            break;
    }


    return 0;
}


#define  MAX_SIZE    100

using namespace std;

fstream in_out_file;

bool tagx = false;//用来标志是否退出系统
class greater_than;

string sg = "./goods.txt";

class goods//商品类
{
public:
    goods(int bianhao, char *pinming, double jinjia, double shoujia, int jinhuoliang, int xiaoshouliang) : number(
        bianhao), price_in(jinjia), price_out(shoujia), number_in(jinhuoliang), number_out(xiaoshouliang)
    {
        strcpy(name, pinming);
        number_remain = number_in - number_out;
        money_in = price_out * number_out;
        net_win = money_in - price_in * number_out;

    }

    goods()
        : number(0), price_in(0), price_out(0), number_in(0), number_out(0), number_remain(0), money_in(0), net_win(0)
    {
        strcpy(name, "");

    }

    ~goods() {}
    friend bool Is_name_used(char (&p)[20]);
    friend bool Is_number_used(int a);
    friend void input_goods(goods s);
    friend void conlect_sell_info();
    friend void delete_goods();
    friend void modify_goods();
    friend void check_with_name();
    friend void check_with_remain();
    friend void show_unchange();
    friend void show_with_money_in();
    friend void show_with_net_win();

    friend class greater_than;

    friend class greater_than2;

private:
    int number;//编号
    char name[20];//品名
    double price_in;//进价
    double price_out;//售价
    int number_in;//进货量
    int number_out;//销售量
    int number_remain;//剩余量
    double money_in;//销售额=售价*销售量
    double net_win;//毛利=销售额-进价*销售量

};

class greater_than
{
public:
    bool operator()(const goods &lhs, const goods &rhs)
    {
        return (lhs.money_in > rhs.money_in ? true : false);
    }
};//函数对象1的定义

class greater_than2
{
public:
    bool operator()(const goods &lhs, const goods &rhs)
    {
        return (lhs.net_win > rhs.net_win ? true : false);
    }
};//函数对象2的定义



bool Is_name_used(char (&p)[20])
{
    bool tag1 = false;//用来标志这个商品名称是否已经存在
    goods goods2;
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char *>(&goods2), sizeof(goods));
    while (!in_out_file.eof()) {
        if (!strcmp(goods2.name, p)) {
            tag1 = true;
            break;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods2), sizeof(goods));
    }
    in_out_file.clear();

    return tag1;
}


bool Is_number_used(int a)
{
    bool tag2 = false;//用来标志这个编号（其实也是记录编号）是否被用过，false表示没有用过，true表示被使用过
    goods goods3;
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char *>(&goods3), sizeof(goods));
    while (!in_out_file.eof()) {
        if (goods3.number == a) {
            tag2 = true;
            break;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods3), sizeof(goods));
    }
    in_out_file.clear();
    return tag2;
}


void input_goods(goods s)
{

    in_out_file.clear();
    in_out_file.seekp((s.number - 1) * sizeof(goods));
    in_out_file.write(reinterpret_cast<const char *>(&s), sizeof(goods));
    in_out_file.clear();

}


void conlect_sell_info()
{
    string s;
    goods goods4;
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char *>(&goods4), sizeof(goods));
    while (!in_out_file.eof()) {
        if (goods4.number != 0)//这条记录非空
        {
            cout << "商品名：" << goods4.name << setw(20) << "销售额：" << goods4.money_in << setw(10)
                 << "剩余数：" << goods4.number_remain << setw(10) << "毛利：" << goods4.net_win << endl;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods4), sizeof(goods));
    }
    in_out_file.clear();
    cin >> s;
}


void produce_goods()
{
    int a1, a2, a3;//分别用来输入:number,number_in,number_out;
    char p[20];//用来输入name[20];
    double b1, b2;//分别用来输入：price_in,price_out;

    cout << "请输入商品的名称" << endl;
    cin >> p;
    if (Is_name_used(p))//Is_name_used(char *)函数用来判断是否已经存在这个商品，是返回true,否则返回false;
    {
        cout << "你输入的商品已经存在" << endl;
        return;
    }

    cout << "请输入商品的编号" << endl;
    cin >> a1;
    while (a1 <= 0 || a1 > MAX_SIZE
        || Is_number_used(a1))//Is_number_used(int)函数用来判断是否这个编号已经存在与记录中，这个函数应该返回false来表示可以使用这个编号
    {
        if (Is_number_used(a1)) {
            cout << "你输入的编号已经存在，请重新指定一个商品编号" << endl;
        } else {
            cout << "你的输入超出范围，请重新指定一个商品编号" << endl;
        }
        cin >> a1;
    }

    cout << "请输入次商品的进价" << endl;
    cin >> b1;
    cout << "请输入此商品的售价" << endl;
    cin >> b2;
    while (b2 < b1) {
        cout << "售价低于进价，此商品将亏本,请重新输入售价" << endl;
        cin >> b2;
    }
    cout << "请输入此商品的进货量" << endl;
    cin >> a2;
    cout << "请输入此商品的销售量" << endl;
    cin >> a3;
    while (a3 > a2) {
        cout << "销售量不能超过进货量，请重新输入" << endl;
        cin >> a3;
    }
    goods gs(a1, p, b1, b2, a2, a3);
    input_goods(gs);//input_goods(goods s )函数用来向记录文件中加入新的商品记录；


}

void show_main_menu();//对show_main_menu（）的声明

void delete_goods()
{
    char p1[20];//用来输入商品名称
    int num;//用来保存商品的记录号
    cout << "请输入你要删除的商品的名称" << endl;
    cin >> p1;
    cin.clear();
    if (!Is_name_used(p1)) {
        cout << "此商品不存在，不能删除" << endl;
        return;
    }

    goods goods5;
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char * >(&goods5), sizeof(goods));
    while (!in_out_file.eof()) {
        if (!strcmp(goods5.name, p1)) {
            break;
        }
        in_out_file.read(reinterpret_cast<char * >(&goods5), sizeof(goods));
    }

    in_out_file.clear();
    num = goods5.number;//保存要删除的记录号
    goods goods6;//产生一个空白记录，用这个空白记录替代原有记录
    in_out_file.seekp((num - 1) * sizeof(goods));
    in_out_file.write(reinterpret_cast<const char *>(&goods6), sizeof(goods));

    in_out_file.clear();

}

void modify_goods()
{
    char p[20];
    cout << "请输入你要修改的商品名称" << endl;
    cin >> p;
    if (!Is_name_used(p)) {
        cout << "没有这个商品，不能修改" << endl;
        return;
    }

    goods goods7;
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char *>(&goods7), sizeof(goods));
    while (!in_out_file.eof()) {
        if (!strcmp(goods7.name, p)) {
            break;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods7), sizeof(goods));
    }

    in_out_file.clear();
    cout << "下面开始修改商品" << "的信息" << endl;
    cout << "要修改它的进价吗？是（Y/y），否按其他键" << endl;
    string s1;
    cin >> s1;
    if (s1 == "Y" || s1 == "y") {
        double a1;
        cout << "请输入它的新的进价" << endl;
        cin >> a1;
        goods7.price_in = a1;
    }
    cout << "要修改它的售价吗？是（Y/y），否按其他键" << endl;
    cin >> s1;
    if (s1 == "Y" || s1 == "y") {
        double a1;
        cout << "请输入它的新的进价" << endl;
        cin >> a1;
        goods7.price_out = a1;
    }
    cout << "要修改它的进货量吗？是（Y/y），否按其他键" << endl;
    if (s1 == "Y" || s1 == "y") {
        int a1;
        cout << "请输入它的新的进货量" << endl;
        cin >> a1;
        goods7.number_in = a1;
    }
    cout << "要修改它的销售量吗？是（Y/y），否按其他键" << endl;
    if (s1 == "Y" || s1 == "y") {
        int a1;
        cout << "请输入它的新的销售量" << endl;
        cin >> a1;
        goods7.number_out = a1;
        goods7.number_remain = goods7.number_in - goods7.number_out;//计算新的剩余量
        goods7.money_in = goods7.number_out * goods7.price_out;//计算新的销售额
        goods7.net_win = goods7.money_in - goods7.price_in * goods7.number_out;//计算新的毛利
    }

    in_out_file.clear();
    in_out_file.seekp((goods7.number - 1) * sizeof(goods));
    in_out_file.write(reinterpret_cast<const char *>(&goods7), sizeof(goods));

    in_out_file.clear();
}

void show_sub_menu2()
{
    int choice2;
    bool tag2 = false;//用来标志是否退出系统
    while (tag2 == false) {
        cout << "请输入选项编号（0-4）" << endl;
        cout << "1--添加新商品" << endl;
        cout << "2--删除原有商品" << endl;
        cout << "3--修改原有商品信息" << endl;
        cout << "4--返回" << endl;
        cout << "0--退出" << endl;
        cin >> choice2;
        while (choice2 > 4 || choice2 < 0) {
            cout << "没有这个选项，请重新输入" << endl;
            cin >> choice2;
        }
        system("cls");
        if (choice2 == 0) {
            tag2 = true;
            tagx = true;
            return;
        } else {
            switch (choice2) {
                case 1:
                    produce_goods();
                    break;
                case 2:
                    delete_goods();//此函数用来删除原有商品
                    break;
                case 3:
                    modify_goods();//此函数用来修改原有商品
                    break;
                case 4:
                    show_main_menu();
                    break;
            }
        }
    }//while结束
    system("cls");
}


void check_with_name()
{
    char p[20];
    goods goods8;
    cout << "请输入你要查询的商品名称" << endl;
    cin >> p;
    if (!Is_name_used(p)) {
        cout << "没有这个商品的信息" << endl;
        return;
    }
    in_out_file.clear();
    in_out_file.seekg(0);


    in_out_file.read(reinterpret_cast<char *>(&goods8), sizeof(goods));
    while (!in_out_file.eof()) {
        if (!strcmp(goods8.name, p)) {
            cout << "商品名:" << goods8.name << setw(10) << "买入量:" << goods8.number_in << setw(10) << "卖出量:"
                 << goods8.number_out << setw(10)
                 << "剩余量:" << goods8.number_remain << setw(10) << "进价:" << goods8.price_in << setw(10)
                 << "售价:" << goods8.price_out << setw(10) << "销售额:" << goods8.money_in << setw(10)
                 << "毛利:" << goods8.net_win << setw(10) << endl;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods8), sizeof(goods));
    }
    in_out_file.clear();
}

void check_with_remain()
{
    cout << "输入一个剩余数的上限，程序将列出所有剩余数小于这个数的商品信息" << endl;
    int limit;
    goods goods9;
    cin >> limit;
    while (limit < 0) {
        cout << "输入数据不合法，请重新输入" << endl;
        cin >> limit;
    }
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char *>(&goods9), sizeof(goods));
    while (!in_out_file.eof()) {
        if (goods9.number != 0 && goods9.number_remain < limit) {
            cout << "商品名:" << goods9.name << setw(10) << "买入量:" << goods9.number_in << setw(10) << "卖出量:"
                 << goods9.number_out << setw(10)
                 << "剩余量:" << goods9.number_remain << setw(10) << "进价:" << goods9.price_in << setw(10)
                 << "售价:" << goods9.price_out << setw(10) << "销售额:" << goods9.money_in << setw(10)
                 << "毛利:" << goods9.net_win << setw(10) << endl;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods9), sizeof(goods));
    }

    in_out_file.clear();
}


void show_sub_menu4()
{
    int choice3;
    bool tag3 = false;//用来标志是否退出系统
    while (tag3 == false) {
        cout << "请输入选项编号（0-3）" << endl;
        cout << "1--按品名查询" << endl;
        cout << "2--按剩余数查询" << endl;
        cout << "3--返回" << endl;
        cout << "0--退出" << endl;

        cin >> choice3;
        while (choice3 > 3 || choice3 < 0) {
            cout << "没有这个选项，请重新输入" << endl;
            cin >> choice3;
        }
        system("cls");
        if (choice3 == 0) {
            tag3 = true;
            tagx = true;
            return;
        } else {
            switch (choice3) {
                case 1:
                    check_with_name();//此函数按品名查询商品信息
                    break;
                case 2:
                    check_with_remain();//此函数按剩余数查询商品信息
                    break;
                case 3:
                    show_main_menu();
                    break;
            }
        }
    }//while结束
    system("cls");
}

void show_unchange()
{
    cout << "下面按照原来顺序来显示商品信息" << endl;
    string s;
    goods goods10;
    in_out_file.clear();
    in_out_file.seekg(0);
    in_out_file.read(reinterpret_cast<char *>(&goods10), sizeof(goods));
    while (!in_out_file.eof()) {
        if (goods10.number != 0)//这条记录非空
        {
            cout << "商品名:" << goods10.name << setw(10) << "买入量:" << goods10.number_in << setw(10) << "卖出量:"
                 << goods10.number_out << setw(10)
                 << "剩余量:" << goods10.number_remain << setw(10) << "进价:" << goods10.price_in << setw(10)
                 << "售价:" << goods10.price_out << setw(10) << "销售额:" << goods10.money_in << setw(10)
                 << "毛利:" << goods10.net_win << setw(10) << endl;
        }
        in_out_file.read(reinterpret_cast<char *>(&goods10), sizeof(goods));
    }
    in_out_file.clear();
    cin >> s;

}

void show_with_money_in()
{
    cout << "下面按照销售额从高到低的顺序显示商品信息" << endl;
    vector<goods> gvec;
    goods gs;
    in_out_file.clear();
    in_out_file.seekp(0);
    in_out_file.read(reinterpret_cast<char *>(&gs), sizeof(goods));
    while (!in_out_file.eof()) {
        if (gs.number != 0) {
            gvec.push_back(gs);
        }
        in_out_file.read(reinterpret_cast<char *>(&gs), sizeof(goods));
    }

    in_out_file.clear();


    sort(gvec.begin(), gvec.end(), greater_than());

    vector<goods>::iterator iter_begin = gvec.begin();
    vector<goods>::iterator iter_end = gvec.end();
    for (; iter_begin != iter_end; ++iter_begin) {
        cout << "商品名:" << (*iter_begin).name << setw(10) << "买入量:" << (*iter_begin).number_in << setw(10) << "卖出量:"
             << (*iter_begin).number_out << setw(10)
             << "剩余量:" << (*iter_begin).number_remain << setw(10) << "进价:" << (*iter_begin).price_in << setw(10)
             << "售价:" << (*iter_begin).price_out << setw(10) << "销售额:" << (*iter_begin).money_in << setw(10)
             << "毛利:" << (*iter_begin).net_win << setw(10) << endl;
    }

}


void show_with_net_win()
{
    cout << "下面按照毛利从高到低显示商品信息" << endl;

    vector<goods> gvec2;
    goods gs;
    in_out_file.clear();
    in_out_file.seekp(0);
    in_out_file.read(reinterpret_cast<char *>(&gs), sizeof(goods));
    while (!in_out_file.eof()) {
        if (gs.number != 0) {
            gvec2.push_back(gs);
        }
        in_out_file.read(reinterpret_cast<char *>(&gs), sizeof(goods));
    }

    in_out_file.clear();


    sort(gvec2.begin(), gvec2.end(), greater_than2());

    vector<goods>::iterator iter_begin = gvec2.begin();
    vector<goods>::iterator iter_end = gvec2.end();
    for (; iter_begin != iter_end; ++iter_begin) {
        cout << "商品名:" << (*iter_begin).name << setw(10) << "买入量:" << (*iter_begin).number_in << setw(10) << "卖出量:"
             << (*iter_begin).number_out << setw(10)
             << "剩余量:" << (*iter_begin).number_remain << setw(10) << "进价:" << (*iter_begin).price_in << setw(10)
             << "售价:" << (*iter_begin).price_out << setw(10) << "销售额:" << (*iter_begin).money_in << setw(10)
             << "毛利:" << (*iter_begin).net_win << setw(10) << endl;
    }

}

void show_sub_menu5()
{
    int choice4;
    while (1) {
        cout << "请输入选项编号（0-4）" << endl;
        cout << "1--按原来顺序显示 " << endl;
        cout << "2--按销售额高低显示 " << endl;
        cout << "3--按毛利高低显示" << endl;
        cout << "4--返回" << endl;
        cout << "0--退出" << endl;
        cin >> choice4;
        while (choice4 > 4 || choice4 < 0) {
            cout << "没有这个选项，请重新输入" << endl;
            cin >> choice4;
        }
        system("cls");
        if (choice4 == 0) {
            tagx = true;
            return;
        } else {
            switch (choice4) {
                case 1:
                    show_unchange();//此函数按原来的顺序显示商品信息
                    break;
                case 2:
                    show_with_money_in();//此函数按销售额的高低显示商品信息
                    break;
                case 3:
                    show_with_net_win();//此函数按毛利的高低显示商品信息
                    break;
                case 4:
                    show_main_menu();
            }
        }
    }//while接受
    system("cls");
}


void show_main_menu()
{
    int choice;
    while (tagx == false) {
        cout << "请输入选项编号（0-5）:" << endl;
        cout << "1--创建商品档案:" << endl;
        cout << "2--编辑商品信息:" << endl;
        cout << "3--统计销售情况:" << endl;
        cout << "4--查询商品信息:" << endl;
        cout << "5--显示商品信息:" << endl;
        cout << "0--退出系统:" << endl;
        cin >> choice;
        while (choice < 0 || choice > 5) {
            cout << "没有这个选项，请重新输入" << endl;
            cin >> choice;
        }
        system("cls");
        if (choice == 0) {
            tagx = true;
            return;
        } else {
            switch (choice) {
                case 1:
                    produce_goods();//创建商品
                    break;
                case 2:
                    show_sub_menu2();
                    if (tagx == true) {
                        return;
                    }
                    break;
                case 3:
                    conlect_sell_info();
                    break;
                case 4:
                    show_sub_menu4();
                    if (tagx == true) {
                        return;
                    }
                    break;
                case 5:
                    show_sub_menu5();
                    if (tagx == true) {
                        return;
                    }
            }
        }//else结束
    }//while结束
}

void store_manage()
{
    in_out_file.open(sg.c_str(), ios::in | ios::out);
    in_out_file.seekg(0, ios_base::end);
    int length1 = in_out_file.tellg();
    if (length1 == 0)//说明文件goods.txt为空，要初始化文件；
    {
        in_out_file.seekp(0);//put指针放到文件头部
        goods goods1;
        for (int ix2 = 1; ix2 <= MAX_SIZE; ix2++) {
            in_out_file.write(reinterpret_cast<const char *>(&goods1), sizeof(goods));
        } //先向文件写入100条空白的记录
        in_out_file.clear();
    }
    show_main_menu();
    in_out_file.close();
}


#endif //AUGUSTEST_STORE_MANAGE_HH
