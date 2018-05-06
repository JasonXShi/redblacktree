/*
 *	Red Black Tree Insertion
 *	Written by Jason Shi
 *	Allows the user to create a red black tree and delete, add, and print out the tree.
 *	
 *
 */

#include "Node.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
//declare methods
void rotateLeft(Node *&root, Node *&pt);
void rotateRight(Node *&root, Node *&pt);

//call this function to fix the tree after every insertion
void fixTree(Node* &root, Node* &pt){
	//makes parent and grandparent of newly inserted node (helps with checking uncle and if parent is left or right)
	Node *parent_pt = NULL;
    	Node *grand_parent_pt = NULL;
    while ((pt != root) && (pt->getColor() != 2) &&
           (pt->getParent()->getColor() == 1))
    {
	    //set variables
        parent_pt = pt->getParent();
        grand_parent_pt = pt->getParent()->getParent();
        //if the parent is the left of grandparent
        if (parent_pt == grand_parent_pt->getLeft())
        {
            Node *uncle_pt = grand_parent_pt->getRight();
            //the uncle is red - just recolor some nodes, no rotation is needed
            if (uncle_pt != NULL && uncle_pt->getColor() == 1)
            {
                grand_parent_pt->setColor(1);
                parent_pt->setColor(2);
                uncle_pt->setColor(2);
                pt = grand_parent_pt;
            }
 	
            else{
          
                //  if the new node is the right of parent rotate the tree left
                if (pt == parent_pt->getRight())
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
                rotateRight(root, grand_parent_pt);
		int parentcolor = parent_pt->getColor();
		int grandcolor = grand_parent_pt->getColor();
		parent_pt->setColor(grandcolor);
		grand_parent_pt->setColor(parentcolor);
                
                pt = parent_pt;
            }
        }
 
        //the parent is right of grandparent
        else
        {
            Node *uncle_pt = grand_parent_pt->getLeft();
 
           // if the uncle is read then recolor
            if ((uncle_pt != NULL) && (uncle_pt->getColor() == 1))
            {
                grand_parent_pt->setColor(1);
                parent_pt->setColor(2);
                uncle_pt->setColor(2);
                pt = grand_parent_pt;
            }
            else {
                //the new node is left of its parent
                if (pt == parent_pt->getLeft())
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
                 rotateLeft(root, grand_parent_pt);
		int parentcolor = parent_pt->getColor();
		int grandcolor = grand_parent_pt->getColor();
		parent_pt->setColor(grandcolor);
		grand_parent_pt->setColor(parentcolor);
                pt = parent_pt;
            }
        }
    }
 //set the root to be black (because the root must always be black in the end)
    root->setColor(2);

}
//recursive function that returns the head (usually same as input)
Node* addNode(Node* head, Node* pt){
	if(head==NULL){
		//the root of the new tree is the new node to be added
		return pt;
	}else if(head->getContent()>=pt->getContent()){
                        head->setLeft(addNode(head->getLeft(), pt));
			//set parent of the new node
			head->getLeft()->setParent(head);
	}else if(head->getContent()<pt->getContent()){
			head->setRight(addNode(head->getRight(), pt));
			//set parent of the new node
			head->getRight()->setParent(head);
		}
		return head;
}

void rotateLeft(Node *&root, Node *&pt)
{
	//makes a right node of the new node for easier rotation
    Node *pt_right = pt->getRight();
    pt->setRight(pt_right->getLeft());
 	//checks if the node to be set actually exist before proceding with rotation
    if (pt->getRight() != NULL){
        pt->getRight()->setParent(pt);
    }
    pt_right->setParent(pt->getParent());
    if (pt->getParent() == NULL){
        root = pt_right;
    }else if (pt == pt->getParent()->getLeft()){
        pt->getParent()->setLeft(pt_right);
}
    else{
        pt->getParent()->setRight(pt_right);
    }
    pt_right->setLeft(pt);
    pt->setParent(pt_right);
}
//same thing but just the other way
void rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->getLeft();
    pt->setLeft(pt_left->getRight());
    if (pt->getLeft() != NULL){
        pt->getLeft()->setParent(pt);
    }
    pt_left->setParent(pt->getParent());
 
    if (pt->getParent() == NULL){
        root = pt_left;
    }
    else if (pt == pt->getParent()->getLeft()){
        pt->getParent()->setLeft(pt_left);
    }
    else{
        pt->getParent()->setRight(pt_left);
    }
    pt_left->setRight(pt);
    pt->setParent( pt_left);
}
//prints the tree spacing to make things look clear
void printTree(Node* head, int space){
    if (head == NULL)
    	return;
    space += 10;
    printTree(head->getRight(), space);
    cout << '\n';
    for (int i = 10; i < space; i++)
        cout << " ";
	
    if(head->getColor()==1){
	    cout <<"red: " << head->getContent();
    }else{
    	cout << "black: " << head->getContent();
    }
    printTree(head->getLeft(), space);
}
//returns the minimum node - used in deletion (not right now though, just when this was a bst)
Node* minValueNode(Node* node){
	Node* current = node;
	while(current->getLeft()!=NULL){
		current = current->getLeft();
	}
	return current;
}
//this deletion works but doesnt adjust the tree (this was for bst)
Node* deleteNode(Node* head, int number){
  	
    if(head->getContent()> number){
    		head->setLeft(deleteNode(head->getLeft(), number));
 	 }else if(number > head->getContent()){
    		head->setRight(deleteNode(head->getRight(), number));
	}else{
		if(head->getLeft() == NULL){
			Node* temp = head->getRight();
			free(head);
			return temp;
		}else if(head->getRight() == NULL){
			Node* temp = head->getLeft();
			free(head);
			return temp;
		}
		Node* temp = minValueNode(head->getRight());
		head->setContent(temp->getContent());
		head->setRight(deleteNode(head->getRight(), temp->getContent()));
	}
}


