//
// Created by AUGUS on 2022/9/11.
// JPEG图像压缩解压算法——C++实现
//

#ifdef __linux__

int main() {
    return 1;
}

#else


#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cmath>

#define MAX 100
#define N 8    //N为每个图像分量的矩阵大小
using namespace std;

/*亮度量化值表*/
struct BrightnessQuantizedValueTable {
    int Q[N][N];

    BrightnessQuantizedValueTable() {
        int x[N][N] = {16, 11, 10, 16, 24, 40, 51, 61,
                       12, 12, 14, 19, 26, 58, 60, 55,
                       14, 13, 16, 24, 40, 57, 69, 56,
                       14, 17, 22, 29, 51, 87, 80, 62,
                       18, 22, 37, 56, 68, 109, 103, 77,
                       24, 35, 55, 64, 81, 104, 113, 92,
                       49, 64, 78, 87, 103, 121, 120, 101,
                       72, 92, 95, 98, 112, 100, 103, 99};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Q[i][j] = x[i][j];
            }
        }
    }
};

BrightnessQuantizedValueTable brightnessQuantizedValueTable;//定义一个亮度量化值表

/*亮度DC差值码表*/
struct BrightnessDC_DifferenceTableList {
    string brightnessDC_DifferenceTable[12];//亮度DC差值码表  类别(数组下标)与码字映射
    BrightnessDC_DifferenceTableList() {
        brightnessDC_DifferenceTable[0] = "00";
        brightnessDC_DifferenceTable[1] = "010";
        brightnessDC_DifferenceTable[2] = "011";
        brightnessDC_DifferenceTable[3] = "100";
        brightnessDC_DifferenceTable[4] = "101";
        brightnessDC_DifferenceTable[5] = "110";
        brightnessDC_DifferenceTable[6] = "1110";
        brightnessDC_DifferenceTable[7] = "11110";
        brightnessDC_DifferenceTable[8] = "111110";
        brightnessDC_DifferenceTable[9] = "1111110";
        brightnessDC_DifferenceTable[10] = "11111110";
        brightnessDC_DifferenceTable[11] = "111111110";
    }
};

BrightnessDC_DifferenceTableList brightnessDC_DifferenceTableList;//定义一个亮度DC差值码表


/*AC系数熵编码时的中间符号*/
struct AC_EntropyCoding_MiddleSymbol {
    string R_S;
    int temp;
};
AC_EntropyCoding_MiddleSymbol ac_EntropyCoding_MiddleSymbol[N * N];//由于用函数返回结构体数组，里面的字符串会出现一些无法处理的乱码，故定义为全局变量

/*熵编码时的编码输出*/
struct EntropyCoding {
    string strTemp1;
    string strTemp;
};
EntropyCoding ac_EntropyCodingStr[N * N];//由于用函数返回结构体数组，里面的字符串会出现一些无法处理的乱码，故定义为全局变量


/* R/S与码字映射结点*/
struct StringMap {
    string key;
    string value;
};

/*亮度AC码表  R/S与码字映射表*/
/**特别注意，以下的亮度AC码表只适用于给出的测试数据，如要其它的测试数据，则必须补全亮度AC码表**/
//网上找到一个fantasy 的博客http://menmory.blog.163.com/blog/static/12690012620114535032530/ 这里面有比较详细的亮度AC码表等
struct StringMapList {
    StringMap stringMap[N * N];
    int partNum;    //该亮度AC码表中的条数

    StringMapList() {
        //部分常用亮度AC码表
        stringMap[0].key = "0/0(EOB)";
        stringMap[0].value = "1010";
        stringMap[1].key = "0/1";
        stringMap[1].value = "00";
        stringMap[2].key = "1/1";
        stringMap[2].value = "1100";
        stringMap[3].key = "1/2";
        stringMap[3].value = "11011";
        stringMap[4].key = "2/1";
        stringMap[4].value = "11100";
        stringMap[5].key = "3/2";
        stringMap[5].value = "111110111";
        stringMap[6].key = "F/0(ZRL)";
        stringMap[6].value = "11111111001";
        stringMap[7].key = "F/F";
        stringMap[7].value = "1111111111111110";
        partNum = 8;
    }
};

StringMapList stringMapList;//定义一个 部分常用亮度AC码表


/*DC差值范围表，本人通过对表找规律发现如下规律 */
int DC_Difference(int temp) {
    int temp1;
    if (temp == 0) {
        temp1 = 0;
    } else {
        for (int i = 1; i <= 11; i++) {
            if (abs(temp) < pow(2, i)) {
                temp1 = i;
                break;
            }
        }
    }
    return temp1;
}


