#include "p1.h"
#include "utility.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <unordered_map>

std::string first_solver(std::string path) {
	std::vector<std::string> data = read_file(data_path / std::filesystem::path(path));
	std::vector<int> left(data.size()), right(data.size());

	for (const auto& str : data) {
		std::vector<std::string> temp = split_string(str, ' ');
		left.push_back(std::stoi(temp.at(0)));
		right.push_back(std::stoi(temp.at(1)));
	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	std::transform(left.begin(), left.end(), right.begin(), left.begin(), [](int l, int r) {
		return std::abs(l - r);
		});

	return std::to_string(std::accumulate(left.begin(), left.end(), 0));
}

std::string second_solver(std::string path) {
	std::vector<std::string> data = read_file(data_path / std::filesystem::path(path));
	std::vector<int> left(data.size()), right(data.size());

	for (const auto& str : data) {
		std::vector<std::string> temp = split_string(str, ' ');
		left.push_back(std::stoi(temp.at(0)));
		right.push_back(std::stoi(temp.at(1)));
	}

	std::unordered_map<int, int> num_to_count;
	
	auto similarity_with_cache = [&num_to_count, &right](int outacc, int l) {
		if (num_to_count.contains(l)) return outacc + l * num_to_count[l];
		else {
			int sum = static_cast<int>(std::count(right.begin(), right.end(), l));
			num_to_count[l] = sum;
			return outacc + l * sum;
		}
		};
	
	return std::to_string(std::accumulate(left.begin(), left.end(), 0, similarity_with_cache));
}

std::string P1::test_first() {
	return first_solver(test_path);
}

std::string P1::test_second() {
	return second_solver(test_path);
}

std::string P1::solve_first() {
	return first_solver(path);
}

std::string P1::solve_second() {
	return second_solver(path);
}