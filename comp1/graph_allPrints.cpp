#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


// Add code as appropriate for your implementation
void Graph::dfs(Node *source, BST *tree){
  static int count = 0;
  count++;
  if(source->visited == 2){
    return;
  }
  source->visited++;
  cout << source->value << "\t" << source->visited << "\t" << count << endl;
  tree->insert(source->value);
  //if(vis == 1){
  //  parent[source.value - 1] = parentNode;
  //}
  //if(visited[source.value - 1] == 1){
  //  Node *p = &source;
  //  cout << "cycle ";
  //  while(parent[p->value - 1].value != p->value){
  //    cout << p->value << " , ";
  //    p = &parent[p->value - 1];
  //    p->inCycle = true;
  //  }
  //  cout << endl;
  //}

  /*Parent stuff*/
  if(source->visited == 1){
  Node *temp = source;
  while(temp != NULL){
    if(source->value == 12) cout << " node 12 wala : " << temp->value << " , ";
    listOfObjects<Node *> *adjList = source->adjacency;
    while(adjList != NULL){
      if(adjList->object->value == temp->value && source->parent != temp){
        temp->inCycle = true;
        Node *temp2 = source;
        while(temp2->value != temp->value){
          temp2->inCycle = true;
          temp2 = temp2->parent;
        }
        cout <<   "parent : " << temp->value << " INCYCLE TREU " << source->value << "\n";
      }
      adjList = adjList->next; 
    }
    temp = temp->parent;
  }
 }

  listOfObjects<Node *> *Adj = source->adjacency;
  while(Adj != nullptr){
    if(Adj->object->visited < 2){
      if(Adj->object->visited == 0){
        Adj->object->parent = source;
      }
      if(Adj->object != source->parent){
        dfs(Adj->object, tree);
      }
    }
    Adj = Adj->next;
  }
  count--;
}

void Graph::modifiedDFS() {
  for(int i = 0; i < numNodes; i++){
    if(nodes[i]->visited == 0){
      TreeNode *root = new TreeNode(nodes[i]->value);
      BST *tree = new BST();
      dfs(nodes[i],tree);
      //tree->printBST("",false);
      trees[i] = tree;
      connectedComponents++;
    }
  }
  return;
}

void Graph::printResults() {

  cout << "No. of connected components: " << connectedComponents << endl;
  for(int i = 0; i < numNodes; i++){
    if(nodes[i]->visited == 1) visOne++;
    else if(nodes[i]->visited == 2) visTwice++;
  }
  for(int i = 0; i < numNodes; i++){
    if(nodes[i]->inCycle){ numNodesInCycle++;
    cout << "incycel : " << nodes[i]->value << endl;}
  }
  cout << "No. of nodes visited once: " << visOne << endl;
  cout << "No. of nodes visited twice: " << visTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << numNodesInCycle << endl;
  for(int i = 0; i < numNodes; i++){
    if(trees[i] != nullptr){
      trees[i]->printBST("",false);
    }
  }
  return;
}

#endif
