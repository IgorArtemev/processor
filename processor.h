#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
namespace Processor{
    class operation{
        public:
            virtual int operator()(int,int);
    };
    class add:public operation{
        public:
            int operator()(int,int);
    };
    class sub:public operation{
        public:
            int operator()(int,int);
    };
    class mul:public operation{
        public:
            int operator()(int,int);
    };
    class div:public operation{
        public:
            int operator()(int,int);
    };
    class inc:public operation{
        public:
            int operator()(int);
    };
    class dec:public operation{
        public:
            int operator()(int);
    };
    class program_memory;
    class jmp:public operation{
        public:
            int operator()(const string&,program_memory&);
    };
    class registers;
    class data_memory;
    class operand_descriptor;
    class jnz:public operation{
        public:
            int operator()(const string&,program_memory&, const registers& ,const data_memory& )
    };
    class move:public  operation{
        public:
            int operator()(operand_descriptor*,operand_descriptor*,registers& r,data_memory& m);
    };
    class hlt:public operation{
        public:
            int operator()();
    };
    class command{                                               
        protected: 
            int type;            
        public:
            operation* getOP(){
                return op;
            }
            int getT(){
                return type;
            }
            virtual void show()=0;
            virtual void modify();
    };
    class operand_descriptor{
        protected:
            int type;                           //0-direct,1-register,2-memory
        public:
            int getT();
            virtual int get()=0;
            virtual void set(int);
            virtual int get(registers&);
            virtual int get(const data_memory&);
    };
    class registers;
    class reg_operand:public  operand_descriptor{
        private:
            int reg;
        public:
            int getR();
            reg_operand();
            reg_operand(int);
            int get(registers&);
            void set(int,registers&);
            int setD(int,registers&);
    };
    class data_memory;
    class id_operand:public  operand_descriptor{
        private:
            string str;
        public:
            string getStr();
            id_operand();
            id_operand(string&);
            int get(const data_memory&);
            void set(string&);
            int setD(int,data_memory&);
    };
    class direct_operand:public  operand_descriptor{
        private:
            int number;
        public:
            direct_operand();
            direct_operand(int);
            int get();
            void set(int);
    };
    class unary_command:public command{
        private:
            string mark;
            operand_descriptor* operand; 
        public:
            string getM();
            unary_command(int,string&,operand_descriptor*,);
            void show();
            void modify(); 
            ~unary_command();  
    };
    class binary_command:public virtual command{
        private:
            string mark;
            operand_descriptor* first;
            operand_descriptor* second;
        public:
            string getM();
            operand_descriptor* getF();
            operand_descriptor* getS();
            binary_command(int, string&,operand_descriptor*,operand_descriptor*);
            void show();
            void modify(); 
            ~binary_command();  
    };  
    class transition_command: public command{
        private:
            string mark;
        public:
            string getM();
            transition_command(string&);
            void show();
            void modify();
            ~transition_command();
    };
    class cond_transition_command: public command{
        private:
            string mark;
            operand_descriptor* op;
        public:
            string getM();
            operand_descriptor* getOp();
            transition_command(string&,operand_descriptor*);
            void show();
            void modify();
            ~transition_command();
    };
    class move_command:public command{
        private:
            operand_descriptor* first;
            operand_descriptor* second;
        public:
            operand_descriptor* getF();
            operand_descriptor* getS();
            move_command(operand_descriptor*,operand_descriptor*);
            void show();
            void modify(); 
            ~move_command();
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
            vector<cell> rg;
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
            int start;
            set<int> ops;
        public:
            actuator();
            actuator(int);
            actuator(int,vector<int>&);
            bool getEmpty();
            int execution(command&,registers&,data_memory&);
            ~actuator();
        friend class control_device;
    };
    class control_device{
        public:
            int selection(command&,vector<actuator>&);
            void transition(command&,program_memory&);
            command& get(program_memory&);
    };
    class program_memory{
        private:
            int ip;
            vector<command> arr;
            map<string,int> marks;
        public:
            program_memory(program&);
            command& getCommand();
            void show();
            program_memory& setIP(int);
            void inc_ip();
            int getM(string&);
            program_memory& modify();
            ~program_memory();
            void show();
    };
    class data_memory{
        private:
            int size;
            map<string,cell> arr;
        public:
            data_memory();
            data_memory(int);
            int get(string&);
            void  set(string&,int);
            void unblock(string&);
            void block(string&);
            void add(string&,int);
    };
    class program{
        private:
            vector<command*> arr;
        public:
            void save();
            void load();
        friend class program_memory;
    };
    class processor{
        private:
            control_device cd;
            registers reg;
            int n_act;
            vector <actuator> act;
            program_memory pr_m;
            data_memory data_m;
        public:
            processor();
            processor& modify();
            int execution(program&); 
            void mod_reg();
            void mod_acts();
            void mod_dm();
    };
}