/*AC系数范围表,本人通过对表找规律发现如下规律*/
int AC_Difference(int temp) {
    int temp1;
    if (temp == 0) {
        temp1 = 0;
    } else {
        for (int i = 1; i <= 10; i++) {
            if (abs(temp) < pow(2, i)) {
                temp1 = i;
                break;
            }
        }
    }
    return temp1;
}


/*将正整数十进制转换成二进制*/
string TenToTwo(int temp) {
    string strTemp = "";
    //旧方法
//	for(int k=abs(temp);k>0;k=k/2){
//		strTemp = strTemp + (k%2==1?'1':'0');
//	}
//	//倒置
//	int len = strTemp.length();
//	for(int k=0;k<len/2;k++){
//		char t = strTemp[k];
//		strTemp[k] = strTemp[len-1-k];
//		strTemp[len-1-k] = t;
//	}
    //新方法
    char str[N * N];
    itoa(temp, str, 2);
    strTemp = str;
    return strTemp;
}


/*将正整数二进制转换成十进制*/
int TwoToTen(const string &strTemp) {
    int temp = 0;
    for (char i: strTemp) {
        temp = temp * 2 + i - '0';
    }
    return temp;
}

/*将一个负数的二进制串逐位取反*/
string ConvertToComplement(const string &strTemp) {
    string str;
    for (char i: strTemp) {
        str = str + (i == '1' ? '0' : '1');
    }
    return str;
}


/*DC系数编码*/
EntropyCoding DC_EntropyCoding(int &temp, int &temp1) {
    //对DC系数生成中间符号（中间符号(temp1,temp)）

    //查DC差值表
    temp1 = DC_Difference(temp);

    /*测试*/
//	cout<<temp1<<endl;

    //对中间符号通过查表进行符号编码
    //对 temp1通过查亮度DC差值码表进行熵编码
    EntropyCoding dc_EntropyCodingStr;
    dc_EntropyCodingStr.strTemp1 = brightnessDC_DifferenceTableList.brightnessDC_DifferenceTable[temp1];

    //对 temp进行转换成补码
    //先将 temp转换成二进制串
    dc_EntropyCodingStr.strTemp = TenToTwo(abs(temp));
    //转换成补码
    if (temp < 0) {
        dc_EntropyCodingStr.strTemp = ConvertToComplement(dc_EntropyCodingStr.strTemp);
    }

    /*测试*/
//	cout<<dc_EntropyCodingStr.strTemp1<<"\t"<<dc_EntropyCodingStr.strTemp<<endl;

    return dc_EntropyCodingStr;
}


/*AC系数编码*/
bool AC_EntropyCoding(int F_[N][N], int &index) {
    //对AC系数生成中间符号中/后的部分
    int SSSS[N][N];

    //查AC系数范围表,本人通过对表找规律发现如下规律
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            SSSS[i][j] = AC_Difference(F_[i][j]);
        }
    }

    /*测试*/
