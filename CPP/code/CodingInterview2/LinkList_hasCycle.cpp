

// https://leetcode-cn.com/problems/linked-list-cycle/
// https://leetcode-cn.com/problems/linked-list-cycle-ii/
// https://leetcode-cn.com/problems/middle-of-the-linked-list/
// https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/

// 判断一个链表中是否有环： 双指针之快慢指针

#include <bits/stdc++.h>

typedef int ElemType;

// 定义单链表结构
struct ListNode
{
    ElemType val;
    struct ListNode* next;

    ListNode(int x = 0):val(x), next(nullptr){}

};



class Solution
{
    public:
        // 判断一个链表是否有环
        bool hasCycle(ListNode* head);
        //  返回一个给定链表中的开始入环的第一个节点位置 
        ListNode* detectCycle(ListNode* head);
        // 删除链表的倒数第n个几点
        ListNode* removeNthFromEnd(ListNode* head, int n);

};


// 判读是否有环
bool Solution::hasCycle(ListNode* head)
{

    // 链表为空
    if(!head)   
        return false;

    ListNode* fast, *slow;
    fast = slow = head;

    while (fast && fast->next)
    { 
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)    // 快指针追上了慢指针，若慢指针走了K步, 那么快指针就走2K步
            return true;
    }
    
    return false;

}

// 返回一个链表中开始入环的第一个位置
ListNode* Solution::detectCycle(ListNode* head)
{

    // 链表为空
    if(!head)   
        return nullptr;

    ListNode* fast, *slow;
    fast = slow = head;


    // step1：判断是否有环
    while (fast != nullptr && fast->next != nullptr)
    { 
        fast = fast->next->next;
        slow = slow->next;
        // 链表中存在环
        if(fast == slow)
            break;
    }
    
    // 无环
    if(fast == nullptr || fast->next == nullptr)
        return nullptr;

    
    // step2: 找出环的位置
    slow = head;    // 重新指向头结点
    while( slow != fast )
    { // 以相同的步伐前进, 当快慢指针再次相遇时, 即找到了开始入环的位置
        fast = fast->next;
        slow = slow->next;

    }
    return slow;

}


// 删除链表中的倒数第N个节点
ListNode* Solution::removeNthFromEnd(ListNode* head, int n) 
{
    if(!head || n < 1)
        return nullptr;
    
    ListNode* fast, *slow;
    fast = slow = head;

    while(n--)  //先让快指针走n步
        fast = fast->next;
    
    if(fast == nullptr)    // 快指针走到头
    {// 此时倒数第n个节点就是链表第一个结点
        return head->next;
    }
    while(fast && fast->next)   // 快慢指针同步前进
    {
        slow = slow->next;
        fast = fast->next;
    }

    // slow->next就是倒数第n个节点
    slow->next = slow->next->next;
    
    return head;

}
