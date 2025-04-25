#include "p8.h"
#include "utility.h"

#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>

using namespace std;

map<char, vector<pair<int, int>>> find_like_points(const vector<string>& data) {
	map<char, vector<pair<int, int>>> out;
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] != '.') {
				out[data[i][j]].push_back(pair<int, int>(j, i));
			}
		}
	}
	return out;
}

bool check_bounds(const pair<int, int>& in, const vector<string>& data) {
	///print_pair(in);
	if (in.first >= 0 && in.first < data[0].size()) {
		if (in.second >= 0 && in.second < data.size()) {
			return true;
		}
	}
	return false;
}

// This whole thing assumes that the form is x,y where x is the col and y is the row
vector<pair<int, int>> calculate_antinode_pos(pair<int, int> first, pair<int, int> second) {
	//print("=====================");
	int x_dist = abs(first.first - second.first);
	int y_dist = abs(first.second - second.second);
	vector<pair<int, int>> out;
	if (first.first > second.first && first.second > second.second) {
		out.push_back(pair<int, int>(first.first + x_dist, first.second + y_dist));
		out.push_back(pair<int, int>(second.first - x_dist, second.second - y_dist));
	}
	else if (first.first < second.first && first.second > second.second) {
		out.push_back(pair<int, int>(first.first - x_dist, first.second + y_dist));
		out.push_back(pair<int, int>(second.first + x_dist, second.second - y_dist));
	}
	else if (first.first > second.first && first.second < second.second) {
		out.push_back(pair<int, int>(first.first + x_dist, first.second - y_dist));
		out.push_back(pair<int, int>(second.first - x_dist, second.second + y_dist));
	}
	else if (first.first < second.first && first.second < second.second) {
		out.push_back(pair<int, int>(first.first - x_dist, first.second - y_dist));
		out.push_back(pair<int, int>(second.first + x_dist, second.second + y_dist));
	}
	//print_pair(first);
	//print_pair(second);
	//print("---------");
	//for_each(begin(out), end(out), [](pair<int, int> in) {
	//	print_pair(in);
	//	});
	return out;
}

string P8::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	//print(to_string(data[0].size()) + " : " + to_string(data.size()));
	// Find all like points
	// For each point type, find all antinodes
	map<char, vector<pair<int, int>>> like_points = find_like_points(data);
	int sum = 0;
	for_each(begin(like_points), end(like_points), [&like_points, &data, &sum](auto in) {
		vector<pair<int, int>> points = like_points[in.first];
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 1; j < points.size(); ++j) {
				if (i == j) continue;
				vector<pair<int, int>> possible_antinodes = calculate_antinode_pos(points[i], points[j]);
				for (auto p : possible_antinodes) {
					if (check_bounds(p, data)) {
						if (data[p.second][p.first] != '#') {
							data[p.second][p.first] = '#';
							++sum;
						}
					}
				}
			}
		}
		});

	for (auto n : data) {
		print(n);
	}
	return to_string(sum);
}

// Also expects x,y where x is column and y is row.
vector<pair<int, int>> find_line_from_two_points_bounds_checked(pair<int, int> in0, pair<int, int> in1, size_t w, size_t h) {
	vector<pair<int, int>> out;
	// y = mx + b
	auto eq = [](int x, double m, double b) -> double { return m * x + b; };

	auto is_whole = [](double in, double tolerance) -> bool {
		double iptr;
		//print("---------------");
		//print(to_string(in));
		//print(to_string(abs(modf(in, &iptr))) + "," + to_string(1 - abs(modf(in, &iptr))));
		//cout << (abs(modf(in, &iptr)) < tolerance) << "," << (1 - abs(modf(in, &iptr)) < tolerance) << endl;;
		if (abs(modf(in, &iptr)) < tolerance || 1 - abs(modf(in, &iptr)) < tolerance) return true;
		return false;
		};

	auto bound_check = [&w, &h](pair<int, int> in) -> bool {
		if (in.first < 0 || in.second < 0) return false;
		if (in.first >= w || in.second >= h) return false;
		return true;
		};

	auto find_m = [&in0, &in1]() -> double { return static_cast<double>(in1.second - in0.second) / static_cast<double>(in1.first - in0.first); };

	auto find_b = [&in0](double m) -> double { return static_cast<double>(in0.second) - (m * static_cast<double>(in0.first)); };

	double m = find_m();
	double b = find_b(m);
	
	for (int x = 0; x < w; ++x) {
		double y = eq(x, m, b);
		if (is_whole(y, 0.000000001)) {
			if (bound_check(pair<int, int>(x, round(y)))) {
				//print(to_string(x) + "," + to_string(y));
				out.push_back(pair<int, int>(x, round(y)));
			}
		}
	}

	return out;
}

string P8::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	map<char, vector<pair<int, int>>> like_points = find_like_points(data);
	int sum = 0;
	for_each(begin(like_points), end(like_points), [&like_points, &data, &sum](auto in) {
		vector<pair<int, int>> points = like_points[in.first];
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 1; j < points.size(); ++j) {
				if (i == j) continue;
				vector<pair<int,int>> line_points = find_line_from_two_points_bounds_checked(points[i], points[j], data[0].size(), data.size());
				for (auto p : line_points) {
					if (data[p.second][p.first] != '#') {
						data[p.second][p.first] = '#';
						++sum;
					}
				}
			}
		}
		});
	for (auto n : data) {
		print(n);
	}
	return to_string(sum);
}

string P8::test_first() {
	return first_solver(test_path);
}

string P8::test_second() {
	return second_solver(test_path);
}

string P8::solve_first() {
	return first_solver(path);
}

string P8::solve_second() {
	return second_solver(path);
}