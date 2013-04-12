#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstddef>
#include <set>
#include <map>
#include "grafy.hpp"
class dijkstra
{
	set<pair <int, wierzcholek*> > listaodl;
	map <wierzcholek*, krawedz*> pary;
	string odle;
	string calkodle;
	string odw;
	public:
	dijkstra (string odl, string codl, string odwe) : odle(odl), calkodle(codl), odw(odwe)
	{
	}
	virtual int odleglosc(krawedz* k)
	{
		return k->prop(odle);
	}
	virtual void setodleglosc(wierzcholek* w, int wart)
	{
		w->setprop(calkodle, wart);
	}
	virtual void odwiedzone(krawedz* k)
	{
		k->setprop(odw, 1);
	}
	void init(wierzcholek* w);
};
class dijkstradata : public techdata
{
	public:
	bool od;
	int odleglosccalk;
	dijkstradata()
	{
		od=0;
		odleglosccalk=100000007;
	}
	void setodw(bool wart)
	{
		od=wart;
	}
	void setodl(int wart)
	{
		odleglosccalk=wart;
	}
	int odl()
	{
		return odleglosccalk;
	}
	bool odw()
	{
		return od;
	}
};
class dijkstrafirstprzegl : public przegladaniewierzcholkow
{	
	public:
	void przegladaj(wierzcholek* w)
	{
		w->danetech=new dijkstradata();
	}
};
class dijkstralastprzegl : public przegladaniewierzcholkow
{
	dijkstra* dd;
	public:
	dijkstralastprzegl(dijkstra* d) : dd(d)
	{
	}
	void przegladaj(wierzcholek* w)
	{
		dd->setodleglosc(w, w->danetech->odl());
		delete w->danetech;
	}
};
class dijkstraprzegladaniekrawedzi : public przegladaniekrawedzi
{
	wierzcholek* ww;
	dijkstra* dijk;
	map <wierzcholek*, krawedz*> *pary;
	set <pair <int, wierzcholek*> > *secik;
	public:
	dijkstraprzegladaniekrawedzi(wierzcholek* w, dijkstra* dij, set <pair <int, wierzcholek*> > *sec, map <wierzcholek*, krawedz*> *par) : ww(w), dijk(dij), secik(sec), pary(par)
	{
	}
	void przegladaj(krawedz* k)
	{
		if(k->nastepny(ww)==NULL)
			return;
		if(!k->nastepny(ww)->danetech->odw())
		{
			int wart1=ww->danetech->odl();
			int wart2=dijk->odleglosc(k);
			pair<int, wierzcholek*> ppp(k->nastepny(ww)->danetech->odl(), k->nastepny(ww));
			set <pair <int, wierzcholek*> >::iterator it1=secik->find(ppp);
			if(it1!=secik->end())
				secik->erase(it1);
			pair<int, wierzcholek*> ppe(min(k->nastepny(ww)->danetech->odl(), wart1+wart2), k->nastepny(ww));
			if(k->nastepny(ww)->danetech->odl()>=wart1+wart2)
			{
				(*pary)[k->nastepny(ww)]=k;
			}
			k->nastepny(ww)->danetech->setodl(min(k->nastepny(ww)->danetech->odl(), wart1+wart2));
			secik->insert(ppe);
		}
	}
};
#endif
