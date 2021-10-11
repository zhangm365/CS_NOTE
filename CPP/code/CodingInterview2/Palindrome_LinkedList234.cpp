

// https://leetcode-cn.com/problems/palindrome-linked-list/

//回文链表



#include <bits/stdc++.h>



/**Definition for singly-linked list.* */
 

struct ListNode {
    int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

 
class Solution {
public:
    bool isPalindrome(ListNode* head);

    // 遍历链表
    bool traverse(ListNode *head);
    // 辅助函数: 反转链表
    ListNode* reverse(ListNode *head);

    private:
        ListNode *left;
};

#if 0
//递归法求解
bool Solution::isPalindrome(ListNode *head)
{

    if( !head ) return true;

    // left记录头结点位置
    left = head;

    return traverse(head);


}

bool Solution::traverse(ListNode *right)
{

    if( !right ) return true;


    bool res = traverse(right->next);

    //后序遍历的位置, right指向链表最后一个节点

    res = res && (left->val == right->val);
    left = left->next;
    return res;


}
#endif


// 迭代法：较好的解法
bool Solution::isPalindrome(ListNode *head)
{

    if( !head || (head->next == nullptr) ) return true;

    
    ListNode *slow = head, *fast = head;


    // step1 : 快慢指针找出链表的中间节点

    while ( fast && fast->next )
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // fast不为null，则链表个数是奇数，slow还需前进一步指向中心节点
    if(fast)
        slow = slow->next;
    
    //step2 : p指向链表反转[中间节点，尾结点]后的头结点
    ListNode *p = reverse(slow);


    // step3 : 判断是否为回文链表：[头结点, 中间节点] [中间节点, 尾节点]
    ListNode *cur = head;
    
    while( p && cur )
    {
        if( p->val != cur->val )
            return false;

        p = p->next;
        cur = cur->next;

    }


    #if 0
    // 迭代法：普通的解法
    ListNode *cur = head;
    ListNode *p = nullptr;
    // step1 : 求出链表长度，并找出中间节点
    int length = 0;
    while(cur)
    {
        cur = cur->next;
        length++;
    }

    // 遍历找到链表的中间节点, p指向中间节点

    //链表为奇数长度，需要多移动一个位置
    int i = (length % 2) ? (i = 0) : (i = 1);
    
    p = head;

    while( i <= (length / 2) )
    {
        p = p->next;
        i++;    
    }
    
    // step 2 : 反转链表[中间节点, 链表尾的节点]
    cur = reverse(p);   //cur指向反转后的头结点

    // step3 : 判断是否为回文链表：[头结点, 中间节点] [中间节点, 尾节点]
    p = head;
    
    while( p && cur )
    {
        if( p->val != cur->val )
            return false;

        p = p->next;
        cur = cur->next;

    }
    #endif

    return true;


}


//反转头指针head指向的链表
ListNode* Solution::reverse(ListNode *head)
{

    if( !head ) return nullptr;

    ListNode *pre = nullptr, *cur = head, *p = nullptr;
    
    while( p )
    {
        p = cur->next;
        cur->next = pre;

        //更新指针
        pre = cur;
        cur = p;

    }

    // pre指向反转后的链表的头结点，cur和p指向同一位置
    return pre;

}


