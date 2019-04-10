#### C++11 �ȶ���C++98/03������ǿ�ķ���
 * ͨ���ڴ�ģ�͡��̡߳�ԭ�Ӳ�������֧�ֱ��ز��б��
 * ͨ��ͳһ��ʼ����﷽ʽ��auto��declytype���ƶ��������ͳһ�Է��ͱ�̵�֧�֡�
 * ͨ��constexpr��POD(����)�ȸ��õ�֧��ϵͳ���
 * ͨ�����������ռ䡢�̳й��캯������ֵ���õȣ��Ը��õ�֧�ֿ�Ĺ���

####### 2.1 ������C99����
 2.1.2 __func__ Ԥ�����ʶ��
   ���غ�����,�ṹ�壬�������
   ```
   const char* testFunc(){
     return __func__;
   }

   struct TestStruct{
     TestStruct() : name(__func__){}
     const char* name;
   };

   class TestClass{
     public:
        TestClass() : name(__func__){}
        const char* name;
      };

    int main()
    {
  	     cout<<testFunc()<<endl;
  	     TestStruct ts;
  	     cout<<ts.name<<endl;
  	     TestClass tc;
  	     cout<<tc.name<<endl;
         return 0;
     }
   ```
   2.1.3 _Pragma Ԥ�����ʶ��
   ָʾ����������ͷ�ļ�ֻ������һ��
    ```
    #pragam once
    ��
    #ifndef THIS_HEADER
    #define THIS_HEADER
    ��
    _Pragma("once")
    ...
    #endif
    Ч��һ��
    ```
    2.1.4 �䳤�����ĺ궨���Լ�__VA_ARGS__
    ```
    // stderr ��׼��������豸
    #define LOG(...){\
	  fprintf(stderr,"%s: Line %d:\n", __FILE__, __LINE__);\
	  fprintf(stderr, __VA_ARGS__);\
	  fprintf(stderr, "\n");\
    }

    int main()
    {
	     int x = 3;
	     LOG("x = %d", x); // fprintf(stderr,"x = %d", x);
	     return 0;
    }
    ```
    2.1.5 ��խ�ַ���������
    ��խ�ַ�������ʱ����խ�ַ���ת���ɿ��ַ�����֮��������ַ�������ƴ��

###### 2.2 long long ����
    long long �����ڲ�ͬƽ̨�в�ͬ�ĳ��ȣ�����64λ��
    long long = signed long long = long long int = signed long long int
    unsigned long long = unsigned long long int
    ��ͨ��LLONG_MIN,LLONE_MAX��ULLONG_MIN���鿴��С��long long,����long long������unsigned long long
    ```
    int main()
    {
	     long long ll_min = LLONG_MIN;
	     long long ll_max = LLONG_MAX;
	     unsigned long long ull_max = ULLONG_MAX;

	     printf("min of long long: %lld\n", ll_min);

	     printf("max of long long: %lld\n", ll_max);

	     printf("max of unsigned long long: %llu\n", ull_max);

	     return 0;
     }
    ```
###### 2.3 ��չ������
    C++ 11 ֻ������5�ֱ�׼���з������ͣ�ÿһ���з������Ͷ����޷��������汾�����з������������Ӧ���޷������;�����ͬ��С�Ĵ洢�ռ�
    * signed char
    * short int
    * int
    * long int
    * long long int
    ��������ͬ���������ʱ����Ҫ�����ͽ���ת����ת�����������ǵ�"�ȼ�"����.�ȼ�ԭ������
    * ����Խ������͵ȼ�Խ�ߣ�long long �ȼ����� int
    * ������ͬʱ����׼���͵ĵȼ�������չ���ͣ�long long int �� _int64 ����64λʱ�� long long int �ȼ�����
    * ��ͬ��С���з������ͺ��޷������͵ĵȼ���ͬ

###### 2.4 __cplusplus
    ͨ����__cplusplus ���Ʊ�����֧�ֵİ汾
    ```
    #if __cplusplus < 201103L
	   #error "should use c++11 implementation"

     #endif
     #include <iostream>
     using namespace std;
     int main()
     {

	      return 0;
    }
    ```
###### 2.5 ����
  2.5.1 ���ԣ� ����ʱ��Ԥ����ʱ assert
    ���������ų���Ƶ��߼��ϲ�Ӧ�ò��������,ͨ��assert�������ԣ�ͨ������NDEBUG���ζ���
    ```
    #include <iostream>
#include <cassert>
using namespace std;
#define NDEBUG NDEBUG

#ifdef NDEBUG
# define assert(expr) (static_cast<void>(0))
#endif

char* ArrayAlloc(int n){
	assert(n > 0);
	return new char[n];
}
int main()
{
	char* a = ArrayAlloc(0);
	return 0;
}
    ```

