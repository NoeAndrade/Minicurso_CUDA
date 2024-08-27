#include <iostream>
#include "SisIni.hpp"
#include "Sim.hpp"
int main()
{

	str dir = "/home/gach/DM/";
	double dens,sig,eps,dt,temp,v0;
	double *p,cajax,cajay,cajaz;
	double *v,*a;
	ush nd,ncp;
	uint np,nc,ncc; 
	std::ofstream ofaedi,ofapin,ofasres,ofasat;
	str dpsco;
	//Creando la configuracion iniial
	LDI(dir,dens,nd,np,sig,eps);
	p=new double[np*nd];
	v=new double[np*nd];
	a=new double[np*nd];
	IDI(dens,nd,np,sig,eps);
	LDC(dir,nc,ncp,dt,temp,v0,ncc);
	AA(dir,dens,nd,np,sig,eps,ofaedi,ofapin,dpsco);
	Cuadrada(nd,cajax,cajay,cajaz,sig,dens,ofapin,p,np);
	IDID(ofaedi,dens,temp,np,nd,nc,ncp,ncc,cajax,cajay,cajaz,dt,v0,sig,eps);
	VIA(v0,v,np,nd);
	AASO(dpsco,ofasres,ofasat);
	Simulacion(np,nd,p,v,a,cajax,cajay,cajaz,sig,eps,temp,ofasres,nc,dt,ncc,dens,ofasat);
	return 0;
}
