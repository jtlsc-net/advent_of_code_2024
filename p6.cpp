#include "p6.h"
#include "utility.h"

#include <algorithm>
#include <numeric>
#include <map>

#include <fstream>
#include <iterator>
#include <filesystem>

using namespace std;

pair<int, int> find_start(const vector<string>& data) {
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == '^') {
				return pair<int, int>(i, j);
			}
		}
	}
	return pair<int, int>(-1, -1);
}

enum dir {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
using direction = struct a{
	bool invalid{ false };
	dir lit{ UP };
	pair<int, int> val{ -1,0 };
	void update_val(dir in) {
		switch (in) {
		case UP:
			val.first = -1;
			val.second = 0;
			break;
		case DOWN:
			val.first = 1;
			val.second = 0;
			break;
		case LEFT:
			val.first = 0;
			val.second = -1;
			break;
		case RIGHT:
			val.first = 0;
			val.second = 1;
			break;
		}
	}
	void next_val() {
		switch (lit) {
		case UP:
			lit = RIGHT;
			val.first = 0;
			val.second = 1;
			break;
		case DOWN:
			lit = LEFT;
			val.first = 0;
			val.second = -1;
			break;
		case LEFT:
			lit = UP;
			val.first = -1;
			val.second = 0;
			break;
		case RIGHT:
			lit = DOWN;
			val.first = 1;
			val.second = 0;
			break;
		}
	}
	void reset() {
		invalid = false;
		lit = UP;
		val = { -1, 0 };
	}
};

bool operator==(const a& lhs, const a& rhs) {
	return lhs.invalid == rhs.invalid &&
		   lhs.lit     == rhs.lit     &&
		   lhs.val     == rhs.val;
}

void take_next_step(pair<int, int>& current_pos, const direction& move_dir) {
	if (move_dir.invalid) return;  // null case
	current_pos.first += move_dir.val.first;
	current_pos.second += move_dir.val.second;
}

bool find_next_step(direction& curr_dir, const pair<int, int>& current_pos, const vector<string>& data) {
	int next_i = current_pos.first + curr_dir.val.first;
	int next_j = current_pos.second + curr_dir.val.second;
	if (next_i < 0 || next_i >= data.size() || next_j < 0 || next_j >= data.at(0).size()) {
		curr_dir.invalid = true;
		return false;
	}
	else {
		if (data[next_i][next_j] == '#') {
			curr_dir.next_val();
			return false;
		}
		return true;
	}
}


string P6::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	// 1. find ^
	// 2. trace path
	// 3. return size of path
	int sum = 1;  // We've already automatically visited a position
	pair<int, int> position = find_start(data);
	direction dir;
	while (true) {
		data[position.first][position.second] = 'X';
		find_next_step(dir, position, data);
		take_next_step(position, dir);
		if (dir.invalid) return to_string(sum);
		if (data[position.first][position.second] != 'X') ++sum;
	}
}

void print_data(const vector<string>& data) {
	for_each(data.begin(), data.end(), [](const string& in) {
		print(in);
		});
}

string P6::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	auto find = [&data]() -> pair<int, int> {
		for (int i = 0; i < data.size(); i++) {
			for (int j = 0; j < data[i].size(); j++) {
				if (data[i][j] == '^') return pair(i, j);
			}
		}
		return pair(-1, -1);
		};
	
	pair<int, int> start_position = find();
	int total_sum = 0;
	vector<pair<int, int>> pos_list;
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.size(); j++) {
			print(to_string(i) + "," + to_string(j));
			vector<string> temp_data = data;
			temp_data[i][j] = '#';

			int sum = 1;  // We've already automatically visited a position
			pair<int, int> position = start_position;
			direction dir;
			while (true) {
				//data[position.first][position.second] = 'X';
				bool res = find_next_step(dir, position, temp_data);
				while (!dir.invalid && !res) {
					res = find_next_step(dir, position, temp_data);
				}
				take_next_step(position, dir);
				if (dir.invalid) {
					print("end");
					break;
				}
				++sum;
				if (sum > 100000) {
					total_sum += 1;
					print("found");
					pos_list.push_back(position);
					break;
				}
			}
		}
	}
	sort(pos_list.begin(), pos_list.end());
	ofstream o_f("./test.txt");
	ostream_iterator<string> o_it(o_f, "\n");
	transform(pos_list.begin(), pos_list.end(), o_it, [](const pair<int, int>& in) {
		return to_string(in.first) + "," + to_string(in.second);
		});
	return to_string(total_sum);
}

string P6::test_first() {
	return first_solver(test_path);
}

string P6::test_second() {
	return second_solver(test_path);
}

string P6::solve_first() {
	return first_solver(path);
}

string P6::solve_second() {
	return second_solver(path);
}