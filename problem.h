#pragma once

#include <string>

class Problem {
public:
	virtual ~Problem() {}

	virtual std::string test_first() = 0;
	virtual std::string test_second() = 0;

	virtual std::string solve_first() = 0;
	virtual std::string solve_second() = 0;

	std::string path = "";
	std::string test_path = "";
	std::string test_second_path = "";
};