2.5.2 ��̬����static_assert
     ʹ��static_assert�ڱ����ڼ伴�ɲ�������
     ʹ�÷������£�
     ```
     #include <iostream>
using namespace std;
template <typename T, typename U>
void bit_copy(T& a, U& b)
{
	static_assert(sizeof(b) == sizeof(a), "the parameters of bit_copy must have same width.");

}

int main()
{
	int a = 0x2468;
	double b;
	bit_copy(a,b);
	return 0;
}
     ```
     static_assert�Ķ��Ա��ʽ�Ľ���������ڱ���ʱ�ڿ��Լ���ı��ʽ�������򲻶�
    ```
    int positive(const int n){
	static_assert(1 > 0, "value must > 0");
}
    ```
##### 2.6 noexcept���η���noexcept������
  ��noexcept���εĺ��������쳣�ǻ�ֱ�ӵ���std::terminate����ֹ���������
  δ�����εĺ������һ��һ���׳��쳣��ֱ����catch��.
  ��������Ĭ����noexcept(true)��
  ```
  #include <iostream>
using namespace std;
struct A{
	~A(){
		throw;
	}
};

struct B{
	~B() noexcept(false){
		throw 2;
	}
};
int main()
{
	try{
		B b;
	}
	catch(...){
		cout<<"b throw"<<endl;
	}

	try{
		A a;
	}
	catch(...){
		cout<<"a throw"<<endl;
	}
	return 0;
}
  ```
#### 2.7 ���ٳ�ʼ����Ա����
 c++98 ֻ�г�����̬��Ա���ͻ�ö���Ͳ��ܾ͵س�ʼ�����Ǿ�̬��Ա���������ڹ��캯���н���
 c++11 ����ʹ��=����{}���о͵طǾ�̬��Ա�����ĳ�ʼ��
 ```
 stauct init{int a = 1; double b {1.2}; };
 ```
##### 2.8 �Ǿ�̬��Ա��sizeof
  ���ԶԷǾ�̬��Ա����sizeof����
  ```
  #include <iostream>
using namespace std;

struct People{
	public:
		int hand;
		static People* all;
};
int main()
{
	People p;
	cout << sizeof(p)<<endl;
	cout << sizeof(p.hand) <<endl;
	cout << sizeof(People::all) <<endl;
	cout << sizeof(People::hand) <<endl;
	return 0;
}
  ```
2.9 ��չ��friend�﷨
    ����ʹ��ģ����������Ԫ
    ```
    #include <iostream>
using namespace std;
template<typename T>
class P{
	friend T;
	private:
		int x = 1;
};

class F{
	public:
		int addP2F(P<F> p){
			return p.x + this->x;
		}
	private:
		int x = 1;
};

int main()
{

	return 0;
}
    ```
2.10 final/override ����
    final��ʹ�������ɱ�����
    verride��ʹ�������뱻����
```
#include <iostream>
using namespace std;
class Base{
	virtual void func1();
	virtual void func2();
};

class DerivedMid: public Base{
	virtual void func1() override;
	virtual void func2() override final;
};

class DerivedTop: public DerivedMid{
	virtual void func1() override;
	//virtual void func2() override final;
};
int main()
{

	return 0;
}
```
2.11 ģ�庯����Ĭ��ģ�����
    ֧��Ĭ��ģ�����
```
#include <iostream>
using namespace std;

template<class T, class U = int>
void add(T t, U u){
	cout<< t + u <<endl;
}
int main()
{
	add(1,2);
	string t = "1";
	string u = "2";
	add(t,u);
	return 0;
}
```
2.12 �ⲿģ��
2.12.1
  �ⲿģ����ʹ��extern�ؼ��֣�ʹ����ļ�����ͬһ�ݱ���������a.c���ж���int i,������һ���ļ�����ʹ�����Ļ�������extern int i

2.12.2 ��ʽ��ʵ�������ⲿģ�������
  ��ʹ��extern�ؼ��ֹ������
  ```
    template <typename T> void fun(T)
    template void fun<int>(int)
    extern template void fun<int>(int)
  ```

