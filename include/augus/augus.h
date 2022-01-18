//
// Created by AUGUS on 2021/5/28.
//

#ifndef AUGUS_H
#define AUGUS_H


#include <vector>
#include <iostream>
#include <type_traits> // std::is_same_v
#include <algorithm>


namespace augus {

    void PrintTest() {}
    template<typename T, typename ...Args>
    void PrintTest(std::vector<T> info, Args ... args) {
        for (auto i: info) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        PrintTest(args...);
    }
    template<typename T, typename ...Args>
    void PrintTest(T info, Args ... args) {
        std::cout << info << " ";
        std::cout << std::endl;
        PrintTest(args...);
    }
    template<typename T>
    void PrintTest(std::vector<T> info) {
        for (auto i: info) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    template<typename T>
    void PrintTest(T info) {
        std::cout << info << " ";
        std::cout << std::endl;
    }


/// Evaluate Factorial
    template<typename T>
    long long GetFactorial(T n) {
        long long factorial = 1;
        for (long long i = 1; i <= n; ++i) {
            factorial *= i;
        }
        return factorial;
    }

    template<typename T>
    T GetFactorial(T num, bool Recursive) {
        if (num == 0) {
            return 1;
        } else {
            return num * GetFactorial(num - 1);
        }
    }

/// Calculate the number of combinations
    template<typename T>
    void ComputeAllChoices(std::vector<T> &data, T n, T outLen, T startIndex, T m, T *arr, T arrIndex) {
        if (m == 0) {
            for (T i = 0; i < outLen; i++) {
                std::cout << arr[i] << "\t";
            }
            std::cout << std::endl;

            return;
        }

        T endIndex = n - m;
        for (T i = startIndex; i <= endIndex; i++) {
            arr[arrIndex] = data[i];
            ComputeAllChoices(data, n, outLen, i + 1, m - 1, arr, arrIndex + 1);
        }
    }

    //命名规则 普通变量小写/下划线 类名大写所有首字母如TestName
    //类数据数据成员同普通变量如test_name但末尾要加_ 结构体数据成员同普通变量
    //https://google.github.io/styleguide/cppguide.html#Structs_vs._Classes
    //函数随意 按public首字母大写 private首词小写
    class AugusUtils {
    public:
        void TrimStr(std::string &s, char str);
    private:
        int test_name_;
    public:
        AugusUtils() = default;
        ~AugusUtils() = default;
    };


} //namespace augus

#endif //AUGUS_H
