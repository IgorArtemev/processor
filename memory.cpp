#include "processor.h"
using namespace Processor;
using namespace std;
namespace Processor{
    registers::registers(){
        N=10;
        cell i;
        for (int i=0; i < 10; i++) {
            rg.push_back(i);
        };
    };
    registers::registers(int n){
        N=n;
        cell i;
        for (int i=0; i < N; i++) {
            rg.push_back(i);
        };
    };
    int registers::set(int reg, int n){
        if(reg>N-1||reg<0)
             throw std::runtime_error("Invalid value of register");
        rg[reg].a=n;
        return 1;
    };
    int registers::get(int n){
        return rg[n].a;
    };
    int registers::block(int reg){
        if(reg>N-1||reg<0)
            return 0;
        rg[reg].free=false;
        return 1;
    };
    void registers::show(){
        for(int i=0;i<rg.size();++i){
            cout<<rg[i].a<<endl;
        }
    };
    int registers::unblock(int reg){
        if(reg>N-1||reg<0)
            return 0;
        rg[reg].free=true;
        return 1;
    };
    void registers::show(){
        for(int i=0;i<rg.size();++i){
            cout<<rg[i].a<<endl;
        }
    };
    data_memory::data_memory(){
        size=100;
    };
    data_memory::data_memory(int N){
        size=N;
    };
    int data_memory::get(string& str){
        int res;
        try{
            res=arr.at(str).a;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
            return 0;
        }
        return res;
    };
    int data_memory::set(string& str,int a){
        int res;
        try{
            arr.at(str).a=a;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
            return 0;
        }
        return 1;
    };
    void unblock(string& str){
        try{
            arr.at(str).free=true;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
            return 0;
        }
        return 1;
    };
    void block(string& str){
        try{
            arr.at(str).free=false;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
            return 0;
        }
        return 1;
    };
    void add(string& str, int a){
        if(arr.size()>=N){
            throw std::runtime_error("Overflow of memory");
        }
        arr[str].a=a;
    };
    program_memory::program_memory(program& pr){
        ip=0;
        for(int i=0;i<pr.arr.size();++i){
            arr[i]
        }
    };
    
    