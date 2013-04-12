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
	map<wierzcholek*, krawedz*>::iterator it1=pary.begin();
	while(it1!=pary.end())
	{
		odwiedzone(it1->second);
		it1++;
	}
	dijkstralastprzegl dlp(this);
	w->grafo()->przegladajwierzcholki(&dlp);
}
