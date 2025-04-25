#include "p3.h"
#include "utility.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>
#include <iostream>
#include <unordered_set>

using namespace std;

const unordered_set<char> digits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

string parens(const string& in) {
	if (in.at(0) != '(') return "";  // null case
	for (int i = 0; i < in.size(); i++) {
		if (in[i] == ')') return in.substr(0, i + 1);  // i hate off by one
	}
	return "";
}

vector<string> parse_innards(const string& in) {
	bool found_comma = false;
	string first, last;
	for (const auto& x : in) {
		if (x == ',' && !found_comma) found_comma = true;
		else if (x == ',' && found_comma) {
			first = "error_val";
			break;
		}
		else if (digits.contains(x)) {
			if (!found_comma) first.push_back(x);
			else last.push_back(x);
		}
		else if (x == '(' || x == ')') {
			continue;
		}
		else {
			first = "error_val";  // not safe lul
			break;
		}
	}
	return vector<string> {first, last};
}

string P3::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	vector<string> mulsplit;
	for_each(data.begin(), data.end(), [&mulsplit](string in) {
		vector<string> temp = split_string_delim_string(in, "mul");
		for (const auto& x : temp) {
			mulsplit.push_back(x);
		}
		});
	// Now parse for (), must be at start.
	vector<string> have_parens;
	for_each(mulsplit.begin(), mulsplit.end(), [&have_parens](const string& in) {
		string temp = parens(in);
		if (temp != "") have_parens.push_back(temp);
		});
	// Now parse for nicely constructed innards (X,Y)
	vector<vector<string>> formed_nicely;
	for_each(have_parens.begin(), have_parens.end(), [&formed_nicely](const string& in) {
		vector<string> temp = parse_innards(in);
		if (temp.at(0) == "error_val") return;
		else {
			formed_nicely.push_back(temp);
			return;
		}
		});
	return to_string(accumulate(formed_nicely.begin(), formed_nicely.end(), 0, [](int acc, const vector<string>& in) {
		return acc + (stoi(in.at(0)) * stoi(in.at(1)));
		}));
}

vector<pair<string, vector<string>>> single_line_parser(const string& in) {
	vector<pair<string, vector<string>>> out;
	string temp_line;
	bool in_mul = false;
	bool in_dont = false;
	int mul_counter = -1;
	unordered_set<string> tokens{ "don't", "do", "mul" };
	for (int i = 0; i < in.size() - 2; ++i) {
		for (const auto& token : tokens) {
			if (in.size() - i < token.size()) continue;
			if (in.substr(i, token.size()) == token) {
				int token_length = token.size();
				string unparsed_paren_pair = parens(in.substr(i + token.size(), in.size()));
				if (unparsed_paren_pair == "") continue;
				vector<string> innards = parse_innards(unparsed_paren_pair);
				if (innards.at(0) == "error_val") continue;
				out.push_back(pair(token, innards));
			}
		}
	}
	return out;
}

string P3::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	vector<pair<string, vector<string>>> parsed_data;
	for (const string& line : data) {
		// TODO: add this data to a wider vector so we can parse the whole dang thing
		vector<pair<string, vector<string>>>parsed_in = single_line_parser(line);
		for (const auto& thing : parsed_in) {
			parsed_data.push_back(thing);
		}
	}
	bool dont = false;
	int acc = 0;
	for (const auto& thing : parsed_data) {
		//print(thing.first);
		//cout << thing.second.at(0) << "," << thing.second.at(1) << endl;
		if (thing.first == "don't") {
			dont = true;
		}
		else if (thing.first == "do") {
			dont = false;
		}
		else if (thing.first == "mul" && !dont) {
			acc += stoi(thing.second.at(0)) * stoi(thing.second.at(1));
		}
	}
	cout << acc << endl;
	return path;
}

string P3::test_first() {
	return first_solver(test_path);
}

string P3::test_second() {
	return second_solver(test_path);
}

string P3::solve_first() {
	return first_solver(path);
}

string P3::solve_second() {
	return second_solver(path);
}