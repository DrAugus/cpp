//
// Created by AUGUS on 2022/8/18.
//


#include <numeric>
#include <iostream>
#include <string>

static int cur_id_pro = 0, cur_id_stu = 0;

class Person {
public:
    std::string name;
    int age{};

    virtual void getdata() = 0;

    virtual void putdata() = 0;

public:
    Person() = default;

    ~Person() = default;
};

class Professor : public Person {
private:
    int publications{};
public:
    void getdata() override {
        std::cin >> name >> age >> publications;
    }

    void putdata() override {
        ++cur_id_pro;
        std::cout << name << " " << age << " " << publications << " " << cur_id_pro << "\n";
    }

public:
    Professor() = default;

    ~Professor() = default;
};

class Student : public Person {
private:
    int marks[6]{};
public:
    void getdata() override {
        std::cin >> name >> age;
        int i = 6;
        while (i--) {
            std::cin >> marks[i];
        }
    }

    void putdata() override {
        ++cur_id_stu;
        std::cout << name << " " << age << " " << std::accumulate(marks, marks + 6, 0) << " " << cur_id_stu << "\n";
    }

public:
    Student() = default;

    ~Student() = default;
};


int main() {
    int n, val;
    std::cin >> n; //The number of objects that is going to be created.
    Person *per[n];

    for (int i = 0; i < n; i++) {
        std::cin >> val;
        if (val == 1) {
            // If val is 1 current object is of type Professor
            per[i] = new Professor;
        } else per[i] = new Student; // Else the current object is of type Student
        per[i]->getdata(); // Get the data from the user.
    }

    for (int i = 0; i < n; i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;
}

/*
4
1
Walter 56 99
2
Jesse 18 50 48 97 76 34 98
2
Pinkman 22 10 12 0 18 45 50
1
White 58 87
 */