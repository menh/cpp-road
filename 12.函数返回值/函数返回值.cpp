#include <iostream>
using namespace std;

class CMh{	
	public:
		CMh(){
			cout<< "construct" <<endl;
		};
		CMh(const CMh& _mh){
			cout<< "cpy construct" <<endl; 
		}

		CMh& operator=(const CMh& _mh){
			cout<< "asign func" <<endl;
		}
};

CMh func(){
	CMh mh;
	cout<<&mh<<endl;
	return mh;
}
int main()
{
	//CMh cmh1;
	//CMh cmh2(cmh1); //CMh cmh2 = cmh1;
	//cmh2 = cmh1;
	CMh cmh3 = func();
	cout<<&cmh3<<endl;
	return 0;
}
