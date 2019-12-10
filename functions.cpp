#include "processor.h"
using namespace Processor;
using namespace std;
namespace Processor{
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
                    res=first->get(); 
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
                res=op->setD(reg,res);
            }
            catch(exception &ex){
                cout<<ex.what()<<std::endl;
                return 0;
            }
        }
        if (op->getT()==2){
            try{
                res=op->set(dm,res); 
            }
            catch(exception &ex){
                cout<<ex.what()<<std::endl;
                return 0;
            }
        }
        return 1;
    };
    
