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
