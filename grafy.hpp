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
class techdata
{
	public:
	virtual void setodw(bool wart) {}
	virtual bool odw() {}
	virtual void setodl(int wart) {}
	virtual int odl() {}
};
class wierzcholek;
class przegladaniekrawedzi
{
	public:
	virtual void przegladaj(krawedz* k) {}
};
class przegladaniewierzcholkow
{
	public:
	virtual void przegladaj(wierzcholek* w) {}
};
class graf
{
	vector <krawedz*> krawedzie;
	vector <wierzcholek*> wierzcholki;
	public:
	int wierzcholkisize()
	{
		return wierzcholki.size();
	}
	int krawedziesize()
	{
		return krawedzie.size();
	}
	wierzcholek* wierzch(int id)
	{
		if(id<wierzcholki.size())
			return wierzcholki[id];
		return NULL;
	}
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
	virtual int odleglosc(string wart)
	{
		return prop(wart);
	}
	virtual void odwiedzone() {}
};

class wierzcholek
{
	map <string, int> properities;
	vector <krawedz*> krawedzie;
	graf* g;
	int ide;
	public:
	int id()
	{
		return ide;
	}
	void setid(int wart)
	{
		ide=wart;
	}
	techdata* danetech;
	void dodajkrawedz(krawedz* kraw);
	graf* grafo();
	wierzcholek(graf* gr);
	void setprop(string str, int wart);
	int prop(string str);
	void przegladajkrawedzie(przegladaniekrawedzi* p);
	void przegladajkrawedziewych(przegladaniekrawedzi* p);
	virtual void poprzkrawedz(krawedz* father) {}
	virtual void setodleglosc(int wart) {}
	virtual void preorder (int wart) {}
	virtual void postorder (int wart) {}
};
#endif