3.1 �̳й��캯��
��������ʹ�û���Ĺ��캯��
```
#include <iostream>
using namespace std;

struct A{
	A(int _a) { a = _a;}
	int a;
};

struct B : A {
	using A::A;

};
int main()
{
	B b(1);

	cout<<b.a<<endl;
	return 0;
}
```
3.2 ί�ɹ��캯��
    ͨ��ί���������캯�������죬Ҳ�����ڹ��캯���е����������캯��
```
class Info{
	public:
		Info(){
			a = 0;
		}
		Info(int i){
			new (this) Info();
			b = 1;
		}
		Info(char c) : Info(){

			c = 'c';
		}
		int a;
		int b;
		char c;
};
```

3.3 ��ֵ���ã��ƶ����������ת��
  3.3.1 ָ���Ա�뿽������
  ָ���Ա�ڿ���ʱҪ���������������ָ��
  3.3.2 �ƶ�����
  ����ʱ�������ڴ汣��������ʹ�µĶ���ָ������ڴ棬�����ڴ��ظ�����
  ```
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
	HasPtrMem a = GetTemp();
	cout<<"resource from " << __func__ << ": " << hex << a.d <<endl;

	//int b = GetTemp1();
	//HasPtrMem a1;
	return 0;
}
  ```
3.3.3 ��ֵ����ֵ����ֵ����
    ��ֵ��Ϊ�˼�����ʱ�����ĸ���,�ӳ���ʱ������������
    ```
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
    ```
3.3.4 std::move ǿ��ת��Ϊ��ֵ
    ǿ�ƽ�һ����ֵת��Ϊ��ֵ

3.3.5 �ƶ������һЩ��������
3.3.6 ����ת��
    �ں���ģ���У���ȫ����ģ��Ĳ������ͣ����������ݸ�ģ�庯���еĵ��õ�����һ������
3.4 ��ʽת��������
    explicit ��ֹ��ʽ���ã���֤�����������ʽ����
    ```
    #include <iostream>
using namespace std;
struct Rational1{
	Rational1(int n = 0, int d = 1) : num(n), den(d){
		cout<< __func__ << "(" << "/" << den << ")" <<endl;
	}
	int num;
	int den;
};

struct Rational2{
	explicit Rational2(int n = 0, int d = 1) : num(n), den(d){
		cout<< __func__ << "(" << "/" << den << ")" <<endl;
	}
	int num;
	int den;
};

void Display1(Rational1 ra){
	cout<< "Numberator: " << ra.num << " Den :" << ra.den <<endl;
}

void Display2(Rational2 ra){
	cout<< "Numberator: " << ra.num << " Den :" << ra.den <<endl;
}
int main()
{
	Rational1 r1_1 = 11;
	Rational1 r1_2(12);

	Rational2 r2_1 = 21;
	Rational2 r2_2(22);

	Display1(1);

	Display2(2);

	Display2(Rational2(2));
	return 0;
 }
    ```

    3.5 �б��ʼ��
    3.5.1 ��ʼ���б�
      �������б��ʼ�����������ȡ�
      ```
      #include <iostream>
#include <map>
#include <vector>
using namespace std;

int main()
{
	int a[] = {1,3,5};
	int b[] {2,4,6};
	vector<int> c{1,3,5};
	map<int, float> d = {{1,1.0}, {2, 2.0}, {3, 3.0}};
	return 0;
 }
      ```

    3.5.2 ��ֹ������խ

    3.6 POD ����

    3.7 ������������

    3.8 �û��Զ���������
u
    3.9 �������ֿռ�

    3.10 ģ�����

    3.11 һ�㻯��SFINEA����

4.1 �Ҽ�����>�Ľ�
    >>������д�����ƶ��ᱻ����������
4.2 auto�����Ƶ�

4.2.1 ��̬���͡���̬�����������Ƶ�
    auto�ؼ��֣������ڼ���滻Ϊ��Ӧ������
4.2.2 auto������
    ��������û������
4.2.2 auto��ʹ��ϸ��
    ��ò���
4.3 decltype
4.3.1 typeid �� decltype
  ͨ��typeid���Բ鿴���������ͣ������������£�
  ```
  #include <iostream>
#include <typeinfo>
using namespace std;
class White{
};

class Black{
};
int main()
{
	White a;
	Black b;
	cout<< typeid(a).name() << endl;
	cout<< typeid(b).name() << endl;
	return 0;
 }
  ```

  ͨ��decltype���������Ƶ�,�����������ڱ��ʽ��ͬ�ı�����Ӧ��ʵ������
  ```
  #include <iostream>
#include <typeinfo>
using namespace std;
class White{
};

class Black{
};
int main()
{
	White a;
	decltype(a) b;
	cout<< typeid(a).name() << endl;
	cout<< typeid(b).name() << endl;
	return 0;
 }
  ```
