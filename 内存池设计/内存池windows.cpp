
#include <iostream>   // std::cout, std::endl
#include <cassert>    // assert()
#include <ctime>      // clock()
#include <vector>     // std::vector
#include <climits>
#include <cstddef>
using namespace std;
// StackAlloc.hpp

#include <memory>
#define ELEMS 25000000
// 重复次数
#define REPS 50
template <typename T>
struct StackNode_
{
  T data;
  StackNode_* prev;
};

// T 为存储的对象类型, Alloc 为使用的分配器,
// 并默认使用 std::allocator 作为对象的分配器
template <class T, class Alloc = std::allocator<T> >
class StackAlloc
{
  public:
    // 使用 typedef 简化类型名
    typedef StackNode_<T> Node;
    typedef typename Alloc::template rebind<Node>::other allocator;

    // 默认构造
    StackAlloc() { head_ = 0; }
    // 默认析构
    ~StackAlloc() { clear(); }

    // 当栈中元素为空时返回 true
    bool empty() {return (head_ == 0);}

    // 释放栈中元素的所有内存
    void clear() {
      Node* curr = head_;
      while (curr != 0)
      {
        Node* tmp = curr->prev;
        allocator_.destroy(curr);
        allocator_.deallocate(curr, 1);
        curr = tmp;
      }
      head_ = 0;
    }

    // 入栈
    void push(T element) {
      // 为一个节点分配内存
      Node* newNode = allocator_.allocate(1);
      // 调用节点的构造函数
      allocator_.construct(newNode, Node());

      // 入栈操作
      newNode->data = element;
      newNode->prev = head_;
      head_ = newNode;
    }

    // 出栈
    T pop() {
      // 出栈操作 返回出栈结果
      T result = head_->data;
      Node* tmp = head_->prev;
      allocator_.destroy(head_);
      allocator_.deallocate(head_, 1);
      head_ = tmp;
      return result;
    }

    // 返回栈顶元素
    T top() { return (head_->data); }

  private:
    allocator allocator_;
    Node* head_;
};


template <typename T, size_t BlockSize = 16>
class MemoryPool
{
  public:
    // 使用 typedef 简化类型书写
    typedef T*              pointer;

    // 定义 rebind<U>::other 接口
    template <typename U> struct rebind {
      typedef MemoryPool<U> other;
    };

    // 默认构造
    // C++11 使用了 noexcept 来显式的声明此函数不会抛出异常
    MemoryPool() noexcept {
      currentBlock_ = nullptr;
      currentSlot_ = nullptr;
      lastSlot_ = nullptr;
      freeSlots_ = nullptr;
    }

    // 销毁一个现有的内存池
    ~MemoryPool() noexcept {
      // 循环销毁内存池中分配的内存区块
      slot_pointer_ curr = currentBlock_;
      while (curr != nullptr) {
        slot_pointer_ prev = curr->next;
        operator delete(reinterpret_cast<void*>(curr));
        curr = prev;
      }
    }

    // 同一时间只能分配一个对象, n 和 hint 会被忽略
    pointer allocate(size_t n = 1, const T* hint = 0) {
      if (freeSlots_ != nullptr) { //空闲槽不为空 
        pointer result = reinterpret_cast<pointer>(freeSlots_);//MH 将freeSlots指针转换成pointer  //https://www.cnblogs.com/chanabi/p/9228998.html 指针变量的理解 
        freeSlots_ = freeSlots_->next;  //将原空闲槽，向下移动一位。  slot是联合体共用内存空间，所以 freeSlots_->next刚好是一个T类型的空间大小 
        return result;
      }
      else {
        if (currentSlot_ >= lastSlot_) { // 
          // 分配一个内存区块
          data_pointer_ newBlock = reinterpret_cast<data_pointer_>(operator new(BlockSize));//operate new 仅仅分配能容纳BlockSize大小的内存 //https://www.cnblogs.com/slgkaifa/p/6887887.html operate用法 
          cout<<"newBlock: "<<(int*)newBlock<<endl;
		  cout<<"lastBlock: " <<(int*)(newBlock + BlockSize)<<endl;
		  reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;
          currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);
          cout<<"currentBlock_: "<< currentBlock_<<endl;
          cout<<"sizeof(slot_pointer_): " << sizeof(slot_pointer_)<<endl;
          data_pointer_ body = newBlock + sizeof(slot_pointer_);
          cout<<"body: " << (int*)body<<endl;
          uintptr_t result = reinterpret_cast<uintptr_t>(body); //https://blog.csdn.net/cs_zhanyb/article/details/16973379 uintptr_t数据
          cout<<"result: "<<result<<endl;
          cout<<"alignof(slot_type_): " <<alignof(slot_type_)<<endl;
          size_t bodyPadding = (alignof(slot_type_) - result) % alignof(slot_type_);//alignof以sloot type对齐 申请的剩余空间 https://blog.csdn.net/luoshabugui/article/details/83268086 alignof 
          cout<<"bodyPadding :"<<bodyPadding<<endl;
		  currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);
		  cout<<"currentSlot_: "<<currentSlot_<<endl; 
          lastSlot_ = reinterpret_cast<slot_pointer_>(newBlock + BlockSize - sizeof(slot_type_) + 1);
          cout<<"lastSlot_ :"<<lastSlot_<<endl;
        }
        return reinterpret_cast<pointer>(currentSlot_++);
      }
    }

    // 销毁指针 p 指向的内存区块
    void deallocate(pointer p, size_t n = 1) {
      if (p != nullptr) {
        reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;
        freeSlots_ = reinterpret_cast<slot_pointer_>(p);
      }
    }

    // 调用构造函数, 使用 std::forward 转发变参模板
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
      new (p) U (std::forward<Args>(args)...);
    }

    // 销毁内存池中的对象, 即调用对象的析构函数
    template <typename U>
    void destroy(U* p) {
      p->~U();
    }

  private:
    // 用于存储内存池中的对象槽
    union Slot_ {
      T element;
      Slot_* next;
    };

    // 数据指针
    typedef char* data_pointer_;
    // 对象槽
    typedef Slot_ slot_type_;
    // 对象槽指针
    typedef Slot_* slot_pointer_;

    // 指向当前内存区块
    slot_pointer_ currentBlock_;
    // 指向当前内存区块的一个对象槽
    slot_pointer_ currentSlot_;
    // 指向当前内存区块的最后一个对象槽
    slot_pointer_ lastSlot_;
    // 指向当前内存区块中的空闲对象槽
    slot_pointer_ freeSlots_;
    // 检查定义的内存池大小是否过小
    //static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};



int main()
{
 /*   clock_t start;

    // 使用默认分配器
    StackAlloc<int, std::allocator<int> > stackDefault;
    start = clock();
    for (int j = 0; j < REPS; j++) {
        assert(stackDefault.empty());
        for (int i = 0; i < ELEMS; i++)
          stackDefault.push(i);
        for (int i = 0; i < ELEMS; i++)
          stackDefault.pop();
    }
    std::cout << "Default Allocator Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
*/ 
    // 使用内存池
/*     StackAlloc<int, MemoryPool<int> > stackPool;
     start = clock();
     for (int j = 0; j < REPS; j++) {
         assert(stackPool.empty());
         for (int i = 0; i < ELEMS; i++)
           stackPool.push(i);
         for (int i = 0; i < ELEMS; i++)
           stackPool.pop();
     }
     std::cout << "MemoryPool Allocator Time: ";
     std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
*/ 
 	StackAlloc<int, MemoryPool<int> > stackPool;
 	stackPool.push(1); 
 	

    return 0;
}

