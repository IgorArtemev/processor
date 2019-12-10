#include "processor.h"
using namespace Processor;
using namespace std;
namespace Processor{
    unary_command::unary_command(string& s,operand_descriptor* od, int t){
        type=t;
        mark=s;
        operand=od;
    };
    string unary_command::getM{
        return mark;
    };
    operand_descriptor* unary_command::getOp(){
        return operand;
    };
    void unary_command::show(){
        cout<<"Unary command:";  
        cout<<arr[type];
        if (operand->getT()==1){
            cout<<"REG "<<operand->getR<<endl;
        }
        else {
            cout<<operand->getStr()<<endl;
        }
    };
    void unary_command::modify(){
        cout<<"Enter type of operation:"<<endl;
        cout<<"1-INC"<<endl;
        cout<<"1-INC"<<endl;
    };
    binary_command::binary_command(string& m,operand_descriptor* f, operand_descriptor* s,int t){
        type=t;
        mark=m;
        first=f;
        second=s;
    };
    string bainary_command::getM(){
        return mark;
    };
    operand_descriptor* binary_command::getF(){
        return first;
    };
    operand_descriptor* binary_command::gets(){
        return second;
    };
    void binary_command::show(){
        cout<<"Unary command:";  
        cout<<arr[type]<<' ';
        if (operand->getT()==1){
            cout<<"REG "<<first->getR;
        }
        else {
            cout<<first->getStr();
        }
        if (second->getT()==0){
            cout<<second->get();
        }
        else if (second->getT()==1){
            cout<<"REG "<<second->getR<<endl;
        }
        else {
            cout<<operand->getStr()<<endl;
        }
    };
    string transition_command::getM(){
        return mark;
    };
    transition_command::transition_command(string& str){
        mark=str;
    };
    void transition_command::show(){
        cout<<"JMP "<<mark<<endl;
    }
    string cond_transition_command::getM(){
        return mark;
    };
    cond_transition_command::cond_transition_command(string& str,operand_descriptor* o){
        mark=str;
        op=o;
    };
    void cond_transition_command::show(){
        cout<<"JNZ "<<mark;
        if (operand->getT()==1){
            cout<<"REG "<<operand->getR<<endl;
        }
        else {
            cout<<operand->getStr()<<endl;
        }
    };
    operand_descriptor* move_command::getF(){
        return first;
    };
    operand_descriptor* move_command::getS(){
        return second;
    };
    move_command::move_command(operand_descriptor* f,operand_descriptor* s){
        first=f;
        second=s;
    };
    void move_command::show(){
        cout<<
        if (operand->getT()==1){
            cout<<"REG "<<first->getR;
        }
        else {
            cout<<first->getStr();
        }
        if (second->getT()==0){
            cout<<second->get();
        }
        else if (second->getT()==1){
            cout<<"REG "<<second->getR<<endl;
        }
        else {
            cout<<operand->getStr()<<endl;
        }
    };
    int operand_descriptor::getT{
        return type;
    };
    int reg_operand::get(registers& m){
        return m.get(reg);
    };
    void reg_operand::set(int n){
        reg=n;
    };
    int reg_operand::setD(int n, registers& m){
        m.set(reg,n);
    };
    id_operand::id_operand(){
        str=string();
    };
    id_operand::id_operand(string& s){
        str=s;
    };
    int id_operand::get(const data_memory& m){
        return m.get(str);
    };
    void id_operand::set(string& s){
        str=s;
    };
    int setD(int n, data_memory& m){
        return m.set(n,str);
    };
    direct_operand::direct_operand(){
        number=0;
    };
    direct_operand::direct_operand(int n){
        number=n;
    };
    void direct_operand::set(int n){
        number=n;
    };
    int direct_operand::get(){
        return nubmer;
    };
     
