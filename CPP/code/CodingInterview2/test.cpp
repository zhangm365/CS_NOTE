
#include <bits/stdc++.h>
#if 0
//计算2的n次方

int square(int a) { return a * a; }

int power2(int n) 
{ // 计算2的n次方
    if (0 == n) return 1;
    return n % 2 ? square(power2(n>>1))<<1 : square(power2(n>>1));
}

int jumpFloorII(int number) {
    return power2(number - 1);
}



int main()
{
    int x;
    std::cin >> x;
    std::cout << jumpFloorII(x) << std::endl;

    
    return 0;
}
#endif

#if 0
using namespace std;


vector<string> split(string str){
    stringstream ss;
    ss<<str;
    string words;
    vector<string> result;
    while (std::getline(ss, words, ',')) {  // 以逗号分割字符串
        result.push_back(words);
    }
    return result;
};

int main() 
{

    vector<string> res;
    string s("my,hello,world,zhang,,,");
    res = split(s);
    //printf("%d\n", result.size());
    for(auto s : res)
        cout << s << endl;
    
    return 0;
}

#endif

template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while(!q.empty()) {
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';
}
 
int main() {
    std::priority_queue<int> q;
 
    const auto data = {1,8,5,6,3,4,0,9,7,2};
 
    for(int n : data)
        q.push(n);
 
    print_queue(q);
 
    std::priority_queue<int, std::vector<int>, std::greater<int>>
        q2(data.begin(), data.end());
 
    print_queue(q2);
 
    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
 
    for(int n : data)
        q3.push(n);
 
    print_queue(q3);
}

