#include <iostream>
#include <cstring>
#include <string>
#include <vector>

// 容器的空间配置器
template<typename T>
struct Allocator {
    // 内存开辟
    T *allocate(size_t size) { return (T *) malloc(sizeof(T) * size); }

    // 内存释放
    void deallocate(void *p) { free(p); }

    // 对象构造
    void construct(T *p, const T &val) { new(p) T(val); }

    // 对象析构
    void destroy(T *p) { p->~T(); }
};


template<typename T, typename Alloc = Allocator<T>>
class vector {
public:
    vector(int size = 10, const Alloc &alloc = Allocator<T>())
            : _allocator(alloc) {
        // _first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    ~vector() {
        // delete[] _first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p); /// 把_first指针指向的数组有效元素进行析构
        }
        _allocator.deallocate(_first); /// 释放堆上数组内存
        _first = _last = _end = nullptr;
    }

    vector(const vector<T> &rhs) {
        int size = rhs._end - rhs._first;
        // _first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i) {
            // _first[i] = rhs._first[i];
            _allocator.construct(_first + i, rhs._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
    }


    vector<T> &operator=(const vector<T> &vecc) {
        if (this == &vecc)
            return *this;

        // 释放原有资源，并重新根据vecc开辟对应的内存空间，并拷贝数据
        // delete[] _first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);
        int size = vecc._end - vecc._first;
        // _first = new T[size];
        _first = _allocator.allocate(size);
        int len = vecc._last - vecc._first;
        for (int i = 0; i < len; ++i) {
            //_first[i] = vecc._first[i];
            _allocator.construct(_first + i, vecc._first[i]);
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }

    void push_back(const T &val) {
        if (is_full()) {
            expand();
        }
        // *_last++ = val;
        /// _last指针指向的内存构造一个值为val的对象
        _allocator.construct(_last, val);
        _last++;
    }

    void pop_back() {
        if (is_empty())
            return;
        /// 析构删除的元素，并把_last指针--
        --_last;
        _allocator.destroy(_last);
    }

    // 返回末尾元素，_last保存的是最后一个元素的后继位置
    T back() const { return *(_last - 1); }

    int size() const { return _last - _first; }

    bool is_full() const { return _last == _end; }

    bool is_empty() const { return _first == _last; }

    T& operator[](int index)
    {
        if(index<0 || index >=size())
        {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    /// 迭代器一般实现成容器的嵌套类型
    class iterator
    {
    public:
        iterator(T *ptr = nullptr)
        :_ptr(ptr) {}

        bool operator!=(const iterator &it) const { return _ptr != it._ptr; }

        void operator++() { _ptr++; }

        T& operator*() { return *_ptr; } /// int data = *it; *it = 20;
        const T& operator*() const { return *_ptr; } /// int data = *it;

    private:
        T *_ptr;
    };

    iterator begin() { return iterator(_first); }
    iterator end() { return iterator(_last); }

private:
    T *_first;
    T *_last;
    T *_end;
    Alloc _allocator;

    void expand() {
        int size = _end - _first;
        // T *ptmp = new T[size * 2];
        T *ptmp = _allocator.allocate(size * 2);
        for (int i = 0; i < size; ++i) {
            // ptmp[i] = _first[i];
            _allocator.construct(ptmp + i, _first[i]);
        }
        // delete[] _first;
        for (T *p = _first; p != _last; ++p)
            _allocator.destroy(p);
        _allocator.deallocate(_first);
        _first = ptmp;
        _last = _first + size;
        _end = _first + size * 2;
    }
};



int main() {
    vector<int> vec;
    for (int i = 0 ; i < 20; ++i)
    {
        vec.push_back(rand() % 100 + 1 );
    }
    vector<int>:: iterator it = vec.begin();
    for(; it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}
