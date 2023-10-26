#ifndef BigInteger_h
#define BigInteger_h

struct BigInt{
    struct node *list;
    int  length;
    int sign;
};

struct node{
    int data;
    struct node *next;
};

struct BigInt initialize(char *);
void display(struct BigInt );
void reverse(struct node **);
int len(struct node *);
int compare(struct node* , struct node* );
struct node * addNum(struct node *, struct node *) ;
struct node * subNum(struct  node *,struct node *);
struct BigInt add(struct BigInt , struct BigInt );
struct BigInt mul(struct BigInt , struct BigInt ) ;
struct BigInt sub(struct BigInt , struct BigInt );
struct BigInt divide(struct BigInt ,struct BigInt );
#endif // BigInt.h
