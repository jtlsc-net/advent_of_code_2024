#include "p11.h"
#include "utility.h"

#include <algorithm>
#include <numeric>
#include <stack>
#include <unordered_map>
#include <map>

using namespace std;

//unordered_map<int, int> zero_map{
//	{1, 1},
//	{2, 1},
//	{3, 2},
//	{4, 4},
//	{5, 4},
//	{6, 7},
//	{7, 14},
//	{8, 16},
//	{9, 20},
//	{10, 39},
//	{11, 62},
//	{12, 81},
//	{13, 110},
//	{14, 200},
//	{15, 328},
//	{16, 418},
//	{17, 667},
//	{18, 1059},
//	{19, 1546},
//	{20, 2377},
//	{21, 3572},
//	{22, 5602},
//	{23, 8268},
//	{24, 12343},
//
//}

//unordered_map<int, int> zero_map;
map<int, long long> zero_map;
map<int, long long> one_map;
map<int, long long> two_map;
map<int, long long> three_map;
map<int, long long> four_map;
map<int, long long> five_map;
map<int, long long> six_map;
map<int, long long> seven_map;
map<int, long long> eight_map;
map<int, long long> nine_map;

vector<string> blink(const vector<string>& data) {
	vector<string> out = {};
	for (int i = 0; i < data.size(); ++i) {
		if (data[i] == "0") out.push_back("1");
		else if (data[i].size() % 2 == 0) {
			string first = "";
			string second;
			bool leading = true;
			for (int j = 0; j < data[i].size() / 2; ++j) {
				first += data[i][j];
			}
			for (int j = static_cast<int>(data[i].size() / 2); j < data[i].size(); ++j) {
				if (data[i][j] != '0' || !leading) {
					leading = false;
					second += data[i][j];
				}
			}
			out.push_back(first);
			if (second.size() == 0) {
				out.push_back("0");
			}
			else {
				out.push_back(second);
			}
		}
		else {
			long long temp = stoll(data[i]);
			temp = temp * 2024;
			out.push_back(to_string(temp));
		}
	}
	return out;
}

string P11::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	vector<string> split_data = split_string(data[0], ' ');
	for (int i = 0; i < 25; ++i) {
		split_data = blink(split_data);
		//vector_print(split_data);
	}

	return to_string(split_data.size());
}

bool is_even_digits(long long in) {
	if (in < 10) return false;
	int count = 0;
	while (in >= 10) {
		in = in / 10;
		count++;
	}
	count++;  // Get the last digit
	if (count % 2 == 0) return true;
	else return false;
}

int count_digits(long long in) {
	if (in < 10) return 1;
	int count = 0;
	while (in >= 10) {
		in = in / 10;
		count++;
	}
	count++;
	return count;
}

tuple<long long, long long> split_num(long long in) {
	int count = count_digits(in);
	long long left = in;
	for (int i = 0; i < (count / 2); i++) {
		left = left / 10;
	}
	long long inter = left;
	for (int i = 0; i < (count / 2); i++) {
		inter = inter * 10;
	}
	long long right = in - inter;
	return { left, right };
}

long long blink_two_stop(long long num, int level, int stop) {
	//if (level % 5 == 0) cout << level << endl;
	int zero_max = 64;
	int one_max = 50;
	int two_max = 49;
	int three_max = 50;
	int four_max = 50;
	int five_max = 50;
	int six_max = 50;
	int seven_max = 50;
	int eight_max = 50;
	int nine_max = 50;
	if (level == stop) {
		return 1;
	}
	if (num == 0) {
		if (stop - level <= zero_max) {
			return zero_map[stop - level];
		}
		return blink_two_stop(1, level + 1, stop);
	}
	else if (num == 1  && stop - level <= one_max) {
		return one_map[stop - level];
	}
	else if (num == 2 && stop - level <= two_max) {
		return two_map[stop - level];
	}
	else if (num == 3 && stop - level <= three_max) {
		return three_map[stop - level];
	}
	else if (num == 4 && stop - level <= four_max) {
		return four_map[stop - level];
	}
	else if (num == 5 && stop - level <= five_max) {
		return five_map[stop - level];
	}
	else if (num == 6 && stop - level <= six_max) {
		return six_map[stop - level];
	}
	else if (num == 7 && stop - level <= seven_max) {
		return seven_map[stop - level];
	}
	else if (num == 8 && stop - level <= eight_max) {
		return eight_map[stop - level];
	}
	else if (num == 9 && stop - level <= nine_max) {
		return nine_map[stop - level];
	}
	else if (is_even_digits(num)) {
		long long sum = 0;
		auto [l, r] = split_num(num);
		sum += blink_two_stop(l, level + 1, stop);
		sum += blink_two_stop(r, level + 1, stop);
		return sum;
	}
	else {
		return blink_two_stop(num * 2024, level + 1, stop);
	}
}

