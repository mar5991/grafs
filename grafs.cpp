#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstddef>
#include <set>
#include <map>
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
	void dodajkrawedz(krawedz* kr)
	{
		krawedzie.insert(kr);
	}
	void dodajwierzcholek(wierzcholek* wi)
	{
		wierzcholki.insert(wi);
	}
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
	void setprop(string str, int wart)
	{
		properities[str]=wart;
	}
	int prop(string str)
	{
		return properities[str];
	}
};

class wierzcholek
{
	map <string, int> properities;
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
	void przegladajkrawedzie(przegladaniekrawedzi* p)
	{
		int s1=krawedzie.size();
		for(int i=0; i<s1; i++)
			p->przegladaj(krawedzie[i]);
	}
	void setprop(string str, int wart)
	{
		properities[str]=wart;
	}
	int prop(string str)
	{
		return properities[str];
	}
	graf* grafo()
	{
		return g;
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
class dfsfirstprzegl : public przegladaniewierzcholkow
{
	public:
	void przegladaj(wierzcholek* w)
	{
		w->danetech=new dfsdata();
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
class dfslastprzegl : public przegladaniewierzcholkow
{
	public:
	void przegladaj(wierzcholek* w)
	{
		delete w->danetech;
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
void properdfs(wierzcholek* w, dfs* df)
{
	w->danetech->setodw(1);
	dfsprzegladaniekrawedzi dpk(w, df);
	df->preorder(w, (df->numerpre));
	(df->numerpre)++;
	w->przegladajkrawedzie(&dpk);
	df->postorder(w, (df->numerpost));
	(df->numerpost)++;

}
void dfsprzegladaniekrawedzi::przegladaj(krawedz* k)
{
	wierzcholek* nast=k->nastepny(poprzedni);
	if(nast==NULL)
		return;
	if(nast->danetech->odw())
		return;
	df->odwiedzone(k);
	properdfs(nast, df);
}
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
void dfs::init(graf* g)
{
	numerpre=0;
	numerpost=0;
	dfsfirstprzegl dfp;
	dfslastprzegl dlp;
	dfssrodkoweprzegl dsp(this);
	g->przegladajwierzcholki(&dfp);
	g->przegladajwierzcholki(&dsp);
	g->przegladajwierzcholki(&dlp);
}
void dijkstra::init(wierzcholek* w)
{
	dijkstrafirstprzegl dfp;
	w->grafo()->przegladajwierzcholki(&dfp);
	pair <int, wierzcholek*> para(0, w);
	w->danetech->setodl(0);
	listaodl.insert(para);
	while(!listaodl.empty())
	{
		pair<int, wierzcholek*> parx=*(listaodl.begin());
		listaodl.erase(parx);
		(parx.second)->danetech->setodw(1);
		dijkstraprzegladaniekrawedzi dpk(parx.second, this, &listaodl, &pary);
		(parx.second)->przegladajkrawedzie(&dpk);
	}
	map<wierzcholek*, krawedz*>::iterator it1=pary.begin();
	while(it1!=pary.end())
	{
		odwiedzone(it1->second);
		it1++;
	}
	dijkstralastprzegl dlp(this);
	w->grafo()->przegladajwierzcholki(&dlp);
}
void graf::przegladajkrawedzie(przegladaniekrawedzi* p)
{
	set <krawedz*>::iterator it1;
	it1=krawedzie.begin();
	while(it1!=krawedzie.end())
	{
		p->przegladaj(*it1);
		it1++;
	}
}
void graf::przegladajwierzcholki(przegladaniewierzcholkow* w)
{	
	set <wierzcholek*>::iterator it1;
	it1=wierzcholki.begin();
	while(it1!=wierzcholki.end())
	{
		w->przegladaj(*it1);
		it1++;
	}
}
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
	dijkstra dij("odl", "kodl", "odw");
	dij.init(w[0]);
	for(int i=0; i<n; i++)
		cout<<w[i]->prop("kodl")<<endl;
	for(int i=0; i<m; i++)
		cout<<"*"<<k[i]->prop("odw")<<endl;
}
