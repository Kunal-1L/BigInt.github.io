#include "BigInteger.h" 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





struct BigInt initialize(char *s) {
    struct BigInt num;
    int i = 0;
    num.length = strlen(s);

    struct node *head = NULL;

    if (s[0] == '-') {
        num.sign = -1;
        i = 1;                                      // Skip the negative sign
    } else {
        num.sign = 1;
    }

    while (i < num.length) {
        struct node *temp = malloc(sizeof(struct node));
        temp->data = s[i] - '0';
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
        } else {
            temp->next = head;
            head = temp;
        }

        i++;
    }

    num.list = head;
    if(num.sign==-1)
        num.length--;
    return num;
}


void traverse(struct node *head)
{
    if(!head)
        return;
    traverse(head->next);
    printf("%d",head->data);
}
void display(struct BigInt num)
{
    traverse(num.list);
}

void reverse(struct node** head) {
    struct node* prev = NULL;
    struct node* current = *head;
    struct node* next = NULL;

    while (current != NULL) {
        next = current->next;  // Store the next node
        current->next = prev;  // Change next of current node

        // Move pointers one position ahead
        prev = current;
        current = next;
    }

    *head = prev;  // Update the head to the new start of the reversed list
}


int len(struct node *list)
{
    if(!list)
        return 0;
    return 1+len(list->next);
}

int compare(struct node *n1 , struct node *n2)
{
    int f=-1;
    if(len(n1)<len(n2))
        return 0;
    else if(len(n1)>len(n2))
        return 1;
    else
    {
        while(n2)
        {
            if(n1->data > n2->data)
                f=1;
            else if(n2->data > n1->data)
                f=0;
            n1=n1->next;
            n2=n2->next;
        }
        if(f==1 || f==-1)
            return 1;
        else
            return 0;
            
    }
}


struct node * addNum(struct node *head1, struct node *head2) {
    int carry = 0;
    int val;
    struct node *head = NULL,*itr=0;
    while (head1 || head2) {
        val = carry;
        if (head1) {
            val += head1->data;
            head1 = head1->next;
        }
        if (head2) {
            val += head2->data;
            head2 = head2->next;
        }

        carry = val / 10;
        val = val % 10;

        struct node *temp = malloc(sizeof(struct node));
        temp->data = val;
        temp->next = 0;
        if(!head)
        {
            head=temp;
        }
        else
        {
            itr->next=temp;
        }
        itr=temp;
    }

    if (carry > 0) {
        struct node *temp = malloc(sizeof(struct node));
        temp->data = carry;
        temp->next = 0;
        itr->next=temp;
    }

    return head;
}



struct node * subNum(struct  node *n1,struct node *n2)
{
    int bin=0,val;
    struct node *res=0,*itr=0;
    while(n1 && n2)
    {
        val=bin + n1->data;
        if(val >= n2->data)
        {
            val-=n2->data;
            bin=0;
            
        }
        else
        {
            val+=10-n2->data;
            bin=-1;
        }
        struct node *temp=malloc(sizeof(struct node));
        temp->data=val;
        temp->next=0;
        if(!res)
        {
            res=temp;
        }
        else
        {
            itr->next=temp;
        }
        itr=temp;
        n1=n1->next;
        n2=n2->next;
    }
    while(n1)
    {
        val=bin + n1->data;
        if(val<0){
            val+=10;
            bin=-1;
        }
        else
            bin=0;
        struct node *temp=malloc(sizeof(struct node));
        temp->data=val;
        temp->next=0;
        itr->next=temp;
        itr=temp;
        n1=n1->next;
        
    }
    struct  node * Trailzero=0;
    itr=res;
    while(itr){
        if(itr->data!=0)
            Trailzero=itr;
        itr=itr->next;
    }
    while(Trailzero && Trailzero->next)
    {
        itr=Trailzero->next;
        Trailzero->next=itr->next;
        free(itr);
    }
    
    return res;
}


struct BigInt add(struct BigInt n1, struct BigInt n2) {
    struct BigInt sum;

    if (n1.sign == -1 && n2.sign == -1) {
        sum.sign = -1;
        if (n1.length > n2.length)
            sum.list = addNum(n1.list, n2.list);
        else
            sum.list = addNum(n2.list, n1.list);
    }
    else if (n1.sign == 1 && n2.sign == 1) {
        sum.sign = 1;
        if (n1.length > n2.length)
            sum.list = addNum(n1.list, n2.list);
        else
            sum.list = addNum(n2.list, n1.list);
    }
    else if (n1.sign == -1 && n2.sign == 1) {
        if (n1.length > n2.length) {
            sum.sign = -1;
            sum.list = subNum(n1.list, n2.list);
        }
        else if (n1.length < n2.length) {
            sum.sign = 1;
            sum.list = subNum(n2.list, n1.list);
        }
        else {
            if (compare(n1.list, n2.list)) {
                sum.sign = -1;
                sum.list = subNum(n1.list, n2.list);
            }
            else {
                sum.sign = 1;
                sum.list = subNum(n2.list, n1.list);
            }
        }
    }
    else if (n1.sign == 1 && n2.sign == -1) {
        if (n2.length > n1.length) {
            sum.sign = -1;
            sum.list = subNum(n2.list, n1.list);
        }
        else if (n2.length < n1.length) {
            sum.sign = 1;
            sum.list = subNum(n1.list, n2.list);
        }
        else {
            if (compare(n2.list, n1.list)) {
                sum.sign = -1;
                sum.list = subNum(n2.list, n1.list);
            }
            else {
                sum.sign = 1;
                sum.list = subNum(n1.list, n2.list);
            }
        }
    }