long long blink_two(long long num, int level) {
	int stop = 75;

	int zero_max = 64;
	int one_max = 50;
	int two_max = 49;
	int three_max = 50;
	int four_max = 50;
	int five_max = 50;
	int six_max = 50;
	int seven_max = 50;
	int eight_max = 50;
	int nine_max = 50;

	if (level == stop) {
		return 1;
	}
	if (num == 0) {
		if (stop - level <= zero_max) {
			return zero_map[stop - level];
		}
		else {
			return blink_two(1, level + 1);
		}
	}
	else if (num == 1 && stop - level <= one_max) {
		return one_map[stop - level];
	}
	else if (num == 2 && stop - level <= two_max) {
		return two_map[stop - level];
	}
	else if (num == 3 && stop - level <= three_max) {
		return three_map[stop - level];
	}
	else if (num == 4 && stop - level <= four_max) {
		return four_map[stop - level];
	}
	else if (num == 5 && stop - level <= five_max) {
		return five_map[stop - level];
	}
	else if (num == 6 && stop - level <= six_max) {
		return six_map[stop - level];
	}
	else if (num == 7 && stop - level <= seven_max) {
		return seven_map[stop - level];
	}
	else if (num == 8 && stop - level <= eight_max) {
		return eight_map[stop - level];
	}
	else if (num == 9 && stop - level <= nine_max) {
		return nine_map[stop - level];
	}
	else if (is_even_digits(num)) {
		long long sum = 0;
		auto [l, r] = split_num(num);
		sum += blink_two(l, level + 1);
		sum += blink_two(r, level + 1);
		return sum;
	}
	else {
		return blink_two(num * 2024, level + 1);
	}
}

void load_memo() {
	vector<string> memos = read_file("11_memo\\zero.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		zero_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "zero_map loaded" << endl;
	memos = read_file("11_memo\\one.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		one_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "one_map loaded" << endl;
	memos = read_file("11_memo\\two.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		two_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "two_map loaded" << endl;
	memos = read_file("11_memo\\three.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		three_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "three_map loaded" << endl;
	memos = read_file("11_memo\\four.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		four_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "four_map loaded" << endl;
	memos = read_file("11_memo\\five.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		five_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "five_map loaded" << endl;
	memos = read_file("11_memo\\six.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		six_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "six_map loaded" << endl;
	memos = read_file("11_memo\\seven.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		seven_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "seven_map loaded" << endl;
	memos = read_file("11_memo\\eight.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		eight_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "eight_map loaded" << endl;
	memos = read_file("11_memo\\nine.txt");
	for (const auto& s : memos) {
		vector<string> n = split_string(s, ':');
		nine_map[stoi(n[0])] = stoll(n[1]);
	}
	cout << "nine_map loaded" << endl;
}

string P11::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	vector<string> split_data = split_string(data[0], ' ');
	long long sum = 0;
	load_memo();
	for (const auto& val : split_data) {
		sum += blink_two(stoll(val), 0);
		cout << sum << endl;
	}
	//for (int i = 1; i < 56; i++) {
	//	zero_map[i] = blink_two_stop(0, 0, i);
	//}
	//for (const auto& val : split_data) {
	//	sum += blink_two(stoll(val), 0);
	//}
	//for (int i = 1; i < 56; i++) {
	//	cout << i << ":" << zero_map[i] << endl;
	//}
	//sum += blink_two(0, 0);
	return to_string(sum);
}

string P11::test_first() {
	return first_solver(test_path);
}

string P11::test_second() {
	return second_solver(test_path);
}

string P11::solve_first() {
	return first_solver(path);
}

string P11::solve_second() {
	return second_solver(path);
}