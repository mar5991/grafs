#include "grafy.hpp"
#include "dfs.hpp"
#include "dijkstra.hpp"
int main()
{
	int n, m;
	cin>>n>>m;
	graf g;
	wierzcholek* w[n];
	krawedz* k[m];
	for(int i=0; i<n; i++)
	{
		w[i]=new wierzcholek(&g);
	}
	for(int i=0; i<m; i++)
	{
		int x, y, z;
		cin>>x>>y>>z;
		x--;
		y--;
		k[i]=new krawedz(&g, w[x], w[y], 1);
		k[i]->setprop("odl", z);
	}
	dijkstra dij("odl", "kodl", "odw", w[0]);
	for(int i=0; i<n; i++)
		cout<<w[i]->prop("kodl")<<endl;
	for(int i=0; i<m; i++)
		cout<<"*"<<k[i]->prop("odw")<<endl;
}
