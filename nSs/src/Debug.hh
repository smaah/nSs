#ifndef DEBUG_HH
#define DEBUG_HH

#include <iostream>


using namespace std;


//http://patrick.wagstrom.net/old/misc/dotfiles/dotbash_profile.html
#define BLACK         "\033[0;30m"
#define RED           "\033[0;31m"
#define GREEN         "\033[0;32m"
#define BROWN         "\033[0;33m"
#define BLUE          "\033[0;34m"
#define MAGENTA       "\033[0;35m"
#define CYAN          "\033[0;36m"
#define WHITE         "\033[0;37m"
#define LIGHTBLACK    "\033[1;30m"
#define LIGHTRED      "\033[1;31m"
#define LIGHTGREEN    "\033[1;32m"
#define YELLOW        "\033[1;33m"
#define LIGHTBLUE     "\033[1;34m"
#define LIGHTMAGENTA  "\033[1;35m"
#define LIGHTCYAN     "\033[1;36m"
#define LIGHTWHITE    "\033[1;37m"
#define RESET         "\033[0m"


#define debugMessage(stream, color, messageType, message, source) \
  stream << color << messageType; \
  if(source)  \
  { \
    stream << "in " << __FILE__ << " on line " << __LINE__ << " ";  \
  } \
  stream << message << BLACK << endl << flush;

#define ERROR(message) \
  debugMessage(std::cerr, RED, "ERROR ", message, true) \
  { cout<<YELLOW<<"\n Erorr: in file"<<__FILE__<<" at line "<<__LINE__<<"\n"<<BLACK; \
    exit(EXIT_FAILURE); }
  
#ifdef DEBUG 
// Asserts expr expression, if false exits with error
#define ASSERT(a) \
  if(!(a)) { cout<<RED<<"\n Cannot read parameter file, error:"<<__FILE__<<" at line "<<__LINE__<<"\n"<<RESET; \
    exit(-1); }								\
   
#define MEM(a)\
  if(a==NULL) { cout<<RED<<"\n Memory allocation failed, error: "<<__FILE__<<" at line "<<__LINE__<<"\n"<<RESET; \
    exit(-1); }\
  else\
    cout<<"\n\n\t.....!!Memory allocation success!!!.....\n\n";

#define INFO cout<<"\n\n\t..... //\\DEBUG MODE IS ON//\\ .....\n\n"\
  <<"\t Date...: "<<__DATE__<<"\n\t Time...: "<<__TIME__<<"\n\n\n" ;

#define BOUND2(x,y,m,n) \
  if(x>=m || y>=n) { cout<<RED<<"\n \n Out of bound index (x,y) file:"<<__FILE__<<" at line "<<__LINE__<<"\n"<<BLACK; \
    exit(-1); }

#define BOUND1(x,m) \
  if(x>=m) { cout<<RED<<"\n \n Out of bound index (x,y) file:"<<__FILE__<<" at line "<<__LINE__<<"\n"<<BLACK; \
    exit(-1); }

#define BOUND3(x,y,z,m,n,o)						\
  if(x>=m || y>=n || z>=o) { cout<<RED<<"\n \n Out of bound index (x,y) file:"<<__FILE__<<" at line "<<__LINE__<<"\n"<<BLACK; \
    exit(-1); }  

#define FILECHECK(a)\
 if(a<2) { cout<<RED<<"\n \n !!!Please enter the name of the parameter file and run again!!! error:"<<__FILE__<<" at line "<<__LINE__<<"\n"<<RESET; \
  exit(-1); }

#define SUCCESS cout<<"\n\n!!!SUCCESSFUL!!!\n\n";


#else
#define ASSERT(a) \
  if(!(a)) { cout<<"\n\n Error... turn on the debug mode to see the details \n\n"; \
    exit(-1); }

#define INFO  cout<<"\n\n\t..... //\\DEBUG MODE IS OFF//\\ .....\n\n";


#endif //DEBUG
#endif // DEBUG_HH
