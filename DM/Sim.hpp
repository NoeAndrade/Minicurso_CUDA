#ifndef SIM_HEADER
#define SIM_HEADER
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>

using str = std::string;
using ush = unsigned short;
using uint = unsigned int;

void AASO(str dpsco,std::ofstream &ofasres,std::ofstream &ofasat)
{
    str asat = dpsco + "/PosicionesSO.txt";
    str asres = dpsco + "/SinOptimizaciones.txt";

    ofasat.open(asat.c_str());
    ofasres.open(asres.c_str());
}

void PLJ(double &eit,double *a,double *p,uint np,ush nd,double cajax,double cajay,double cajaz,double sig,double eps)
{
    double eitt=0.0;
    eit=0.0;
    int ip,jp;
    double dx,dy,dz,dis,fue,pot;
    double di,d2,d6,d12;
    for(ip=0;ip<np;ip++){
        eitt=0.0;
        a[nd*ip]=0.0;
        a[nd*ip+1]=0.0;
        a[nd*ip+2]=0.0;
        for(jp=0;jp<np;jp++){
            if(ip!=jp){
                dx = p[nd*ip] - p[nd*jp];
                dy = p[nd*ip+1] - p[nd*jp+1];
                dz = p[nd*ip+2] - p[nd*jp+2];
                //condiciones de periodicidad
                if(fabs(dx) > cajax/2){
                    dx -= (fabs(dx)/dx) * cajax;
                }
                if(fabs(dy) > cajay/2){
                    dy -= (fabs(dy)/dy) * cajay;
                }
                if(fabs(dz) > cajaz/2){
                    dz -= (fabs(dz)/dz) * cajaz;
                }
                dis=dx*dx+dy*dy+dz*dz;
                di=1/dis;
                d2=sig*sig/dis;
                d6=d2*d2*d2;
                d12=d6*d6;
                pot=4.0*eps*(d12-d6);
                fue=24.0*eps*(2.0*d12-d6)*di;               
            }else{
                pot=0;
                fue=0;
            }
            
            eit+=pot;
            eitt+=pot;
            a[nd*ip] += fue*dx;
            a[nd*ip+1]+=fue*dy;
            a[nd*ip+2]+=fue*dz;            
        }
        //printf("ip: %d,eit: %f\n",ip,eitt);
        //std::cout << "ax["<<ip<< "]: "<< a[nd*ip] << std::endl;
    }
    eit/=2.0*np;
}

double EC(int np, ush nd,double *v)
{
    //Energía cinética
    int ip,id;
    double ec=0.0;

    for(ip=0; ip<np; ip++){
        for(id=0; id<nd; id++){
            ec += v[id+ip*nd] * v[id+ip*nd];
        }
    }
    return(ec/np);
}

void Vel(uint np, ush nd,double *v,double *a,double dt)
{
    //Velocidades
    int id, ip;

    for(ip=0; ip<np;ip++){
        for(id=0;id<nd;id++){
            v[id+ip*nd] += a[id+ip*nd] * 0.5 * dt;
        }
    }
}

//imprimir los atomos a disco
void IAaD(uint np,std::ofstream &ofasat,double *p,double *v,double *a,ush nd)
{    
    int ip;
    ofasat << "ip,p[],v[],a[]"<< std::endl;
    for(ip=0; ip<np; ip++)
    {
        ofasat << ip << " " <<
        p[ip*nd] << " " << p[1+ip*nd] << " " << p[2+ip*nd] << " " <<
        v[ip*nd] << " " << v[1+ip*nd] << " " << v[2+ip*nd] << " " <<
        a[ip*nd] << " " << a[1+ip*nd] << " " << a[2+ip*nd] << std::endl;
    }
}

