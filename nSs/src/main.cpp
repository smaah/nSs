#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>

#include "FileReader.hh"
#include "Array.hh"
#include "Types.hh"
#include "Debug.hh"
#include "Solver.hh"
#include "VTKFileWriter.hh"
#include "Particle.hh"

using namespace std;

int main(int argc, char *argv[]) {

    INFO;
    FILECHECK(argc);
    real delx,dely;
    real eps;
    int maxit, xmax, ymax, bcE,bcW,bcS,bcN;
    string name;
    real omega,gx,gy,Re,dtt,gamma,uinit,vinit,pinit,tau,tend, xlength;
    real t_vis, del_save, del_inj, s_x1, s_y1, s_x2, s_y2;
    int n_part;

    vector<double > length;
    vector<int > dimension;


    FileReader InT(argv[1]), DouB(argv[1]), StR(argv[1]);
    map<const string, int> IntParameters;
    map<const string, real> DoubleParameters;
    map<const string, string> StrParameters;

    map<const string, int>::iterator Iit;
    map<const string, int>::iterator point;
    map<const string, real>::iterator Dit;
    map<const string, string>::iterator Sit;
    
    ASSERT(InT.ReadFile());
    // Insert the parameters here with default integer values
    IntParameters.insert(pair<const string, int>("nparticles",10));
    IntParameters.insert(pair<const string, int>("imax", 0));
    IntParameters.insert(pair<const string, int>("jmax", 0));
    IntParameters.insert(pair<const string, int>("itermax", 0));
    IntParameters.insert(pair<const string, int>("bcN", 0));
    IntParameters.insert(pair<const string, int>("bcS", 0));
    IntParameters.insert(pair<const string, int>("bcE", 0));
    IntParameters.insert(pair<const string, int>("bcW", 0));
    
 
    //Insert the parameters here with default double values
    
    DoubleParameters.insert(pair<const string, real>("xlength", 0.0));
    DoubleParameters.insert(pair<const string, real>("ylength", 0.0));
    DoubleParameters.insert(pair<const string, real>("eps", 0.0));
    DoubleParameters.insert(pair<const string, real>("omg", 0.0));
    DoubleParameters.insert(pair<const string, real>("GX", 0.0));
    DoubleParameters.insert(pair<const string, real>("GY", 0.0));
    DoubleParameters.insert(pair<const string, real>("Re", 100.0));
    DoubleParameters.insert(pair<const string, real>("U_INIT", 0.0));
    DoubleParameters.insert(pair<const string, real>("V_INIT", 0.0));
    DoubleParameters.insert(pair<const string, real>("P_INIT", 0.0));
    DoubleParameters.insert(pair<const string, real>("delt", 0.001));
    DoubleParameters.insert(pair<const string, real>("gamma", 0.5));
    DoubleParameters.insert(pair<const string, real>("tau", 0.5));
    DoubleParameters.insert(pair<const string, real>("t_end", 5.0));
    DoubleParameters.insert(pair<const string, real>("t_visualize",10.0));
    DoubleParameters.insert(pair<const string, real>("delt_save",5.0));
    DoubleParameters.insert(pair<const string, real>("delt_inject",5.0));
    DoubleParameters.insert(pair<const string, real>("streak_x1",0.0));
    DoubleParameters.insert(pair<const string, real>("streak_y1",0.0));
    DoubleParameters.insert(pair<const string, real>("streak_x2",0.0));
    DoubleParameters.insert(pair<const string, real>("streak_y2",2.5));
    
    //Insert the string parameters here with default string 
    StrParameters.insert(pair<const string, string > ("name", "TEST"));

    //Registering the parameters and updating the parameters from file
    for (Iit = IntParameters.begin();  Iit!= IntParameters.end(); ++Iit) {
      InT.RegisterIntParameter((*Iit).first, (*Iit).second);
        InT.SetParameter((*Iit).first, (*Iit).second);
        (*Iit).second = InT.GetIntParameter((*Iit).first);
    }


    for (Dit = DoubleParameters.begin(); Dit != DoubleParameters.end(); ++Dit) {
      DouB.RegisterDoubleParameter((*Dit).first, (*Dit).second);
        DouB.SetParameter((*Dit).first, (*Dit).second);
        (*Dit).second = DouB.GetDoubleParameter((*Dit).first);
    }


    for (Sit = StrParameters.begin(); Sit != StrParameters.end(); ++Sit) {
      StR.RegisterStringParameter((*Sit).first, (*Sit).second);
        StR.SetParameter((*Sit).first, (*Sit).second);
        (*Sit).second = StR.GetStringParameter((*Sit).first);
    }


       //Initialization of the pressure and right hand side
       bcW=IntParameters.find("bcW")->second;
       bcN=IntParameters.find("bcN")->second;
       bcS=IntParameters.find("bcS")->second;
       bcE=IntParameters.find("bcE")->second;
       eps =DoubleParameters.find("eps")->second;
       maxit = IntParameters.find("itermax")->second;
       omega = DoubleParameters.find("omg")->second;
       dtt=DoubleParameters.find("delt")->second;
       Re=DoubleParameters.find("Re")->second;
       gamma=DoubleParameters.find("gamma")->second;
       gx=DoubleParameters.find("GX")->second;
       gy=DoubleParameters.find("GY")->second;
       name = StrParameters.find("name")->second;
       uinit=DoubleParameters.find("U_INIT")->second;
       vinit=DoubleParameters.find("V_INIT")->second;
       pinit=DoubleParameters.find("P_INIT")->second;
       tau=DoubleParameters.find("tau")->second;
       tend=DoubleParameters.find("t_end")->second;
       xlength=DoubleParameters.find("xlength")->second;
       xmax=IntParameters.find("imax")->second;
       ymax=IntParameters.find("jmax")->second;
       t_vis=DoubleParameters.find("t_visualize")->second;
       del_save=DoubleParameters.find("delt_save")->second;
       del_inj=DoubleParameters.find("delt_inject")->second;
       s_x1=DoubleParameters.find("streak_x1")->second;
       s_y1=DoubleParameters.find("streak_y1")->second;
       s_x2=DoubleParameters.find("streak_x2")->second;
       s_y2=DoubleParameters.find("streak_y2")->second;
       n_part=IntParameters.find("nparticles")->second;

       Iit=IntParameters.find("imax");
       Dit=DoubleParameters.find("xlength");    
       delx= ((*Dit).second)/((*Iit).second);
      
       point=IntParameters.find("jmax");
       Dit=DoubleParameters.find("ylength");
       dely=((*Dit).second)/((*point).second);
       

       //Dynamic memory allocation of the Array
       Array pp(xmax+2,ymax+2), 
	 ff(xmax+2,ymax+2),
	 U(xmax+1,ymax+2),
	 F(xmax+1,ymax+2),
	 V(xmax+2,ymax+1),
	 G(xmax+2,ymax+1);     
     
       //Initialization
       pp.fill(pinit,xmax+2,ymax+2,0);
       ff.fill(0.0,xmax+2,ymax+2,0);
       U.fill(uinit,xmax+1,ymax+2,0);
       F.fill(uinit,xmax+1,ymax+2,0);
       V.fill(vinit,xmax+2,ymax+1,0);
       G.fill(vinit,xmax+2,ymax+1,0);


       length.push_back(delx);
       length.push_back(dely);
       dimension.push_back(xmax);
       dimension.push_back(ymax);
     
       
       Solver kk(xmax,ymax,maxit,bcE,bcW,bcN,bcS,delx,dely,eps,omega,Re,gamma,gx,gy,tau,tend,dtt,name);
       //kk.initFields(U);

       Data dome(xmax+2,ymax+2,delx,dely);
       dome.createRectangle(3.5,1.5,6.0,2.5);
       //dome.createRectangle(0.0,0.0,7.5,0.75);
       dome.writepgm(name);
       ParticleLine Part(s_x1, s_y1, s_x2, s_y2,xmax,ymax,n_part);
       //kk.initFields(U,dome);
       kk.SOLVE(pp, ff, U, V, F, G,dome,Part,xlength,s_x1,s_y1,s_x2,s_y2,n_part, t_vis,  del_save, del_inj);
       
       return 0;
}