4.3.2 decltype ��Ӧ��
ͨ��decltype��typedef/using����һЩ�������͵ı�������ʽת��Ϊһ���򵥵ı��ʽ
```
using size_t = decltype(sizeof(0));
using ptrdiff_t = decltype((int*)0 - (int*)0);
using nullptr_t = decltype(nullptr);

vector<int> vec;
typedef decltype(vec.begin()) vectype;
```

4.3.3 dectype �Ƶ����Ĺ���

4.3.4 cv���Ʒ��ļ̳к�����ķ���
  auto�����Ƶ����ܴ���cv���Ʒ�
  decltype�ܹ�����cb���Ʒ�

4.4 ׷�ٷ�������

4.4.1 ׷�ٷ������͵�����

4.4.2 ʹ��׷�ٷ������͵ĺ���
  ׷�ٺ��������������auto��decltypeʵ�ַ��ͱ��
  ```
  #include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
{
	return t1 + t2;
}

double add(const double& d1, const double& d2)
{
	return d1 + d2;
}

int add (const int& i1, const int& i2)
{
	return i1 + i2;
}

template<typename T>
auto Forward(const T& t1, const T& t2) -> decltype(add(t1, t2))
{
	return add(t1, t2);
}
int main()
{
	cout<< add(1,2) <<endl;
	cout<< add(1.2,2.3) <<endl;
	cout<<Forward(1,2)<<endl;
	cout<<Forward(1.2,2.3)<<endl;
	return 0;
 }
  ```
4.5 ���ڷ�Χ��forѭ��
��ͨ��for_each��for(:)������forѭ��
```
#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>
using namespace std;
int action1(int& e)
{
	e *= 2;
	return e;
}
int action2(int & e)
{
	cout<< e <<endl;
}
int main()
{
	int arr[5] = {1,2,3,4,5};
	for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action1);
	for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action2);
	for(auto e : arr)
	{
		action2(e);
	}
	return 0;
 }
```

5.1 ǿ����ö��

5.1.1 ö�٣����ű�������ֵ������

5.1.2 ��ȱ�ݵ�ö������

5.1.3 ǿ����ö���Լ�C++11 ��ԭ��ö�����͵���չ
����ָ��ö������
```
enum class Type_c : char {
	General,Light,Medium,Heavy
};
```

5.2 ���ڴ���� ����ָ������������

5.2.1 ��ʽ�ڴ����

5.2.2 C++11 ������ָ��
��unique_ptr, shared_ptr�� weak_ptr������ָ���Զ����նѷ���Ķ���
unique_ptrΨһָ�룬�����ڴ�
shared_ptr�͹���ָ�룬�����ڴ棬���ü���
weak_ptr��ָ�룬�ҿ�������ָ���ϣ���������֤share_ptr����Ч��
```
#include <iostream>
#include <memory>
using namespace std;

void Check(weak_ptr<int> & wp)
{
	shared_ptr<int> sp = wp.lock();
	if(sp != nullptr)
		cout<< "still " << *sp <<endl;
	else
		cout<< "pointer is invalid." <<endl;
}
int main()
{
	shared_ptr<int> sp1(new int(22));
	shared_ptr<int> sp2 = sp1;
	weak_ptr<int> wp =sp1;

	cout<< *sp1 <<endl;
	cout<< *sp2 <<endl;
	Check(wp);

	sp1.reset();
	Check(wp);

	sp2.reset();
	Check(wp);

	return 0;
}
```
5.2.3 �������յķ���
�������շ�ʽ
1. �������ü���������������

2. ���ڸ��ٴ��������������
  ��1�� ��� - ���
  �Գ���������ʹ�õĶ�����Ϊ�������� �Ӹ�����ʼ�������������õĶѿռ䣬������Щ�ѿռ�������ǡ���ǽ��������б���ǵĶ�����ǿɴ��������󣬶�û�б���ǵĶ�������������ڵڶ�����ɨ�׶λᱻ����
  ���ַ������ص��ǻ�ö��󲻻ᱻ�ƶ������ǻ���ڳ��ִ������ڴ���Ƭ������
  (2) ��� - ����
  ���� - ��������ƣ����Ǳ�����֮���ٱ������ж�����ɨ���������ǽ���ö��������룬��ͽ�����ڴ���Ƭ������
  ��� - �������ص�����ƶ���ö��������Ӧ�ó��������еö��ڴ�����ö�������¡�
  (3) ��� - ����
  ���ѿռ��Ϊ�����֣�From �� To���տ�ʼϵͳֻ�Ǵ�From�Ķѿռ���������ڴ棬��From��������ʱ��ϵͳ�Ϳ�ʼ�������գ���From�ѿռ��ҳ����еĻ���󣬿�����To�Ķѿռ��������From�Ķѿռ������ȫʣ�����������󱻿�����To�������To�����ǽ������еġ�Ȼ����ǽ���From��To�Ľ�ɫ�����Ŵ�From�����ȿ�ʼ����
  ��ǿ����㷨�������Ƕѵ�������ֻ��һ�룬������Ҫ�ƶ���ö���
