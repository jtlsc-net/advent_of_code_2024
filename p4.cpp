#include "p4.h"
#include "utility.h"

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool range_check(const vector<string>& data, int i, int j) {
	if (0 <= i && i < data.size()) {
		if (0 <= j && j < data.at(0).size()) {
			return true;
		}
	}
	return false;
}

bool range_check(const vector<string>& data, pair<int, int> in) {
	if (0 <= in.first && in.first < data.size()) {
		if (0 <= in.second && in.second < data.at(0).size()) {
			return true;
		}
	}
	return false;
}

pair<int, int> next_loc(pair<int, int> curr_loc, pair<int, int> prev_loc) {
	pair<int, int> out;
	if (prev_loc.first < curr_loc.first) out.first = curr_loc.first + 1;
	else if (prev_loc.first > curr_loc.first) out.first = curr_loc.first - 1;
	else out.first = curr_loc.first;

	if (prev_loc.second < curr_loc.second) out.second = curr_loc.second + 1;
	else if (prev_loc.second > curr_loc.second) out.second = curr_loc.second - 1;
	else out.second = curr_loc.second;

	return out;
}

int find_m(int i, int j, const vector<string>& data) {
	int count = 0;
	for (int ii = i - 1; ii < i + 2; ++ii) {
		for (int jj = j - 1; jj < j + 2; ++jj) {
			if (range_check(data, ii, jj)) {
				if (data[ii][jj] == 'M') {
					pair<int, int> a_test = next_loc(pair(ii, jj), pair(i, j));
					if (range_check(data, a_test)) {
						if (data[a_test.first][a_test.second] == 'A') {
							pair<int, int> s_test = next_loc(a_test, pair(ii, jj));
							if (range_check(data, s_test)) {
								if (data[s_test.first][s_test.second] == 'S') {
									count++;
								}
							}
						}
					}
				}
			}
		}
	}
	return count;
}

string P4::first_solver(string path) {
	int count = 0;
	vector<string> data = read_file(data_path / filesystem::path(path));
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.at(0).size(); j++) {
			// Find X
			if (data[i][j] == 'X') {
				// check each thing around X (BFS)
				count += find_m(i, j, data);
			}
		}
	}
	return to_string(count);
}

bool check_s_a(pair<pair<int, int>, pair<int, int>> in, const vector<string>& data) {
	unordered_set<char> a_s{ 'M', 'S' };
	//print("Checking " + to_string(in.first.first) + "," + to_string(in.first.second) + " : " + to_string(in.second.first) + "," + to_string(in.second.second));
	//print("Found " + string(1, data[in.first.first][in.first.second]) + " : " + string(1, data[in.second.first][in.second.second]));
	if (a_s.contains(data[in.first.first][in.first.second])
		&& a_s.contains(data[in.second.first][in.second.second])
		&& data[in.first.first][in.first.second] != data[in.second.first][in.second.second]) {
		return true;
	}
	return false;
}

bool xmas(int i, int j, const vector<string>& data) {
	pair<pair<int, int>, pair<int, int>> left_right, right_left;

	left_right.first = pair(i - 1, j - 1);
	left_right.second = pair(i + 1, j + 1);
	right_left.first = pair(i - 1, j + 1);
	right_left.second = pair(i + 1, j - 1);

	if (!range_check(data, left_right.first) || !range_check(data, left_right.second)) return false;
	if (!range_check(data, right_left.first) || !range_check(data, right_left.second)) return false;

	return check_s_a(left_right, data) && check_s_a(right_left, data);
}

string P4::second_solver(string path) {
	int count = 0;
	vector <string> data = read_file(data_path / filesystem::path(path));

	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.at(0).size(); j++) {
			if (data[i][j] == 'A') {
				// check around A
				if (xmas(i, j, data)) {
					count += 1;
				}
			}
		}
	}

	return to_string(count);
}

string P4::test_first() {
	return first_solver(test_path);
}

string P4::test_second() {
	return second_solver(test_path);
}

string P4::solve_first() {
	return first_solver(path);
}

string P4::solve_second() {
	return second_solver(path);
}