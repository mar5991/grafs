#include "grafy.hpp"
void graf::dodajkrawedz(krawedz* kr)
{
	krawedzie.push_back(kr);
}
void graf::dodajwierzcholek(wierzcholek* wi)
{
	wierzcholki.push_back(wi);
}
wierzcholek* krawedz::nastepny(wierzcholek* w)
{
	if(w==start)
		return stop;
	if(w==stop && dwukier)
		return start;
	return NULL;
}
wierzcholek* krawedz::poprzedni(wierzcholek* w)
{	
	if(w==start && dwukier)
		return stop;
	if(w==stop)
		return start;
	return NULL;
}
bool krawedz::czywychodzacy(wierzcholek* w)
{
	if(w==start)
		return true;
	if(w==stop && dwukier)
		return true;
	return false;
}
bool krawedz::czywchodzacy(wierzcholek* w)
{
	if(w==start && dwukier)
		return true;
	if(w==stop)
		return true;
	return false;
}
void krawedz::setprop(string str, int wart)
{
	properities[str]=wart;
}
int krawedz::prop(string str)
{
	return properities[str];
}
wierzcholek::wierzcholek(graf* gr) : g(gr)
{
	ide=gr->wierzcholkisize();
	gr->dodajwierzcholek(this);
	danetech=NULL;
}
void wierzcholek::dodajkrawedz(krawedz* kraw)
{
	krawedzie.push_back(kraw);
}
void wierzcholek::przegladajkrawedzie(przegladaniekrawedzi* p)
{
	int s1=krawedzie.size();
	for(int i=0; i<s1; i++)
		p->przegladaj(krawedzie[i]);
}
void wierzcholek::przegladajkrawedziewych(przegladaniekrawedzi* p)
{
	int s1=krawedzie.size();
	for(int i=0; i<s1; i++)
		if(krawedzie[i]->czywychodzacy(this))
			p->przegladaj(krawedzie[i]);
}
void wierzcholek::setprop(string str, int wart)
{
	properities[str]=wart;
}
int wierzcholek::prop(string str)
{
	return properities[str];
}
graf* wierzcholek::grafo()
{
	return g;
}
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
void graf::przegladajkrawedzie(przegladaniekrawedzi* p)
{
	vector <krawedz*>::iterator it1;
	it1=krawedzie.begin();
	while(it1!=krawedzie.end())
	{
		p->przegladaj(*it1);
		it1++;
	}
}
void graf::przegladajwierzcholki(przegladaniewierzcholkow* w)
{	
	vector <wierzcholek*>::iterator it1;
	it1=wierzcholki.begin();
	while(it1!=wierzcholki.end())
	{
		w->przegladaj(*it1);
		it1++;
	}
}
