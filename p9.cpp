#include "p9.h"
#include "utility.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>
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

tuple<vector<string>, map<int, int>, map<int, int>> generate_memmap_vec_chunk(const string& in) {
	vector<string> first_out;
	map<int, int> second_out;
	map<int, int> third_out;
	for (int i = 0; i < in.size(); ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < stoi(string(1, in[i])); ++j) {
				//if (j == 0) temp_str = to_string(i / 2);
				first_out.push_back(to_string(i / 2));
			}
			//second_out[i + stoi(string(1, in[i]))] = i;
		}
		else {
			for (int j = 0; j < stoi(string(1, in[i])); ++j) {
				first_out.push_back(".");
			}
			//third_out[i] = i + stoi(string(1, in[i]));
		}
	}

	int i_c = 0;
	int j_c = 0;
	bool ten = false;  // Won't work since there can be multiple things like 9996
	if (first_out[0][0] == '.') ten = true;
	for (auto w : first_out) {
		if (ten && w != ".") {
			third_out[j_c] = i_c;
			ten = false;
			++i_c;
			j_c = i_c;
		}
		else if (!ten && w == ".") {
			second_out[i_c] = j_c;
			ten = true;
			++i_c;
			j_c = i_c;
		}
		else {
			++i_c;
		}
	}
	return { first_out, second_out, third_out };
}

vector<string> move_blocks_vec_chunk(vector<string> in, map<int, int> block, map<int, int> empty) {
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

	// starts with r pointing at the end of the block.
	auto block_swap = [&block, &empty, &in](auto l, auto r) -> bool {
		// find r begin and l end;
		int r_idx = static_cast<int>(distance(begin(in), r));
		int r_start = block[r_idx];
		int l_end = empty[static_cast<int>(distance(begin(in), l))];

		while (l < r) {
			int l_idx = static_cast<int>(distance(begin(in), l));
			if (empty.contains(l_idx) && block.contains(r_idx)) {
				if ((empty[l_idx] - l_idx) >= (r_idx - r_start)) {
					// actually move it.
					while (distance(begin(in), r) >= r_start) {
						iter_swap(l, r);
						++l;
						--r;
					}
					return true;
				}
			}
			++l;
		}
		return false;
		};

	find_next();

	while (l < r) {
		if (!block_swap(l, r)) {
			--r;
		}
		//++l;
		//--r;
		find_next();
		vector_print(in);
	}
	return in;
}

string P9::second_solver(string path) {
	vector<string> data = read_file(data_path / filesystem::path(path));
	if (data.size() > 1) return "error";
	auto [memmap, block_size, empty_size] = generate_memmap_vec_chunk(data[0]);
	vector_print(memmap);
	for (auto stuff : block_size) {
		print(to_string(stuff.second) + "," + to_string(stuff.first));
	}
	print("=================");
	for (auto stuff : empty_size) {
		cout << stuff.first << "," << stuff.second << endl;
	}
	//vector<string> blocks = move_blocks_vec_chunk(memmap, block_size, empty_size);
	print("==================");
	//vector_print(blocks);
	return path;
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