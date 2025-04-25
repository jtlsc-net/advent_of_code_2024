#pragma once

#include "problem.h"

class P2 : public Problem {
public:
	~P2() {}
	std::string test_first() override;
	std::string test_second() override;
	std::string solve_first() override;
	std::string solve_second() override;
};