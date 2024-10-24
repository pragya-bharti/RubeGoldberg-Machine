#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//STRUCTURE CREATION


//structure for node used in Queues and Linked List
struct node{
  char lname[30];
  char fname[30];
  char age[5];
  char dob[15];
  struct node *next;
}*front1=NULL,*rear1=NULL,*front2=NULL,*rear2=NULL,*top=NULL, *first=NULL,*last=NULL;

//structure for node used in the Tree
struct node_tree{
	struct node_tree *lchild;
	struct node *data;
	struct node_tree *rchild;
}*root=NULL;

//structure for node used in Queue whose element points on a node of the tree(Lets call this "queue_tq")
struct node_tree_queue{
	struct node_tree *p;
	struct node_tree_queue *next;
}*front_tq=NULL,*rear_tq=NULL;


int n=0;  //global declaration to keep count of number of nodes created and enqueued.


//QUEUES AND STACK



//enqueues a node into first queue
void enqueue1(struct node *t){
  if(front1==NULL){
    front1=rear1=t;
  }
  else{
    rear1->next=t;
    rear1=t;
  }
}

//dequeues a node from first queue
struct node * dequeue1(){
  struct node *t;
  int x=0;
  if(front1==NULL)
    x++;
  else{
    t=front1;
    front1=front1->next;
  }
  return t;
}

//enqueues a node into second queue
void enqueue2(struct node *t){
  if(front2==NULL){
    front2=rear2=t;
  }
  else{
    rear2->next=t;
    rear2=t;
  }
}

//dequeues a node into second queue
struct node * dequeue2(){
  struct node *t;
  int x=0;
  if(front2==NULL)
    x++;
  else{
    t=front2;
    front2=front2->next;
  }
  return t;
}

//pushes node into stack
void push(struct node *t){	
	t->next=top;
	top=t;
}

//pops the top of stack
struct node * pop(){
	struct node * t;
	t=top;
	top=top->next;
	return t;
}

//reverses the queue
void reverse_q(){
	while(front2){                                           //the loop runs until second queue is empty
		push(dequeue2());                                      //dequeue2() function returns node from front of the queue, and the node gets pushed into stack
	}
	while(top){																						   //the loop runs until stack is empty
		enqueue1(pop());                                       //pop() function returns node from top of the stack, and the node is enqueued into queue
	}
}

//prints first queue
void display_q1(){
  while(front1){
    struct node *t=dequeue1();                                         //dequeues node from first queue
		printf("%s %s %s %s\n", t->fname, t->lname, t->age, t->dob);       //prints contents of the node
    enqueue2(t);																											 //enqueues node into second queue
  }
}

void display_q2(){
  while(front2){
    struct node *t=dequeue2();                                         //dequeues node from first queue
		printf("%s %s %s %s\n", t->fname, t->lname, t->age, t->dob);       //prints contents of the node
    enqueue1(t);																										   //enqueues node into second queue
  }
}



//TREE CREATION USING QUEUE



//this function enqueues into "queue_tq" i.e it makes its element point on a node of the tree created
void enqueue_tq(struct node_tree *x){

  struct node_tree_queue *t=(struct node_tree_queue*)malloc(sizeof(struct node_tree_queue));
	t->p=x;
	t->next=NULL;
	if(front_tq==NULL){
    front_tq=rear_tq=t;
  }
  else{
    rear_tq->next=t;
    rear_tq=t;
  }
}
//this function dequeues the "queue_tq" and returns the front node
struct node_tree * dequeue_tq(){
  struct node_tree_queue *t;
  if(front_tq==NULL)
    printf("Queue is Empty\n");
  else{
    t=front_tq;
    front_tq=front_tq->next;
  }
  return t->p;
}

