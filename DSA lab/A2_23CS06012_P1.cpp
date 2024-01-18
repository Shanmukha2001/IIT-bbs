#include <bits/stdc++.h>

using namespace std;

struct node
{
    int data;
    struct node *next;
};

void sortListWithDuplicates(int a[],int n1, struct node *&head)
{
    struct node *n, *tempHead;
    head = new node;
    head->data = a[0];
    head->next = NULL;
    tempHead = head;
    for (int i = 1; i < n1; i++)
    {
        n = new node;
        n->data = a[i];
        if (head->data >= a[i])
        {
            n->next = head;
            head = n;
        }
        else
        {
            tempHead = head;
            while (tempHead->next != NULL && tempHead->next->data < a[i])
            {
                tempHead = tempHead->next;
            }
            n->next = tempHead->next;
            tempHead->next = n;
        }
    }
}

void removeDuplicates(struct node *head)
{
    struct node *tempCurr = head;
    struct node *tempNext = head->next;
    while (tempNext != NULL)
    {
        if (tempCurr->data == tempNext->data)
        {
            tempNext = tempNext->next;
        }
        tempCurr->next = tempNext;
        tempCurr = tempCurr->next;
        if (tempNext != NULL)
        {
            tempNext = tempNext->next;
        }
    }
}

void reverseList(struct node *&head, int k)
{
    if(k == 1) return;
    struct node* prev = NULL;
    struct node* curr = head;
    struct node* nxt = curr->next;
    
    while((k--)>0 && curr!=NULL){
        curr->next = prev;
        prev = curr;
        curr = nxt;
        nxt = nxt->next;
    }
    head->next = curr;
    head = prev;
}

void printList(struct node *head)
{
    while (head != nullptr)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    // int n = 10, k;
    // int a[10] = {8, 7, 1, 1, 8, 9, 6, 3, 2, 4};
    int n,k;
    cout <<"n:";
    cin >>n;
    int a[n];
    for(int i=0;i<n;i++)
        cin >> a[i];
    struct node *head = NULL;
    cout <<"k:";
    cin >> k;
    sortListWithDuplicates(a,n, head);
    printList(head);
    removeDuplicates(head);
    printList(head);
    reverseList(head, k);    
    printList(head);
    return 0;
}