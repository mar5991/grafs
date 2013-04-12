#ifndef GRAFY_HPP
#define GRAFY_HPP
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstddef>
#include <set>
#include <map>
using namespace std;
class krawedz;
class wierzcholek;
class przegladaniekrawedzi
{
	public:
	virtual void przegladaj(krawedz* k)
	{
	}
};
class przegladaniewierzcholkow
{
	public:
	virtual void przegladaj(wierzcholek* w)
	{
	}
};
class techdata
{
	public:
	virtual void setodw(bool wart)
	{
	}
	virtual bool odw()
	{
	}
	virtual void setodl(int wart)
	{
	}
	virtual int odl()
	{
	}
};
class graf
{
	set <krawedz*> krawedzie;
	set <wierzcholek*> wierzcholki;
	public:
	void dodajkrawedz(krawedz* kr);
	void dodajwierzcholek(wierzcholek* wi);
	void przegladajkrawedzie(przegladaniekrawedzi *p);
	void przegladajwierzcholki(przegladaniewierzcholkow *w);
};

class krawedz
{
	wierzcholek* start;
	wierzcholek* stop;
	graf* g;
	map <string, int> properities;
	bool dwukier;
	public:
	techdata* danetech;
	krawedz(graf* gr, wierzcholek* sta, wierzcholek* sto, bool dwukie);
	wierzcholek* nastepny(wierzcholek* w);
	wierzcholek* poprzedni(wierzcholek* w);
	bool czywychodzacy(wierzcholek* w);
	bool czywchodzacy(wierzcholek* w);
	void setprop(string str, int wart);
	int prop(string str);
};

class wierzcholek
{
	map <string, int> properities;
	vector <krawedz*> krawedzie;
	graf* g;
	public:
	techdata* danetech;
	wierzcholek(graf* gr);
	void dodajkrawedz(krawedz* kraw);
	void przegladajkrawedzie(przegladaniekrawedzi* p);
	void setprop(string str, int wart);
	int prop(string str);
	graf* grafo();
};
#endif
