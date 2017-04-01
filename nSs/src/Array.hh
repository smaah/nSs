#ifndef ARRAY_HH
#define ARRAY_HH

#include "Types.hh"
#include "Debug.hh"


using namespace std;

class Array {
  
    public:
  
  // Constructor 1D
  Array(int x);	
  // Constructor 2D
  Array(int x,int y);
  
  // Constructor 3D
  Array(int x,int y,int z);
  
  ~Array();
  
  // Operator() 1D
  inline real& operator ()(int i){
    BOUND1(i,m);
    return oneD[i];
  }

  

        // Operator() 2D
  inline real& operator ()(int i,int j){
    BOUND2(i,j,m,n);
    return twoD[i][j];
  }

     

        // Operator() 3D
  inline real& operator ()(int i, int j, int k){
    BOUND3(i,j,k,m,n,o);
    return threeD[i][j][k];
  }

       

  //initialize the whole array with a constant value
  inline void fill(real in,int mm, int nn, int oo);
  
  //return the dimension of the array
  inline int getDimension() const;
        

  //return total size of the array
  inline int getSize() const;
     
  // Print the whole array after doubling
  inline void print();
    

private:
  real *oneD;
  real **twoD;
  real ***threeD;
  int m,n,o;
  
};


Array::Array(int x){

  oneD=new real[x];
  m=x;
  n=0;
  o=0;
}

Array::Array(int x,int y){
  try{
    twoD=new real *[x];
    for(int i=0;i<x;++i)
      twoD[i]= new real [y];
  }catch(bad_alloc& bad){
    cout<<"Checking Memory................................" <<bad.what()<<endl;
  }  
  m=x;
  n=y;
  o=0;
}

Array::Array(int x, int y, int z){
  threeD=new real **[x];
  for(int i=0;i<x;++i){
    threeD[i]=new real *[y];
    for(int j=0;j<y;++j)
      threeD[i][j]=new real [z];
}
  m=x;
  n=y;
  o=z;
}



inline void Array::fill(real in, int mm, int nn, int oo)
{ 
  
  if(mm!=0 && nn==0 && oo==0)
    for(int i=0;i<mm;++i)
      oneD[i]=in;
  else if(mm!=0 && nn!=0 && oo==0){
    for(int i=0; i<mm;++i)
      for(int j=0; j<nn; ++j){
	twoD[i][j]=in;
      }
  }else if(mm!=0 && nn!=0 && oo!=0){
    for (int i = 0; i < mm; ++i) 
      {
        for (int j = 0; j < nn; ++j)
	  {
	  for(int k=0; k<oo; ++k)
	    threeD[i][j][k]=in;
	  } 
      }
  }
  
  
}

inline int Array::getDimension() const
        {
	  cout<<"\n\n the dimension is row = "<<m<<" column =  "<<n<<" length= "<<o<<"\n";
	  return 0;
        }


inline void Array::print(){

  if(m!=0 && n!=0 && o==0){
    for(int i=0; i<m;++i){
      {for(int j=0; j<n; ++j)
	  //cout<<"\n Array["<<i<<"]"<<"["<<j<<"] = "<<twoD[i][j];
	  cout<<twoD[i][j]<<"\n";
      }
      //cout<<"\n...............\n";
    }
  }else if(m!=0 && n!=0 && o!=0){
    for(int i=0; i<m;++i){
      for(int j=0; j<n; ++j){
	for(int k=0;k<o;++k)
	  //     cout<<"\n Array["<<i<<"]"<<"["<<j<<"]"<<"["<<k<<"] ="<<threeD[i][j][k];
	  cout<<threeD[i][j][k]<<"\n";
      }
      
      cout<<"\n...............\n";
    }
  }else{
    for(int i=0; i<m;++i)
      //cout<<"\n Array["<<i<<"] = "<<oneD[i];
      cout<<oneD[i]<<"\n";
  }
}

Array::~Array(){
  cout<<"I am called from Array"<<endl;
  cout<<"\n \n.......Deallocation.....\n \n";
  if(m!=0 && n==0 && o==0){
    delete[] oneD;
    oneD=NULL;
    if(!oneD)
      cout<<"\n \n Success";}
  else if(m!=0 && n!=0 && o==0){
    for(int i=0; i<m;++i)
      delete[] twoD[i];
    delete[] twoD;
    twoD=NULL;
    if(!twoD)
      cout<<"\n \n Success \n \n";
  }else if(m!=0 && n!=0 && o!=0){
    for (int i = 0; i < m; ++i) 
      {
        for (int j = 0; j < n; ++j)
	  {
            delete[] threeD[i][j];
	  }
        delete[] threeD[i];
      }
    delete[] threeD;
  }
  threeD=NULL;
}

#endif //ARRAY_HH

