#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


struct TreeNode{
    int value;	// Train Number
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int initValue) : value(initValue), left(nullptr), right(nullptr) {}
    TreeNode(int initValue, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(initValue), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode *root;

public:

	// Constructors!
	BST(){
    root = nullptr;
  }
	BST(TreeNode *root){
    this->root = root;
  }
  void printBST(const string& prefix, bool isLeft){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  }
	bool insert(int value){
    TreeNode *newNode = new TreeNode(value);
    TreeNode *y = nullptr;      // Using 2 pointers x and y to keep track
    TreeNode *x = root;         // of current Node and its parent
    while(x != nullptr){
        y = x;
        if(newNode->value < x->value) x = x->left;
        else x = x->right;
    }
    newNode->parent = y;
    if(y == nullptr) root = newNode;
    else if(newNode->value < y->value) y->left = newNode;
    else y->right = newNode;
    return true;
  }
};

template <typename T> class adjList {
  public:
  T object;
  adjList<T> *next;
  adjList<T> *prev;
  adjList(T obj){
    object = obj;
    next = nullptr;
    prev = nullptr;
  }
  ~adjList(){;}
};

class Node {
 public:
  int value;
  adjList<Node> *adjacency;
  Node(){
    value = 0;
    adjacency = nullptr;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int *visited;
  Node *nodes;
  Node *parent;
  int connectedComponents;
  int visOne;
  int visTwice;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visOne = 0;
    visTwice = 0;
    connectedComponents = 0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    visited = new int[numNodes];
    parent = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      visited[i] = 0;
    }

    //srand(time(0));
    srand(1);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      graphFile << n1+1 << " " << n2+1 << endl;
      int node1 = n1+1, node2 = n2+1;
      adjList<Node> *node1Adj = nodes[n1].adjacency;
      adjList<Node> *checkAdj = nodes[n1].adjacency;
      //bool inserted = false;
      //while(checkAdj != nullptr){
      //  if(checkAdj->object.value == nodes[n2].value){
      //    inserted = true;
      //    break;
      //  }
      //  checkAdj = checkAdj->next;
      //}
      adjList<Node> *node2Adj = nodes[n2].adjacency;
      if(nodes[n1].adjacency == nullptr){
        nodes[n1].adjacency = new adjList<Node>(nodes[n2]);
      }
      else{
        while(node1Adj->next != nullptr){
          node1Adj = node1Adj->next;
        }
        node1Adj->next = new adjList<Node>(nodes[n2]);
        node1Adj->next->prev = node1Adj;
      }
      if(nodes[n2].adjacency == nullptr){
        nodes[n2].adjacency = new adjList<Node>(nodes[n1]);
      }
      else{
        while(node2Adj->next != nullptr){
          node2Adj = node2Adj->next;
        }
        node2Adj->next = new adjList<Node>(nodes[n1]);
        node2Adj->next->prev = node2Adj;
      }
      countEdges++;
    }

    // Printing Adjacency list of all Nodes
    for(int i = 0; i < numNodes; i++){
      cout << "Node : " << nodes[i].value << endl;
      adjList<Node> *Adj = nodes[i].adjacency;
      while(Adj != nullptr){
        cout << Adj->object.value <<  "\t";
        Adj = Adj->next;
      }
      cout << endl;
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  void dfs(Node source, Node parentNode, Node parent[], BST *tree);
};

#endif
