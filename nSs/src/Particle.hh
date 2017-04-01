#ifndef __PARTICLE_HPP
#define __PARTICLE_HPP

#include <vector>

#include "FileReader.hh"
#include "Data.hh"
#include "Array.hh"

using namespace std;

class Particle {
  
public:

  Particle(double x, double y):X(x),Y(y){
  }

  double X, Y;

  int getDim();

private:

  // The default constructor is not allowed!
  Particle();
};



class ParticleLine{

public:

  // Construct a particle line with p particles
  // on a 1D, 2D or 3D line
  ParticleLine(double x1, double y1, double x2, double y2, int xm, int ym, int p){
    xmax=xm;
    ymax=ym;
    particles=p;
    double dx=abs((x1-x2)/(p-1));    
    double dy=abs((y1-y2)/(p-1));
    for(int i=0;i<p;++i){
      pp.push_back(Particle(x1+i*dx,y1+i*dy));
      //cout<<pp[i].X<<" "<<pp[i].Y<<endl;
    }
  }
  //ParticleLine(double x1, double y1, double z1, double x2, double y2, double z2, int p = 10);

  // This function computes the next time step
  // for all particles of the line
  
  void advanceParticles(Data& dom, Array& u, Array& v, double delx, double dely,double dt){
    double A,B,C,A1,B1,C1;
    double x1,x2,y1,y2;
    double u1, u2, u3, u4,uu(0.),v1,v2,v3,v4,vv(0.);
    int i, j;
    static int dt_tstep=0;
    ofstream f;
    A = -(2.5 - 1.5);
    B =0.0;
    C = -(A * 3.5 + B * 1.5);
    A1=-(2.5-1.5);
    B1=0.0;
    C1=-(A1*6+B*1.5);

    f.open("particle.dat",fstream::app);
 
    for(int k=0;k<particles;++k){
      if(dt_tstep%20==0)
	f<<pp[k].X<<" "<<pp[k].Y<<endl;

      i=(int)(pp[k].X/delx)+1;
      j=(int)((pp[k].Y+dely/2)/dely)+1;
      if(i<xmax && j<ymax){
      if(dom.isFluid(i,j)){
      x1=(i-1)*delx;
      x2=i*delx;
      y1=(j-3/2)*dely;
      y2=(j-1/2)*dely;

      if(!dom.isFluid(i-1,j-1))
	u1=0.0;
      else
	u1=u(i-1,j-1);

      if(!dom.isFluid(i,j-1))
	u2=0.0;
      else
	u2=u(i,j-1);

      if(!dom.isFluid(i-1,j))
	u3=0.0;
      else
	u3=u(i-1,j);

      if(!dom.isFluid(i,j))
	u4=0.0;
      else
	u4=u(i,j);

      uu=(1/(delx*dely))*((x2 - (pp[k].X))*(y2 - (pp[k].Y))*u1 
			  +((pp[k].X) - x1)*(y2 - (pp[k].Y))*u2
			  +(x2 -(pp[k].X))*((pp[k].Y) - y1)*u3
			  +((pp[k].X) - x1)*((pp[k].Y) - y1)*u4);
      }
      }


      i=(int)((pp[k].X+delx/2)/delx)+1;
      j=(int)(pp[k].Y/dely)+1;
      if( i<xmax && j<ymax){
      if(dom.isFluid(i,j)){
	x1=(i-3/2)*delx;
	x2=(i-1/2)*delx;
	y1=(j-1)*dely;
	y2=j*dely;

	if(!dom.isFluid(i-1,j-1))
	  v1=0.0;
	else
	  v1=v(i-1,j-1);

	if(!dom.isFluid(i,j-1))
	  v2=0.0;
	else
	  v2=v(i,j-1);

	if(!dom.isFluid(i-1,j))
	  v3=0.0;
	else
	  v3=v(i-1,j);

	if(!dom.isFluid(i,j))
	  v4=0.0;
	else
	  v4=v(i,j);

	vv=(1/(delx*dely))*((x2 -pp[k].X)*(y2- pp[k].Y)*v1 
			    +(pp[k].X- x1 )*(y2 - pp[k].Y)*v2 
			    +(x2 - pp[k].X)*(pp[k].Y - y1 )*v3 
			    +(pp[k].X - x1 )*(pp[k].Y - y1 )*v4);
      }
      if((A*pp[k].X+dt*uu+B*pp[k].Y+dt*vv+C)>0.0 ||((A1*pp[k].X+dt*uu+B1*pp[k].Y+dt*vv+C1)<=0.0)|| ((pp[k].Y+dt*vv)>=2.5)||((pp[k].Y+dt*vv)<=1.5) ){
      pp[k].X=pp[k].X+dt*uu;
      pp[k].Y=pp[k].Y+dt*vv;
      }
      }
    }
    ++dt_tstep;
    f.close();
  }
  
