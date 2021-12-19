
#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

ListNode* mergeTwoLists( ListNode *l1, ListNode *l2 )
{
    if( !l1 ) return l2;
    if( !l2 ) return l1;
    ListNode *newHead = new ListNode(0);    // 头节点
    ListNode *p = l1, *q = l2;
    ListNode *r = newHead;
    while( p && q )
    {
        if( p->val > q->val )
        {
            r->next = q;
            q = q->next;
        }
        else
        {
            r->next = p;
            p = p->next;
        }
        r = r->next;
    }
    if(p) r->next = p;
    if(q) r->next = q;
    return newHead->next;
}

ListNode* creatList( const vector<int> &vec )
{
    int n = vec.size();
    if( n <= 0 ) return nullptr;

    ListNode *head = nullptr;
    head = new ListNode(vec[0]);
    ListNode *p = head;
    for( int i = 1; i < n; ++i )
    {
        ListNode *node = new ListNode(vec[i]);
        p->next = node;
        p = node;
        delete node;

    }
    return head;
}


void printList( ListNode *head )
{
    
    ListNode *p = head;
    while( p )
    {
        
        cout << p->val << " ";
        p = p->next;

    }

}


int main()
{

    vector<int> v1 = {1, 2, 5, 7, 9};
    vector<int> v2 = {2, 4, 6, 8, 10};

    ListNode *h1 = creatList(v1);
    ListNode *h2 = creatList(v2);

    ListNode *ret = mergeTwoLists(h1, h2);

    printList(ret);

    return 0;
}

