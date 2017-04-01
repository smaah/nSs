#ifndef DATA_HH
#define DATA_HH

typedef enum {NORTH, EAST, SOUTH, WEST} DIRECTION;

class Data{

public:
  Data(int ix,int jx,double dlx,double dly): imax(ix),jmax(jx),delx(dlx),dely(dly){
    fcell=0;
  }

  
  ~Data(){}

  //wrapped access
  inline double UU(Array& u,int x,int y, DIRECTION dir);
  inline double VV(Array& v,int x,int y, DIRECTION dir);
  inline double PP(Array& p,int x,int y, DIRECTION dir);

  //direct access
  /*  inline double& uu(const int x,const  int y);
  inline double& vv(const int x,const  int y);
  inline double& pp(const int x,const  int y);
  */

  inline bool  isFluid(const int x, const int y);

  //get total number of fluid cells
  inline int getNumFluid();

  //Read and write geometry information to grayscale bitmap format
  void readpgm(string filename);
  void writepgm(string filename);

  //create basic geometries
  void blockCell(int x, int y);
  void createRectangle(double x1, double y1, double x2, double y2);
  void createCircle(int x, int y, int r);

 
  private:
  vector<vector<int>> domain;
  int imax,jmax;
  double delx, dely;
  int fcell;
};


void Data::writepgm(string filename){
  filename+=".pgm";
  ofstream f(filename);
  f<<"P2"<<endl;
  f<<imax-2<<" "<<jmax-2<<endl;
  f<<255<<endl;

  for(int j=(jmax-2);j>=1;--j){

    for(int i=1;i<(imax-1);++i){
      if(domain[i][j]==0)                                                                                                         
	f<<domain[i][j]<<" ";
      else
	f<<255<<" ";
    }
    f<<"\n";
  }
}


void Data::createRectangle(double x1,double y1,double x2, double y2){
  domain.resize(imax,vector<int>(jmax,0));
  cout<<x1<<".."<<x2<<".."<<" "<<y1<<".."<<y2<<endl;
  //  cout<<delx<<"..........."<<dely<<".."<<x1/delx<<".."<<x2/delx<<".."<<y1/dely<<".."<<y2/dely<<endl;
  
  for(int j=(jmax-2);j>=1;--j){
    
    for(int i=1;i<(imax-1);++i){
      //      if(((i>=0 && i<=40) || (i>=60 && i<=100)) && j<=10 && j>=0){
      if((i-1)>=(x1/delx) && (i-1)<(x2/delx) && (j-1)>=(y1/dely) && (j-1)<(y2/dely)){
	domain[i][j]=0; //obstacle cells
      }else{ 
	// fluid cellss
	domain[i][j]=1;
	++fcell;
      }
     
      if(i==1){
	domain[i-1][j]=0; //boundary dummy cells                                                                                                           
      }
      if(i==imax-1){
        domain[i+1][j]=0; //boundary dummy cells                                                                                                       
      }
      if(j==1){
	domain[i][j-1]=0; //boundary dummy cells                                                                                                      
      }
      if(j==jmax-1){
        domain[i][j+1]=0; //boundary dummy cells                                                                                                           
      }

    }
    
  }
}

inline int Data::getNumFluid(){

  return fcell;
}


inline bool  Data::isFluid(const int x, const int y){
  
  return domain[x][y];
}


inline double Data::UU(Array& u,int x,int y, DIRECTION dir){ 
  if(dir==NORTH)
    return u(x,y-1);
  if(dir==SOUTH)
    return u(x,y+1);
  

  return 0.0;
}

inline double Data::VV(Array& v,int x,int y, DIRECTION dir){

  if(dir==WEST)
    return v(x+1,y);
  if(dir==EAST)
    return v(x-1,y);



  return 0.0;
}

inline double Data::PP(Array& p,int x,int y, DIRECTION dir){
  if(dir==EAST)
    return p(x-1,y);
  if(dir==WEST)
    return p(x+1,y);
  if(dir==NORTH)
    return p(x,y-1);
  if(dir==SOUTH)
    return p(x,y+1);

  return 0.0;
}





#endif // DATA_HH
