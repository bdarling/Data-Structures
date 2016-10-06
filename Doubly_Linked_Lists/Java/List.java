/*	List
	A simple doubly linked list.
	Written by Bailey Darling
		September 2016

	List has a front, back, and current (curr)

	index indicates where curr is.
	if index is -1, its undefined
	0 is front
	length-1 is back

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

	length()		returns length
	index()			returns index value
	front()			returns front data
	back()			returns back data
	geth()			returns curr's data

	equals			returns true if two lists are identical
	isEmpty			returns true if empty

	Copy 			copies this into a new list
	toString		overloads standard toString


*/

class List{

	private class Node{
		//the node
		int data;
		Node Next;
		Node Prev;

		Node(int data){
			this.data=data;
			Next = null;
			Prev = null;
		}

		public String toString(){
			return String.valueOf(data);

		}

		public boolean equals(Node x){
			//if equal to current node, returns true
			return ((this.data)==(x.data));
		}
	}

	private Node front; Node back; Node curr;
	private int length; int index;

	List(){
		front = back = curr= null;
		length = 0;
		index = -1;
	}

	//--------------Manipulation Procedures---------------------//
	// clear : resets the list to empty

	void clear(){
		front = back = curr = null;
		index = -1;
		length = 0;

	}

	//moveFront
	// if the list is not empty, moves curr to the front

	void moveFront(){
		if(!isEmpty()){
			index=0;
			curr=front;
		}
	}

	//moveBack
	// if list is not empty, moves curr to the back
	void moveBack(){
		if(!isEmpty()){
			index=length-1;
			curr=back;
		}

	}

	//moveNext
	// if list is not empty, moves curr to next node
	// if there is no next node, curr is undefined and index is -1
	void moveNext(){
		if(!isEmpty()){
			if(index==length-1){
				index= -1;
				curr = null;
			}else{
				index++;
				curr=curr.Next;
			}
		}

	}

	//movePrev
	//if list is not empty, moves curr to previous node
	//if there is no previous node, curr is null and index is -1

	void movePrev(){
		if(!isEmpty()){
			if(index==0){
				index=-1;
				curr=null;

			}else{
				index--;
				curr=curr.Prev;
			}
		}
	}

	// ------------- insertions -----------------//

	//appends to the front of the list
	void prepend(int data){
		Node R = new Node(data);
		if(isEmpty()){
			front=back=R;
		}else{
			R.Next=front;
			front.Prev=R;
			front=R;
		}
		length++;
	}

	//appends to the back of the list
	void append(int data){
		Node R= new Node(data);
		if(this.isEmpty()){
			front=back=R;
		}else{
			back.Next=R;
			R.Prev=back;
			back=R;
		}
		length++;
	}

	void insertBefore(int data){
		if(length >=0 && index >=0){
			Node R = new Node(data);
			if(this.isEmpty()){
				front=back=R;
			}else if(index==-1 ||curr.Prev ==null){
				prepend(data);
			}else{
				curr.Prev.Next=R;
				curr.Prev=R;
				R.Prev=curr.Prev;
				R.Next=curr;
				index++;
			}
			length++;
		}

	}

	void insertAfter(int data){
		if(length>=0 && index<=length-1){
			Node R = new Node(data);
			if(this.isEmpty()){
				front=back=R;
			}else if(index==-1 || curr.Next==null){
				append(data);
			}else{
				curr.Next.Prev=R;
				R.Next=curr.Next;
				R.Prev=curr;
				curr.Next=R;
			}
		}
		length++;
	}

	//-------------deletions------------------//
	//Deletes the front element
	void deleteFront(){
		front=front.Next;
		length--;
	}
	//Deletes the rear element
	void deleteBack(){
		back=back.Prev;
		length--;
	}
	//Deletes the cursor element
	void delete(){
		if(length>0 &&index>=0){
			curr.Prev.Next= curr.Next;
			curr.Next.Prev=curr.Prev;
			curr=null;
			index=-1;
			length--;
		}
	}


	//---------------Access functions -----------------------//

	//returns the length of the list
	int length(){
		return length;
	}

	//returns the index
	// returns -1 if cursor is undefined
	int index(){
		return index;
	}

	//returns the front element
	int front(){
		if(this.isEmpty()){
			throw new RuntimeException(
				"front() cannot be called on an empty list");
		}
		return front.data;
	}
	
	//returns rear element
	int back(){
		if(this.isEmpty()){
			throw new RuntimeException(
				"back() cannot be called on an empty list");	
		}
		return back.data;
	}

	//returns the curr element
	int get(){
		if(this.isEmpty()){
			throw new RuntimeException(
				"get() cannot be called on an empty list");	
		}
		return curr.data;
	}


	//Ignores cursors
	//returns true if lists are identical
	boolean equals(List L){
		Node N= this.front;
		Node K= L.front;

		boolean equal = (this.length()== L.length());

		while(N!= null){
			if(!equal) return false;

			equal = N.equals(K);
			N=N.Next;
			K=K.Next;
		}
		return equal;
	}

	boolean isEmpty(){
		return length==0;
	}

	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N= front;
		while(N!=null){
			sb.append(" ");
			sb.append(N.toString());
			N=N.Next;
		}
		return new String(sb);
	}

// Copy
// Copies the list

	List copy(){
		List R= new List(); // the new list
		Node N= this.front; //the start of the list to be copied

		while(N!=null){
			R.append(N.data);
			N=N.Next;
		}
		R.length = this.length;
		return R;
	}

}