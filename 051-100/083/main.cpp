#include <iostream>
#include <list>
#include <cstdlib>
#include <queue>

#define OUTPUT true

using namespace std;

struct node
{
  int val, d;
  list<node*> neighbours;

  node() : val(0), d(0x7fffffff) {}
};

struct graph
{
  node *nodes;
  int n, m;
};

int shortest_path(graph *g, node *s, node *t)
{
  int m;
  queue<node*> q;

  s->d = s->val;
  q.push(s);
  while (!q.empty())
  {
    node *u = q.front();
    q.pop();

    for (node *v : u->neighbours)
    {
      m = u->d + v->val;
      if (m < v->d)
      {
        v->d = m;
	q.push(v);
      }
    }
  }

  return t->d;
}

int main(int argc, char *argv[])
{
  graph g;
  int w = 80;

  if (argc == 2)
    w = atoi(argv[1]);

  g.n = w*w;
  g.nodes = new node[g.n];
  
  for (int i = 0; i < g.n; i++)
  {
    cin >> g.nodes[i].val;

    if (i >= w)
    {
      g.nodes[i].neighbours.push_back(&(g.nodes[i-w]));
      g.m++;
    }
    if (i < (w*w-w))
    {
      g.nodes[i].neighbours.push_back(&(g.nodes[i+w]));
      g.m++;
    }
    if (i % w != 0)
    {
      g.nodes[i].neighbours.push_back(&(g.nodes[i-1]));
      g.m++;
    }
    if ((i+1) % w != 0)
    {
      g.nodes[i].neighbours.push_back(&(g.nodes[i+1]));
      g.m++;
    }
  }

  if (OUTPUT)
    cout << "Graph has " << g.n << " nodes and " << g.m << " edges." << endl;
  cout << shortest_path(&g, &g.nodes[0], &g.nodes[g.n-1]) << endl;
  
  delete[] g.nodes;
  return 0;
}
