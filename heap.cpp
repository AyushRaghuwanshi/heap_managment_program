#include<iostream>
using namespace std;


typedef struct Node{
    int size,sa,ea;
    struct Node *next;
}Node; 



Node *for_nf;

Node* createFreeList(){

    int size=rand()%500+1;
    int sa=0;
    int ea=sa+size;
    Node *start,*current;
    current=new Node();
    current->size=size;
    current->sa=sa;
    current->ea=size+sa;
    current->next=NULL;
    start=current;
    for(int i=1;i<10;i++){
        Node *temp;
        temp=new Node();
        temp->size=rand()%500+1;
        temp->sa=current->ea+rand()%50+1;
        temp->ea=temp->sa+temp->size;
        temp->next=NULL;
        current->next=temp;
        current=current->next;
    }
    return start;

}

// first fit implemantation
Node* malloc_ff(int n,Node **allocated_head,Node *free_list){
    Node *temp=free_list;
    while(temp!=NULL){
        if(temp->size>n){
            break;
        }
        temp=temp->next;
    }
    if(temp==NULL){
        cout<<"\nno block found";
        return *allocated_head;
    }
    else{
        Node *newNode=new Node();
        newNode->sa=temp->sa;
        newNode->size=n;
        newNode->ea=newNode->size+newNode->sa;
        newNode->next=NULL;
        temp->sa=temp->sa+n;
        temp->size=temp->size-n;
        if(*allocated_head==NULL){
            *allocated_head=newNode;
            return newNode;
        }
        else{
            newNode->next=*allocated_head;
            *allocated_head=newNode;
            return newNode;
        }
    }
}



//best fit
Node *malloc_bf(int n,Node **allocated_head,Node *free_list){
    Node *temp=free_list;
    int ssize;
    Node *short_size=NULL;
    while(temp!=NULL){
        if(short_size==NULL){
            if(temp->size>=n){
                short_size=temp;
                ssize=temp->size;
            }
        }
        else{
            if(temp->size<ssize&&temp->size>=n){
                short_size=temp;
                ssize=temp->size;
            }                 

        }
        temp=temp->next;
    }
    if(short_size==NULL){
        cout<<"\nno block found";
        return *allocated_head;
    }
    else{
        Node *newNode=new Node();
        newNode->sa=short_size->sa;
        newNode->size=n;
        newNode->ea=newNode->size+newNode->sa;
        newNode->next=NULL;
        short_size->sa=short_size->sa+n;
        short_size->size=short_size->size-n;
        if(*allocated_head==NULL){
            *allocated_head=newNode;
            return newNode;
        }
        else{
            newNode->next=*allocated_head;
            *allocated_head=newNode;
            return newNode;
        }
    }
}



//next fit 
Node* malloc_nf(int n,Node **allocated_head,Node *free_list){
    int counter=1;
    while(for_nf!=NULL){
        if(for_nf->size>n){
            break;
        }
        if(for_nf->next==NULL&&counter==1){
            for_nf=free_list;
            counter=0;
        }

        for_nf=for_nf->next;
    }
    if(for_nf==NULL){
        cout<<"\nno block found";
        return *allocated_head;
    }
    else{
        Node *newNode=new Node();
        newNode->sa=for_nf->sa;
        newNode->size=n;
        newNode->ea=newNode->size+newNode->sa;
        newNode->next=NULL;
        for_nf->sa=for_nf->sa+n;
        for_nf->size=for_nf->size-n;
        if(*allocated_head==NULL){
            *allocated_head=newNode;
            return newNode;
        }
        else{
            newNode->next=*allocated_head;
            *allocated_head=newNode;
            return newNode;
        }
    }
}



void removee(Node **s,Node *x){
    
   	 	Node *temp=*s;
        if(temp->ea==x->ea&&temp->size==x->size&&temp->sa==x->sa){
            *s=temp->next;
            //free(temp);
        }
        else{Node *pre=temp;
            while(!(temp->ea==x->ea&&temp->size==x->size&&temp->sa==x->sa)){
                pre=temp;
                temp=temp->next;
            }
            pre->next=temp->next;
           // free(temp);

        }
	
   	
}


void add(Node **s,Node *x){
    Node *temp=*s;
    if(temp->sa>=x->ea){
        if(temp->sa==x->ea){
            
            temp->sa=x->sa;
            temp->size=temp->size+x->size;
        }
        else{
            x->next=*s;
            *s=x;
        }
        
    }
    else{Node *pre=temp;
        //cout<<"\njhdsiahi";
        while((true)){
        if(temp->sa>=x->ea){
            //cout<<"\n gihojo";
            cout<<temp->ea;
            break;
        }
        pre=temp;
        temp=temp->next;
        }
        if(pre->ea==x->sa){
            //cout<<"\nlololo";
            pre->ea=x->ea;
            pre->size=pre->size+x->size;
        }
        else if (temp->sa==x->ea){
            //cout<<"\nhohohoho";
            temp->sa=x->sa;
            temp->size=temp->size+x->size;
        }
        
         else{
            x->next=temp->next;
            temp=x;
        }
        
    }
}


void freee(Node **b,Node **allocated_head,Node **free_list){
    removee(allocated_head,*b);
    
    add(free_list,*b);
    //free(b);
    *b=NULL;
}


void printList(Node *start){
    cout<<"\n";
    while(start!=NULL){
         cout<< "size="<<start->size<<"sa="<<start->sa<<"ea"<<start->ea<<"--->";
         start=start->next;
    }
    
}


int main(){

    /*Node *free_head,*allocated_head=NULL;
    free_head=createFreeList(); 
    printList(free_head);
    Node *b1=malloc_ff(400,&allocated_head,free_head);
    Node *b2=malloc_ff(100,&allocated_head,free_head);
    Node *b3=malloc_ff(300,&allocated_head,free_head);
    Node *b4=malloc_ff(600,&allocated_head,free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);
    freee(&b1,&allocated_head,&free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);*/
    
    
    /*Node *free_head,*allocated_head=NULL;
    free_head=createFreeList(); 
    printList(free_head);
    Node *b1=malloc_ff(100,&allocated_head,free_head);
    Node *b2=malloc_ff(100,&allocated_head,free_head);
    Node *b3=malloc_ff(300,&allocated_head,free_head);
    Node *b4=malloc_ff(600,&allocated_head,free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);
    freee(&b1,&allocated_head,&free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);*/
    
    Node *free_head,*allocated_head=NULL;
    free_head=createFreeList(); 
    printList(free_head);
    Node *b1=malloc_bf(400,&allocated_head,free_head);
    Node *b2=malloc_bf(100,&allocated_head,free_head);
    Node *b3=malloc_bf(300,&allocated_head,free_head);
    Node *b4=malloc_bf(600,&allocated_head,free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);
    freee(&b2,&allocated_head,&free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);

   /* Node *free_head,*allocated_head=NULL;
    free_head=createFreeList(); 
    for_nf=free_head;
    printList(free_head);
    Node *b1=malloc_nf(400,&allocated_head,free_head);
    Node *b2=malloc_nf(100,&allocated_head,free_head);
    Node *b3=malloc_nf(300,&allocated_head,free_head);
    Node *b4=malloc_nf(600,&allocated_head,free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);
    freee(&b2,&allocated_head,&free_head);
    cout<<"\n\n\nfree list=";
    printList(free_head);
    cout<<"\n\n\nallocated list=";
    printList(allocated_head);*/
    

}
