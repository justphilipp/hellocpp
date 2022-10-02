#include <iostream>
#include <vector>

template<typename T>
class vector {
public:
    vector(int size = 10) {
        _first = new T[size];
        _last = _first;
        _end = _first + size;
    }

    ~vector() {
        delete[] _first;
        _first = _last = _end = nullptr;
    }

    vector(const vector<T> &rhs) {
        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i < len; ++i) {
            _first[i] = rhs._first[i];
        }
        _last = _first + len;
        _end = _first + size;
    }

    vector<T> &operator=(const vector<T> &vecc) {
        if (this == &vecc)
            return *this;

        // 释放原有资源，并重新根据vecc开辟对应的内存空间，并拷贝数据
        delete[] _first;

        int size = vecc._end - vecc._first;
        _first = new T[size];
        int len = vecc._last = vecc._first;
        for (int i = 0; i < len; ++i) {
            _first[i] = vecc._first[i];
        }
        _last = _first + len;
        _end = _first + size;
        return *this;
    }

    void push_back(const T &val) {
        if (is_full()) {
            expand();
        }
        *_last++ = val;
    }

    void pop_back() {
        if (is_empty())
            return;
        --_last;
    }

    // 返回末尾元素，_last保存的是最后一个元素的后继位置
    T back() const { return *(_last - 1); }

    int size() const { return _last - _first; }

    bool is_full() const { return _last == _end; }

    bool is_empty() const { return _first == _last; }

    // this指针访问私有变量与直接访问私有变量等价
    void check() {
        if (this->_first == _first)
            std::cout << "this->_first == _first " << std::endl;
        else std::cout << 0 << std::endl;
    }

private:
    T *_first;
    T *_last;
    T *_end;

    void expand() {
        int size = _end - _first;
        T *ptmp = new T[size * 2];
        for (int i = 0; i < size; ++i) {
            ptmp[i] = _first[i];
        }
        delete[] _first;
        _first = ptmp;
        _last = _first + size;
        _end = _first + size * 2;
    }
};

int main() {

    std::vector<int> vec100{1, 2, 4};
    vector<int> vec_default;
    for (int i = 0; i < 20; ++i) {
        vec_default.push_back(i);
    }
    std::cout << vec_default.size() << std::endl; // 20
    while (!vec_default.is_empty()) {
        std::cout << vec_default.back() << " ";
        vec_default.pop_back();
    }
    std::cout << std::endl;
    std::cout << vec_default.size() << std::endl; // 0

    return 0;
}
