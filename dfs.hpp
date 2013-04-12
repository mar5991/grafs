#ifndef DFS_HPP
#define DFS_HPP
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstddef>
#include <set>
#include <map>
#include "grafy.hpp"
class dfs
{
	public:
	int numerpre;
	int numerpost;
	string preo;
	string poso;
	string odwi;
	dfs(string pre, string pos, string odw)
	{
		preo=pre;
		poso=pos;
		odwi=odw;
	}
	virtual void preorder(wierzcholek* w, int wart)
	{
		if(preo!="")
			w->setprop(preo, wart);
	}
	virtual void postorder(wierzcholek* w, int wart)
	{	
		if(preo!="")
			w->setprop(poso, wart);
	}
	virtual void odwiedzone(krawedz* k)
	{	
		if(preo!="")
			k->setprop(odwi, 1);
	}
	void init(graf* g);
};
class dfsdata : public techdata
{
	public:
	bool od;
	void setodw(bool wart)
	{
		od=wart;
	}
	bool odw()
	{
		return od;
	}
	dfsdata()
	{
		od=0;
	}
};
class dfsfirstprzegl : public przegladaniewierzcholkow
{
	public:
	void przegladaj(wierzcholek* w)
	{
		w->danetech=new dfsdata();
	}
};
class dfslastprzegl : public przegladaniewierzcholkow
{
	public:
	void przegladaj(wierzcholek* w)
	{
		delete w->danetech;
	}
};
class dfsprzegladaniekrawedzi : public przegladaniekrawedzi
{
	wierzcholek* poprzedni;
	dfs* df;
	public:
	dfsprzegladaniekrawedzi(wierzcholek* w, dfs* dfss) : df(dfss)
	{
		poprzedni=w;
	}
	void przegladaj(krawedz* k);
};
void properdfs(wierzcholek* w, dfs* df);
class dfssrodkoweprzegl : public przegladaniewierzcholkow
{
	dfs* df;
	public:
	dfssrodkoweprzegl(dfs* dfss) : df(dfss)
	{
	}
	void przegladaj(wierzcholek* w)
	{
		if(!w->danetech->odw())
			properdfs(w, df);
	}
};
#endif
