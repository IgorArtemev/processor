#include <iostream>
#include <string>
#include "vector.h"
#include <map>
#include <set>
using namespace std;
    class operand_descriptor;
    class registers;
    class processor;
    class program;
    class data_memory;
    class program_memory;
    class actuator;
    class add{
        public:
            int operator()(int,int);
    };
    class sub{
        public:
            int operator()(int,int);
    };
    class mul{
        public:
            int operator()(int,int);
    };
    class div_a{
        public:
            int operator()(int,int);
    };
    class inc{
        public:
            int operator()(int);
    };
    class dec_a{
        public:
            int operator()(int);
    };
    class jmp{
        public:
            int operator()(string,program_memory&);
    };
    class jnz{
        public:
            int operator()(string,program_memory&,operand_descriptor*, registers& , data_memory& );
    };
    class move_a{
        public:
            int operator()(operand_descriptor*,operand_descriptor*,registers& r,data_memory& m);
    };
    class hlt{
        public:
            int operator()(program_memory&);
    };
    class command{                                               
        protected: 
            int type;
            string mark;         
        public:
            string getM(){
                return mark;
            };
            int getT(){
                return type;
            };
            virtual void show()=0;
            virtual operand_descriptor* getF(){

            };
            virtual operand_descriptor* getS(){

            };
            virtual operand_descriptor* getOp(){

            };
            virtual string getTM(){
            };
    };
    class operand_descriptor{
        protected:
            int type;                           //0-direct,1-register,2-memory
        public:
            virtual int f()=0;
            int getT();
            virtual int get(){};
            virtual void set(int){};
            virtual int get(registers&){};
            virtual int get( data_memory&){};
            virtual int getR(){};
            virtual int setD(int,registers&){};
            virtual string getStr(){};
            virtual void set(string){};
            virtual int setD(int,data_memory&){};
    };
    class reg_operand:public  operand_descriptor{
        private:
            int reg;
        public:
            int f(){};
            int getR();
            reg_operand(int);
            int get(registers&);
            void set(int);
            int setD(int,registers&);
    };
    class id_operand:public  operand_descriptor{
        private:
            string str;
        public:
            int f(){};
            string getStr();
            id_operand(string);
            int get( data_memory&);
            void set(string);
            int setD(int,data_memory&);
    };
    class direct_operand:public  operand_descriptor{
        private:
            int number;
        public:
            int f(){};
            direct_operand();
            direct_operand(int);
            int get();
            void set(int);
    };
    class unary_command:public command{
        private:
            operand_descriptor* operand; 
        public:
            operand_descriptor* getF();
            unary_command(string,operand_descriptor*,int);
            void show();
    };
    class binary_command:public virtual command{
        private:
            operand_descriptor* first;
            operand_descriptor* second;
        public:
            operand_descriptor* getF();
            operand_descriptor* getS();
            binary_command(string,operand_descriptor*,operand_descriptor*, int);
            void show();
    };  
    class transition_command: public command{
        private:
            string tmark;
        public:
            string getTM(){
                return tmark;
            };
            transition_command(string,string);
            void show();
    };
    class cond_transition_command: public command{
        private:
            string tmark;
            operand_descriptor* op;
        public:
            cond_transition_command(string,string, operand_descriptor*);
            string getTM(){
                return tmark;
            };
            operand_descriptor* getOp();
            void show();
    };
    class move_command:public command{
        private:
            operand_descriptor* first;
            operand_descriptor* second;
        public:
            operand_descriptor* getF();
            operand_descriptor* getS();
            move_command(operand_descriptor*,operand_descriptor*,string);
            void show();
            void modify(); 
    };
    class hlt_command:public command{
        public:
            hlt_command(string);
            void show();
    };
    struct cell{
        int a;
        bool free;
        cell(){
            a=0;
            free=true;
        };
    };
    class registers{
        private:
            int N;
            Vector<cell> rg;
        public:
            registers();
            registers(int);
            int insert(int,int);
            int get(int);
            int unblock(int);
            int block(int);
            void set(int,int);
            void show();
    };
    class actuator{
        private:
            bool empty;
            int time;
            set<int> ops;
        public:
            actuator();
            actuator(int);
            actuator(int,set<int>&);
            bool getEmpty();
            int execution(command*,registers&,data_memory&);
            friend class control_device;
    };
    class control_device{
        public:
            int selection(command*,Vector<actuator>&);
            void transition(command*,program_memory&,registers&, data_memory&);
            command* get(program_memory&);
    };
    class program_memory{
        private:
            int ip;
            Vector<command*> arr;
            map<string,int> marks;
        public:
            void loadPr(program&);
            command* getCommand();
            void show();
            program_memory& setIP(int);
            void setEnd();
            void inc_ip();
            int getM(string);
            program_memory& modify();
    };
    class data_memory{
        private:
            int size;
            map<string,cell> arr;
        public:
            data_memory();
            data_memory(int);
            int get(string);
            void  set(string,int);
            void unblock(string);
            void block(string);
            void add(string,int);
            void show();
    };
    class program{
        private:
            Vector<command*> arr;
        public:
            program();
            void show();
            void modify();
            void save();
            void load();
            void modify_command(int);
        friend class program_memory;
    };
    class processor{
        private:
            control_device cd;
            registers reg;
            int n_act;
            Vector <actuator> act;
            program_memory pr_m;
            data_memory data_m;
        public:
            processor();
            void modify();
            int execution(program&); 
            void show_memory();
    };
    int setOp(operand_descriptor* op,registers& reg,data_memory& dm, int res);
    int getOp(operand_descriptor* op,registers& reg,data_memory& dm);
