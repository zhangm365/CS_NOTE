string maxMatched( const string &str, const vector<string> &dict )
{
    string ret;
    int n = dict.size();
    int max_len = 0;
    unordered_map<int, int>  mymap;
    for( int i = 0; i < n; ++i )
    {
        int len = helper(dict[i], str);
        mymap[len] = i;
        max_len = max(len, max_len);
    }    
    return dict[mymap[max_len]];
}
int helper( const string &src, const string &dst )// 寻找最长子串
{
    int ans = 0;
    for( int i = 0, j = 0; i < src.size() && j < dst.size(); )
    {
        if( dst[i] == src[j] )
        {
            ans++;
            i++;
            j++;
        }    
        else j++;        
    }
    return ans;
}