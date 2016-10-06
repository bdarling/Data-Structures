/*	List
	A simple doubly linked list.
	Written by Bailey Darling
		September 2016

	List has a front, back, and current (curr)

	index indicates where curr is.
	if index is -1, its undefined
	0 is front
	length-1 is back

	length()		returns length
	index()			returns index value
	front()			returns front data
	back()			returns back data
	get()			returns curr's data

	clear:			clears the list
	moveFront:		moves curr to front
	moveBack:		moves curr to back
	moveNext:		moves curr forward one
	movePrev:		moves curr back one

	prepend:		appends to front of the list
	append:			appends to back of the list
	insertBefore:	appends before curr
	insertAfter:	appends after curr

	delete:			deletes current
	deleteFront:	deletes the front node
	deleteBack:		deletes the rear node

	equals			returns true if two lists are identical
	isEmpty			returns true if empty

	Copy 			copies this into a new list
	toString		overloads standard toString


*/

	#include <stdio.h>
	#include <stdlib.h>
	#include "List.h"

////////////////////////Structs///////////////////////////////////

	//Node struct
typedef struct NodeObj{
		int data;
		struct NodeObj* next;		//pointers for connecting nodes
		struct NodeObj* prev;

	}NodeObj;

	typedef NodeObj* Node;			//Initialize

typedef struct ListObj{
	Node front;
	Node back;
	Node curr;
	int length;
	int index;
}ListObj;

Node newNode(int data){
	Node N= malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;

		return(N);
	}

	void freeNode(Node* pN){
		if(pN!=NULL && *pN != NULL){
			free(*pN);
			*pN= NULL;
		}
	}

//Creates a new List

List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front= L->back = NULL;
	L->length = 0;
	L->index = -1;
	L->curr = NULL;

	return L; 
}

// Helper function that Frees a List //

void freeList(List* L){
	if(L!= NULL && *L!=NULL){
		while(length(*L)!=0){
			deleteFront(*L);
		}
		clear(*L);
		free(*L);
		*L= NULL;
	}
}


// --------------------- Access Functions -----------------------//

int length(List L){
	if(L==NULL){
		printf("ERROR: Cannot get length for a NULL reference\n");
		exit(1);
	}
	return (L->length);
}

int index(List L){
	if(L==NULL){
		printf("ERROR: Cannot get index of a NULL reference\n");
		exit(1);
	}
	return(L->index);
}

int front(List L){
	if(L==NULL){
		printf("ERROR: Cannot get front of a NULL reference\n");
		exit(1);
	}
	return(L->front->data);
}

int back(List L){
	if(L==NULL){
		printf("ERROR: Cannot get back of a NULL reference\n");
		exit(1);
	}
	return(L->back->data);
}

int get(List L){
	if(L==NULL){
		printf("ERROR: Cannot get from a NULL reference\n");
		exit(1);
	}else if(L->index == -1){
		printf("ERROR: Cursor is off the list\n");
		return -1;
	}else{
		return L->curr->data;
	}
}

int equals(List A, List B){
	//Returns true only if A and B are equal

	if(A == NULL || B == NULL){
		printf("ERROR: called equals() on a NULL reference\n");
	}
	Node N = NULL;
	Node M = NULL;
	int flag = 0;
	flag = (A->length == B->length);

	N = A->front;
	M = B->front;

	while(flag && N!=NULL){
		flag = N->data == M->data;
		N = N->next;
		M = M->next;
	}
	return flag;
}

// --------------------- Manipulation Functions ------------------------//

void clear(List L){				// helper fn, clears a list.
	if(L->front == NULL) return;

	Node tmp1 = L->front;
	Node tmp2;

	while(tmp1!= NULL){
		tmp2= tmp1->next;
		free(tmp1);
		tmp1=tmp2;
	}

	L->front = L->back = L->curr = NULL;
	L->length = 0;
	L->index = -1;
}

void moveFront(List L){				// curr = front
	if(L->length != 0){
		L->curr = L->front;
		L->index = 0;
	}
}

void moveBack(List L){				// curr = back
	if(L->length != 0){
		L->curr = L->back;
		L->index = L->length-1;
	}
}

void movePrev(List L){				// decrements curr
	if(index(L)== -1) return;
	if(length(L) >= 0){
		if(length(L)==0){
			L->curr = NULL;
			L->index= -1;
			return;
		}
		L->curr = L->curr->prev;
		L->index--;
	}
}

void moveNext(List L){				//increments curr
	if(L->length != 0){
		if(L->index == length(L)-1){
			L->curr = NULL;
			L->index = -1;
		}
		else{
			L->curr = L->curr->next;
			L->index++;
		}
	}
}

void prepend(List L, int data){		//Appends to the beginning of the list
	Node N = newNode(data);
	if(L->length==0){
		L->front= L->back = N;
	}else{
		N->next= L->front;
		L->front->prev = N;
		L->front= N;
	}
	L->length++;
}

void append(List L, int data){		//Appends to the end of the list
	Node N = newNode(data);
	if(L->length==0){
		L->front=L->back=N;
	}else{
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
}

void insertBefore(List L, int data){ //inserts before curr
	Node N= newNode(data);
	if(L->length==0){
		L->front=L->back=N;
	}else if(L->index == -1 || L->curr->prev == NULL){
		printf("ERROR: Cursor undefined\n");
		return;
	}else{
		L->curr->prev->next = N;
		N->next = L->curr;
		N->prev = L->curr->prev;
		L->curr->prev = N;
		L->index++;
	}
	L->length++;
}

void insertAfter(List L, int data){
	Node N = newNode(data);
	if(L->length==0){
		L->front=L->back=N;
	}else if(L->index == -1 || L->curr->prev == NULL){
		printf("ERROR: Cursor undefined\n");
		return;
	}else{
		L->curr->next->prev = N;
		N->next = L->curr->next;
		N->prev = L->curr;
		L->curr->next = N;
	}
	L->length++;
}

void deleteFront(List L){


    if(L->length==0){
        printf("Error: cannot call a delete function on an empty List");
        exit(1);
    }
    Node N = NULL;
    N=L->front;
    if(L->length>1){
        L->front = L->front->next;
        L->front->prev = NULL;
    }else{
        L->front=L->back= L->curr =NULL;
    }
    L->length--;
    freeNode(&N);
}



void deleteBack(List L){
    Node N = NULL;

    if(L->length==0){
        printf("Error: cannot call a delete function on an empty List");
        exit(1);
    }
    N= L->back;
    if(L->length>1){

        L->back = L->back->prev;
        L->back->next = NULL;
    }else{
        L->front=L->back=L->curr=NULL;
        L->index=-1;
    }
    L->length--;
    freeNode(&N);

}

void delete(List L){
    //deletes curr
    Node N = NULL;
    if(L->length==0){
        printf("Error: cannot call a delete function on an empty List");
        exit(1);
    }
    N= L->curr;
    if(L->length>1){
        L->curr->prev->next = L->curr->next;
        L->curr->next->prev = L->curr->prev;
        L->length--;
    }else{
        L->front=L->back=NULL;
    }
        L->curr = NULL;
        L->index = -1;

        freeNode(&N);

}

//--------------------------Other ----------------------------//
List copyList(List L){
    List K = newList();
    Node N;
    N = L->front;

    while(N != NULL){
        append(K, N->data);
        N = N->next;
    }

    return(K);

}

int isEmpty(List L){
    return(L->length==0);
}

void printList(FILE* out, List L){
    //Node T;
    for(moveFront(L); index(L)!= -1; moveNext(L)){
        fprintf(out, "%d ", get(L));
    }
}

































