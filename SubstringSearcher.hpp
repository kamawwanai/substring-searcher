#pragma once

#include <iostream>
#include <string>
#include <fstream>


void read_file(const std::string& path_to_file, std::string& str);


class SubstringSearcher {
public:
    SubstringSearcher(const std::string& path_to_file, const std::string& path_to_sub_file) {
        read_file(path_to_file, m_full_str);
        read_file(path_to_sub_file, m_sub_str);
    }

    void print_full_str() const {
        std::cout << m_full_str << std::endl;
    }

    void print_sub_str() const {
        std::cout << m_sub_str << std::endl;
    }

    int64_t algorithm();

    [[nodiscard]] int get_count_of_opers() const { return m_count_of_opers; }

private:
    std::string m_full_str;
    std::string m_sub_str;

    int m_count_of_opers = 0;
};


void read_file(const std::string& path_to_file, std::string& str) {

    std::ifstream in;
    in.open(path_to_file);

    std::string temp_str;

    if (!in.is_open()) {
        std::cout << "incorrect file name" << std::endl;
    } else {

        while(getline(in, temp_str)) {
            str += temp_str;
        }

        in.close();
    }
}
