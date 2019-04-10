#### C++11 先对于C++98/03显著增强的方面
 * 通过内存模型、线程、原子操作等来支持本地并行编程
 * 通过统一初始化表达方式、auto、declytype、移动语义等来统一对泛型编程的支持。
 * 通过constexpr、POD(概念)等更好的支持系统编程
 * 通过内联命名空间、继承构造函数和右值引用等，以更好的支持库的构建

####### 2.1 保持与C99兼容
 2.1.2 __func__ 预定义标识符
   返回函数名,结构体，类等名称
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
   2.1.3 _Pragma 预定义标识符
   指示编译器，该头文件只被编译一次
    ```
    #pragam once
    与
    #ifndef THIS_HEADER
    #define THIS_HEADER
    与
    _Pragma("once")
    ...
    #endif
    效果一致
    ```
    2.1.4 变长参数的宏定义以及__VA_ARGS__
    ```
    // stderr 标准错误输出设备
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
    2.1.5 宽窄字符串的连接
    宽窄字符串连接时，将窄字符串转换成宽字符串，之后在与宽字符串进行拼接

###### 2.2 long long 整型
    long long 整型在不同平台有不同的长度，至少64位。
    long long = signed long long = long long int = signed long long int
    unsigned long long = unsigned long long int
    可通过LLONG_MIN,LLONE_MAX和ULLONG_MIN来查看最小的long long,最大的long long，最大的unsigned long long
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
###### 2.3 拓展的整型
    C++ 11 只定义了5种标准的有符号整型，每一种有符号整型都有无符号整数版本，且有符号整型与其对应的无符号整型具有相同大小的存储空间
    * signed char
    * short int
    * int
    * long int
    * long long int
    当两个不同整型运算的时候，需要对类型进行转换，转换规则由他们的"等级"决定.等级原则如下
    * 长度越大的整型等级越高，long long 等级高于 int
    * 长度相同时，标准整型的等级高于扩展类型，long long int 和 _int64 都是64位时， long long int 等级更高
    * 相同大小的有符号类型和无符号类型的等级相同

###### 2.4 __cplusplus
    通过宏__cplusplus 控制编译器支持的版本
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
###### 2.5 断言
  2.5.1 断言： 运行时与预处理时 assert
    断言用于排除设计的逻辑上不应该产生的情况,通过assert产生断言，通过定义NDEBUG屏蔽断言
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

2.5.2 静态断言static_assert
     使用static_assert在编译期间即可产生断言
     使用方法如下：
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
     static_assert的断言表达式的结果必须是在编译时期可以计算的表达式，如下则不对
    ```
    int positive(const int n){
	static_assert(1 > 0, "value must > 0");
}
    ```
##### 2.6 noexcept修饰符与noexcept操作符
  被noexcept修饰的函数发生异常是会直接调用std::terminate来中止程序的运行
  未被修饰的函数则会一层一层抛出异常，直到被catch到.
  析构函数默认是noexcept(true)的
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
#### 2.7 快速初始化成员变量
 c++98 只有常量静态成员整型或枚举型才能就地初始化。非静态成员常量必须在构造函数中进行
 c++11 可以使用=或者{}进行就地非静态成员变量的初始化
 ```
 stauct init{int a = 1; double b {1.2}; };
 ```
##### 2.8 非静态成员的sizeof
  可以对非静态成员进行sizeof操作
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
2.9 拓展的friend语法
    可以使用模板来声明友元
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
2.10 final/override 控制
    final，使函数不可被重载
    verride，使函数必须被重载
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
2.11 模板函数的默认模板参数
    支持默认模板参数
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
2.12 外部模板
2.12.1
  外部模板是使用extern关键字，使多个文件共享同一份变量，例如a.c中有定义int i,则在另一个文件中想使用他的话可以用extern int i

2.12.2 显式的实例化与外部模板的声明
  可使用extern关键字共享代码
  ```
    template <typename T> void fun(T)
    template void fun<int>(int)
    extern template void fun<int>(int)
  ```

3.1 继承构造函数
在子类中使用基类的构造函数
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
3.2 委派构造函数
    通过委派其他构造函数来构造，也就是在构造函数中调用其他构造函数
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

3.3 右值引用：移动语义和完美转发
  3.3.1 指针成员与拷贝构造
  指针成员在拷贝时要用深拷贝，避免悬挂指针
  3.3.2 移动语义
  将临时变量的内存保留下来，使新的对象指向这块内存，避免内存重复申请
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
3.3.3 左值，右值与右值引用
    右值是为了减少临时变量的复制,延长临时变量的生存期
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
3.3.4 std::move 强制转化为右值
    强制将一个左值转换为右值

3.3.5 移动语义的一些其他问题
3.3.6 完美转发
    在函数模板中，完全依照模板的参数类型，将参数传递给模板函数中的调用的另外一个函数
3.4 显式转换操作符
    explicit 禁止隐式调用，保证对象必须是显式构造
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

    3.5 列表初始化
    3.5.1 初始化列表
      可以用列表初始化数组容器等。
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

    3.5.2 防止类型收窄

    3.6 POD 类型

    3.7 非受限联合体

    3.8 用户自定义字面量
u
    3.9 内联名字空间

    3.10 模板别名

    3.11 一般化的SFINEA规则

4.1 右尖括号>改进
    >>可以连写，不移动会被解析成右移
4.2 auto类型推导

4.2.1 静态类型、动态类型与类型推导
    auto关键字，编译期间会替换为对应的类型
4.2.2 auto的优势
    除了懒外没有优势
4.2.2 auto的使用细则
    最好不用
4.3 decltype
4.3.1 typeid 与 decltype
  通过typeid可以查看变量的类型，样例代码如下：
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

  通过decltype进行类型推导,声明与括号内表达式相同的变量，应用实例如下
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
4.3.2 decltype 的应用
通过decltype和typedef/using来将一些复杂类型的变量或表达式转化为一个简单的表达式
```
using size_t = decltype(sizeof(0));
using ptrdiff_t = decltype((int*)0 - (int*)0);
using nullptr_t = decltype(nullptr);

