#include "p2.h"
#include "utility.h"

#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

vector<vector<int>> reader(const string& path) {
	vector<vector<int>> out;
	
	vector<string> data = read_file(data_path / filesystem::path(path));

	auto split_wrapper = [](string in) {
		return split_string_int(in, ' ');
		};
	transform(data.begin(), data.end(), back_inserter(out), split_wrapper);

	return out;
}

bool is_decreasing(const vector<int>& in) {
	bool prev_init = false;
	int prev = 0;
	for (const auto& v : in) {
		if (!prev_init) {
			prev_init = true;
		}
		else {
			if (prev <= v || prev - v > 3) {
				return false;
			}
		}
		prev = v;
	}
	return true;
}

bool is_increasing(const vector<int>& in) {
	bool prev_init = false;
	int prev = 0;
	for (const auto& v : in) {
		if (!prev_init) {
			prev_init = true;
		}
		else {
			if (prev >= v || v - prev > 3) {
				return false;
			}
		}
		prev = v;
	}
	return true;
}

bool check_safety(const vector<int>& in) {
	// didn't feel like doing it all at once
	return is_increasing(in) || is_decreasing(in);
}

string first_solver(const string& path) {
	vector<vector<int>> data = reader(path);

	auto is_safe = [](int acc, const vector<int>& in) {
		if (check_safety(in)) return acc + 1;
		else return acc;
		};
	
	return to_string(accumulate(data.begin(), data.end(), 0, is_safe));
}

bool giga_time_waste_fixer(const vector<int>& in) {
	vector<int> n = in;
	for (int i = 0; i < n.size(); ++i) {
		vector<int> temp = n;
		temp.erase(temp.begin() + i);
		if (is_decreasing(temp) || is_increasing(temp)) return true;
	}
	return false;
}

bool check_safety_2(const vector<int>& in) {
	bool dec = is_decreasing(in);
	bool inc = is_increasing(in);
	if (dec || inc) return true;
	return giga_time_waste_fixer(in);
}

string second_solver(const string& path) {
	vector<vector<int>> data = reader(path);

	auto is_safe = [](int acc, const vector<int>& in) {
		if (check_safety_2(in)) return acc + 1;
		else return acc;
		};
	
	return to_string(accumulate(data.begin(), data.end(), 0, is_safe));
}

string P2::test_first() {
	return first_solver(test_path);
}

string P2::test_second() {
	return second_solver(test_path);
}

string P2::solve_first() {
	return first_solver(path);
}

string P2::solve_second() {
	return second_solver(path);
}