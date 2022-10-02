#include <iostream>
#include <cstring>


// define a template
template<typename T>
bool compare(T a, T b){
    std::cout << "template compare" << std::endl;
    return a > b;
}

/*调用函数模板的过程：在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
 * 模板函数：
 * bool compare<int>(int a, int b){
    std::cout << "template compare" << std::endl;
    return a > b;
 *
 * bool compare<double>(double a, double b){
    std::cout << "template compare" << std::endl;
    return a > b;
 * */

/// 模板的特例化
/// 针对compare函数模板，提供const char*类型的特例化版本
template<>
bool compare(const char* a, const char* b)
{
    std::cout << "compare<const char*>" << std::endl;
    return strcmp(a,b) > 0;
}

/// 非模板函数
bool compare(const char* a, const char* b)
{
    std::cout << "normal compare" << std::endl;
    return strcmp(a,b) > 0;
}



int main()
{
    // compare is the name of template
    // compare<> is the name of function
    compare<int>(10,20);

    // 函数模板的实参推演，可以根据用户传入的实参的类型，推导出模板类型
    compare(10,20);

    // 无法实参推演,因为没有对应的模板
    // compare(10,20.5);

    // 把double类型转换为整型
    compare<int>(10 , 20.5);

    // 函数模板提供的compare，对于const char*类型，a>b比较的是地址
    // 若要比较ASCII码顺序，则需要特例化函数模板提供的compare
    compare<const char*>("philipp","mike");

    // 优先调用非模板函数，而不是进行模板的实参推演
    compare("philipp", "mike");


    return 0;
}
