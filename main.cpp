#include <iostream>
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

Problem* create_problem(const std::string& input) {
	auto gen_txt = [](Problem* ptr, std::string num) {
		ptr->path = num + ".txt";
		ptr->test_path = num + "_test.txt";
		ptr->test_second_path = num + "_second_test.txt";
		};

	if (input == "1") {
		P1* ptr = new P1();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "2") {
		P2* ptr = new P2();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "3") {
		P3* ptr = new P3();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "4") {
		P4* ptr = new P4();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "5") {
		P5* ptr = new P5();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "6") {
		P6* ptr = new P6();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "7") {
		P7* ptr = new P7();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "8") {
		P8* ptr = new P8();
		gen_txt(ptr, input);
		return ptr;
	}
	else if (input == "9") {
		P9* ptr = new P9();
		gen_txt(ptr, input);
		return ptr;
	}
	else {
		return nullptr;
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

int main() {
	std::string input;
	std::cout << "problem?: ";
	std::cin >> input;
	Problem* p_pointer = create_problem(input);
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