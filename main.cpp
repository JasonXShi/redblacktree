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
void rotateLeft(Node *&root, Node *&pt);
void rotateRight(Node *&root, Node *&pt);

void fixTree(Node* &root, Node* &pt){
	Node *parent_pt = NULL;
    	Node *grand_parent_pt = NULL;
    while ((pt != root) && (pt->getColor() != 2) &&
           (pt->getParent()->getColor() == 1))
    {
        parent_pt = pt->getParent();
        grand_parent_pt = pt->getParent()->getParent();
        //if the parent is the left of grandparent
        if (parent_pt == grand_parent_pt->getLeft())
        {
            Node *uncle_pt = grand_parent_pt->getRight();
            //the uncle is red
            if (uncle_pt != NULL && uncle_pt->getColor() == 1)
            {
                grand_parent_pt->setColor(1);
                parent_pt->setColor(2);
                uncle_pt->setColor(2);
                pt = grand_parent_pt;
            }
 
            else{
          
                //   the new node is the right of parent
                if (pt == parent_pt->getRight())
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
 
                /* 
                   the new node is left of parent */
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
 
           //the uncle is read
            if ((uncle_pt != NULL) && (uncle_pt->getColor() == 1))
            {
                grand_parent_pt->setColor(1);
                parent_pt->setColor(2);
                uncle_pt->setColor(2);
                pt = grand_parent_pt;
            }
            else
            {
                //the new node is left of its parent
                if (pt == parent_pt->getLeft())
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
 
                //else, it is right of parent, so rotate and swap the colors of the parent and grandparent
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
Node* addNode(Node* head, Node* pt){
	if(head==NULL){
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
    Node *pt_right = pt->getRight();
 
    pt->setRight(pt_right->getLeft());
 
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

Node* minValueNode(Node* node){
	Node* current = node;
	while(current->getLeft()!=NULL){
		current = current->getLeft();
	}
	return current;
}
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
			cout << "Enter the number you want to add: " <<endl;
			cin >> number;
			cin.get();
			Node* pt = new Node();
			pt->setContent(number);
			head = addNode(head, pt);
			fixTree(head, pt);
		}else if(strcmp(command, "PRINT") == 0){
			
            if(head->getContent() == NULL){
                    
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
