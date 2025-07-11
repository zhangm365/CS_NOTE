
#include <iostream>
#include <vector>
#include <cstdint>

/*****
 * Find the two largest numbers in a vector.
 */

std::vector<int64_t> findMax2(const std::vector<int64_t>& input) {
    /// Your code here
    /// This function should return the one or two largest numbers in the input vector.
    if (input.size() == 0) return {};
    
    int64_t max_1 = INT64_MIN, max_2 = INT64_MIN;

    for (const auto& val : input) {
        if (val > max_1) {
            max_2 = max_1;
            max_1 = val;
            
        } else if (val > max_2 && val != max_1) {
            max_2 = val;
        }
    }

    //std::cout << max_1 << " " << max_2 << std::endl;

    if (max_2 == INT64_MIN) {
        return {max_1};
    }

    return  {max_1, max_2};

}

int main()
{
    std::vector<int64_t> input{INT64_MIN, INT64_MIN, INT64_MIN};
    std::vector<int64_t> ans = findMax2(input);
    for (const auto& val : ans) {
        std::cout << val << " ";
    }
    
    std::cout << std::endl;
    return 0;
}