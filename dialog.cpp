#include "processor2.cpp"
using namespace std;

int dialog() {
		print("choose what to do");
		print("0 - quit");
		print("1 - show the program");
		print("2 - show the memory");
		print("3 - modify the program");
		print("4 - modify processor");
		print("5 - execute program");
		int d = 0;
		input(d);
		return d;
	}
int menu(int d, processor& proc, program& pr) {
		switch (d) {
		case 0: return 0;
		case 1:{
			pr.show();
			break;
		}
		case 2:{
			proc.show_memory();
			break;
		}
		case 3:{
			pr.modify();
			break;
		}
		case 4:{
			proc.modify();
			break;
		}
		case 5:{
			proc.execution(pr);
			break;
		}
		default: {
			print("incorrect choice");
		}
		}
		return 1;
	}
int main(){
    processor proc;
	program pr;
	int q=0;
	do {
		int d = dialog();
		q=menu(d,proc,pr);
	} while (q);
	return 0;
}