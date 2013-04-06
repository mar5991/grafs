#include <vector>
#include <cstddef>
#include <set>
using namespace std;
class wierzcholek;
class krawedz;

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
};
class graf
{
	set <krawedz*> krawedzie;
	set <wierzcholek*> wierzcholki;
	public:
	void dodajkrawedz(krawedz* kr)
	{
		krawedzie.insert(kr);
	}
	void dodajwierzcholek(wierzcholek* wi)
	{
		wierzcholki.insert(wi);
	}
	void przegladajkrawedzie(przegladaniekrawedzi p)
	{
		set <krawedz*>::iterator it1;
		it1=krawedzie.begin();
		while(it1!=krawedzie.end())
		{
			p.przegladaj(*it1);
			it1++;
		}
	}
	void przegladajwierzcholki(przegladaniewierzcholkow w)
	{	
		set <wierzcholek*>::iterator it1;
		it1=wierzcholki.begin();
		while(it1!=wierzcholki.end())
		{
			w.przegladaj(*it1);
			it1++;
		}
	}
};

class krawedz
{
	wierzcholek* start;
	wierzcholek* stop;
	graf* g;
	bool dwukier;
	public:
	techdata* danetech;
	krawedz(graf* gr, wierzcholek* sta, wierzcholek* sto, bool dwukie);
	wierzcholek* nastepny(wierzcholek* w)
	{
		if(w==start)
			return stop;
		if(w==stop && dwukier)
			return start;
		return NULL;
	}
	wierzcholek* poprzedni(wierzcholek* w)
	{	
		if(w==start && dwukier)
			return stop;
		if(w==stop)
			return start;
		return NULL;
	}
	bool czywychodzacy(wierzcholek* w)
	{
		if(w==start)
			return true;
		if(w==stop && dwukier)
			return true;
		return false;
	}
	bool czywchodzacy(wierzcholek* w)
	{
		if(w==start && dwukier)
			return true;
		if(w==stop)
			return true;
		return false;
	}
};

class wierzcholek
{
	vector <krawedz*> krawedzie;
	graf* g;
	public:
	techdata* danetech;
	wierzcholek(graf* gr) : g(gr)
	{
		gr->dodajwierzcholek(this);
		danetech=NULL;
	}
	void dodajkrawedz(krawedz* kraw)
	{
		krawedzie.push_back(kraw);
	}
	void przegladajkrawedzie(przegladaniekrawedzi p)
	{
		int s1=krawedzie.size();
		for(int i=0; i<s1; i++)
			p.przegladaj(krawedzie[i]);
	}
};
krawedz::krawedz(graf* gr, wierzcholek* sta, wierzcholek* sto, bool dwukie) : g(gr)
{
	danetech=NULL;
	g->dodajkrawedz(this);
	dwukier=dwukie;
	start=sta;
	stop=sto;
	start->dodajkrawedz(this);
	stop->dodajkrawedz(this);
}
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
	public:
	dfsprzegladaniekrawedzi(wierzcholek* w)
	{
		poprzedni=w;
	}
	void przegladaj(krawedz* k);
};
void properdfs(wierzcholek* w)
{
	w->danetech->setodw(1);
	dfsprzegladaniekrawedzi dpk(w);
	w->przegladajkrawedzie(dpk);
}
void dfsprzegladaniekrawedzi::przegladaj(krawedz* k)
{
	wierzcholek* nast=k->nastepny(poprzedni);
	if(nast==NULL)
		return;
	if(nast->danetech->odw())
		return;
	properdfs(nast);
}
class dfssrodkoweprzegl : public przegladaniewierzcholkow
{
	public:
	void przegladaj(wierzcholek* w)
	{
		properdfs(w);
	}
};
class dfs
{
	void init(graf* g)
	{
		dfsfirstprzegl dfp;
		dfslastprzegl dlp;
		dfssrodkoweprzegl dsp;
		g->przegladajwierzcholki(dfp);
		g->przegladajwierzcholki(dsp);
		g->przegladajwierzcholki(dlp);
	}
};
int main()
{
}
