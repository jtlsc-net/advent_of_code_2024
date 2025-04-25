#include "p7.h"
#include "utility.h"

#include <algorithm>
#include <numeric>

using namespace std;

bool calculate(vector<long long> in, long long target) {
	if (in.size() == 2) {
		if (in[0] + in[1] == target) return true;
		if (in[0] * in[1] == target) return true;
		return false;
	}

	vector<long long> sum_copy = in;
	sum_copy[1] = sum_copy[0] + sum_copy[1];
	sum_copy.erase(begin(sum_copy));
	
	vector<long long> mult_c = in;
	mult_c[1] = mult_c[0] * mult_c[1];
	mult_c.erase(begin(mult_c));

	return calculate(sum_copy, target) || calculate(mult_c, target);
}

string P7::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	long long sum = 0;
	for (auto line : data) {
		vector<string> pieces = split_string(line, ':');
		long long target = stoll(jtrim(pieces[0]));
		vector<long long> dat;
		for (auto pie : split_string(jtrim(pieces[1]), ' ')) {
			dat.push_back(stoll(pie));
		}
		if (calculate(dat, target)) {
			sum += target;
		}
	}
	return to_string(sum);
}

long long or_or(long long left, long long right) {
	return stoll(to_string(left) + to_string(right));
}

bool calculate_two(vector<long long> in, long long target) {
	if (in.size() == 2) {
		if (in[0] + in[1] == target) return true;
		if (in[0] * in[1] == target) return true;
		if (or_or(in[0], in[1]) == target) return true;
		return false;
	}

	vector<long long> sum_copy = in;
	sum_copy[1] = sum_copy[0] + sum_copy[1];
	sum_copy.erase(begin(sum_copy));

	vector<long long> mult_c = in;
	mult_c[1] = mult_c[0] * mult_c[1];
	mult_c.erase(begin(mult_c));

	vector<long long> or_c = in;
	or_c[1] = or_or(or_c[0], or_c[1]);
	or_c.erase(begin(or_c));

	return calculate_two(sum_copy, target) || calculate_two(mult_c, target) || calculate_two(or_c, target);
}

string P7::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	long long sum = 0;
	for (auto line : data) {
		vector<string> pieces = split_string(line, ':');
		long long target = stoll(jtrim(pieces[0]));
		vector<long long> dat;
		for (auto pie : split_string(jtrim(pieces[1]), ' ')) {
			dat.push_back(stoll(pie));
		}
		if (calculate_two(dat, target)) {
			sum += target;
		}
	}
	return to_string(sum);
}

string P7::test_first() {
	return first_solver(test_path);
}

string P7::test_second() {
	return second_solver(test_path);
}

string P7::solve_first() {
	return first_solver(path);
}

string P7::solve_second() {
	return second_solver(path);
}