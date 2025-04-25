#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

static const std::filesystem::path data_path = "C:\\Users\\josh\\dev\\aoc_2024\\data";

std::vector<std::string> read_file(std::filesystem::path input_file);

std::vector<std::string> split_string(const std::string& input, char delim);

std::vector<std::string> split_string_delim_string(const std::string& input, const std::string& delim);

std::vector<int> split_string_int(const std::string& input, char delim);

std::string join_vec(const std::vector<std::string>& in, std::string delim);

std::string join_vec(const std::vector<int>& in, const std::string& delim);

bool contains(const std::string& input, const std::string& delim);

bool string_contains(const std::string& input, char delim);

bool vector_contains(const std::vector<int>& in_vec, int delim);

template <typename T>
bool generic_vector_contains(const std::vector<T>& in_vec, T delim) {
    for (const auto& in : in_vec) {
        if (in == delim) return true;
    }
    return false;
}

void print(const std::string& input);

template<typename T>
void vector_print(const std::vector<T> in) {
    for (const auto& x : in) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
}

template<typename T>
inline void print_pair(const std::pair<T, T>& in) {
    std::cout << in.first << "," << in.second << std::endl;
}


// trim from start (in place)
inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

std::string jtrim(std::string s);