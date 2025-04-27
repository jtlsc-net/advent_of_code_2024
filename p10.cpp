#include "p10.h"
#include "utility.h"

#include <algorithm>
#include <numeric>

using namespace std;

bool check_idx(const pair<int, int>& in, const vector<string>& data) {
	if (in.first < 0 || in.second < 0) return false;
	if (in.first >= data.size() || in.second > data[0].size()) return false;
	return true;
}

vector<pair<int, int>> find_trails(char curr, pair<int, int> loc, vector<pair<int, int>> found, const vector<string>& data) {
	vector<char> order = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int curr_idx = 0;
	for (int i = 0; i < order.size(); ++i) {
		if (curr == order[i]) {
			curr_idx = i;
			break;
		}
	}
	if (curr_idx == 9) {
		if (!generic_vector_contains(found, loc)) found.push_back(loc);
		return found;
	}

	int next_idx = curr_idx + 1;
	pair<int, int> left = pair(loc.first, loc.second - 1);
	pair<int, int> up = pair(loc.first - 1, loc.second);
	pair<int, int> right = pair(loc.first, loc.second + 1);
	pair<int, int> down = pair(loc.first + 1, loc.second);

	// sorry for the copying...
	if (check_idx(left, data) && data[left.first][left.second] == order[next_idx]) {
		vector<pair<int, int>> temp = find_trails(order[next_idx], left, found, data);
		if (found.size() < temp.size()) {
			for (size_t i = found.size(); i < temp.size(); ++i) {
				found.push_back(temp[i]);
			}
		}
	}
	if (check_idx(up, data) && data[up.first][up.second] == order[next_idx]) {
		vector<pair<int, int>> temp = find_trails(order[next_idx], up, found, data);
		if (found.size() < temp.size()) {
			for (size_t i = found.size(); i < temp.size(); ++i) {
				found.push_back(temp[i]);
			}
		}
	}
	if (check_idx(right, data) && data[right.first][right.second] == order[next_idx]) {
		vector<pair<int, int>> temp = find_trails(order[next_idx], right, found, data);
		if (found.size() < temp.size()) {
			for (size_t i = found.size(); i < temp.size(); ++i) {
				found.push_back(temp[i]);
			}
		}
	}
	if (check_idx(down, data) && data[down.first][down.second] == order[next_idx])
	{
		vector<pair<int, int>> temp = find_trails(order[next_idx], down, found, data);
		if (found.size() < temp.size()) {
			for (size_t i = found.size(); i < temp.size(); ++i) {
				found.push_back(temp[i]);
			}
		}
	}
	return found;
}

vector<pair<int, int>> find_starts(const vector<string>& data) {
	vector<pair<int, int>> out;
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[0].size(); ++j) {
			if (data[i][j] == '0') {
				out.push_back(pair(i, j));
			}
		}
	}
	return out;
}

string P10::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	vector<pair<int, int>> starts = find_starts(data);
	int sum = 0;
	for (const auto& start : starts) {
		vector<pair<int, int>> found;
		sum += static_cast<int>(find_trails('0', start, found, data).size());
	}
	return to_string(sum);
}

int find_trail_ratings(char curr, pair<int, int> loc, const vector<string>& data) {
	vector<char> order = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int curr_idx = 0;
	for (int i = 0; i < order.size(); ++i) {
		if (curr == order[i]) {
			curr_idx = i;
			break;
		}
	}

	if (curr_idx == 9) {
		return 1;
	}

	int next_idx = curr_idx + 1;
	pair<int, int> left = pair(loc.first, loc.second - 1);
	pair<int, int> up = pair(loc.first - 1, loc.second);
	pair<int, int> right = pair(loc.first, loc.second + 1);
	pair<int, int> down = pair(loc.first + 1, loc.second);
	
	int sum = 0;
	if (check_idx(left, data) && data[left.first][left.second] == order[next_idx]) {
		sum += find_trail_ratings(order[next_idx], left, data);
	}
	if (check_idx(up, data) && data[up.first][up.second] == order[next_idx]) {
		sum += find_trail_ratings(order[next_idx], up, data);
	}
	if (check_idx(right, data) && data[right.first][right.second] == order[next_idx]) {
		sum += find_trail_ratings(order[next_idx], right, data);
	}
	if (check_idx(down, data) && data[down.first][down.second] == order[next_idx])
	{
		sum += find_trail_ratings(order[next_idx], down, data);
	}
	return sum;
}

string P10::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	vector<pair<int, int>> starts = find_starts(data);
	int sum = 0;
	for (const auto& start : starts) {
		sum += find_trail_ratings('0', start, data);
	}
	return to_string(sum);
}

string P10::test_first() {
	return first_solver(test_path);
}

string P10::test_second() {
	return second_solver(test_path);
}

string P10::solve_first() {
	return first_solver(path);
}

string P10::solve_second() {
	return second_solver(path);
}