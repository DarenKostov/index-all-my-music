
#include "mainClass.hxx"

#include <iostream>
#include <csignal>

//prints the licence
void printLicence();
//prints all flags
void printHelp();
//prints the version
void printVersion();


//at exit free the MainClass object 
void atExitFree(MainClass*);

static void freeVariable(){

  std::cout << "\e[93mAbout to Free Main\n\e[0m";
  atExitFree(NULL);
}

void atExitFree(MainClass* in){

  //store a static pointer to our Main
  static MainClass* eternalPtr;


  //if we give it a valid pointer, store it; if not, delete it
  if(in){
    std::cout << "\e[93mStoring Main\n\e[0m";
    eternalPtr=in;
    atexit(freeVariable);
  }else{
    std::cout << "\e[93mFreeing Main\n\e[0m";
    delete eternalPtr;
  }
}




void signal_handler(int signal_num){

  std::cout << "\n\e[93mSignal Handler!\n";
  std::cout << "Signal: " << signal_num << "\n\e[0m";
  exit(signal_num);
}


int main(int argc, char **argv){


  //check all flags
  for(int i=0; i<argc; i++){
    std::string thisArg=std::string(argv[i]);
    if(thisArg=="-l" || thisArg=="--licence"){
      printLicence();
      return 0;
    }else if(thisArg=="-h" || thisArg=="--help"){
      printHelp();
      return 0;
    }else if(thisArg=="-v" || thisArg=="--version"){
      printVersion();
      return 0;
    }
  }


  std::cout << "\e[93mstart of program\n\e[0m";

  signal(SIGINT, signal_handler);


  MainClass* mainInstance=new MainClass();
  atExitFree(mainInstance);

  mainInstance->startProgram();
  

}

//FUNCTION DEFINITION


void printHelp(){
  std::cout << "-h, --help: this help\n";
  std::cout << "-l, --licence: print the licence\n";
  std::cout << "-v, --version: prints the version\n";

}


void printVersion(){
  std::cout << "Copyright (c) Daren Kostov\n";
  std::cout << "GPLv3\n";
  std::cout << "TEMPLATE\n";
    
  //Version Major.Minor.Patch
  std::cout << "Version 0.0.0\n";

}