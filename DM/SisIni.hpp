#ifndef DATOSI_HEADER
#define DATOSI_HEADER

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

using str = std::string;
using ush = unsigned short;
using uint = unsigned int;

//Las funciones que estan entre /***/ se encargan de leer datos para definir el sistema inicial
/**************************************************************************************************************************************************************/
//Leyendo datos
void LDI(str dir,double &dens,ush &nd,uint &np,double &sig, double &eps)
{
    str a;
    str aedi= dir+"Datos/I1.txt";

    std::ifstream ifaedi(aedi);
    if(!ifaedi){
        std::cout << "Error al abrir archivo Datos\n";
        exit(EXIT_FAILURE);
    }
    ifaedi >> dens;    ifaedi >> a;
    ifaedi >> nd;    ifaedi >> a;
    ifaedi >> np;    ifaedi >> a;
    ifaedi >> sig;    ifaedi >> a;
    ifaedi >> eps;    ifaedi >> a;
    ifaedi.close();
}

//Imprimiendo Datos
void IDI(double dens,ush nd,uint np,double sig,double eps)
{
    std::cout << "\nPROPIEDADES DEL SISTEMA\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "Densidad: " << dens << std::endl;
    std::cout << "Dimensiones: " << nd << std::endl;
    std::cout << "Numero de atomos: " << np << std::endl;
    std::cout << "diametro: " << sig << std::endl;
    std::cout << "profundidad del pozo de potencial: " << eps << std::endl;
    std::cout << "-----------------------------------------------\n";
}

//Leyendo datos
void LDC(str dir,uint &nc,ush &ncp,double &dt,double &temp,double &v0,uint &ncc)
{
    str a;
    str aedi=dir+"Datos/Cor.txt";
    std::ifstream ifaedi(aedi);
    if(!ifaedi){
        std::cout << "Error al abrir archivo cor\n";
        exit(EXIT_FAILURE);
    }
    ifaedi >> nc;    ifaedi >> a;
    ifaedi >> ncp;    ifaedi >> a;
    ifaedi >> dt;    ifaedi >> a;
    ifaedi >> temp;    ifaedi >> a;
    ifaedi >> v0;    ifaedi >> a;
    ifaedi.close();

    ncc = nc * ncp / 100.;
}

/**************************************************************************************************************************************************************/

void AA(str dir,double dens,ush nd,uint np,double sig,double eps,std::ofstream &ofaedi,std::ofstream &ofapin,str &dpsco)
{
    //Creando Carpetas y abriendo archivos para escribir en ellos 
    str dpsc1 = dir + "Corridas";
    //creando el directorio de corridas
    mkdir(dpsc1.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    str dpsc = dpsc1 +"/dens_"+ std::to_string(dens) + "_nd_" + std::to_string(nd) + "_np_" + std::to_string(np)+"_sig_"+ std::to_string(sig)+"_eps_"+ std::to_string(eps);

    std::cout << "LOS ARCHIVOS DE ESTA CORRIDA SE GUARDAN EN: " << dpsc << std::endl;
    //creando el directorio de psc
    mkdir(dpsc.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    dpsco = dpsc+"/Resultados";
    mkdir(dpsco.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    str aedi = dpsc + "/DatosIniciales.txt";
    str apin = dpsc + "/PosIni.txt";

    ofaedi.open(aedi.c_str());
    ofapin.open(apin.c_str());
}

void Cuadrada(ush nd,double &cajax,double &cajay,double &cajaz,double sig,
              double dens,std::ofstream &ofapin,double *p,uint np)
{
    //configuracion inicial cuadrada
    ush ndivx=0,ndivy=0,ndivz=0;
    int ndiv=pow(np,1.0/nd)+0.5;
    double celx=sig,cely=sig,celz=sig;
    double fcx=celx/2,fcy=cely/2,fcz=celz/2;
    ndivx=ndiv;
    int prod=0;
    prod=np/ndivx;
    int ndiv2=0;
    ndiv2=pow(prod,1.0/(nd-1))+0.5;
    ndivy=ndiv2;
    ndivz=np/(ndivx*ndivy);
    if(np%prod!=0){
        ndivz++;
    }
    cajax = ndivx*celx;
    cajay = ndivy*cely;
    cajaz = ndivz*celz;
    double di=0.0;
    di=pow(dens,1.0/nd);
    cajax/=di;
    cajay/=di;
    cajaz/=di;
    celx=cajax/ndivx;
    cely=cajay/ndivy;
    celz=cajaz/ndivz;

    std::cout <<"\ndimensiones de la caja: (" << cajax <<","<< cajay<<","<< cajaz <<")"<< std::endl;
    switch(nd){
        case 2: std::cout << "tamano de la caja: " << cajax*cajay << std::endl;
        break;
        case 3: std::cout << "tamano de la caja: " << cajax*cajay*cajaz << std::endl;
        break;
    }
    ofapin <<"ip"<< "\t\t" << "px:" << "\t\t" << "py:" << "\t\t" << "pz:" << std::endl;
    int ip=0;
    int x=0,y=0,z=0;
    for(ip=0;ip<np;ip++){
        p[nd*ip]=x*celx+fcx;
        p[nd*ip+1]=y*cely+fcy;
        p[nd*ip+2]=z*cely+fcz;
        x++;
        if(x>=ndivx){
            x=0;
            y++;
        }
        if(y>=ndivy){
            y=0;
            z++;
        }
        if(z>=ndivz){
            break;
        }
        ofapin << ip << "\t\t" << p[nd*ip]<< "\t\t" <<p[1+nd*ip]<< "\t\t"<<p[2+nd*ip] << std::endl;
    }
}

//Imprimir datos iniciales a disco
void IDID(std::ofstream &ofaedi,double dens,double temp,uint np,ush nd,uint nc,ush ncp,uint ncc,double cajax,double cajay,double cajaz,double dt,double v0,double sig,double eps)
{
ofaedi << "DatosIniciales" << std::endl;

    ofaedi << "dens,temp " << dens << " " << temp << std::endl;
    ofaedi << "Numero de particulas: "<< np << std::endl;
    ofaedi << "Sigma: " << sig << std::endl;
    ofaedi << "Epsilon: " << sig << std::endl;
    ofaedi << "np,nd,nc "<< np << " " << nd << " " << nc << std::endl;
    ofaedi << "ncp,ncc " << ncp << " " << ncc << std::endl;
    ofaedi << "Lx:\t" <<  cajax<< "\nLy:\t" <<  cajay<< "\nLz:\t" <<  cajaz  << std::endl;
    ofaedi << "dt,v0 " << dt << " " << v0 << std::endl;
}

void VIA(double v0,double *v,uint np,ush nd)
{
    //velocidades Iniciales al azar
    double r;
    srand(1);
      for(int ip=0; ip<np; ip++)
      {
          for(int id=0;id<nd;id++){
            r=(rand() % 10000 /10000.)*2.0-1.0;
            v[id+ip*nd] = v0*r;
          }
      }

}
#endif
