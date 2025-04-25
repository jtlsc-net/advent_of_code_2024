#include "p5.h"
#include "utility.h"

#include <algorithm>
#include <numeric>
#include <map>
#include <span>
#include <queue>

using namespace std;

void parse_rules(const string& in, map<int, vector<int>>& rules) {
	if (in.size() == 0) return;
	vector<string> pieces = split_string(in, '|');

	int key = stoi(jtrim(pieces.at(0)));
	int value = stoi(jtrim(pieces.at(1)));
	if (rules.contains(key)) {
		rules[key].push_back(value);
	}
	else {
		rules[key] = vector<int>{ value };
	}
}

bool check_values(const string& in, map<int, vector<int>>& rules) {
	if (in.size() == 0) return false;
	vector<string> updates = split_string(in, ',');
	for (int i = 0; i < updates.size(); i++) {
		string up = updates.at(i);
		int val = stoi(jtrim(up));
		if (rules.contains(val)) {
			for (int j = 0; j < updates.size(); j++) {
				if (vector_contains(rules[val], stoi(jtrim(updates[j])))) {
					if (j < i) return false;
				}
			}
		}
	}
	return true;
}

int find_middle(const string& in) {
	vector<string> updates = split_string(in, ',');
	// size should always be odd.
	int idx = int(updates.size() / 2);
	return stoi(jtrim(updates[idx]));
}

string P5::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	map<int, vector<int>> rules;
	int sum = 0;

	auto compose = [&rules, &sum](const string& in) {
		if (string_contains(in, '|')) {
			parse_rules(in, rules);
		}
		else {
			if (check_values(in, rules)) {
				sum += find_middle(in);
			}
		}
		};

	for_each(data.begin(), data.end(), compose);

	return to_string(sum);
}

string P5::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	map<int, vector<int>> rules;
	int sum = 0;

	auto fix_update = [&rules](const string& in) -> string {
		vector<int> updates = split_string_int(in, ',');
		sort(updates.begin(), updates.end(), [&rules](int a, int b) {
			if (vector_contains(rules[a], b)) {
				return true;
			}
			return false;
			});
		return join_vec(updates, ",");
		};

	auto compose = [&fix_update, &rules, &sum](const string& in) {
		if (in.size() == 0) {
			return;
		}
		else if (string_contains(in, '|')) {
			parse_rules(in, rules);
		}
		else {
			if (!check_values(in, rules)) {
				sum += find_middle(fix_update(in));
			}
		}
		};
	for_each(data.begin(), data.end(), compose);

	return to_string(sum);
}

string P5::test_first() {
	return first_solver(test_path);
}

string P5::test_second() {
	return second_solver(test_path);
}

string P5::solve_first() {
	return first_solver(path);
}

string P5::solve_second() {
	return second_solver(path);
}