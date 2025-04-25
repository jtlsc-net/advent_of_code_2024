#include "p9.h"
#include "utility.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <tuple>

using namespace std;

vector<string> generate_memmap_vec(const string& in) {
	vector<string> out;
	for (int i = 0; i < in.size(); ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < stoi(string(1, in[i])); ++j) {
				out.push_back(to_string(i / 2));
			}
		}
		else {
			for (int j = 0; j < stoi(string(1, in[i])); ++j) {
				out.push_back(".");
			}
		}
	}
	return out;
}

vector<string> move_blocks_vec(vector<string> in) {
	auto l = in.begin();
	auto r = in.end();
	--r;
	auto find_next = [&l, &r, &in]() {
		while (*r == ".") {
			--r;
			if (r == in.begin()) break;
		}
		while (*l != ".") {
			++l;
			if (l == in.end()) break;
		}
		};

	find_next();

	while (l < r) {
		iter_swap(l, r);
		find_next();
	}
	return in;
}

long long update_checksum_vec(const vector<string>& in) {
	long long sum = 0;
	for (size_t i = 0; i < in.size(); ++i) {
		if (in.at(i) != ".")
			sum += i * (stoi(in.at(i)));
	}
	return sum;
}

string P9::first_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	if (data.size() > 1) return "error";
	vector<string> mmap = generate_memmap_vec(data[0]);
	vector<string> blocks = move_blocks_vec(mmap);
	string out = to_string(update_checksum_vec(blocks));
	//vector_print(mmap);
	//vector_print(blocks);
	return out;
}

struct Block {
	string type;
	string data;
	Block() {
		type = "";
		data = "";
	}
};

tuple<vector<string>, set<string>> generate_memmap_vec_chunk(const string& in) {
	vector<string> memmap;
	set<string>    found_numbers;
	for (int i = 0; i < in.size(); ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < stoi(string(1, in[i])); ++j) {
				memmap.push_back(to_string(i / 2));
			}
			found_numbers.insert(to_string(i / 2));
		}
		else {
			for (int j = 0; j < stoi(string(1, in[i])); ++j) {
				memmap.push_back(".");
			}
		}
	}
	return { memmap, found_numbers};
}

vector<string> move_blocks_vec_chunk(vector<string> in, set<string> found_nums) {
	auto l = in.begin();
	auto r = in.end();
	--r;
	auto find_next = [&l, &r, &in]() {
		while (*r == ".") {
			--r;
			if (r == in.begin()) break;
		}
		while (*l != ".") {
			++l;
			if (l == in.end()) break;
		}
		};

	auto gap_size = [&in](auto l) -> int {
		// Assume on start of gap.
		int count = 0;
		while (*l == ".")
		{
			++count;
			++l;
		}
		return count;
		};

	auto value_size = [&in](auto r, string c) -> int {
		// Assume on end of value list
		int count = 0;
		while (*r == c) {
			++count;
			--r;
		}
		return count;
		};

	auto find_next_gap = [&in](auto l) -> vector<string>::iterator {
		while (l < end(in) && *l == ".") ++l;
		while (l < end(in) && *l != ".") ++l;
		return l;
		};

	// starts with r pointing at the end of the block.
	auto block_swap = [&in](auto l, auto r, string swap_char) {
		while (l < r && *r == swap_char) {
			iter_swap(l, r);
			++l;
			--r;
		}
		};

	auto find_first_match = [&in, &gap_size, &value_size, &find_next_gap, &block_swap](vector<string>::iterator l, vector<string>::iterator r) -> bool {
		while (l < r) {
			int l_size = gap_size(l);
			int r_size = value_size(r, *r);
			if (l_size >= r_size) {
				block_swap(l, r, *r);
				return true;
			}
			auto temp = find_next_gap(l);
			if (temp == l) break;
			l = temp;
		}
		return false;
		};

	auto find_next_good_value = [&in, &found_nums](auto r) -> vector<string>::iterator {
		if (found_nums.contains(*r)) return r;
		while (r > begin(in) && !found_nums.contains(*r)) --r;
		return r;
		};

	find_next();

	while (l < r) {
		string temp_r = *r;
		if (found_nums.contains(*r)) {
			find_first_match(l, r);
			found_nums.erase(temp_r);
		}
		r = find_next_good_value(r);
		if (*l != ".") l = find_next_gap(l);
	}
	return in;
}

string P9::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	if (data.size() > 1) return "error";
	auto [memmap, found_nums] = generate_memmap_vec_chunk(data[0]);
	vector<string> blocks = move_blocks_vec_chunk(memmap, found_nums);
	return to_string(update_checksum_vec(blocks));
}

string P9::test_first() {
	return first_solver(test_path);
}

string P9::test_second() {
	return second_solver(test_path);
}

string P9::solve_first() {
	return first_solver(path);
}

string P9::solve_second() {
	return second_solver(path);
}