void Simulacion(uint np, uint nd,double *p,double *v,double *a,double cajax,double cajay,double cajaz,double sig,double eps,
                double temp,std::ofstream &ofasres,uint nc,double dt,uint ncc,double dens,std::ofstream &ofasat)
{
    std::cout << "\nInicia la simulacion\n"<< std::endl;
    clock_t ti, tf;
    double dtt;

    double ets=0.0,etp=0.0,ett=0.0;
    double ecs=0.0,ecp=0.0,ect=0.0;
    double eis=0.0,eip=0.0,eit=0.0;
    double temps;
    int ns,id,ip,ic=0;

    PLJ(eit,a,p,np,nd,cajax,cajay,cajaz,sig,eps);
    
    ect=EC(np,nd,v);
    temp= ect/nd;
    ect=ect/2.0;
    ett = ect + eit;

    std::cout << "ett,ect,eit,temp " << ett << " " << ect << " " <<
            eit << " " << temp << std::endl;
    
    ti=clock();
    std::cout << " " << std::endl;
    std::cout << "Resultados parciales" << std::endl;
    std::cout << "ic,temp,dens,ett,ect,eit,dtt " << std::endl;
    ofasres << "Resultados parciales" << std::endl;
    ofasres << "ic,temp,dens,ett,ect,eit,dtt " << std::endl;
    eis=ns=0;
    for(ic=0;ic<nc;ic++){
        for(ip=0; ip<np; ip++){

            //Ciclo de dimensiones
            for(id=0; id<nd; id++){
                p[id+ip*nd] +=(v[id+ip*nd] * dt + a[id+nd*ip]*dt*dt*0.5);              
            }
            if(p[ip*nd] > cajax){p[ip*nd] -= cajax;}
            if(p[ip*nd] < 0){p[ip*nd] += cajax;}
            if(p[1+ip*nd] > cajay){p[1+ip*nd] -= cajay;}
            if(p[1+ip*nd] < 0){p[1+ip*nd] += cajay;}
            if(p[2+ip*nd] > cajaz){p[2+ip*nd] -= cajaz;}
            if(p[2+ip*nd] < 0){p[2+ip*nd] += cajaz;}  
        }

        Vel(np,nd,v,a,dt);
        //esto en la version en paralelo cada elemento este loop va a ser una rutina que va a ser un stream
        eit=0;
        PLJ(eit,a,p,np,nd,cajax,cajay,cajaz,sig,eps);
        Vel(np,nd,v,a,dt);
        if(ic>0 && ic % ncc == 0){
            tf = clock();
            dtt =((double)(tf - ti))/CLOCKS_PER_SEC;

            ect = EC(np,nd,v);
            temp = ect/nd;
            ect=ect/2.0;
            ett = ect + eit;

            ets = ets + ett;
            ecs = ecs + ect;
            eis = eis + eit;
            temps = temps + temp;
            ns++;

            std::cout << ic<< " "<< temp<< " "<< dens<< " "<< ett<<
            " "<< ect << " "<< eit << " " << dtt <<std::endl;

            ofasres << ic<< " "<< temp<< " "<< dens<< " "<< ett<<
            " "<< ect << " "<< eit << " " << dtt <<std::endl;

            dens=dens;
        }
    }
    ets += ett;
    ecs += ect;
    eis += eit;
    temps += temp;
    ns++;

    etp =ets / ns;
    eip =eis / ns;
    ecp =ecs / ns;

    std::cout << " " << std::endl;
    std::cout << "Resultados finales" << std::endl;
    tf = clock();
    dtt = ((double)(tf - ti))/CLOCKS_PER_SEC;
    ect=EC(np,nd,v);

    std::cout << "nc,temp,dens,etp,ecp,eip,dtt"<<std::endl;
    std::cout << nc << " " << temp << " " << dens << " " << etp << " " << ecp << " " << eip << " " << dtt << std::endl;

    ofasres << std::endl;
    ofasres <<"Resultados finales"<<std::endl;
    ofasres << "nc,temp,dens,etp,ecp,eip,dtt"<<std::endl;
    ofasres << nc << " " << temp << " " << dens << " " << etp << " " << ecp << " " << eip << " " << dtt << std::endl;

    IAaD(np,ofasat,p,v,a,nd);
    
}
#endif
