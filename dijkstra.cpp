#include "dijkstra.hpp"
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
	int s5=pary.size();
	for(int i=0; i<s5; i++)
	{
		odwiedzone(pary[i]);
		poprzkrawedz(w->grafo()->wierzch(i), pary[i]);
	}
	dijkstralastprzegl dlp(this);
	w->grafo()->przegladajwierzcholki(&dlp);
}
void dijkstraprzegladaniekrawedzi::przegladaj(krawedz* k)
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
			(*pary)[k->nastepny(ww)->id()]=k;
		}
		k->nastepny(ww)->danetech->setodl(min(k->nastepny(ww)->danetech->odl(), wart1+wart2));
		secik->insert(ppe);
	}
}
