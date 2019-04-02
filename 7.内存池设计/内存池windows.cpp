
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
// �ظ�����
#define REPS 50
template <typename T>
struct StackNode_
{
  T data;
  StackNode_* prev;
};

// T Ϊ�洢�Ķ�������, Alloc Ϊʹ�õķ�����,
// ��Ĭ��ʹ�� std::allocator ��Ϊ����ķ�����
template <class T, class Alloc = std::allocator<T> >
class StackAlloc
{
  public:
    // ʹ�� typedef ��������
    typedef StackNode_<T> Node;
    typedef typename Alloc::template rebind<Node>::other allocator;

    // Ĭ�Ϲ���
    StackAlloc() { head_ = 0; }
    // Ĭ������
    ~StackAlloc() { clear(); }

    // ��ջ��Ԫ��Ϊ��ʱ���� true
    bool empty() {return (head_ == 0);}

    // �ͷ�ջ��Ԫ�ص������ڴ�
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

    // ��ջ
    void push(T element) {
      // Ϊһ���ڵ�����ڴ�
      Node* newNode = allocator_.allocate(1);
      // ���ýڵ�Ĺ��캯��
      allocator_.construct(newNode, Node());

      // ��ջ����
      newNode->data = element;
      newNode->prev = head_;
      head_ = newNode;
    }

    // ��ջ
    T pop() {
      // ��ջ���� ���س�ջ���
      T result = head_->data;
      Node* tmp = head_->prev;
      allocator_.destroy(head_);
      allocator_.deallocate(head_, 1);
      head_ = tmp;
      return result;
    }

    // ����ջ��Ԫ��
    T top() { return (head_->data); }

  private:
    allocator allocator_;
    Node* head_;
};


template <typename T, size_t BlockSize = 16>
class MemoryPool
{
  public:
    // ʹ�� typedef ��������д
    typedef T*              pointer;

    // ���� rebind<U>::other �ӿ�
    template <typename U> struct rebind {
      typedef MemoryPool<U> other;
    };

    // Ĭ�Ϲ���
    // C++11 ʹ���� noexcept ����ʽ�������˺��������׳��쳣
    MemoryPool() noexcept {
      currentBlock_ = nullptr;
      currentSlot_ = nullptr;
      lastSlot_ = nullptr;
      freeSlots_ = nullptr;
    }

    // ����һ�����е��ڴ��
    ~MemoryPool() noexcept {
      // ѭ�������ڴ���з�����ڴ�����
      slot_pointer_ curr = currentBlock_;
      while (curr != nullptr) {
        slot_pointer_ prev = curr->next;
        operator delete(reinterpret_cast<void*>(curr));
        curr = prev;
      }
    }

    // ͬһʱ��ֻ�ܷ���һ������, n �� hint �ᱻ����
    pointer allocate(size_t n = 1, const T* hint = 0) {
      if (freeSlots_ != nullptr) { //���в۲�Ϊ�� 
        pointer result = reinterpret_cast<pointer>(freeSlots_);//MH ��freeSlotsָ��ת����pointer  //https://www.cnblogs.com/chanabi/p/9228998.html ָ���������� 
        freeSlots_ = freeSlots_->next;  //��ԭ���вۣ������ƶ�һλ��  slot�������干���ڴ�ռ䣬���� freeSlots_->next�պ���һ��T���͵Ŀռ��С 
        return result;
      }
      else {
        if (currentSlot_ >= lastSlot_) { // 
          // ����һ���ڴ�����
          data_pointer_ newBlock = reinterpret_cast<data_pointer_>(operator new(BlockSize));//operate new ��������������BlockSize��С���ڴ� //https://www.cnblogs.com/slgkaifa/p/6887887.html operate�÷� 
          cout<<"newBlock: "<<(int*)newBlock<<endl;
		  cout<<"lastBlock: " <<(int*)(newBlock + BlockSize)<<endl;
		  reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;
          currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);
          cout<<"currentBlock_: "<< currentBlock_<<endl;
          cout<<"sizeof(slot_pointer_): " << sizeof(slot_pointer_)<<endl;
          data_pointer_ body = newBlock + sizeof(slot_pointer_);
          cout<<"body: " << (int*)body<<endl;
          uintptr_t result = reinterpret_cast<uintptr_t>(body); //https://blog.csdn.net/cs_zhanyb/article/details/16973379 uintptr_t����
          cout<<"result: "<<result<<endl;
          cout<<"alignof(slot_type_): " <<alignof(slot_type_)<<endl;
          size_t bodyPadding = (alignof(slot_type_) - result) % alignof(slot_type_);//alignof��sloot type���� �����ʣ��ռ� https://blog.csdn.net/luoshabugui/article/details/83268086 alignof 
          cout<<"bodyPadding :"<<bodyPadding<<endl;
		  currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);
		  cout<<"currentSlot_: "<<currentSlot_<<endl; 
          lastSlot_ = reinterpret_cast<slot_pointer_>(newBlock + BlockSize - sizeof(slot_type_) + 1);
          cout<<"lastSlot_ :"<<lastSlot_<<endl;
        }
        return reinterpret_cast<pointer>(currentSlot_++);
      }
    }

    // ����ָ�� p ָ����ڴ�����
    void deallocate(pointer p, size_t n = 1) {
      if (p != nullptr) {
        reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;
        freeSlots_ = reinterpret_cast<slot_pointer_>(p);
      }
    }

    // ���ù��캯��, ʹ�� std::forward ת�����ģ��
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
      new (p) U (std::forward<Args>(args)...);
    }

    // �����ڴ���еĶ���, �����ö������������
    template <typename U>
    void destroy(U* p) {
      p->~U();
    }

  private:
    // ���ڴ洢�ڴ���еĶ����
    union Slot_ {
      T element;
      Slot_* next;
    };

    // ����ָ��
    typedef char* data_pointer_;
    // �����
    typedef Slot_ slot_type_;
    // �����ָ��
    typedef Slot_* slot_pointer_;

    // ָ��ǰ�ڴ�����
    slot_pointer_ currentBlock_;
    // ָ��ǰ�ڴ������һ�������
    slot_pointer_ currentSlot_;
    // ָ��ǰ�ڴ���������һ�������
    slot_pointer_ lastSlot_;
    // ָ��ǰ�ڴ������еĿ��ж����
    slot_pointer_ freeSlots_;
    // ��鶨����ڴ�ش�С�Ƿ��С
    //static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};



int main()
{
 /*   clock_t start;

    // ʹ��Ĭ�Ϸ�����
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
    // ʹ���ڴ��
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

