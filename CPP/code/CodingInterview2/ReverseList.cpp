


//逆序输出单链表中的值


#include <bits/stdc++.h>


struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

class Solution
{
    public:
        std::vector<int> reversePrint(ListNode* head);
        std::vector<int> reversePrint2(ListNode* head);

};


std::vector<int> Solution::reversePrint(ListNode *head)
{
    if(!head)
        return {};
    
    //建立一个堆:后进先出
    std::stack<int> st ;
    std::vector<int> ret;
    ListNode* p = head;

    while(p)
    {
        st.push(p->val);
        p = p -> next;
    }
    
    while(!st.empty())
    {
        ret.push_back(st.top());
        st.pop();
    }


    return ret;

}


std::vector<int> Solution::reversePrint2(ListNode *head)
{
    if(!head)
        return {};
    
    
    std::vector<int> ret;
    ListNode* p = head;

    while(p)
    {
        ret.push_back(p->val);
        p = p -> next;
    }
    
    //原地翻转数组
    reverse(ret.begin(), ret.end());

    return ret;

}

int main()
{
    
    Solution So;

    int n, x;
    printf("Please input the number of Node:\n");
    scanf("%d", &n);
    ListNode *head, *p;
    p = head = nullptr;

    for(int i = 0 ; i < n; ++i)
    {

        scanf("%d", &x);
        //创建新结点
        ListNode *newNode = new ListNode(x);
        if(!head)   //空链表
        {
            head = newNode;
            p = head;
        }
        else
        {
            p->next = newNode;
            p = newNode;    
        }
        
    }

    std::vector<int> ans = So.reversePrint2(head);

    for(int i = 0; i < ans.size(); ++i)
    {
        if(i !=0 ) printf(" ");
        printf("%d", ans[i]);
    }
    
    printf("\n");
    
    return 0;
}