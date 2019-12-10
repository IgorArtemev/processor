#include "processor.h"
using namespace Processor;
using namespace std;
namespace Processor{
    int add::operator()(int a, int b){
        return a+b;
    };
    int sub::operator()(int a, int b){
        return a-b;
    };
    int mul::operator()(int a, int b){
        return a*b;
    };
    int div::operator()(int a, int b){
        int res;
        try{
            res=a/b;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Division by zero");
        }
        return res;
    };
    int inc::operator()(int a){
        return ++a;
    };
    int dec::operator()(int a){
        return --a;
    };
    int jmp::operator()(const string& s,program_memory& prm){
        int i;
        try{
            i=prm.getM(s);
        }
        catch(exception &ex){
                    cout<<ex.what()<<std::endl;
                    throw std::runtime_error("Invalid mark");
        }
        if(i!=-1)
            prm.setIP(i);
        return i;
    };
    int jnz::operator()(const string& s,program_memory& prm,const operand_descriptor* od,const registers& reg,const data_memory& dm){
        int i,t; 
        t=getOp(od,reg,dm);
        if(t){
        try{
            i=prm.getM(s);
        }
        catch(exception &ex){
                    cout<<ex.what()<<std::endl;
                    throw std::runtime_error("Incorect mark");
        }
        if(i!=-1)
            prm.setIP(i);
        return i;
        }
        return 1;
    };
    int hlt::operator(){
        return 0;
    };
    int move::operator()(operand_descriptor* f,operand_descriptor* s,registers& reg,data_memory& dm){
        if (f->getT()==0)   
        int n;
        n=getOp(s,reg,dm);
        setOp(f,reg,dm,n);
        return 1;
    };
}