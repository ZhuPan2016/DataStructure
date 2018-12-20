#include <iostream>
using namespace std;
typedef struct poly* PtrToPoly;
struct poly{
    int coef;
    int exp;
    PtrToPoly next;
};
typedef PtrToPoly Polynomial;

void Attach(int c, int e, Polynomial &rear){
    Polynomial s = (Polynomial)malloc(sizeof(struct poly));
    s->coef = c;
    s->exp = e;
    s->next = nullptr;
    rear->next=s;
    rear = s;
}


Polynomial readPolynomial(){
    Polynomial rear, p, t;
    int c,e,N;
    cin>>N;
    p=(Polynomial)malloc(sizeof(struct poly));
    p->next = nullptr;
    rear = p;
    while(N--){
        cin>>c>>e;
        Attach(c,e,rear);
    }
    t=p;
    p=p->next;
    free(t);
    return p;
}

Polynomial Add(Polynomial p1, Polynomial p2){
    Polynomial t1 = p1;
    Polynomial t2 = p2;
    Polynomial p = (Polynomial)malloc(sizeof(struct poly));
    p->next = NULL;
    Polynomial rear = p;
    Polynomial t;
    while(t1 && t2){
        if(t1->exp>t2->exp){
            Attach(t1->coef,t1->exp,rear);
            t1=t1->next;
        }
        else if(t1->exp<t2->exp){
            Attach(t2->coef,t2->exp,rear);
            t2 = t2->next;
        }
        else{
            Attach(t1->coef+t2->coef,t1->exp,rear);
            t1 = t1->next;
            t2 = t2->next;
        }
    }
    while(t1){
        Attach(t1->coef,t1->exp,rear);
        t1 = t1->next;
    }
    while(t2){
        Attach(t2->coef,t2->exp,rear);//如果错写为t1，是会出问题的！t1是null了
        t2 = t2->next;
    }
    t=p;
    p = p->next;
    free(t);
    return p;
}
Polynomial subMulti(int c,int e,Polynomial p){//将第一个多项式中的某一项与第二个多项式的每一项相乘
    Polynomial tt,rear;
    Polynomial t = (Polynomial) malloc(sizeof(struct poly));
    t->next = NULL;
    rear = t;//zhicuo
    while(p){
        Attach(c*p->coef, e+p->exp, rear);
        p = p->next;
    }
    tt = t;
    t = t->next;
    free(tt);
    return t;
}
Polynomial Multi(Polynomial p1, Polynomial p2){
    Polynomial t1,t2 ,p , result;
    t1 = p1;
    t2 = p2;
    result = (Polynomial)malloc(sizeof(struct poly));//务必要初始化，否则result指针会指向主函数中的变量，最终产生意外
    result->coef = 0;
    result->exp = 0;
    result->next = NULL;
    while(t1){
        p = subMulti(t1->coef, t1->exp,t2);//t1写错t2
        result = Add(result,p);
        t1 = t1->next;
    }
    return result;
}
int main() {
    Polynomial p1 = readPolynomial();
    Polynomial p2 = readPolynomial();
    Polynomial p = Add(p1,p2);
    Polynomial pp = Multi(p1,p2);
    while(p){
        cout<<p->coef<<" "<<p->exp<<" ";
        p=p->next;
    }
    cout<<endl;
    while(pp){
        cout<<pp->coef<<" "<<pp->exp<<" ";
        pp=pp->next;
    }
    return 0;
}
