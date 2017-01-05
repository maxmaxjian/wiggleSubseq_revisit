#include <iostream>
#include <vector>
// #include <unordered_map>
// #include <functional>
#include <algorithm>
#include <iterator>

// struct hasher {
//     size_t operator()(const std::vector<int> & vec) const {
// 	return std::accumulate(vec.begin(), vec.end(), std::bit_xor<int>());
//     }
// };

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<std::vector<int>,bool> & pr) {
	std::copy(pr.first.begin(), pr.first.end(), std::ostream_iterator<int>(os," "));
	os << std::boolalpha << pr.second;
	return os;
    }
}

class solution {
public:
    int wiggleMaxLength(const std::vector<int> & nums) {
	std::vector<std::pair<std::vector<int>, bool>> incr;
	bool flag = true;
	for (auto n : nums) {
	    if (incr.empty()) {
		incr.push_back(std::make_pair(std::vector<int>{n},flag));
	    }
	    else {
		auto it = incr.rbegin();
		while (it != incr.rend()) {
		    if (it->first.back() < n && it->second == true)
			break;
		    else if (it->first.back() > n && it->second == false)
			break;
		    else
			++it;
		}
		if (it != incr.rend()) {
		    auto cpy = *it;
		    cpy.first.push_back(n);
		    cpy.second = !cpy.second;

		    incr.push_back(cpy);
		}		
	    }
	}

	std::copy(incr.begin(), incr.end(), std::ostream_iterator<std::pair<std::vector<int>,bool>>(std::cout, "\n"));

	auto it = std::max_element(incr.begin(), incr.end(), [](const std::pair<std::vector<int>, bool> & p1, const std::pair<std::vector<int>,bool> & p2){
		return p1.first.size() < p2.first.size();
	    });
	return it->first.size();
    }
};

int main() {
    // std::vector<int> nums{1,7,4,9,2,5};
    // std::vector<int> nums{1,17,5,10,13,15,10,5,16,8};
    std::vector<int> nums{1,2,3,4,5,6,7,8,9};

    solution soln;
    int mLen = soln.wiggleMaxLength(nums);
    std::cout << "The length of the longest wiggle subsequence is:\n"
	      << mLen << std::endl;
}


