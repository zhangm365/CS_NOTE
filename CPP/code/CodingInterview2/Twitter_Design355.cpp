


// https://leetcode-cn.com/problems/design-twitter/

#include <bits/stdc++.h>

static int timestamp;

// 存储推文内容，是一个链表
class Tweet
{
    public:
        Tweet(){}

        Tweet(int _id, int _time) : id(_id), time(_time), next(nullptr){}

        // 数据域：推文内容的id和时间
        int id;
        int time;

        // 指针域
        Tweet *next;
        

};


// 面向对象设计 ：用户信息封装: 「关注用户」，「取消关注」，「发推文」
class User
{
    public:
        User(int _id) {

            this->id = _id;
            head = nullptr;
            follow(id);    // 默认关注自己
        
        }

        // 关注用户
        void follow( int userId);

        // 取消关注
        void unfollow(int userId);

        // 发文
        void post(int tweetId);

        // 关注的用户集合：快速查找
        std::unordered_set<int> followed;   //
        // 推文的头结点
        Tweet *head;
        // 用户id
        int id;
        

};


void User::follow( int userId )
{

    followed.insert(userId);

}


void User::unfollow( int userId )
{

    if( this->id != userId )    // 不可以取关自己
        followed.erase(userId);

}


void User::post( int tweetId )
{

    Tweet *twt = new Tweet(tweetId, timestamp);
    timestamp++;

    // 「头插法」新的推文插入链表头，越靠前的time越新
    twt->next = head;
    head = twt;

}



class Twitter {
    public:
    /** Initialize your data structure here. */
        Twitter(){}
        
        /** Compose a new tweet. */
        void postTweet(int userId, int tweetId) 
        {

            if( !userMap.count(userId) )
            {   // 用户不存在，则创建
                User *newUser = new User(userId);
                userMap.insert({userId, newUser});
            }

            auto u = userMap.find(userId);
            u->second->post(tweetId);

        }
        
        /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
        std::vector<int> getNewsFeed(int userId) ;
        
        /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
        void follow(int followerId, int followeeId) {

            if( !userMap.count(followerId) )
            {
                User *u = new User(followerId);
                userMap.insert({followerId, u});
            }

            if( !userMap.count(followeeId) )
            {
                User *u = new User(followeeId);
                userMap.insert({followeeId, u});
            }

            userMap.find(followerId)->second->follow(followeeId);

        }
        
        /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
        void unfollow(int followerId, int followeeId) {

            if( !userMap.count(followerId) ) return;

            auto flwer = userMap.find(followerId);
            flwer->second->unfollow(followeeId);

        }

    private:
        std::unordered_map<int, User*> userMap;  // 将用户id和用户对象对应


};


// 重载「< 运算符」按推文时间降序排列
bool operator< (Tweet &a, Tweet &b)
{
    return b.time > a.time;
}

// 优先队列「合并」k个有序链表 
std::vector<int> Twitter::getNewsFeed( int userId)
{
    
    if( !userMap.count(userId) ) return {};

    std::vector<int> res;

    // 用户userId的所有关注用户数
    std::unordered_set<int> users = userMap.find(userId)->second->followed;

    // 优先队列合并k个有序链表
    std::priority_queue<Tweet*> pq;

    // 把关注的各个用户的推文链表加入优先队列并排序
    for (auto &id : users )
    {
        auto usr = userMap.find(id)->second->head;
        if ( !usr ) continue;
        
        pq.push(usr);

    }


    while( !pq.empty() )
    {

        if ( res.size() == 10 ) break;

        // 弹出链表头的结点「time最新」
        Tweet *twt = pq.top();
        pq.pop();
        res.push_back(twt->id);

        // 将下一篇tweet插入排序
        if( twt->next )
        {
            pq.push(twt->next);
        }

    }

    return res;

}