  // all coordinates of the particles
  std::vector<Particle>& getCoords();

  // Tells whether this particle line doesn't
  // hold any particles
  bool isEmpty();

private:
  int particles;
  int xmax, ymax;
  vector<Particle > pp;
  //  vector<vector<double> > particle; 
  // The default constructor is not allowed!
  ParticleLine();
};



class StreakLine {

public:

  // Construct a streak line with p particles
  // on a  2D or 3D line
  StreakLine(double x1, double y1, double x2, double y2, int xm, int ym, int p){
    xmax=xm;
    ymax=ym;
    particles=p;
    double dx=abs((x1-x2)/(p-1));
    double dy=abs((y1-y2)/(p-1));
    for(int i=0;i<p;++i){
      pp.push_back(Particle(x1+i*dx,y1+i*dy));
      //cout<<pp[i].X<<" "<<pp[i].Y<<endl;
    }
  }
  
  //StreakLine(double x1, double y1, double z1, double x2, double y2, double z2, int p = 10);

  // This function does the whole streak line stuff!
  void traceAndInject(Data& dom, Array& u, Array& v, double delx, double dely,double dt){
    double A, B, C,A1,B1,C1;
    double x1,x2,y1,y2;
    double u1, u2, u3, u4,uu(0.),v1,v2,v3,v4,vv(0.);
    int i, j;
  
    A = -(2.5 - 1.5);
    B =0.0;
    C = -(A * 3.5 + B * 1.5);
    A1=-(2.5-1.5);
    B1=0.0;
    C1=-(A1*6+B*1.5);

    for(int k=0;k<particles;++k){
      
      i=(int)(pp[k].X/delx)+1;
      j=(int)((pp[k].Y+dely/2)/dely)+1;
      if(i<=xmax && j<=ymax){
      if(dom.isFluid(i,j)){
      x1=(i-1)*delx;
      x2=i*delx;
      y1=(j-3/2)*dely;
      y2=(j-1/2)*dely;

      if(!dom.isFluid(i-1,j-1))
	u1=0.0;
      else
	u1=u(i-1,j-1);

      if(!dom.isFluid(i,j-1))
	u2=0.0;
      else
	u2=u(i,j-1);

      if(!dom.isFluid(i-1,j))
	u3=0.0;
      else
	u3=u(i-1,j);

      if(!dom.isFluid(i,j))
	u4=0.0;
      else
	u4=u(i,j);

      uu=(1/(delx*dely))*((x2 - (pp[k].X))*(y2 - (pp[k].Y))*u1 
			  +((pp[k].X) - x1)*(y2 - (pp[k].Y))*u2
			  +(x2 -(pp[k].X))*((pp[k].Y) - y1)*u3
			  +((pp[k].X) - x1)*((pp[k].Y) - y1)*u4);
      }
      }


      i=(int)((pp[k].X+delx/2)/delx)+1;
      j=(int)(pp[k].Y/dely)+1;
      if( i<=xmax && j<=ymax){
      if(dom.isFluid(i,j)){
	x1=(i-3/2)*delx;
	x2=(i-1/2)*delx;
	y1=(j-1)*dely;
	y2=j*dely;

	if(!dom.isFluid(i-1,j-1))
	  v1=0.0;
	else
	  v1=v(i-1,j-1);

	if(!dom.isFluid(i,j-1))
	  v2=0.0;
	else
	  v2=v(i,j-1);

	if(!dom.isFluid(i-1,j))
	  v3=0.0;
	else
	  v3=v(i-1,j);

	if(!dom.isFluid(i,j))
	  v4=0.0;
	else
	  v4=v(i,j);

	vv=(1/(delx*dely))*((x2 -pp[k].X)*(y2- pp[k].Y)*v1 
			    +(pp[k].X- x1 )*(y2 - pp[k].Y)*v2 
			    +(x2 - pp[k].X)*(pp[k].Y - y1 )*v3 
			    +(pp[k].X - x1 )*(pp[k].Y - y1 )*v4);
      }

      if((A*pp[k].X+dt*uu+B*pp[k].Y+dt*vv+C)>0.0 ||((A1*pp[k].X+dt*uu+B1*pp[k].Y+dt*vv+C1)<=0.0)|| ((pp[k].Y+dt*vv)>=2.5)||((pp[k].Y+dt*vv)<=1.5) ){
	      pp[k].X=pp[k].X+dt*uu;
	      pp[k].Y=pp[k].Y+dt*vv;
	    }
      }
    }
  }

  // all coordinates of the particles
  std::vector<Particle>&  getCoords(){
    return pp;
  }

private:
  int particles;
  int xmax, ymax;
  vector<Particle> pp;
  // The default constructor is not allowed!
  StreakLine();

};

#endif
