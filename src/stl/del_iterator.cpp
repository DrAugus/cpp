//
// del_iterator.cpp
// Created by AUGUS on 2022/9/23.
// info
//

#include <iostream>
#include <vector>
#include <map>

enum class DelType {
    INDEX = 1,
    VALUE,
    RANGE,
};

struct DelItem {
    int index;
    int value;
    int index2;
    DelType type;
};

class DelIterator {
public:
    static void del_vec(std::vector<int> &v, DelItem del_item);

    template<class T1, class T2>
    void del_map(std::map<T1, T2> &m, T1 key) {
//        m.erase(m.find(key));
        m.erase(key);
    }
};

void DelIterator::del_vec(std::vector<int> &v, DelItem del_item) {
    switch (del_item.type) {
        case DelType::INDEX: {
            v.erase(std::begin(v) + del_item.index);
        }
            break;
        case DelType::VALUE: {
            for (auto ii = v.begin(); ii != v.end(); ++ii) {
                if (*ii == del_item.value) {
                    v.erase(ii);
                }
            }
        }
            break;
        case DelType::RANGE: {
            v.erase(std::begin(v) + del_item.index, std::begin(v) + del_item.index2);
        }
            break;
    }
}

void del_iterator() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    DelItem delItem{};
    delItem.index = 1;
    delItem.index2 = 3;
    delItem.value = 3;
    delItem.type = DelType::RANGE;

    DelIterator delIterator;
    delIterator.del_vec(vec, delItem);

    std::map<std::string, int> people{{"Fred",  45},
                                      {"Joan",  33},
                                      {"Linda", 33},
                                      {"Au",    33},
                                      {"Jill",  22}};

    std::string ss = "Fred";
    delIterator.del_map(people, ss);
    for (const auto &i: people) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    std::cout << "del_iterator: ";
    for (auto i: vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {

    del_iterator();

    std::cout << 25u - 50;

    return 1;
}