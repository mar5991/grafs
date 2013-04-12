#include "dfs.hpp"
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