5.2.4 C++ �� ��������
  ���̸��ӣ�û�н���취

5.2.5 C++11����С��������֧��
  ��ȫ����ָ����ָ����new����ö�������Ӷ����ָ�롣
  ��ȫ����ָ�����������
    * �ڽ����û����ϵ����ã����� &*p
    * ������ȷ��ָ������� ���� p + 1
    * ������ȷ��ָ��ת���� ���� static_case<void*>(p)
    * ָ�������֮��� reinterpret_cast, ���� reinterpret_cast<intptr_t>(p)

    �ڲ���ȫ����֮ǰʹ��declare_reachableʹ��ɴʹ��undeclare_reachable,ȡ���ɴ

    ����һ��Ƭ�����ö��ڴ��Ͻ���ָ��ʽ����ʱ��Ϊ�������������������ĸ�����Ҳ����ʹ��declare_no_pointers��undeclare_no_pointers
5.2.6 �������յü�����
  �ܽ���˵��������Ķ��ǻ��룬��û�еõ�֧��

6.1 �������ʽ

6.1.1 ����ʱ�����������ʱ������
    ����ʱ���� constexpr

6.1.2 �������ʽ����
�������ʽҪ��û����ʲô����
 * ������ֻ�е�һ��return �������
 * ��������뷵��ֵ(������void����)
 * ��ʹ��ǰ�������ж���
 * return ���������ʽ�в���ʹ�÷ǳ������ʽ�ĺ�����ȫ�����ݣ��ұ�����һ���������ʽ
6.1.3 �������ʽֵ
const �� constexpr�������û�������

6.1.4 �������ʽ������Ӧ��
������Ϊ�������ʽ��ģ�庯���󣬶�ĳ��ģ�庯����ʵ������������㳣�����ʽ������Ļ���constexpr���Զ�����

6.2 �䳤ģ��

6.2.1 �䳤�����ͱ䳤��ģ�����
```
#include <iostream>
#include <stdarg.h>
using namespace std;
double SumOfFloat(int count, ...)
{
	va_list ap;
	double sum  = 0;
	va_start(ap, count);
	for(int i = 0; i < count; i++)
	{
		sum += va_arg(ap, double);
	}
	va_end(ap);
	return sum;
}
int main()
{
	cout<< SumOfFloat(2, 1.0, 2.2) <<endl;
	return 0;
}
```

6.2.2 �䳤ģ�壺ģ��������ͺ���������

template<typename... Elements> class tuple
  Elements ��������һ��ģ�������
һ��ģ���������ģ���Ƶ�ʱ�ᱻ��Ϊ��ģ��ĵ���������Ϊ��ʹ��ģ�������������������Ҫ����������ͨ��ͨ��һ����Ϊ����չ�ı��ʽ�����
��template<typename... A> class Template: private B<A...>{};
����A...����һ������չ

6.2.3 �䳤ģ�壺 ����
 ������չ��λ�ã�
 * ���ʽ
 * ��ʼ���б�
 * ���������б�
 * ���Ա��ʼ���б�
 * ģ������б�
 * ͨ�������б�
 * lambda�����Ĳ�׽�б�
 ���ڰ���չ���ԣ�����������������ʽϢϢ��أ���������
 template<typename... A> class T : private B<A>...{};
����T<X,Y>���Ϊ
class T<X, Y> : private B<X>, private B<Y> {};
  �����ؼ̳е�������

  template<typename... A> class T : private B<A...>{};
  ����T<X,Y>�����Ϊ
  class T<X,Y>: private B<X,Y>{}
6.3 ԭ��������ԭ�Ӳ���

6.3.1 ���б�̣����߳���C++11

������߳�֧�֣�����ԭ�����͸���

6.3.2 ԭ�Ӳ�����C++11ԭ������

6.3.3 �ڴ�ģ�ͣ��ڴ�һ������memory_order

6.4 �ֲ߳̾��洢
