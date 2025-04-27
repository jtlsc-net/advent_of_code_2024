#include <iostream>
#include <map>
#include <memory>

#include "problem.h"
#include "p1.h"
#include "p2.h"
#include "p3.h"
#include "p4.h"
#include "p5.h"
#include "p6.h"
#include "p7.h"
#include "p8.h"
#include "p9.h"
#include "p10.h"
#include "p11.h"


void solve_problem(Problem *problem, bool first) {
	std::string input;
	std::cout << "Test? y/n: ";
	std::cin >> input;
	if (input == "y" && first) {
		std::cout << problem->test_first() << std::endl;
	}
	else if (input == "y" && !first) {
		std::cout << problem->test_second() << std::endl;
	}
	else if (input == "n" && first) {
		std::cout << problem->solve_first() << std::endl;
	}
	else if (input == "n" && !first) {
		std::cout << problem->solve_second() << std::endl;
	}
}

bool query_first() {
	std::string input;
	std::cout << "First? y/n: ";
	std::cin >> input;
	if (input == "y") {
		return true;
	}
	else {
		return false;
	}
}

void gen_txt(Problem* ptr, std::string num) {
	ptr->path = num + ".txt";
	ptr->test_path = num + "_test.txt";
	ptr->test_second_path = num + "_second_test.txt";
}

bool validate_input(const std::string& input, const std::map<std::string, Problem* (*)()> m) {
	for (const auto& keyval : m) {
		if (input == keyval.first) return true;
	}
	return false;
}

int main() {
	std::string input;
	std::cout << "problem?: ";
	std::cin >> input;

	std::map<std::string, Problem* (*)()> p_map{
		{"1", []()->Problem* { return new P1(); }}	,
		{ "2", []()->Problem* { return new P2(); } },
		{ "3", []()->Problem* { return new P3(); } },
		{ "4", []()->Problem* { return new P4(); } },
		{ "5", []()->Problem* { return new P5(); } },
		{ "6", []()->Problem* { return new P6(); } },
		{ "7", []()->Problem* { return new P7(); } },
		{ "8", []()->Problem* { return new P8(); } },
		{ "9", []()->Problem* { return new P9(); } },
		{ "10", []()->Problem* { return new P10(); } },
		{ "11", []()->Problem* { return new P11(); } }
	};

	if (!validate_input(input, p_map)) {
		std::cout << "invalid input" << std::endl;
		return 1;
	}

	Problem* p_pointer = p_map[input]();
	gen_txt(p_pointer, input);
	if (p_pointer) {
		if (query_first()) {
			solve_problem(p_pointer, true);
		}
		else {
			solve_problem(p_pointer, false);
		}
	}
	else {
		std::cout << "invalid input" << std::endl;
	}
	delete p_pointer;
}