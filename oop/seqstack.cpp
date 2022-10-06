#include <iostream>


// 类模板
template<typename T = int> // 默认类型参数
class SeqStack   // 模板名称
{
public:
    // 构造和析构函数，模板后尖括号参数列表可以省略
    SeqStack<T>(int size = 10)  // 模板名称+类型参数列表 = 类名称
            : _pstack(new T[size]), _top(0), _size(size) { std::cout << this << " SeqStack()" << std::endl; }

    ~SeqStack<T>() {
        std::cout << this << "~SeqStack()" << std::endl;
        delete[] _pstack;
        _pstack = nullptr;
    }
     // copy
    SeqStack<T>(const SeqStack<T> &stack)
        : _top(stack._top)
        , _size(stack._size)
    {
        std::cout << this << " const SeqStack&" << std::endl;
        _pstack = new T[_size];
        // 不能用memcopy浅拷贝
        for (int i = 0; i < _top ; ++i)
        {
            _pstack[i] = stack._pstack[i];
        }
    }

    SeqStack<T>& operator=(const SeqStack<T> &stack)
    {
        std::cout << this << " operator=.(const SeqStack&)" << std::endl;
        if (this == &stack)
            return *this;
        delete[] _pstack;

        _top = stack._top;
        _size = stack._size;
        _pstack = new T[_size];
        // 不能用memcopy浅拷贝
        for (int i = 0; i < _top ; ++i)
        {
            _pstack[i] = stack._pstack[i];
        }
        return *this;
    }

    void push(const T &val);

    void pop() {
        if (is_empty())
            return;

        --_top;
    }

    T top() const {
        if (is_empty())
            // 抛异常也代表函数逻辑结束，抛出的异常无须与返回值类型一致
            throw "stack is empty!";
        return _pstack[_top - 1];
    }

    bool is_full() const { return _top == _size; }

    bool is_empty() const { return _top == 0; }


private:
    T *_pstack;
    int _top;
    int _size;

    // 顺序栈底层数组按二倍方式扩容
    void expand() {
        T *ptmp = new T[_size * 2];
        for (int i = 0; i < _top; ++i) {
            ptmp[i] = _pstack[i];
        }
        delete[] _pstack;
        _pstack = ptmp;
        _size *= 2;

    }

};

// 类外实现成员方法：添加类作用域SeqStack<T>
template<typename T>
void SeqStack<T>::push(const T &val) {
    if (is_full())
        expand();
    _pstack[_top++] = val;
}

int main() {
    SeqStack<std::string> string_seqstack;
    SeqStack<std::string> s1 =string_seqstack;
    SeqStack<std::string> s2(string_seqstack); // s2与s3等价，都调用拷贝构造函数，而不是operator=
    string_seqstack.push("all we need");
    string_seqstack.push("is just a little");
    string_seqstack.push("patience");
    string_seqstack.pop();
    std::cout << string_seqstack.top() << std::endl;

    s2 = s1; // 调用operator=

    return 0;
}

/*
Output:
0x3c5b5ffd00 SeqStack()
0x3c5b5ffcf0 const SeqStack&
0x3c5b5ffce0 const SeqStack&
is just a little
0x3c5b5ffce0 operator=.(const SeqStack&)
0x3c5b5ffce0~SeqStack()
0x3c5b5ffcf0~SeqStack()
0x3c5b5ffd00~SeqStack()

Process finished with exit code 0

*/