//this function is used to create a binary tree, adhering to binary tree shape property
void CreateTree(){
  struct node_tree *m,*t;

  root=(struct node_tree*)malloc(sizeof(struct node_tree));  //allocate space
  root->data=NULL;                                      
  root->data=dequeue2();                                     //makes root->data point on the node returned by dequeue2() function
  root->lchild=root->rchild=NULL;                       
  enqueue_tq(root);                                          //makes the first element of "queue_tq" point on root node
  int x=n;																                   //initializing x to value n (i.e the total number of nodes in queue)
  while(x--){																					       //so that for every node in the initial queue a node in tree is created
		m=dequeue_tq();																	      	 //dequeue_tq() dequeues "queue_tq" and returns a pointer to a tree node
		
    t=(struct node_tree*)malloc(sizeof(struct node_tree));   //left child of that node is created (space allocated)
		t->data=NULL;
		t->data=dequeue2();																			 //makes t->data point on the node returned by dequeue2() function
		t->lchild=t->rchild=NULL;																 //t->lchild and t->rchild are initialized to NULL
		m->lchild=t;																						 //t is made the left child of node m
 		enqueue_tq(t);                                           //node t is enqueued into "queue_tq"
		
		t=(struct node_tree*)malloc(sizeof(struct node_tree));   //right child of that node is created (space allocated)
		t->data=NULL;
	  t->data=dequeue2();																			 //makes t->data point on the node returned by dequeue2() function
	  t->lchild=t->rchild=NULL;																 //t->lchild and t->rchild are initialized to NULL
	  m->rchild=t;                                             //t is made the left child of node m
	  enqueue_tq(t);																					 //node t is enqueued into "queue_tq"
  }
}

//this function deletes the nodes in the tree and returns pointer to a node
struct node * delete_tree_node(struct node_tree * t){
	struct node *n;
	n=t->data;
	t->data=NULL;
	
	return n;
}

//this function recursively prints the tree in preorder
void preorder(struct node_tree * t){
	if(t->rchild!=NULL){
		printf("%s %s %s %s\n", t->data->fname, t->data->lname, t->data->age, t->data->dob);
		preorder(t->lchild);
		preorder(t->rchild);
	}
}

//this function recursively prints the tree in postorder
void postorder(struct node_tree * t){
	if(t->rchild!=NULL){
		postorder(t->lchild);
		postorder(t->rchild);
		printf("%s %s %s %s\n", t->data->fname, t->data->lname, t->data->age, t->data->dob);
	}
}


//------------------------------------------------------------LINKED LIST CREATION----------------------------------------------------------------------



//creates Linked List from existing nodes (refer inorder() function)
void CreateLL(struct node *p){
  struct node *t;
	t=p;
	t->next=NULL;
  if(first==NULL){
  	first=last=t;
	}
  else{
  	last->next=t;
  	last=t;
	}
}

//displays Linked List
void display_LL(){
	struct node *p=first;
	while(p){
		printf("%s %s %s %s\n", p->fname, p->lname, p->age, p->dob);
		p=p->next;
	}
}

//this function creates a linked list in an inorder way, recursively!
void inorder(struct node_tree * t){
	if(t->rchild!=NULL){
		inorder(t->lchild);
		CreateLL(delete_tree_node(t));
		inorder(t->rchild);	
	}
}


//SORTING THE LINKED LIST(QUICKSORT)



//returns the last node of the list 
struct node *getTail(struct node *cur) 
{ 
    while (cur != NULL && cur->next != NULL) 
        cur = cur->next; 
    return cur; 
} 
  
//partitions the list taking the last element as the pivot 
struct node *partition(struct node *head, struct node *end, struct node **newHead, struct node **newEnd){
 
  struct node *pivot = end; 
  struct node *prev = NULL, *cur = head, *tail = pivot; 
  
  //during partition, both the head and end of the list might change which is updated in the newHead and newEnd variables
  while (cur != pivot) { 
    if(strcmp(pivot->age,cur->age)>0){ 
      
      if ((*newHead) == NULL)                                         //first node that has a value less than the pivot - becomes the new head 
        (*newHead) = cur; 
  
        prev = cur;  
        cur = cur->next; 
    }
		//if cur node is greater than pivot
    else{ 
      //move cur node to next of tail, and change tail 
      if (prev) 
        prev->next = cur->next; 
      struct node *tmp = cur->next; 
      cur->next = NULL; 
      tail->next = cur; 
      tail = cur; 
      cur = tmp; 
    } 
  } 
  
  //if the pivot data is the smallest element in the current list,  pivot becomes the head
  if ((*newHead) == NULL) 
    (*newHead) = pivot; 
  
  //update newEnd to the current last node 
  (*newEnd) = tail; 
  
  //return the pivot node 
  return pivot; 
} 
  
  
//here the sorting happens exclusive of the end node 
struct node *quickSortRecur(struct node *head, struct node *end) 
{ 
  // base condition 
  if (!head || head == end) 
    return head; 
  
  struct node *newHead = NULL, *newEnd = NULL; 
  
  // Partition the list, newHead and newEnd will be updated 
  // by the partition function 
  struct node *pivot = partition(head, end, &newHead, &newEnd); 
  
