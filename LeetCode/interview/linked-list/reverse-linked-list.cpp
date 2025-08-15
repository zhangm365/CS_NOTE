
/*

单链表：
1, 2, 3, 4, 5

每两个节点进行翻转: 2, 1, 4, 3, 5
*/

struct Node {
    int value;
    struct Node *next;
    Node(int val) : value(val), next(nullptr) {}

};

Node* reverse(Node* head) {

    if (!head || !head->next) {
        return head;
    }

    // 虚拟头节点
    Node* dummy = new Node(-1);
    dummy->next = head;

    // 遍历
    Node *pre = dummy, *cur = head;

    while (cur && cur->next) {
        Node *p = cur;
        Node *pn = cur->next;

        // 
        pre->next = pn;
        p->next = pn->next;
        pn->next = p;
        
        pre = p;
        cur = p->next;
    }

    return dummy->next;
}



