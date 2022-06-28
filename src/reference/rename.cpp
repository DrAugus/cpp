//
// rename.cpp
// Created by AUGUS on 2022/6/28.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    bool ok{std::ofstream("from.txt").put('o')}; // create and write to file
    if (!ok) {
        std::perror("Error creating from.txt");
        return 1;
    }

    if (std::rename("from.txt", "to.txt")) {
        std::perror("Error renaming");
        return 1;
    }

    std::cout << std::ifstream("to.txt").rdbuf() << '\n'; // print file

    //remove
    if (std::remove("from.txt")) {
        std::perror("Error remove from.txt");
    }
    if (std::remove("to.txt")) {
        std::perror("Error remove to.txt");
    }

    std::cout << "================\n";

    fs::path p = fs::current_path() / "sandbox";
    fs::create_directories(p / "from");
    std::ofstream(p / "from/file1.txt").put('a');
    fs::create_directory(p / "to");

//    fs::rename(p/"from/file1.txt", p/"to/"); // error: to is a directory
    fs::rename(p / "from/file1.txt", p / "to/file2.txt"); // OK
//    fs::rename(p/"from", p/"to"); // error: to is not empty
    fs::rename(p / "from", p / "to/subdir"); // OK

//    fs::remove_all(p);

}
