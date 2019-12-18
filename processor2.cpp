#include "processor.h"
using namespace std;
    template<class T>
	void print(T a) {
		std::cout << a << std::endl;
	};
    template <class T>
	int input(T& number) {
    int res, err_flag = 0;
	do {
		err_flag = 0;
		std::cin >> number;
        if (std::cin.eof()){
            std::cin.clear();
            std::cin.ignore(256, '\n');
            return 0;
        }
		if (std::cin.good()) {
			res = 1;
		}
		else {
            std::cin.clear();
            std::cin.ignore(256, '\n');
			res=-1;
		}

		if (res < 0) {
			err_flag = 1;
			std::cout << "You are wrong" << std::endl;
		}
		if (err_flag) {
			std::cout << "Try again -->";
		}
	} while (err_flag);
    return res;
	};
    int getOp(operand_descriptor* op,registers& reg,data_memory& dm){
        int res;
        if (op->getT()==0){
                try{
                    res=op->get(); 
                }
                catch(exception &ex){
                    cout<<ex.what()<<std::endl;
                    return 0; 
                }
            }
        if(op->getT()==1){
            try{
                res=op->get(reg);
            }
            catch(exception &ex){
                cout<<ex.what()<<std::endl;
                return 0;
            }
        }
        if (op->getT()==2){
            try{
                res=op->get(dm); 
            }
            catch(exception &ex){
                cout<<ex.what()<<std::endl;
                return 0;
            }
        }
        return res;
    };
    int setOp(operand_descriptor* op,registers& reg,data_memory& dm, int res){
        if(op->getT()==1){
            try{
                res=op->setD(res,reg);
            }
            catch(exception &ex){
                cout<<ex.what()<<std::endl;
                return 0;
            }
        }
        if (op->getT()==2){
            try{
                res=op->setD(res,dm); 
            }
            catch(exception &ex){
                cout<<ex.what()<<std::endl;
                return 0;
            }
        }
        return 1;
    };
    string arr[10]={"ADD","SUB","MUL","DIV","INC","DEC","MOVE","JMP","JNZ","HLT"};
    unary_command::unary_command(string s,operand_descriptor* od, int t){
        type=t;
        mark=s;
        operand=od;
    };
    void unary_command::show(){
        cout<<arr[type]<<"  ";
        if (operand->getT()==1){
            cout<<"REG-"<<operand->getR()<<"    ";
        }
        else {
            cout<<operand->getStr()<<"     ";
        }
        cout<<mark<<endl;
    };
    operand_descriptor* unary_command::getF(){
        return operand;
    };
    binary_command::binary_command(string m,operand_descriptor* f, operand_descriptor* s,int t){
        type=t;
        mark=m;
        first=f;
        second=s;
    };
    operand_descriptor* binary_command::getF(){
        return first;
    };
    operand_descriptor* binary_command::getS(){
        return second;
    };
    void binary_command::show(){ 
        cout<<arr[type]<<"     ";
        if (first->getT()==1){
            cout<<"REG-"<<first->getR()<<"  ";
        }
        else {
            cout<<first->getStr()<<"    ";
        }
        if (second->getT()==0){
            cout<<second->get()<<"      ";
        }
        else if (second->getT()==1){
            cout<<"REG-"<<second->getR()<<"     ";
        }
        else {
            cout<<second->getStr()<<"   ";
        }
        cout<<mark<<endl;
    };
    transition_command::transition_command(string str,string tstr){
        mark=str;
        tmark=tstr;
        type=7;
    };
    void transition_command::show(){
        cout<<"JMP  "<<tmark<<"       "<<mark<<endl;
    };
    cond_transition_command::cond_transition_command(string str,string tstr, operand_descriptor* o){
        mark=str;
        op=o;
        tmark=tstr;
        type=8;
    };
    operand_descriptor* cond_transition_command::getOp(){
        return op;
    };
    void cond_transition_command::show(){
        cout<<"JNZ "<<tmark;
        if (op->getT()==1){
            cout<<"REG-"<<op->getR()<<"     ";
        }
        else {
            cout<<op->getStr()<<"    ";
        }
        cout<<mark<<endl;
    };
    operand_descriptor* move_command::getF(){
        return first;
    };
    operand_descriptor* move_command::getS(){
        return second;
    };
    move_command::move_command(operand_descriptor* f,operand_descriptor* s,string m){
        first=f;
        second=s;
        type=6;
        mark=m;
    };
    void move_command::show(){
        cout<<"MOVE     ";
        if (first->getT()==1){
            cout<<"REG-"<<first->getR()<<"  ";
        }
        else {
            cout<<first->getStr()<<"    ";
        }
        if (second->getT()==0){
            cout<<second->get()<<"      ";
        }
        else if (second->getT()==1){
            cout<<"REG-"<<second->getR()<<"     ";
        }
        else {
            cout<<second->getStr()<<"   ";
        }
        cout<<mark<<endl;
    };
    int operand_descriptor::getT(){
        return type;
    };
    reg_operand::reg_operand(int n){
        reg=n;
        type=1;
    }
    int reg_operand::getR(){
        return reg;
    };
    int reg_operand::get(registers& m){
        return m.get(reg);
    };
    void reg_operand::set(int n){
        reg=n;
    };
    int reg_operand::setD(int n, registers& m){
        m.set(reg,n);
        return 0;
    };
    id_operand::id_operand(string s){
        str=s;
        type=2;
    };

    int id_operand::get(data_memory& m){
        return m.get(str);
    };
    void id_operand::set(string s){
        str=s;
    };
    string id_operand::getStr(){
        return str;
    };
    int id_operand::setD(int n, data_memory& m){
         m.set(str,n);
         return 0;
    };
    direct_operand::direct_operand(){
        number=0;
        type=0;
    };
    direct_operand::direct_operand(int n){
        number=n;
    };
    void direct_operand::set(int n){
        number=n;
    };
    int direct_operand::get(){
        return number;
    };
    hlt_command::hlt_command(string str){
        mark=str;
        type=9;
    };
    void hlt_command::show(){
        cout<<"HLT"<<endl;
    };
    registers::registers(){
        N=10;
        cell a;
        for (int i=0; i < 10; i++) {
            rg.push_back(a);
        }
    };
    registers::registers(int n){
        N=n;
        cell a;
        for (int i=0; i < N; i++) {
            rg.push_back(a);
        }
    };
    void registers::set(int reg, int n){
        if(reg>N-1||reg<0)
             throw std::runtime_error("Invalid value of register");
        rg[reg].a=n;
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
        cout<<"Registers:"<<endl;
        for(int i=0;i<rg.size();++i){
            cout<<i<<"   "<<rg[i].a<<endl;
        }
    };
    int registers::unblock(int reg){
        if(reg>N-1||reg<0)
            return 0;
        rg[reg].free=true;
        return 1;
    };
    data_memory::data_memory(){
        size=100;
    };
    data_memory::data_memory(int N){
        size=N;
    };
    int data_memory::get(string str){
        int res;
        try{
            res=arr[str].a;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
            return 0;
        }
        return res;
    };
    void data_memory::set(string str,int a){
        try{
            arr[str].a=a;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
        }
    };
    void data_memory::unblock(string str){
        try{
            arr[str].free=true;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
        }
    };
    void data_memory::block(string str){
        try{
            arr[str].free=false;
        }
        catch(exception &ex){
            cout<<ex.what()<<std::endl;
            throw std::runtime_error("Invalid string");
        }
    };
    void data_memory::add(string str, int a){
        if(arr.size()>=size){
            throw std::runtime_error("Overflow of memory");
        }
        arr[str].a=a;
    };
    void program_memory::loadPr(program& pr){
        ip=0;
        for(int i=0;i<pr.arr.size();++i){
            arr.push_back(pr.arr[i]);
            string s=pr.arr[i]->getM();
            if(s.size()>0){
                if (marks.find(s)!=marks.end()){
                    throw std::runtime_error("This mark has been added");
                }
                marks[s]=i;
            }
        }
    };
    int program_memory::getM(string s){
        return marks[s];
    }
    command* program_memory::getCommand(){
        if (ip>=arr.size())
            return nullptr;
        return arr[ip];
    };
    program_memory& program_memory::setIP(int i){
        if(i>=arr.size()){
            throw std::runtime_error("Out of the range");
        }
        ip=i;
        return *this;
    };
    void program_memory::setEnd(){
        ip=arr.size();
    };
    void program_memory::inc_ip(){
        ++ip;
    };
    void program_memory::show(){
        for (int i=0;i<arr.size();++i){
            arr[i]->show();
        };
    };
    processor::processor(){
        n_act=1;
        actuator t_act;
        act.push_back(t_act);
    };      

    int processor::execution(program& pr){
        pr_m.loadPr(pr);
        command* ptr_cmd;
        int i;
        while(ptr_cmd=cd.get(pr_m)){
            try{
                i=cd.selection(ptr_cmd,act);
            }
            catch(std::exception &ex){
                    std::cout<<ex.what()<<std::endl;
                    return 1;
            }
            if (i<0){
                try{
                    cd.transition(ptr_cmd,pr_m,reg,data_m);
                }
                catch(std::exception &ex){
                    std::cout<<ex.what()<<std::endl;
                    return 1;
                }
            }
            else{
                try{
                    act[i].execution(ptr_cmd,reg,data_m);
                }
                catch(std::exception &ex){
                    std::cout<<ex.what()<<std::endl;
                    return 1;
                }
                pr_m.inc_ip();
            }
        };
        return 0;
    };
    command* control_device::get(program_memory& pm){
        return pm.getCommand();
    }
    int control_device::selection(command* cmd,Vector<actuator>& acts){
        int type=cmd->getT();
        if (type>6){
            return -1;
        }
        for(int i=0;i<acts.size();++i){
            if (acts[i].ops.count(type))
                return i;
        }
        throw std::runtime_error("There is no actuator to execute this command");
        return 0;
    };
    void control_device::transition(command* cmd, program_memory& pr_m,registers& reg, data_memory& dm){
        int t=cmd->getT();
        switch(t){
            case 7:{
                jmp a;
                a(cmd->getTM(),pr_m);
                break;
            }
            case 8:{
                jnz a;
                a(cmd->getTM(),pr_m,cmd->getOp(),reg,dm);
                break;
            }
            case 9:{
                hlt a;
                a(pr_m);
                break;
            }
        }
    };
    int add::operator()(int a, int b){
        return a+b;
    };
    int sub::operator()(int a, int b){
        return a-b;
    };
    int mul::operator()(int a, int b){
        return a*b;
    };
    int div_a::operator()(int a, int b){
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
    int dec_a::operator()(int a){
        return --a;
    };
    int jmp::operator()(string s,program_memory& prm){
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
    int jnz::operator()( string s,program_memory& prm, operand_descriptor* od, registers& reg, data_memory& dm){
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
    int hlt::operator()(program_memory& prm){
        prm.setEnd();
        return 1;
    };
    int move_a::operator()(operand_descriptor* f,operand_descriptor* s,registers& reg,data_memory& dm){   
        int n;
        n=getOp(s,reg,dm);
        setOp(f,reg,dm,n);
        return 1;
    };
     actuator::actuator(){
        empty=true;
        time=1;
        ops={0,1,2,3,4,5,6,7,8,9};
    };
    actuator::actuator(int n){
        empty=true;
        time=n;
        ops={0,1,2,3,4,5,6,7,8,9};
    };
    actuator::actuator(int n,set<int>& arr){
        empty=true;
        time=n;
        ops=arr;
    };
    bool actuator::getEmpty(){
        return empty;
    };
    int actuator::execution(command* cmd, registers& reg, data_memory& dm){
        empty=false;
        int type=cmd->getT();
        if(type<4){
            operand_descriptor* op1=cmd->getF();
            operand_descriptor* op2=cmd->getS();
            int t1=getOp(op1,reg,dm);
            int t2=getOp(op2,reg,dm);
            int res;
            switch(type){
                case 0:{
                    add a;
                    res=a(t1,t2);
                    break;
                }
                case 1:{
                    sub a;
                    res=a(t1,t2);
                    break;
                }
                case 2:{
                    mul a;
                    res=a(t1,t2);
                    break;
                }
                case 3:{
                    div_a a;
                    res=a(t1,t2);
                    break;
                }
            }
            setOp(op1,reg,dm,res);
        }
        else if(type<6){
            operand_descriptor* op1=cmd->getF();
            int t1=getOp(op1,reg,dm);
            int res;
            switch(type){
                case 4:{
                    inc a;
                    res=a(t1);
                    break;
                }
                case 5:{
                    dec_a a;
                    res=a(t1);
                    break;
                }
            }
            setOp(op1,reg,dm,res);
        }
        else {
            operand_descriptor* op1=cmd->getF();
            operand_descriptor* op2=cmd->getS();
            move_a a;
            a(op1,op2,reg,dm);
        }
        return 0;
    };
    program::program(){
        operand_descriptor* o11=new reg_operand(1);
        operand_descriptor* o12=new direct_operand(5);
        string m1;
        command* c1=new move_command(o11,o12,m1);
        arr.push_back(c1);
        operand_descriptor* o21=new id_operand("a");
        operand_descriptor* o22=new direct_operand(2);
        string m2;
        command* c2=new move_command(o21,o22,m2);
        arr.push_back(c2);
        operand_descriptor* o31=new reg_operand(1);
        operand_descriptor* o32=new id_operand("a");
        string m3;
        command* c3=new binary_command(m3,o31,o32,0);
        arr.push_back(c3);
        operand_descriptor* o41=new id_operand("a");
        operand_descriptor* o42=new direct_operand(1);
        string m4;
        command* c4=new binary_command(m4,o41,o42,1);
        arr.push_back(c4);
        string tm5="first";
        string m5;
        command* c5=new transition_command(m5,tm5);
        arr.push_back(c5);
        operand_descriptor* o61=new id_operand("a");
        operand_descriptor* o62=new direct_operand(1);
        string m6;
        command* c6=new binary_command(m6,o61,o62,1);
        arr.push_back(c6);
        operand_descriptor* o71=new id_operand("a");
        operand_descriptor* o72=new reg_operand(1);
        string m7="first";
        command* c7=new binary_command(m7,o71,o72,0);
        arr.push_back(c7);
    };
    void program::show(){
        for (int i=0;i<arr.size();++i){
            arr[i]->show();
        }
    };
    void processor::show_memory(){
        reg.show();
        data_m.show();
    };
    void data_memory::show(){
        cout<<"Data memory:"<<endl;
       map<string,cell>::iterator i;
       for(i=arr.begin();i!=arr.end();++i){
           cout<<i->first<<"    "<<i->second.a<<endl;
       }
    };
    int proc_dialog() {
		print("choose what to modify");
		print("0 - quit");
		print("1 - data memory");
		print("2 - actuators");
        print("3 - registers");
		int d = 0;
		input(d);
		return d;
	}
    void processor::modify(){
        int d=0;
        do{
            d=proc_dialog();
            switch (d){
                case 0:{
                    break;
                }
                case 3:{
                    int n;
                    cout<<"Enter number of registers:"<<endl;
                    input(n);
                    registers t(n);
                    reg=t;
                    break;
                }
                case 1:{
                    int n;
                    cout<<"Enter size of data memory:"<<endl;
                    input(n);
                    data_memory t(n);
                    data_m=t;
                    break;
                }
                case 2:{
                    int n;
                    cout<<"Enter number of actuators:"<<endl;
                    input(n);
                    n_act=n;
                    int a;
                    int t1;
                    Vector<actuator> tmp;
                    for(int i=0;i<n;++i){
                        set<int> t;
                        cout<<"Enter the time of execution"<<endl;
                        input(t1);
                        cout<<"Enter the set of operations of "<<i<<" actuator, -1 to end"<<endl;
                        do{
                            input(a);
                            if(a<0)
                                break;
                            t.insert(a);
                        }while(true);
                        actuator ta(t1,t);
                        tmp.push_back(ta);
                    }
                    act=tmp;
                    break;
                }
                default: {
			    cout<<"incorrect choice"<<endl;
		        }
		    }
        }while (d);
    };
    int pr_dialog() {
        print("Count number of command");
		int d = 0;
		input(d);
		return d;
	};
    void program::modify_command(int d){
        int t;
        this->arr[d]->show();
        print("Enter the type of command");
        input(t);
        switch (t){
            case 0:{
                print("Enter type of first operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                operand_descriptor* op2;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter type of second operand");
                int t2;
                input (t2);
                switch (t2){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op2=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op2=new id_operand(o2);
                        break;
                    }
                    case 0:{
                        print("Enter the number");
                        int o3;
                        input(o3);
                        op1=new direct_operand(o3);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new binary_command(mark,op1,op2,t);
                break;
            }
            case 1:{
                print("Enter type of first operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                operand_descriptor* op2;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter type of second operand");
                int t2;
                input (t2);
                switch (t2){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op2=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op2=new id_operand(o2);
                        break;
                    }
                    case 0:{
                        print("Enter the number");
                        int o3;
                        input(o3);
                        op1=new direct_operand(o3);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new binary_command(mark,op1,op2,t);
                break;
            }
            case 2:{
                print("Enter type of first operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                operand_descriptor* op2;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter type of second operand");
                int t2;
                input (t2);
                switch (t2){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op2=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op2=new id_operand(o2);
                        break;
                    }
                    case 0:{
                        print("Enter the number");
                        int o3;
                        input(o3);
                        op1=new direct_operand(o3);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new binary_command(mark,op1,op2,t);
                break;
            }
            case 3:{
                print("Enter type of first operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                operand_descriptor* op2;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter type of second operand");
                int t2;
                input (t2);
                switch (t2){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op2=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op2=new id_operand(o2);
                        break;
                    }
                    case 0:{
                        print("Enter the number");
                        int o3;
                        input(o3);
                        op1=new direct_operand(o3);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new binary_command(mark,op1,op2,t);
                break;
            }
            case 4:{
                print("Enter type of operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new unary_command(mark,op1,t);
                break;
            }
            case 5:{
                print("Enter type of operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new unary_command(mark,op1,t);
                break;
            }
            case 6:{
               print("Enter type of first operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                operand_descriptor* op2;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter type of second operand");
                int t2;
                input (t2);
                switch (t2){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op2=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op2=new id_operand(o2);break;
                        break;
                    }
                    case 0:{
                        print("Enter the number");
                        int o3;
                        input(o3);
                        op1=new direct_operand(o3);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new move_command(op1,op2,mark);
                break;
            }
            case 7:{
                print("Enter mark  of transition");
                string tmark;
                input(tmark);
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new transition_command(mark,tmark);
                break;
            }
            case 8:{
                print("Enter type of operand");
                int t1;
                input (t1);
                operand_descriptor* op1;
                switch (t1){
                    case 1:{
                        print("Enter number of register");
                        int o1;
                        input(o1);
                        op1=new reg_operand(o1);
                        break;
                    }
                    case 2:{
                        print("Enter id");
                        string o2;
                        input(o2);
                        op1=new id_operand(o2);
                        break;
                    }
                    default: {
			            cout<<"incorrect choice"<<endl;
		            }
                }
                print("Enter mark  of transition");
                string tmark;
                input(tmark);
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new cond_transition_command(mark,tmark,op1);
                break;
            };
            case 9:{
                print("Enter the mark");
                string mark;
                input(mark);
                arr[d]=new hlt_command(mark);
                break;
            }
            default: {
			    cout<<"incorrect choice"<<endl;
		    }
        }
    }
    void program::modify(){
        int d=0;
        do{
            this->show();
            d=pr_dialog();
            if(d<0)
                break;
            this->modify_command(d);
        }while(true);
    };
