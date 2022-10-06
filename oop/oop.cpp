#include <iostream>
#include <cstring>

const int NAME_LEN = 20;

// CDate is a part of CGoods
class CDate {
public:
    CDate(int y, int m, int d) {
        _year = y;
        _month = m;
        _day = d;
    }

    void showDate() const { std::cout << _year << "/" << _month << "/" << _day << std::endl; }

private:
    int _year;
    int _month;
    int _day;
};

class CGoods {
public:
    CGoods(char *n, int a, double p, int y, int m, int d)
            : _date(y, m, d), _amount(a), _price(p) {
        strcpy(_name, n);
        _count++;
    }

    void show() { _date.showDate(); } // CGoods *this

    // const member function
    void show() const { _date.showDate(); } // const CGoods *this

    // static member function
    static void showCGoodsCount() {
        std::cout << "CGoodsCount = " << _count << std::endl;
        // invalid use of member '_name' in static member function
        //
//        std::cout << "name = " << _name << std::endl;
    }

private:
    char _name[NAME_LEN];
    double _price;
    int _amount;
    CDate _date;
    static int _count;
};

// static can only be specified inside the class definition
int CGoods::_count = 0;

// CMemberPtrTest
class CMemberPtrTest {
public:
    int ma;
    static int mb;

    void func() { std::cout << "call CMemberPtrTest::func" << std::endl; }

    static void static_func() { std::cout << "CMemberPtrTest::static_func" << std::endl; }
};

int CMemberPtrTest::mb;

int main() {
    CGoods pepsi("pepsi", 100, 3.5, 2022, 3, 4); // initialize a object
    CGoods coca("coca", 100, 3.5, 2022, 3, 4);
    coca.show();
    CGoods::showCGoodsCount();

    const CGoods special("special", 100, 3.2, 2022, 3, 4);
    special.show(); // CGoods::show(&special)

    CMemberPtrTest test1;
    CMemberPtrTest *test2 = new CMemberPtrTest();

    // 无法从"CMemberPtrTest::*" 转换成"int *",必须加类作用域
    int CMemberPtrTest::*p = &CMemberPtrTest::ma;
    test1.*p = 20;
    std::cout << test1.*p << std::endl;
    test2->*p = 30;
    std::cout << test2->*p << std::endl;

    // static member variable不依赖对象，可以定义普通指针指向该变量
    int *p_static = &CMemberPtrTest::mb;
    *p_static = 40;
    std::cout << *p_static << std::endl;

    // ptr to memeber function
    void (CMemberPtrTest::*pfunc)() = &CMemberPtrTest::func;
    (test1.*pfunc)();
    (test2->*pfunc)();

    void (*pfunc_static)() = &CMemberPtrTest::static_func;
    pfunc_static();

    delete test2;
    return 0;
}
