#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//Node struct
struct Node {
  int value = -1;
  Node* left = NULL;
  Node* right = NULL;
};

//function prototypes
Node* addNode(Node*, int);
void getInput(Node*&);
bool searchTree(Node*, int, bool);
Node* deleteNode(Node*, int target);
void printTree(Node*, int depth);


int main() {
  cout << "Welcome to Binary Search Tree!" << endl;
  cout << "Valid commands: ADD, SEARCH, DELETE, PRINT, and QUIT" << endl;
  
  Node* tree = NULL;

  char input[20];
  while (strcmp(input, "QUIT") != 0) {
    cout << ">> ";
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      getInput(tree);
    } else if (strcmp(input, "SEARCH") == 0) {
      int target;
      bool answer = false;
      cout << "Searching for: ";
      cin >> target;
      answer = searchTree(tree, target, answer);
      if (answer) {
	cout << target << " is in the tree." << endl;
      } else {
	cout << target << " is NOT in the tree." << endl;
      }
    } else if (strcmp(input, "DELETE") == 0) {
      int target;
      cout << "Deleting: ";
      cin >> target;
      tree = deleteNode(tree, target);
    } else if (strcmp(input, "PRINT") == 0) {
      printTree(tree, 0);
    } else if (strcmp(input, "QUIT") != 0) { //anything else besides QUIT is invalid
      cout << "Invalid command." << endl;
    }  
  }
  cout << "Goodbye!" << endl;

  return 0;
}


//adds a node to tree via console or file input
Node* addNode(Node* tree, int newValue) {
  if (!tree) {
    tree = new Node;
    tree->value = newValue;
    return tree;
  }
  if (tree->value < newValue) {
    tree->right = addNode(tree->right, newValue);
  } else {
    tree->left = addNode(tree->left, newValue);
  }
  return tree;
}

void getInput(Node* &tree) {
  char method[10];
  cout << "Add by FILE or by CONSOLE? ";

  char data[300];
  int i = 0;
  while (true) {
    cin >> method;

    if (strcmp(method, "FILE") == 0) { //if FILE option, open and read file
      char fileName[30];
      cout << "File name: ";
      cin >> fileName;

      ifstream numbers;
      srand(time(0));
      numbers.open(fileName);
      if (!numbers) {
        cout << "Could not find/open " << fileName;
        exit(1);
      }
      while (numbers >> data) { //copy all the numbers into the heap
        tree = addNode(tree, atoi(data));
      }
      break;
    } else if (strcmp(method, "CONSOLE") == 0) {
      cout << "Please enter a series of space separated integers between 1 and 999:" << endl;
      cin.get();
      cin.get(data, 300);
      cin.get();

      //use string tokenizer to split on spaces and copy into the heap
      char *ptr;
      ptr = strtok(data, " ");

      while (ptr) {
	tree = addNode(tree, atoi(ptr)); //parse and add the int
        ptr = strtok(NULL, " ");
      }
      break;
    } else {
      cout << "Please enter either FILE or CONSOLE: ";
    }
  }
  cout << "Added." << endl;
}

//recursively searches tree for whether or not a number is in it
bool searchTree(Node* root, int target, bool answer) {
  if (!root) {return answer;} //dead end
  if (root->value == target) {
    return true;
  } else {
    answer = searchTree(root->right, target, answer);
    answer = searchTree(root->left, target, answer);
  }
  return answer;
}

//deletes given node from the tree using recursion
Node* deleteNode(Node* root, int target) {
  if (!root) {return root;} //dead end
  if (root->value == target) {
    //if no or one child, return the other child   NOT WORKING FOR 
    if (!root->right) {
      Node* temp = root->left;
      delete(root);
      return temp;
    } else if (!root->left) {
      Node* temp = root->right;
      delete(root);
      return temp;
    } else {
      //if two children, pick one side (right)
      //then, go all the way to the other side from there (left) - TEMP
      //now, replace that one with it's only child (if it has one)
      //finally, swap the head and TEMP
      Node* temp = root->right;
      if (!temp->left) {
	root->value = temp->value;
	root->right = temp->right;
      } else {
	while (temp->left->left) {
	  temp = temp->left;
	}
	//temp's parent's child need to be temp's child
	root->value = temp->left->value;
	temp->left = temp->left->right;
	return root;
      }
    }
  } else {
    root->right = deleteNode(root->right, target);
    root->left = deleteNode(root->left, target);
  }
  return root;
}

//visually prints out tree horizontally using recursion
void printTree(Node* root, int depth) {
  if (!root) {return;} //root is complete
  
  printTree(root->right, depth+1); //print top (right) root

  for (int i = 0; i < depth; i++) { //spacing
    cout << "   ";
  }
  cout << root->value << endl; //print data

  printTree(root->left, depth+1); //print bottom (left) root
}