vector<int> vec;
typedef decltype(vec.begin()) vectype;
```

4.3.3 dectype 推导的四规则

4.3.4 cv限制符的继承和冗余的符号
  auto类型推导不能带走cv限制符
  decltype能够带走cb限制符

4.4 追踪返回类型

4.4.1 追踪返回类型的引入

4.4.2 使用追踪返回类型的函数
  追踪函数返回类型配合auto与decltype实现泛型编程
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
4.5 基于范围的for循环
可通过for_each和for(:)来遍历for循环
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

5.1 强类型枚举

5.1.1 枚举：分门别类与数值的名字

5.1.2 有缺陷的枚举类型

5.1.3 强类型枚举以及C++11 对原有枚举类型的拓展
可以指定枚举类型
```
enum class Type_c : char {
	General,Light,Medium,Heavy
};
```

5.2 堆内存管理： 智能指针与垃圾回收

5.2.1 显式内存管理

5.2.2 C++11 的智能指针
用unique_ptr, shared_ptr和 weak_ptr等智能指针自动回收堆分配的对象
unique_ptr唯一指针，独享内存
shared_ptr和共享指针，共享内存，引用计数
weak_ptr弱指针，挂靠在其他指针上，可用于验证share_ptr的有效性
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
5.2.3 垃圾回收的分类
垃圾回收方式
1. 基于引用计数的垃圾回收器

2. 基于跟踪处理的垃圾回收器
  （1） 标记 - 清楚
  以程序中正在使用的对象视为“根对象” 从根对象开始查找他们所引用的堆空间，并在这些堆空间上做标记。标记结束后，所有被标记的对象就是可达对象或活对象，而没有被标记的对象就是垃圾，在第二步清扫阶段会被回收
  这种方法的特点是活得对象不会被移动。但是会存在出现大量得内存碎片的问题
  (2) 标记 - 整理
  与标记 - 清楚法类似，但是标记完成之后不再遍历所有对象清扫垃圾，而是将活得对象向左靠齐，这就解决了内存碎片的问题
  标记 - 整理法的特点就是移动活得对象，因此相应得程序中所有得对内存得引用都必须更新。
  (3) 标记 - 拷贝
  将堆空间分为两部分，From 和 To。刚开始系统只是从From的堆空间里面分配内存，当From分配满的时候系统就开始垃圾回收，从From堆空间找出所有的活对象，拷贝到To的堆空间里，这样，From的堆空间里面就全剩阿吉。而对象被拷贝到To里面后，在To里面是紧凑排列的。然后就是交换From和To的角色。接着从From李米娜开始分配
  标记拷贝算法的问题是堆的利用率只有一半，而且需要移动活得对象
5.2.4 C++ 与 垃圾回收
  过程复杂，没有解决办法

5.2.5 C++11与最小垃圾回收支持
  安全派生指针是指向由new分配得对象或其子对象得指针。
  安全派生指针操作包括：
    * 在解引用基础上得引用，比如 &*p
    * 定义明确的指针操作， 比如 p + 1
    * 定义明确的指针转换， 比如 static_case<void*>(p)
    * 指针和整型之间的 reinterpret_cast, 比如 reinterpret_cast<intptr_t>(p)

    在不安全派生之前使用declare_reachable使其可达，使用undeclare_reachable,取消可达。

    当在一大片连续得堆内存上进行指针式操作时，为了让垃圾回收器不关心该区域，也可以使用declare_no_pointers和undeclare_no_pointers
5.2.6 垃圾回收得兼容性
  总结来说就是上面的都是幻想，还没有得到支持

6.1 常量表达式

6.1.1 运行时常量性与编译时常量性
    编译时常量 constexpr

6.1.2 常量表达式函数
常量表达式要求，没看出什么作用
 * 函数体只有单一的return 返回语句
 * 函数体必须返回值(不能是void函数)
 * 在使用前必须已有定义
 * return 返回语句表达式中不能使用非常量表达式的函数，全局数据，且必须是一个常量表达式
6.1.3 常量表达式值
const 和 constexpr大多数是没有区别的

6.1.4 常量表达式的其他应用
当声明为常量表达式的模板函数后，而某个模板函数的实例化结果不满足常量表达式的需求的话，constexpr会自动忽略

6.2 变长模板

6.2.1 变长函数和变长的模板参数
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

6.2.2 变长模板：模板参数包和函数参数包

template<typename... Elements> class tuple
  Elements 被称作是一个模板参数包
一个模板参数包在模板推导时会被认为是模板的单个参数，为了使用模板参数包，我们总市需要将其解包，这通常通过一个名为包扩展的表达式来完成
如template<typename... A> class Template: private B<A...>{};
这里A...就是一个包扩展

6.2.3 变长模板： 进阶
 参数包展开位置：
 * 表达式
 * 初始化列表
 * 基类描述列表
 * 类成员初始化列表
 * 模板参数列表
 * 通用属性列表
 * lambda函数的捕捉列表
 对于包扩展而言，其解包与其声明的形式息息相关，例如下面
 template<typename... A> class T : private B<A>...{};
对于T<X,Y>解包为
class T<X, Y> : private B<X>, private B<Y> {};
  即多重继承的派生类

  template<typename... A> class T : private B<A...>{};
  对于T<X,Y>则会解包为
  class T<X,Y>: private B<X,Y>{}
6.3 原子类型与原子操作

6.3.1 并行编程，多线程与C++11

引入多线程支持，引入原子类型概念

6.3.2 原子操作与C++11原子类型

6.3.3 内存模型，内存一致性与memory_order

6.4 线程局部存储
