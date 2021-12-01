
#include <iostream>
#include <algorithm>

#include <cmath>
#include <vector>

using namespace std;


bool compare( int a, int b)
{
    return (abs(a) < abs(b));
}


// 按每个元素的绝对值大小来排序
void absSort( vector<int>& arr )
{
    
    /*
    std::sort(arr.begin(), arr.end(), compare);
    */
    
    std::sort(arr.begin(), arr.end(), 
        // lambda expression
        [](int a, int b) -> bool
        {
            
            return (std::abs(a) < std::abs(b));
        }
        // end the lambda
    );
    
    
}

class Lambda
{

    public:
        // 求大于等于一个给定长度的单词有多少
        void biggies( vector<string>& words, vector<string>::size_type sz)
        {

            // words按字典序排序,删除重复单词
            elimDups(words);

            stable_sort(words.begin(), words.end(),

                // 按长度由小到大排序，相同长度按字典序排序
                []( const string& s1, const string& s2 )->bool
                {
                    return (s1.size() < s2.size());
                }
            );


            // 找到第一个大于等于长度sz的元素
            auto ge = find_if(words.begin(), words.end(), 
                [sz]( const string& str )
                {
                    return str.size() >= sz;
                }
            );


            int count = words.end() - ge;

            cout << "the count greater sz is " << count << endl;


            for_each(ge, words.end(), 
                [](const string& str)
                {
                    cout << str << " ";
                }
            
            );

            cout << endl;


        }

        void elimDups( vector<string>& words )
        {
            
            // 按字典序排序, 方便查找重复单词
            sort(words.begin(), words.end());
            
            // unique算法让每个单词仅出现一次，end_unique返回不重复区域之后的第一个位置
            auto end_unique = unique(words.begin(), words.end());

            // 删除重复元素
            words.erase(end_unique, words.end());
        
        }




};



int main()
{

    // vector<int> arr = {-1, 2, 3, 0, -5, 6};
    // absSort(arr);

    // for( int val : arr )
    //     cout << val << " ";     

    // cout << endl;

    Lambda la;

    vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle", "quick"};
    la.biggies(words, 4);
    
    return 0;

}