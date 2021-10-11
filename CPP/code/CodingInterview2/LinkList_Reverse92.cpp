

// https://leetcode-cn.com/problems/reverse-linked-list-ii/

// 反转链表 给定区间[m, n]间的链表


#include <bits/stdc++.h>



/********************************************************
 
 * 一定防止出现空指针！！！！！
首先根据剑指offer的反转整个链表的思路，使用**迭代法+快慢指针**反转[m, n]间的指针

核心思想 ： **遍历 + 快慢指针**

1. 初始化：指针cur指向要反转的第m个节点（反转前）, 并p指向cur的后继节点，q指向p的后继节点（**快慢指针**）；
2. 反转[m, n]区间内的指针；
3. 反转完成后pre指向第n个节点，cur和p指向同一个位置；
4. 处理细节问题，为了防止空指针的出现；
- 头指针指向；
- 断链问题；

****************************************///////////

struct ListNode
{

    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){}
    ListNode(int x) : val(x), next(nullptr){}

};



class Solution
{

    public:
        ListNode* reverseBetween(ListNode* head, int m, int n);

        // // 建立单链表
        ListNode* Build_LinkedList(std::vector<int> nums);
        // 打印单链表
        void Print_LinkedList(ListNode *head);

};



ListNode* Solution::reverseBetween( ListNode *head, int m, int n )
{

    if ( !head || m > n ) return nullptr;
    if( m == n ) return head;

    //pre是遍历过程中cur节点的前驱节点，p_r记录第m个节点的前驱节点

    ListNode *pre = nullptr, *p_r = nullptr;

    ListNode *cur = head;

    //step1: cur指向第m个节点
    int i = 1;

    while( cur && (i < m ) )
    {
        i++;
        if( cur == nullptr ) return head;
        p_r = cur;
        cur = cur->next;
    
    }
    // r记录第m个节点位置
    ListNode *r = cur;

    ListNode *p = cur;

    i = 0;  //i重新计数
    //三指针反转区间[m, n]的指针
    while( p && (i <= n-m) )
    {
        p = cur->next;
        cur->next = pre; 
        
        //更新指针
        pre = cur;               
        cur = p;
        i++;
    
    }
    
    // cur == p
    //pre此时指向第n个节点，处理头结点和断链位置
    
    r->next = p;

    if( m == 1 ) // 头结点被反转
    {
        head = pre;
    } 
    else
    {//第m个节点的前驱接到第n个节点
        p_r->next = pre;
    }
    
    return head;

}




// 建立单链表
ListNode* Solution::Build_LinkedList(std::vector<int> nums)
{
  
    if(nums.empty()) return nullptr;

    //建立根节点
    ListNode *head = new ListNode(nums[0]);
    
    //遍历指针
    ListNode *p = head;

    for( int i = 1; i < nums.size(); ++i )
    {

        ListNode *q = new ListNode(nums[i]);
        p->next = q;
        p = q;
        
    }

    p->next = nullptr;

    return head;

}


// 打印链表
void Solution::Print_LinkedList(ListNode *head)
{

    ListNode *p = head;

    while(p)
    {
        if( p != head ) printf("->");
        printf("%d", p->val);
        p = p->next;

    }

    printf("\n");

}


int main()
{

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    Solution So;
    ListNode *head = So.Build_LinkedList(nums);
    So.Print_LinkedList(head);
    int m = 3, n = 5;
    head = So.reverseBetween(head, m, n);

    So.Print_LinkedList(head);
    
    return 0;

}

#if 0

// 递归反转链表

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n);
    //反转链表中的前n个节点
    ListNode* reverseN(ListNode* head, int n);
    private:
        ListNode *successor;
};


ListNode* Solution::reverseBetween( ListNode *head, int m, int n )
{

    if( !head ) return nullptr;
    // 直接返回前n个节点的结果
    if( m == 1 ) return reverseN(head, n);


    head->next = reverseBetween(head->next, m-1, n-1);

    return head;

}


// 返回链表的前n个节点
ListNode* Solution::reverseN( ListNode *head, int n )
{
    if( !head || n <= 0 ) return nullptr;
    
    // base case
    if( n == 1 )
    {
        //记录第n+1个节点
        successor = head->next;
        return head;
    }

    ListNode *last = reverseN(head->next, n-1);

    head->next->next = head;
    head->next = successor;

    return last;

}

#endif