//	for(int i=0;i<N;i++){
//		for(int j=0;j<N;j++){
//			cout<<SSSS[i][j]<<" ";
//		}
//		cout<<endl;
//	}

    //Z字形编码
    int count = 0;//计算0的个数
    int i, j, t;
    for (i = 0, j = 1, t = 1; t <= N - 2; t++) {//以下语句设为一个周期，大概要执行N-2个周期（这里N=8，通过观察发现每一下一上为一周期，则有6个周期+半段）
        //向左下方向
        for (; i < N && j >= 0; i++, j--) {
            if (F_[i][j] == 0) {
                count++;
            } else {
                char countString[N * N];
                itoa(count, countString, 10);//将整数count转换为字符串并保存在countString（以10进制方式，也可指定2、8、10、16等进制实现进制转换，进制转换新玩法）
                string strTemp = "/";
                strTemp = countString + strTemp;
                //cout<<"--"<<strTemp<<"--"<<endl;
                char SSSS_String[N * N];
                itoa(SSSS[i][j], SSSS_String, 10);
                strTemp = strTemp + SSSS_String;
                //cout<<"**"<<strTemp<<"**"<<endl;

                //中间符号
                ac_EntropyCoding_MiddleSymbol[index].R_S = strTemp;
                ac_EntropyCoding_MiddleSymbol[index].temp = F_[i][j];
                index++;
                count = 0;//置为0 ，计算下个不为0的数前面0的个数
            }
        }
        if (i >= N && j < 0) {//当出现正中间往下时，挪回正规
            i--;
            j = j + 2;
        } else if (i >= N) {//当出现往下突出时，挪回正规
            i--;
            j = j + 2;
        } else if (j < 0) {//当出现往左突出时，挪回正规
            j++;
        }

        //向右上方向
        for (; i >= 0 && j < N; i--, j++) {
            if (F_[i][j] == 0) {
                count++;
            } else {
                char countString[N * N];
                itoa(count, countString, 10);
                string strTemp = "/";
                strTemp = countString + strTemp;
                //cout<<"--"<<strTemp<<"--"<<endl;
                char SSSS_String[N * N];
                itoa(SSSS[i][j], SSSS_String, 10);
                strTemp = strTemp + SSSS_String;
                //cout<<"**"<<strTemp<<"**"<<endl;

                //中间符号
                ac_EntropyCoding_MiddleSymbol[index].R_S = strTemp;
                ac_EntropyCoding_MiddleSymbol[index].temp = F_[i][j];
                index++;
                count = 0;//置为0 ，计算下个不为0的数前面0的个数
            }
        }
        if (i < 0 && j >= N) {//当出现正中间往上时，挪回正规
            j--;
            i = i + 2;
        } else if (i < 0) {//当出现往上突出时，挪回正规
            i++;
        } else if (j >= N) {//当出现往右突出时，挪回正规
            j--;
            i = i + 2;
        }
    }

    //剩下半个周期的编码
    //向左下方向
    for (; i < N && j >= 0; i++, j--) {
        if (F_[i][j] == 0) {
            count++;
        } else {
            char countString[N * N];
            itoa(count, countString, 10);
            string strTemp = "/";
            strTemp = countString + strTemp;
            //cout<<"--"<<strTemp<<"--"<<endl;
            char SSSS_String[N * N];
            itoa(SSSS[i][j], SSSS_String, 10);
            strTemp = strTemp + SSSS_String;
            //cout<<"**"<<strTemp<<"**"<<endl;

            //中间符号
            ac_EntropyCoding_MiddleSymbol[index].R_S = strTemp;
            ac_EntropyCoding_MiddleSymbol[index].temp = F_[i][j];
            index++;
            count = 0;//置为0 ，计算下个不为0的数前面0的个数
        }
    }
    if (i >= N) {//当出现往下突出时，挪回正规
        i--;
        j = j + 2;
    }
    if (F_[i][j] == 0) {//最后一个点
        count++;
        ac_EntropyCoding_MiddleSymbol[index].R_S = "0/0(EOB)";
        ac_EntropyCoding_MiddleSymbol[index].temp = INT_MAX;
        index++;
    } else {
        char countString[N * N];
        itoa(count, countString, 10);
        string strTemp = "/";
        strTemp = countString + strTemp;
        //cout<<"--"<<strTemp<<"--"<<endl;
        char SSSS_String[N * N];
        itoa(SSSS[i][j], SSSS_String, 10);
        strTemp = strTemp + SSSS_String;
        //cout<<"**"<<strTemp<<"**"<<endl;

        //中间符号
        ac_EntropyCoding_MiddleSymbol[index].R_S = strTemp + "(EOB)";
        ac_EntropyCoding_MiddleSymbol[index].temp = F_[i][j];
        index++;
    }

    /*测试*/
//	for(int k=0;k<index;k++){
//		cout<<ac_EntropyCoding_MiddleSymbol[k].R_S<<"\t"<<ac_EntropyCoding_MiddleSymbol[k].temp<<endl;
//	}


    //对中间符号进行符号编码
    //对R/S通过查亮度AC码表进行熵编码
    for (int u = 0; u < index; u++) {
        for (int v = 0; v < stringMapList.partNum; v++) {
            if (ac_EntropyCoding_MiddleSymbol[u].R_S == stringMapList.stringMap[v].key) {
                ac_EntropyCodingStr[u].strTemp1 = stringMapList.stringMap[v].value;
            }
        }
        //对 temp进行转换成补码
        //先将 temp转换成二进制串
        if (ac_EntropyCoding_MiddleSymbol[u].R_S != "0/0(EOB)") {
            ac_EntropyCodingStr[u].strTemp = TenToTwo(abs(ac_EntropyCoding_MiddleSymbol[u].temp));
            //转换成补码
            if (ac_EntropyCoding_MiddleSymbol[u].temp < 0) {
                ac_EntropyCodingStr[u].strTemp = ConvertToComplement(ac_EntropyCodingStr[u].strTemp);
            }

            /*测试*/
//			cout<<"**********"<<ac_EntropyCodingStr[u].strTemp<<endl;
        } else {
            ac_EntropyCodingStr[u].strTemp = "" + '\0';

            /*测试*/
//			cout<<"**********+"<<ac_EntropyCodingStr[u].strTemp<<endl;
        }
    }

    /*测试*/
