
/**
 * @brief k 个有序数组，归并成一个有序数组。
 * 
 */

#include <iostream>
#include <vector>

std::vector<int> merge(const std::vector<std::vector<int>> &arrs) {
    
    if (arrs.size() == 0) return {};

    std::vector<int> res = arrs[0];

    // 遍历
    for (int i = 1; i < arrs.size(); i++) {
        std::vector<int> tmp;
        int j = 0, k = 0;
        while (j < res.size() && k < arrs[i].size()) {
            if (res[j] <= arrs[i][k]) {
                tmp.push_back(res[j++]);
            } else {
                tmp.push_back(arrs[i][k++]);
            }
        }

        while(j < res.size()) {
            tmp.push_back(res[j++]);
        }

        while(k < arrs[i].size()) {
            tmp.push_back(arrs[i][k++]);
        }
        // 更新结果
        res = std::move(tmp);
    }

    return res;
}