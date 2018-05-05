#ifndef NODE_H
#define NODE_H

class Node{
 public:
  Node();
  Node* getRight();
  Node* getLeft();
  Node* getParent();
  int getContent();
  void setContent(int);
  void setLeft(Node*);
  void setRight(Node*);
  void setParent(Node*);
  int getColor();
  void setColor(int);
 	void setSibiling(Node*);
	Node* getSibiling();
  ~Node();
 private:
  Node* left;
  Node* right;
  Node* parent;
  Node* sibiling;
  int content;
  int color;
};
#endif
