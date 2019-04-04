#include <iostream> 
using namespace std;
class HasPtrMem{
	public:
		HasPtrMem(): d(new int(0)){
			cout<< "construct: " << ++n_cstr <<endl;  
		}
		
		HasPtrMem(const HasPtrMem& h): d(new int(*h.d)){
			cout<< "copy construct: " << ++n_cptr <<endl;
		}
		
		HasPtrMem(HasPtrMem&& h): d(h.d){
			h.d = nullptr;
			cout<< "Move construct:" << ++n_mvtr <<endl;
		}
		
		~HasPtrMem(){
			cout << "destruct: " << ++n_dstr <<endl;
		}
		int* d;
		static int n_cstr;
		static int n_dstr;
		static int n_cptr;
		static int n_mvtr; 
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_mvtr = 0;

HasPtrMem GetTemp(){
	HasPtrMem h;
	cout<<"resource from " << __func__ << ": " << hex << h.d <<endl;
	return h;
}
int GetTemp1(){
	HasPtrMem a = HasPtrMem();
	return 1;
}

int getint(){
	int ia = 1 ;
	return ia;
}
int main()
{
	HasPtrMem temp;
	HasPtrMem a = std::move(temp);
	cout<<"resource from " << __func__ << ": " << hex << a.d <<endl;
	
	//int b = GetTemp1();
	//HasPtrMem a1;
	return 0;
}
