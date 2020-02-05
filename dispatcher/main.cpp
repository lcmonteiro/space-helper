/**
 * ------------------------------------------------------------------------------------------------
 * File:   main.cpp
 * Author: Luis Monteiro
 *
 * Created on February 3, 2020, 22:11 PM
 * ------------------------------------------------------------------------------------------------
 **
 * std
 */
#include <memory>
#include <iostream>
#include <functional>
/**
 * local
 */
#include "SDispatcher.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Definitions
 * ------------------------------------------------------------------------------------------------
 *  Model 1
 * ----------------------------------------------------------------------------
 */
static int runable(int i) {
    return i * i;
}
class Process {
public:
    int run(int i) {
        return i + i;
    }
};
/**
 * ----------------------------------------------------------------------------
 *  Model 2
 * ----------------------------------------------------------------------------
 */
class Callable {
public:
    virtual int operator()(int i) = 0;
};
class Operation1: public Callable {
Public:
    Operation1(int a, int b)
    : __a(a), __b(b) {}

    int operator()(int i){
        return i * __a + __b;
    }
};
class Operation2: public Callable {
    int operator()(int i){
        return i * 10;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Main
 * ------------------------------------------------------------------------------------------------
 */
int main() {  
    using namespace std::placeholders; 
    /**
     * --------------------------------------------------------------------------
     * Model 1
     * --------------------------------------------------------------------------
     */
    {
        std::cout << "Model 1 ..." << std::endl;
        /**
         * register
         */
        using Dispatcher = Helper::SDispatcher<
            std::string, std::function<int(int)>>;
        Dispatcher d;
        Process p;
        d.emplace("process" , std::bind(&Process::run, &p, _1));
        d.emplace("lambda"  , [](int i){ return i; });
        d.emplace("function", &runable);
        /**
         * invoke
         */
        std::cout << d("process" , 3) << std::endl;
        std::cout << d("lambda"  , 3) << std::endl;
        std::cout << d("function", 3) << std::endl;
    }
    /**
     * --------------------------------------------------------------------------
     * Model 2
     * --------------------------------------------------------------------------
     */
    {
        std::cout << "Model 2 ..." << std::endl;
        /**
         * register
         */
        using Dispatcher = Helper::SDispatcher<
            std::string, std::shared_ptr<Callable>>;
        Dispatcher d;
        d.emplace("Operation1" , std::make_shared<Operation1>(3, 4));
        d.emplace("Operation2" , std::make_shared<Operation2>());
        /* 
         * invoke
         */
        std::cout << d("Operation1", 3) << std::endl;
        std::cout << d("Operation2", 3) << std::endl;
    }
    /**
     * --------------------------------------------------------------------------
     * Model 3
     * --------------------------------------------------------------------------
     */
    {
        std::cout << "Model 3 ..." << std::endl;
        /**
         * register d1
         */
        using Dispatcher1 = Helper::SDispatcher<
            std::string, std::shared_ptr<Callable>>;
        auto d1 = std::make_shared<Dispatcher1>();
        d1->emplace("Operation1" , std::make_shared<Operation1>(1, 7));
        d1->emplace("Operation2" , std::make_shared<Operation2>());
        /**
         * register d2
         */
        using Dispatcher2 = Helper::SDispatcher<
            std::string, std::shared_ptr<Dispatcher1>>;
        Dispatcher2 d2;
        d2.emplace("d1" , d1);
        /* 
         * invoke d1 from d2
         */
        std::cout << d2("d1", "Operation1", 3) << std::endl;
        std::cout << d2("d1", "Operation2", 3) << std::endl;
    }
    return 0;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