//	for(int k=0;k<index;k++){
//		cout<<ac_EntropyCodingStr[k].strTemp1<<" "<<ac_EntropyCodingStr[k].strTemp<<endl;
//	}
    return true;
}

int main() {
    cout << "压缩编码过程：" << endl;
    /*压缩编码*/
    const double PI = acos(-1);
//	double f[N][N]={139,144,149,153,155,155,155,155,
//					144,151,153,156,159,156,156,156,
//					150,155,160,163,158,156,156,156,
//					159,161,162,160,160,159,159,159,
//					159,160,161,162,162,155,155,155,
//					161,161,161,161,160,157,157,157,
//					162,162,161,163,162,157,157,157,
//					162,162,161,161,163,158,158,158};
    double f[N][N];
    double ff[N][N], F[N][N];

    /*输入图像的一个分量样本*/
    for (auto &i: f) {
        for (double &j: i) {
            cin >> j;
        }
    }

    cout << "源图像的一个分量样本：" << endl;
    /*输出—源图像的一个分量样本*/
    for (auto &i: f) {
        for (double j: i) {
            cout << j << "\t";
        }
        cout << endl;
    }

    //图像的一个分量样本-128后
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ff[i][j] = f[i][j] - 128;
        }
    }

    cout << "源图像的一个分量样本-128后：" << endl;
    /*输出—图像的一个分量样本-128后*/
    for (auto &i: ff) {
        for (double j: i) {
            cout << j << "\t";
        }
        cout << endl;
    }

    //由公式计算DCT变化后的系数矩阵
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            double temp = 0.0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    temp = temp +
                           ff[i][j] * cos((2 * i + 1) * u * PI * 1.0 / 16) * cos((2 * j + 1) * v * PI * 1.0 / 16);
                }
            }
            F[u][v] = 1.0 / 4 * (u == 0 ? 1.0 / sqrt(2) : 1) * (v == 0 ? 1.0 / sqrt(2) : 1) * temp;
        }
    }

    /*输出—DCT变化后的系数矩阵*/
    //DCT变化后的系数矩阵
    cout << "DCT变化后的系数矩阵:" << endl;
    for (auto &u: F) {
        for (double v: u) {
            printf("%.1f\t", v);
            //cout<<F[u][v]<<" ";
        }
        cout << endl;
    }

    //利用公式将DCT变化后的系数矩阵转换为规格化量化系数矩阵
    int F_[N][N];//规格化量化系数矩阵
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {//二维数组Q 为亮度量化值表
            F_[i][j] = (int) ((F[i][j] / brightnessQuantizedValueTable.Q[i][j]) > 0.0) ? floor(
                    (F[i][j] / brightnessQuantizedValueTable.Q[i][j]) + 0.5) : ceil(
                    (F[i][j] / brightnessQuantizedValueTable.Q[i][j]) - 0.5);//进行量化，然后进行四舍五入
        }
    }

    /*输出—规格化量化系数矩阵*/
    //规格化量化系数矩阵
    cout << "规格化量化系数:" << endl;
    for (auto &u: F_) {
        for (int v: u) {
            cout << v << "\t";
        }
        cout << endl;
    }

    //对DC系数生成中间符号(temp1,temp)
    int temp = F_[0][0];
    int temp1;
    EntropyCoding dc_EntropyCodingStr = DC_EntropyCoding(temp, temp1);

    cout << "中间符号：" << endl;
    /*输出—DC系数中间符号*/
    cout << temp1 << "\t" << temp << endl;


    int index = 0; //AC系数生成中间符号的个数
    //对AC系数生成中间符号
    AC_EntropyCoding(F_, index);

    /*输出—AC系数中间符号*/
    for (int k = 0; k < index; k++) {
        cout << ac_EntropyCoding_MiddleSymbol[k].R_S << "\t";
        if (ac_EntropyCoding_MiddleSymbol[k].R_S != "0/0(EOB)") {
            cout << ac_EntropyCoding_MiddleSymbol[k].temp;
        }
        cout << endl;
    }

    cout << "熵编码输出：" << endl;
    /*输出—DC系数熵编码输出*/
    cout << dc_EntropyCodingStr.strTemp1 << "\t" << dc_EntropyCodingStr.strTemp << endl;

    /*输出—AC系数熵编码输出*/
    for (int k = 0; k < index; k++) {
        cout << ac_EntropyCodingStr[k].strTemp1 << "\t" << ac_EntropyCodingStr[k].strTemp << endl;
    }


    cout << "----------------------------------------------------------------------" << endl << endl;
    cout << "解码过程：" << endl;
    //下面的解码过程只用到了压缩过程传输过来的熵编码和熵编码中AC系数的个数index(也可以通过一个循环来计算出这个index)

    cout << "待解码的熵编码：" << endl;
    /*输出—DC系数熵编码输出*/
    cout << dc_EntropyCodingStr.strTemp1 << "\t" << dc_EntropyCodingStr.strTemp << endl;

    /*输出—AC系数熵编码输出*/
    for (int k = 0; k < index; k++) {
        cout << ac_EntropyCodingStr[k].strTemp1 << "\t" << ac_EntropyCodingStr[k].strTemp << endl;
    }

    /*解码*/
    //将DC系数熵编码的编码转换为中间符号
    //对strTemp1进行反向查找亮度DC差值码表得到temp1
    int Itemp1;
    for (int i = 0; i < 11; i++) {
        if (dc_EntropyCodingStr.strTemp1 == brightnessDC_DifferenceTableList.brightnessDC_DifferenceTable[i]) {
            Itemp1 = i;
        }
    }
    //对strTemp进行反向补码得到temp，可通过查找规律发现若是负数转换为补码后首个数字必为0，正数必不为0
    int Itemp;
    if (dc_EntropyCodingStr.strTemp[0] == '0') {//为负数，先取反
        string tempStr = ConvertToComplement(dc_EntropyCodingStr.strTemp);
        //转换为10进制
        Itemp = TwoToTen(tempStr);
        //加负号
        Itemp = -Itemp;
    } else {//为正数，直接转换为10进制即可
        Itemp = TwoToTen(dc_EntropyCodingStr.strTemp);
    }

    cout << "中间符号：" << endl;
    /*输出—DC中间符号*/
    cout << Itemp1 << "\t" << Itemp << endl;


    //将AC系数熵编码的编码转换为中间符号
    AC_EntropyCoding_MiddleSymbol Iac_EntropyCoding_MiddleSymbol[N * N];
    //遍历所有的AC系数熵编码的编码对strTemp1进行反向查找亮度AC码表得到R_S
    for (int i = 0; i < index; i++) {
        for (int u = 0; u < stringMapList.partNum; u++) {
            if (ac_EntropyCodingStr[i].strTemp1 == stringMapList.stringMap[u].value) {
                Iac_EntropyCoding_MiddleSymbol[i].R_S = stringMapList.stringMap[u].key;
            }
        }
        //对strTemp进行反向补码得到temp，可通过查找规律发现若是负数转换为补码后首个数字必为0，正数必不为0
        if (ac_EntropyCodingStr[i].strTemp[0] == '0') {//为负数，先取反
            string tempStr = ConvertToComplement(ac_EntropyCodingStr[i].strTemp);
            //转换为10进制
            Iac_EntropyCoding_MiddleSymbol[i].temp = TwoToTen(tempStr);
            //加负号
            Iac_EntropyCoding_MiddleSymbol[i].temp = -Iac_EntropyCoding_MiddleSymbol[i].temp;
        } else {//为正数，直接转换为10进制即可
            Iac_EntropyCoding_MiddleSymbol[i].temp = TwoToTen(ac_EntropyCodingStr[i].strTemp);
        }
    }

    /*输出—AC中间符号*/
    for (int i = 0; i < index; i++) {
        cout << Iac_EntropyCoding_MiddleSymbol[i].R_S << "\t";
        if (Iac_EntropyCoding_MiddleSymbol[i].R_S != "0/0(EOB)") {
            cout << Iac_EntropyCoding_MiddleSymbol[i].temp;
        }
        cout << endl;
    }

    //规格化量化系数
    int IF_[N][N];

    //初始化矩阵
    for (auto &u: IF_) {
        for (int &v: u) {
            v = 0;
        }
    }

    //DC系数
    //还原编码
    IF_[0][0] = Itemp;
    //AC系数
    //Z字形还原编码
    int count;//计算0的个数
    int a = 0, b = 1; //初始位置
    for (int h = 0; h < index; h++) {
        //将/前的字符串转换为整数
        count = 0;
        for (int w = 0; Iac_EntropyCoding_MiddleSymbol[h].R_S[w] != '/'; w++) {
            count = count * 10 + Iac_EntropyCoding_MiddleSymbol[h].R_S[w] - '0';
        }
        /*测试*/
//		cout<<"count:"<<count<<endl;

        while (Iac_EntropyCoding_MiddleSymbol[h].R_S != "0/0(EOB)") {
            //根据查找规律发现，当行+列为奇数时向左下方向，当行+列为偶数时为右上方向
            if ((a + b) % 2 == 0) {//偶数，向右上方向
                for (; count >= 0 && a >= 0 && b < N; a--, b++) {
                    if (count == 0) {//此时放temp
                        IF_[a][b] = Iac_EntropyCoding_MiddleSymbol[h].temp;
                        count--;
                        break;
                    } else {//此时放0
                        IF_[a][b] = 0;
                        count--;
                    }
                }
                if (count < 0) {//向右上移动
                    a--;
                    b++;
                }
                if (a < 0 && b >= N) {//当出现正中间往上时，挪回正规
                    b--;
                    a = a + 2;
                } else if (a < 0) {//当出现往上突出时，挪回正规
                    a++;
                } else if (b >= N) {//当出现往右突出时，挪回正规
                    b--;
                    a = a + 2;
                }
                if (count < 0) {//跳出到第一层循环
                    break;
                }
            } else {//奇数，向左下方向
                for (; count >= 0 && a < N && b >= 0; a++, b--) {
                    if (count == 0) {//此时放temp
                        IF_[a][b] = Iac_EntropyCoding_MiddleSymbol[h].temp;
                        count--;
                        break;
                    } else {//此时放0
                        IF_[a][b] = 0;
                        count--;
                    }
                }
                if (count < 0) {//向左下移动
                    a++;
                    b--;
                }
                if (a >= N && b < 0) {//当出现正中间往下时，挪回正规
                    a--;
                    b = b + 2;
                } else if (a >= N) {//当出现往下突出时，挪回正规
                    a--;
                    b = b + 2;
                } else if (b < 0) {//当出现往左突出时，挪回正规
                    b++;
                }
                if (count < 0) {//跳出到第一层循环
                    break;
                }
            }
        }
    }

    /*输出—规格化量化系数矩阵*/
    //规格化量化系数矩阵
    cout << "规格化量化系数:" << endl;
    for (auto &u: IF_) {
        for (int v: u) {
            cout << v << "\t";
        }
        cout << endl;
    }


    //利用公式将规格化量化系数矩阵转换为逆量化后的系数矩阵
    double IF[N][N];//逆量化后的系数矩阵
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            //二维数组Q 为亮度量化值表
            IF[i][j] = 1.0 * IF_[i][j] * brightnessQuantizedValueTable.Q[i][j];
        }
    }

    /*输出—逆量化后的系数矩阵*/
    cout << "逆量化后的系数矩阵:" << endl;
    for (auto &i: IF) {
        for (double j: i) {
            cout << j << "\t";
        }
        cout << endl;
    }

    //由公式计算IDCT变化后的系数矩阵
    double Iff[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int u = 0; u < N; u++) {
                for (int v = 0; v < N; v++) {
                    sum = sum + (u == 0 ? 1.0 / sqrt(2.0) : 1.0) * (v == 0 ? 1.0 / sqrt(2.0) : 1.0) * IF[u][v] *
                                cos((2 * i + 1) * u * PI * 1.0 / 16) * cos((2 * j + 1) * v * PI * 1.0 / 16);
                }
            }
            Iff[i][j] = 1.0 / 4 * sum;
        }
    }

    /*输出—IDCT变化后的系数矩阵*/
    cout << "IDCT变化后的系数矩阵:" << endl;
    for (auto &i: Iff) {
        for (double j: i) {
            //cout<<Iff[i][j]<<"\t";
            printf("%.0f\t", j);
        }
        cout << endl;
    }


    cout << "源图像的一个分量样本的重构图像：" << endl;
    /*IDCT变化后的系数矩阵+128后变成源图像的一个分量样本的重构图像*/
    double If[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            If[i][j] = Iff[i][j] + 128;
        }
    }

    /*输出—源图像的一个分量样本的重构图像*/
    for (auto &i: If) {
        for (double j: i) {
            //cout<<If[i][j]<<"\t";
            printf("%.0f\t", j);
        }
        cout << endl;
    }
    return 0;
}

#endif