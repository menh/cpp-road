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
