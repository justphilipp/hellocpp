#include <iostream>
#include <typeinfo>

/**
 * 基类和派生类的析构和构造
 * 打印结果：先析构派生类
 * Base()
 * Derive()
 * ~Derive()
 * ~Base()
*/
class Base {
public:
    Base(int data) : ma(data),mb(0) { std::cout << "Base()" << std::endl; }
    virtual ~Base() { std::cout << "~Base()" << std::endl; }
    virtual void show() { std::cout << "Base::show()" << std::endl; }
    virtual void show(int) { std::cout << "Base::show(int)" << std::endl; }
protected:
    int ma;
private:
    int mb;
};

class Derive : public Base {
public:
    Derive(int data) : Base(data),mc(0) { std::cout << "Derive()" << std::endl; }
    ~Derive() { std::cout << "~Derive()" << std::endl; }
    void show() { std::cout << "Derive::show()" << std::endl; }
protected:
    int mc;
};

int main() {
//    Base base(20);
//    Derive derive(10);
//
//    /// 隐藏关系
//    derive.show();
//    //derive.show(10); // Too many arguments to function call, expected 0, have 1; did you mean 'Base::show'?
//    derive.Base::show(); /// 优先找的是派生类自己作用域的成员，没有的话才去基类里面找
//
//    /// 基类对象 <- 派生类对象 类型从下到上的转换 Y
//    base = derive;
//    /// 派生类对象 <- 基类对象 类型从上到下的转换 N
//    // derive = base;
//    /// 基类指针（引用） <- 派生类对象 类型从下到上的转换 Y
//    Base *pb = &derive;
//    /// 派生类指针（引用） <- 基类对象 类型从上到下的转换 N
//    // Derive *pd = &base;
//
//
//    /**
//     pb->Base Base::show 如果发现show是普通函数，就进行静态绑定 call Base::show
//     pb->Base Base::show 如果发现show是虚函数，就进行动态（运行时期）绑定（函数调用）
//     mov eax dword ptr[pb]
//     mov ecx dword ptr[eax]
//     call ecx(虚函数的地址)
//     * */
//    pb->show();
//    pb->show(10);
//
//    std::cout << sizeof(Base) << " " << sizeof(Derive) << std::endl;
//    /**
//     * pb的类型:Base -> 有没有虚函数
//     * 如果Base没有虚函数，*pb识别的就是编译时期的类型 *pb即为Base类型
//     * 如果Base有虚函数，*pb识别的就是运行时期的类型， 即RTTI类型
//     * */
//    std::cout << typeid(pb).name() << " " << typeid(*pb).name() << std::endl;

    Base *ptrb = new Derive(10);
    Derive *ptrd = new Derive(100);
    ptrb->show(); // 动态绑定 ptrb Base*  *ptrb Derive
    ptrd->show();
    /**如果析构函数并非虚函数，
     * ptrb->Base Base::~Base 调用析构函数，静态绑定
     * 如果析构函数是虚函数
     * ptrb->Base Base::~Base 调用析构函数，动态绑定
     */
    delete ptrb; // 派生类的析构函数没有调用到！


    return 0;
}
