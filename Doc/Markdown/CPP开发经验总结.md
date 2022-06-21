# CPP开发经验总结 
## Modern CPP 
* [How to Adopt Modern C++17 into Your C++ Code](https://www.youtube.com/watch?v=UsrHQAzSXkA)


## 智能指针 
* unique_ptr经常作为返回值使用，设计模式中经常用到，异常安全
* 还有一个原因是因为： Return unique_ptr by value means caller taking the ownership. caller must take on the pointer 
    ```
    class PizzaFactory {
    public:
        enum PizzaType {
            HamMushroom,
            Deluxe,
            Hawaiian
        };
        static  unique_ptr<Pizza> createPizza(PizzaType pizzaType) {
            switch (pizzaType) {
            case HamMushroom: return make_unique<HamAndMushroomPizza>();
            case Deluxe:      return make_unique<DeluxePizza>();
            case Hawaiian:    return make_unique<HawaiianPizza>();
            }
            throw "invalid pizza type.";
        }
    };
    ```

## 什么时候用shared_ptr,什么时候用unique_ptr?

* 我一直在思考这个问题,其实判别很简单，就是ownership，独占所有权就用unique_ptr ，共享就shared
* 总结:
    > 正确使用智能指针的方式是在函数中作为参数传递是，尽量避免使用智能指针，使用*或者引用，跟以前一样
    尽量使用unique_ptr,他比shared_ptr更light (轻量)
    尽量使用makeshared/ make_unique 来代替new
    不出现new 和 delete
    
## 关于inline函数 
* 若一个非static函数在多个编译单元中被重复定义，那么在链接阶段会发生multiple definition的错误，这是因为面对同一符号的多个定义，链接器并不知道使用哪个。但是对于header-only的程序库来说，所有的函数定义都位于头文件，若不加特殊处理被多个源文件包含，则一定会发生multiple definition的错误。解决这个问题的方法是在函数声明处加上inline修饰，这样的话编译器在处理该函数时就会认为它是一个弱符号，链接器在面对多个名字相同的弱符号时只会保留其中一个的定义（具体的保留规则视编译器而定）[ 链接 ](https://www.zhihu.com/question/24185638/answer/2404153835)