int main(){
	//some unused code for bst is commented out
//get input
	/* 
	char* text = new char[400];
	cout << "Enter input as file or in console? (Type 'FILE' or 'CONSOLE')" << endl;
	cin.getline(text, 50);
	int count = 0;
	int * stor = new int[1000];
	if(strcmp(text, "FILE")==0){
		//gets filename
		cout << "Enter the filename: (Ex. 'text.txt') (Make sure to seperate the numbers just by spaces.)" << endl;
		char* filename = new char[50];
		cin.getline(filename, 50);
		ifstream inFile;
		inFile.open(filename);
		int a = 0;
		//puts all into the storage of numbers starting from 1
		while(inFile >> a){
			stor[count] = a;
			count++;
		}

	}else if(strcmp(text, "CONSOLE")==0){
		//gets input
		cout << "Enter the numbers you want to add to the tree, seperated by commas and spaces(Ex. 1, 2, 3)" << endl;
		char* input2  = new char[400];		
		cin.getline(input2, 400);
		char* token = strtok(input2, ", ");
		
		while(token != NULL){
			//changes it to int and puts it in the array starting from 1
			stor[count] = atoi(token);
			//deletes token
			token = strtok(NULL, ", ");
			count ++;
		}
		
	}
	Node* head = NULL;
	for(int i =0; i< count; i++){
		Node* pt = new Node();
		pt->setContent(stor[i]);
		head = addNode(head, pt);
		
		fixTree(head, pt);
	}	
	*/
	//makes a head so I can call the addNode function
	Node* head = NULL;
	while(1){
		cout << '\n' <<"Enter a command:" << endl;
		cout << "'ADD' to add a number." << endl;
		cout << "'PRINT' to print the tree." << endl; 
		cout << "'READ' to read in numbers from a file." << endl;
		//cout << "'DELETE' to delete a number." << endl;
		cout << "Or 'EXIT' to exit the program" << endl;
		char* command = new char[10];
		cin.getline(command, 10);
		int number = 0;
		if(strcmp(command, "ADD") == 0){
			//allows adding 1 number to the tree
			cout << "Enter the number you want to add: " <<endl;
			cin >> number;
			cin.get();
			//makes a new node with the number to be added
			Node* pt = new Node();
			pt->setContent(number);
			//if this is the first time (creating the tree) this function still works because a NULL pointer for head was made
			head = addNode(head, pt);
			//calls the method to fix the tree after every insertion
			fixTree(head, pt);
		}else if(strcmp(command, "PRINT") == 0){
			
            if(head == NULL){
                    cout << "There is nothing in the tree" << endl;
                    }else{
                printTree(head, 0);
            }
		}else if(strcmp(command, "DELETE") == 0){
			cout << "Enter the number you want to delete: " << endl;
			cin >> number;
			cin.get();
			if(head->getLeft() == NULL & head->getRight() == NULL){
                head->setContent(NULL);
            }else{
                 head = deleteNode(head, number);
            }
		}
		else if(strcmp(command, "READ") == 0){
		
		int count = 0;
		int * stor = new int[1000];
		//gets filename
		cout << "Enter the filename: (Ex. 'text.txt') (Make sure to seperate the numbers just by commas.)" << endl;
		char* filename = new char[50];
		cin.getline(filename, 50);
		ifstream inFile;
		inFile.open(filename);
		//puts all into the storage of numbers starting from 1
		char* input2  = new char[400];		
		inFile.getline(input2, 400);
		char* token = strtok(input2, ",");
		
		while(token != NULL){
			//changes it to int and puts it in the array starting from 1
			stor[count] = atoi(token);
			//deletes token
			token = strtok(NULL, ", ");
			count ++;
		}
			//for each item in the storage call the addNode and then fixTree, one by one
		for(int i =0; i< count; i++){
			Node* pt = new Node();
			pt->setContent(stor[i]);
			head = addNode(head, pt);
			fixTree(head, pt);
		}
	
        }else if(strcmp(command, "EXIT") == 0){
			exit(0);
		}
	
	}	

}