  // If pivot is the smallest element - no need to recur for 
  // the left part. 
  if (newHead != pivot) { 
    // Set the node before the pivot node as NULL 
    struct node *tmp = newHead; 
    while (tmp->next != pivot) 
      tmp = tmp->next; 
    tmp->next = NULL; 
  
    //recur for the list before pivot 
    newHead = quickSortRecur(newHead, tmp); 
  
    //change next of last node of the left half to pivot 
    tmp = getTail(newHead); 
    tmp->next = pivot; 
  } 
  
  //recur for the list after the pivot element 
  pivot->next = quickSortRecur(pivot->next, newEnd); 
  
  return newHead; 
} 
  
// this function is the main function for quick sort. This is a wrapper over recursive function quickSortRecur()
void quickSort(struct node **headRef) 
{ 
  (*headRef) = quickSortRecur(*headRef, getTail(*headRef)); 
  return; 
} 


//SORTED INSERT(LINKED LIST)



//this function is used create and insert a node into sorted Linked List
void insert(){
	struct node *q=NULL,*p=first;
	struct node *t=(struct node*)malloc(sizeof(struct node));
	
	// fscanf(stdin,"%s %s %s %s",t->fname,t->lname,t->age,t->dob);
	t->next=NULL;
	
	if(strcmp(t->age,first->age)<0){                          //comparision returns true if the data in node is smaller than data in first node
		t->next=first;
		first=t;
	}
	else{
		while(strcmp(t->age,p->age)>0 && p){                   //the loop runs until data in node becomes greater than data in a node of linked list
			q=p;																								 //q tails the pointer p
		  p=p->next;
		}
	  //when the loop stops p points on the node that has greater value, so we take q which is still smaller
		t->next=q->next;
		q->next=t;
  }
}



//DRIVER FUNCTION



//the driver function to call all other functions
int main()
{
	
  FILE* ptr = fopen("sample.txt","r");                               //opens file in read mode
  
  if(ptr==NULL){
  	printf("NO SUCH FILE FOUND!\n");
  	return 0;
	}
	while(!feof(ptr)){                                                //loop runs until End Of File is reached
		struct node *t= (struct node*)malloc(sizeof(struct node));     //creates node
		
    // fscanf(ptr,"%s %s %s %s",t->fname,t->lname,t->age,t->dob);      //takes input from the file

		t->next=NULL;

		enqueue1(t);                                                    //enqueues node into first queue
		n++;                                                            //increments n to keep a count of nodes
	}
  fclose(ptr);                                                      //file is closed
  
  printf("QUEUE");
  printf("\n________________________________________________________\n\n");
	display_q1();
	
	
	printf("\nPress any key to continue.\n\n");
	
	getch();
	
	printf("REVERSED QUEUE");
	printf("\n________________________________________________________\n\n");	

  reverse_q();
  display_q1();
  
	printf("\nPress any key to continue.\n\n");
	
	getch();
	
	printf("PREORDER DISPLAY OF TREE");
	printf("\n________________________________________________________\n\n");
	
	CreateTree();
	preorder(root);
	
	printf("\nPress any key to continue.\n\n");
	
	getch();
	
	printf("POSTORDER DISPLAY OF TREE");
	printf("\n________________________________________________________\n\n");
	
	postorder(root);
	

	printf("\nPress any key to continue.\n\n");
	getch();
	printf("INORDER CONVERSION OF TREE INTO LINKED LIST");
	printf("\n________________________________________________________\n\n");
	
  inorder(root);
  display_LL();
  
  printf("\nPress any key to continue.\n\n");
	getch();
	printf("LINKED LIST AFTER QUICK SORT (sorted by age*)");
	printf("\n________________________________________________________\n\n");
	
	quickSort(&first);
	display_LL();
	
  printf("\nPress any key to continue.\n\n");
	getch();
	printf("Enter value for insertion!!!\n\nThe values entered should be in the format\nMallika David, 49, 1960\nJames Bond, 05, 1960\n\n");
	printf("Make sure the age is double digit followed by a comma!\n\n");
	
	insert();
	
	printf("\n\nLINKED LIST AFTER INSERTION");
	printf("\n________________________________________________________\n\n");
	
	display_LL();
	
	printf("\n\n\n----------The program has ended!!!----------\n\n                THANK YOU!\n\n\n\n");
	
	getch();
  return 0;
}
