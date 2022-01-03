
/*
    lambda 表达式排序数对 pair<int, int>。
    按第一个元素降序排序，如果第一个元素相同，则按第二个元素升序排序。
*/


vector<vector<int>> nums = { {7,1}, {3,2}, {6,0}, {5,1} };
sort(nums.begin(), nums.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] > b[0];
            }
            return a[1] < b[1];
        });