    return sum;
}
struct BigInt mul(struct BigInt num1, struct BigInt num2) {
    struct BigInt ans;
    struct node *n1 = num1.list, *n2 = num2.list, *res = NULL, *ptr = NULL, *prev = NULL,*current;
    int carry = 0, val;

    while (n1) {
        struct node *temp = malloc(sizeof(struct node));
        temp->next = NULL;
        temp->data = 0;
        val = (temp->data + n1->data * n2->data + carry);
        carry = val / 10;
        temp->data = val % 10;
        n1 = n1->next;
        if (!res) {
            res = temp;
            ptr = res;
        } else {
            ptr->next = temp;
            ptr = ptr->next;
        }
        prev = temp;
    }

    if (carry) {
        struct node *temp = malloc(sizeof(struct node));
        temp->data = carry;
        temp->next = NULL;
        prev->next = temp;
    }

    n2 = n2->next;
    ptr = res->next;

    while (n2) {
        carry = 0;
        current = ptr;
        n1 = num1.list;

        while (n1) {
            if (!current) {
                current = malloc(sizeof(struct node));
                current->next = NULL;
                current->data = 0;
                prev->next = current;
            }

            val = (current->data + n1->data * n2->data + carry);
            carry = val / 10;
            current->data = val % 10;

            n1 = n1->next;
            prev = current;
            current = current->next;
        }

        if (carry) {
            if (!current) {
                current = malloc(sizeof(struct node));
                current->next = NULL;
                current->data = 0;
                prev->next = current;
            }
            current->data += carry;
        }

        n2 = n2->next;
        ptr = ptr->next;
    }

    ans.list = res;
    return ans;
}

struct BigInt sub(struct BigInt n1, struct BigInt n2) {
    struct BigInt sum;

    if (n1.sign == -1 && n2.sign == +1) {
        sum.sign = -1;
        if (n1.length > n2.length)
            sum.list = addNum(n1.list, n2.list);
        else
            sum.list = addNum(n2.list, n1.list);
    }
    else if (n1.sign == 1 && n2.sign == -1) {
        sum.sign = 1;
        if (n1.length > n2.length)
            sum.list = addNum(n1.list, n2.list);
        else
            sum.list = addNum(n2.list, n1.list);
    }
    else if (n1.sign == -1 && n2.sign == -1) {
        if (n1.length > n2.length) {
            sum.sign = -1;
            sum.list = subNum(n1.list, n2.list);
        }
        else if (n1.length < n2.length) {
            sum.sign = 1;
            sum.list = subNum(n2.list, n1.list);
        }
        else {
            if (compare(n1.list, n2.list)) {
                sum.sign = -1;
                sum.list = subNum(n1.list, n2.list);
            }
            else {
                sum.sign = 1;
                sum.list = subNum(n2.list, n1.list);
            }
        }
    }
    else if (n1.sign == 1 && n2.sign == 1) {
        if (n2.length > n1.length) {
            sum.sign = -1;
            sum.list = subNum(n2.list, n1.list);
        }
        else if (n2.length < n1.length) {
            sum.sign = 1;
            sum.list = subNum(n1.list, n2.list);
        }
        else {
            if (compare(n2.list, n1.list)) {
                sum.sign = -1;
                sum.list = subNum(n2.list, n1.list);
            }
            else {
                sum.sign = 1;
                sum.list = subNum(n1.list, n2.list);
            }
        }
    }

    return sum;
}

struct BigInt divide(struct BigInt num1,struct BigInt num2)
{
    struct node *res,*add;
    res=malloc(sizeof(struct node));
    add=malloc(sizeof(struct node));
    res->data=0;
    res->next=0;
    add->data=1;
    add->next=0;
    struct node *itr1=num1.list;
    struct node *itr2=num2.list;
    while(compare(itr1,itr2))
    {
        res=addNum(res,add);
        reverse(&res);
        itr2=addNum(itr2,num2.list);
        reverse(&itr2);
    }
    struct BigInt quotient;
    reverse(&res);
    quotient.list=res;
    quotient.sign=1;
    return quotient;
}


