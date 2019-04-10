#include <iostream>
using namespace std;
enum BitSet{
	V0 = 1 << 0,
	V1 = 1 << 1,
	V2 = 1 << 2,
	VMAX = 1 << 3
};

const BitSet operator|(BitSet x, BitSet y){
	return static_cast<BitSet>(((int) x | y) & (VMAX - 1));
}

template <int i = V0 | V1>
void LikeConst(){
}
int main()
{
	return 0;
}
