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
	vector <krawedz*> pary;
	wierzcholek* end;
	string odle;
	string calkodle;
	string odw;
	void init(wierzcholek* w);
	vector <wierzcholek*> sciezka(wierzcholek* start, wierzcholek* stop)
	{
		vector <wierzcholek*> wynik;
		int st=start->id();
		int so=stop->id();
		while(st!=so)
		{
			wynik.push_back(start->grafo()->wierzch(st));
			st=pary[st]->poprzedni(start->grafo()->wierzch(st))->id();
		}
		wynik.push_back(stop);
		reverse(wynik.begin(), wynik.end());
		return wynik;
	}
	vector <krawedz*> sciezka2(wierzcholek* start, wierzcholek* stop)
	{
		vector <krawedz*> wynik;
		int st=start->id();
		int so=stop->id();
		while(st!=so)
		{
			wynik.push_back(pary[st]);
			st=pary[st]->poprzedni(start->grafo()->wierzch(st))->id();
		}
		reverse(wynik.begin(), wynik.end());
		return wynik;
	}
	public:
	dijkstra (string odl, string codl, string odwe, wierzcholek* w) : odle(odl), calkodle(codl), odw(odwe), pary(w->grafo()->wierzcholkisize())
	{
		init(w);
	}
	dijkstra (string odl, wierzcholek* start, wierzcholek* stop, vector<wierzcholek*> *sc) : odle(odl), pary(start->grafo()->wierzcholkisize())
	{
		init(start);
		*sc=sciezka(start, stop);
	}
	dijkstra (string odl, wierzcholek* start, wierzcholek* stop, vector<krawedz*> *sc) : odle(odl), pary(start->grafo()->wierzcholkisize())
	{
		init(start);
		*sc=sciezka2(start, stop);
	}
	virtual void poprzkrawedz(wierzcholek* syn, krawedz* father)
	{
		syn->poprzkrawedz(father);
	}
	virtual int odleglosc(krawedz* k)
	{
		return k->odleglosc(odle);
	}
	virtual void setodleglosc(wierzcholek* w, int wart)
	{
		w->setodleglosc(wart);
		if(calkodle!="")
			w->setprop(calkodle, wart);
	}
	virtual void odwiedzone(krawedz* k)
	{
		k->odwiedzone();
		if(odw!="")
			k->setprop(odw, 1);
	}
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
	vector <krawedz*> *pary;
	set <pair <int, wierzcholek*> > *secik;
	public:
	dijkstraprzegladaniekrawedzi(wierzcholek* w, dijkstra* dij, set <pair <int, wierzcholek*> > *sec, vector <krawedz*> *par) : ww(w), dijk(dij), secik(sec), pary(par)
	{
	}
	void przegladaj(krawedz* k);
};
#endif
