#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


// Add code as appropriate for your implementation
void Graph::dfs(Node source, Node parentNode, Node parent[], BST *tree){
  static int count = 0;
  count++;
  if(visited[source.value - 1] == 2){
    return;
  }
  visited[source.value - 1]++;
  //cout << source.value << "\t" << visited[source.value - 1] << "\t" << count << endl;
  tree->insert(source.value);
  if(visited[source.value -1] == 1){
    parent[source.value - 1] = parentNode;
  }
  adjList<Node> *Adj = source.adjacency;
  while(Adj != nullptr){
    if(visited[Adj->object.value - 1] < 2){
      dfs(Adj->object, source, parent, tree);
    }
    Adj = Adj->next;
  }
  count--;
}

void Graph::modifiedDFS() {
  for(int i = 0; i < numNodes; i++){
    if(visited[i] == 0){
      TreeNode *root = new TreeNode(nodes[i].value);
      BST *tree = new BST();
      dfs(nodes[i],nodes[i],parent,tree);
      tree->printBST("",false);
      connectedComponents++;
    }
  }
  // dfs(nodes[0]);
  return;
}

void Graph::printResults() {

  cout << "No. of connected components: " << connectedComponents << endl;
  for(int i = 0; i < numNodes; i++){
    if(visited[i] == 1) visOne++;
    else if(visited[i] == 2) visTwice++;
  }
  cout << "No. of nodes visited once: " << visOne << endl;
  cout << "No. of nodes visited twice: " << visTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << endl;
  return;
}

#endif
