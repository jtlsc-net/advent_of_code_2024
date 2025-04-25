#include "utility.h"

#include <fstream>

std::vector<std::string> read_file(std::filesystem::path input_file) {
	std::vector<std::string> output;
	std::ifstream istream(input_file);
	
	std::string line;
	while (std::getline(istream, line)) {
		output.push_back(line);
	}

	return output;
}

std::vector<std::string> split_string(const std::string& input, char delim) {
	std::vector<std::string> out;
	std::string temp_line;
	for (auto c : input) {
		if (delim != c) {
			temp_line.push_back(c);
		}
		else {
			if (temp_line.size() > 0) {
				out.push_back(temp_line);
				temp_line.clear();
			}
		}
	}
	out.push_back(temp_line);

	return out;
}

std::vector<std::string> split_string_delim_string(const std::string& input, const std::string& delim) {
	std::vector<std::string> out;
	int window_size = static_cast<int>(delim.size());
	std::string temp_line;
	int delim_count = -1;
	for (int i = 0; i < input.size() - window_size + 1; ++i) {
		if (input.substr(i, window_size) == delim) {
			if (temp_line.size() > 0) {
				out.push_back(temp_line);
				temp_line.clear();
			}
			delim_count = 3;
		}
		else {
			if (delim_count <= 0)
				temp_line.push_back(input[i]);
		}
		delim_count--;
	}
	if (delim_count <= 0)
		out.push_back(temp_line + input.substr(input.size() - window_size + 1, window_size - 1));
	else if (temp_line.size() > 0) {
		out.push_back(temp_line);
	}
	return out;
}

std::vector<int> split_string_int(const std::string& input, char delim) {
	std::vector<int> out;
	std::string temp_line;
	for (auto c : input) {
		if (delim != c) {
			temp_line.push_back(c);
		}
		else {
			if (temp_line.size() > 0) {
				out.push_back(std::stoi(temp_line));
				temp_line.clear();
			}
		}
	}
	out.push_back(std::stoi(temp_line));

	return out;
}

std::string join_vec(const std::vector<std::string>& in, const std::string& delim) {
	std::string out{ "" };
	for (int i = 0; i < in.size(); i++) {
		out += in[i];
		if (!(i + 1 == in.size())) out += delim;
	}
	return out;
}

std::string join_vec(const std::vector<int>& in, const std::string& delim) {
	std::string out{ "" };
	for (int i = 0; i < in.size(); i++) {
		out += std::to_string(in[i]);
		if (!(i + 1 == in.size())) out += delim;
	}
	return out;
}

bool contains(const std::string& input, const std::string& delim) {
	int window_size = static_cast<int>(delim.size());
	for (int i = 0; i < input.size() - window_size + 1; ++i) {
		if (input.substr(i, window_size) == delim) {
			return true;
		}
	}
	return false;
}

bool string_contains(const std::string& input, char delim) {
	for (auto c : input) {
		if (c == delim) return true;
	}
	return false;
}

bool vector_contains(const std::vector<int>& in_vec, int delim) {
	for (const auto& in : in_vec) {
		if (in == delim) return true;
	}
	return false;
}

void print(const std::string& input) {
	std::cout << input << std::endl;
}

std::string jtrim(std::string s) {
	ltrim(s);
	rtrim(s);
	return s;
}