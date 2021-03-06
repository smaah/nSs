#ifndef FILEREADER_HH
#define FILEREADER_HH


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <sstream>
#include "Debug.hh"
#include <cctype>
using namespace std;

//typedef enum {width, height, x, y,initial} BCTYPE;

class FileReader
{
   
public:

  FileReader(char *fname);
  ~FileReader();          

	//register a new parameter with name key and initial int value
        void RegisterIntParameter(const std::string& key, int init);

	//register a new parameter with name key and initial double value
        void RegisterDoubleParameter(const std::string& key, double init);

	//register a new parameter with name key and initial string value
        void RegisterStringParameter(const std::string& key, const std::string &init);

	//set a value for the key string with value in
	void SetParameter(const std::string &key, const std::string &in);

	//set a value for the key string with value in
	void SetParameter(const std::string &key, double in);

	//set a value for the key string with value in

	void SetParameter(const std::string &key, int in);

	// get the int value of key 
	inline int GetIntParameter(const std::string &key) const;

	// get the double value of key 
	inline double GetDoubleParameter(const std::string &key) const;

	// get the string value of key 
	inline std::string GetStringParameter(const std::string &key) const;

	//try to read the file name
	bool ReadFile();

       
   
   private:
    size_t pos;
    int val1;
    double val2;
    std::string s;
    std::ifstream f;
    char *filename;
  

};



 FileReader::FileReader(char *fname){
   std::cout<<"\n.....Constructing data base....";
 filename=fname;
}


void FileReader::RegisterIntParameter(const std::string& key, int init)
{
std::cout<<"\n Registering... "<<key;
 val1=init;
}

void FileReader::RegisterDoubleParameter(const std::string& key, double init)
{
 std::cout<<"\n Registering... "<<key;
 val2=init;
}

void FileReader::RegisterStringParameter(const std::string& key, const std::string &init)
{
  std::cout<<"\n Registering... "<<key;
  s=init;
}


void FileReader::SetParameter(const std::string &key, const std::string& in)
{
  f.open(filename);
  std::string l1, l2;
  std::string line;
  s=in;
 while (!f.eof()) // runs until the end of file
    {
        std::getline(f, line, '#'); //getting each line until #
        pos = line.find(key); //finding the position of the key word
        if (pos != string::npos) {  //if the key is found 
	   istringstream str(line); // splitting the string
	    while(l1!=key){ 
            str >> l1;
	    str >> l2;
	    if(l1==key) s=l2;   
	    }
	    l1.clear();
	    l2.clear();  
	    l1.resize(25);
            l2.resize(25);
        }    
       f.ignore(numeric_limits<streamsize>::max(), '\n'); //going to the next line neglecting further elements
       line.clear();
       line.resize(25);
    }

 f.close();
}


void FileReader::SetParameter(const std::string &key, double in)
{
  f.open(filename);
  std::string l1, l2;
  std::string line;
  val2=in;
 while (!f.eof()) // runs until the end of file
    {
        getline(f, line, '#'); //getting each line until #
        pos = line.find(key); //finding the position of the key word
        if (pos != string::npos) {  //if is found 
           istringstream str(line); // splitting the string
	   while(l1!=key && !atof(l2.c_str())){
	     str>>l1;
	     str>>l2;
	     if(l1==key) val2=atof(l2.c_str());
	   }                                                                                              
	   l1.clear();
	   l2.clear();
	   l1.resize(25);
           l2.resize(25);          
        }    
	f.ignore(numeric_limits<streamsize>::max(),'\n'); //going to the next line neglecting further elements
	line.clear();
	line.resize(25);
    }
 f.close();

}


void FileReader::SetParameter(const std::string &key, int in)
{
  f.open(filename);
  std::string line;
  std::string l1, l2;
  val1=in;
  while (!f.eof()) // runs until the end of file
    {
      std::getline(f,line,'#'); 	
        pos = line.find(key); //finding the position of the key word
        if (pos != string::npos) {  //if is found 

	  istringstream str(line); // splitting the string                                                                                          

	  while(l1!=key){
            str >> l1;
	    str >> l2;
	    if(l1==key) {val1 = atoi(l2.c_str());}
	  }
      
	    l1.clear();
	    l2.clear();
	    l1.resize(50);
            l2.resize(50);
        }    
        f.ignore(numeric_limits<streamsize>::max(), '\n'); //going to the next line  neglecting further elements
	line.clear();
	line.resize(50);
    }

  f.close();
}

inline int FileReader::GetIntParameter(const std::string &key) const
{
  cout<<"\n" << key<< " is " << val1<<"\n";
  return val1;
}


inline double FileReader::GetDoubleParameter(const std::string &key) const
{
 cout<<"\n" << key<< " is " << val2<<"\n";
 return val2;
}

inline std::string FileReader::GetStringParameter(const std::string &key) const
{
 cout<<"\n" << key<< " is " << s<<"\n";
 return s;
}


bool FileReader::ReadFile()
{  
  f.open(filename);
  if(f.is_open()){
    f.close();
    return true;
  }else 
    return false;
  }


FileReader::~FileReader(){

  if(f.is_open())
    cout<<"\n \n ....Destructor closed the file.... \n";
  else
    cout<<"\n \n ....The parameter file is closed.... \n";

}


#endif //FILEREADER_HH

