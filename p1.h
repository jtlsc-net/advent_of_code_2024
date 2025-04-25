#pragma once

#include "problem.h"

class P1 : public Problem {
public:
	~P1() {}
	std::string test_first() override;
	std::string test_second() override;
	std::string solve_first() override;
	std::string solve_second() override;
};