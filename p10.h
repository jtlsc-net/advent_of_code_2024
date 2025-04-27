#pragma once
#include "problem.h"

class P10 : public Problem {
private:
	std::string first_solver(std::string path);
	std::string second_solver(std::string path);
public:
	~P10() {}
	std::string test_first() override;
	std::string test_second() override;
	std::string solve_first() override;
	std::string solve_second() override;
};