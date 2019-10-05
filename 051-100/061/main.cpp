#include <iostream>
#include <list>

using namespace std;

const bool OUTPUT = false;



// Graph structure
struct node
{
  int data;  // Number stored here
  int order; // 3 if number is triangular, 4 if square, etc.
  list<node*> neighbours;

  node(int n, int o) : data(n), order(o) {}
};

struct graph
{
  node **nodes;
  int m, n;
};



// Global variables
bool visitedOrders[6] = {false, false, false, false, false, false};
const int first3 = 45;
const int last3  = 140;
const int first4 = 32;
const int last4  = 99;
const int first5 = 26;
const int last5  = 81;
const int first6 = 23;
const int last6  = 70;
const int first7 = 21;
const int last7  = 63;
const int first8 = 19;
const int last8  = 58;
const int totalNums = 351;
node *srcnode;


// Polygonal number functions
int tri(const int n)
{
  return n*(n+1)/2;
}

int square(const int n)
{
  return n*n;
}

int pent(const int n)
{
  return n*(3*n-1)/2;
}

int hex(const int n)
{
  return n*(2*n-1);
}

int hept(const int n)
{
  return n*(5*n-3)/2;
}

int oct(const int n)
{
  return n*(3*n-2);
}



int dfs(node *u)
{
  // We can move to another node if it is of an order that has not been visited
  // If all orders have been visited, and this node is neighbours with the
  // srcnode, return the value at this node.
  
  bool visitedAll = true;
  for (int i = 0; i < 6; i++)
    visitedAll &= visitedOrders[i];
  
  if (visitedAll)
  {
    for (auto v : u->neighbours)
      if (v == srcnode)
        return u->data;
    return 0;
  }

  for (auto v : u->neighbours)
  {
    int o = v->order - 3;
    if (!visitedOrders[o])
    {
      visitedOrders[o] = true;
      int n = dfs(v);
      visitedOrders[o] = false;

      if (n > 0)
        return n + u->data;
    }
  }

  return 0;
}



int solve(graph &g)
{
  visitedOrders[0] = true;
  for (int i = first3; i <= last3; i++)
  {
    srcnode = g.nodes[i];
    int m = dfs(srcnode);
    if (m > 0)
      return m;
  }

  return 0;
}



int main()
{
  graph g;
  
  // Make nodes
  g.nodes = new node*[totalNums];
  g.n = 0;
  for (int j = first3; j <= last3; j++) g.nodes[g.n++] = new node(tri(j),    3);
  for (int j = first4; j <= last4; j++) g.nodes[g.n++] = new node(square(j), 4);
  for (int j = first5; j <= last5; j++) g.nodes[g.n++] = new node(pent(j),   5);
  for (int j = first6; j <= last6; j++) g.nodes[g.n++] = new node(hex(j),    6);
  for (int j = first7; j <= last7; j++) g.nodes[g.n++] = new node(hept(j),   7);
  for (int j = first8; j <= last8; j++) g.nodes[g.n++] = new node(oct(j),    8);

  // Make edges
  g.m = 0;
  for (int i = 0; i < totalNums; i++)
  {
    g.nodes[i]->neighbours.clear();
    for (int j = 0; j < totalNums; j++)
    {
      if ( (g.nodes[i]->data % 100 == g.nodes[j]->data / 100) &&
           (g.nodes[i]->order      != g.nodes[j]->order) )
      {
        g.nodes[i]->neighbours.push_back(g.nodes[j]);
	g.m++;
      }
    }
  }

  if (OUTPUT)
    cout << "Graph has " << g.n << " nodes and " << g.m << " edges." << endl;

  int m = solve(g);
  cout << m << endl;

  // Clean up
  for (int i = 0; i < totalNums; i++)
    delete g.nodes[i];
  delete[] g.nodes;
  return 0;
}
