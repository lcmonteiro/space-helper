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
 * Main
 * ------------------------------------------------------------------------------------------------
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

class Callable {
public:
    virtual int operator()(int i) = 0;
};
class Callable1: public Callable {
    int operator()(int i){
        return i * 10;
    }
};
class Callable2: public Callable {
    int operator()(int i){
        return i * 10;
    }
};

int main() {   
    using namespace std::placeholders;
    /**
     * --------------------------------------------------------------------------
     * type 1
     * --------------------------------------------------------------------------
     */
    {
        using Dispatcher = Helper::SDispatcher<std::string, std::function<int(int)>>;
        Dispatcher d;
        /**
         * register
         */
        Process p;
        d.add_callable("process" , std::bind(&Process::run, &p, _1));
        d.add_callable("lambda"  , [](int i){ return i; });
        d.add_callable("function", &runable);
        /**
         * invoke
         */
        std::cout << d.invoke("process" , 3) << std::endl;
        std::cout << d.invoke("lambda"  , 3) << std::endl;
        std::cout << d.invoke("function", 3) << std::endl;
    }
    /**
     * --------------------------------------------------------------------------
     * type 2
     * --------------------------------------------------------------------------
     */
    // {
    //     using Dispatcher = Helper::SDispatcher<
    //         std::string, std::shared_ptr<Callable>>;
    //     Dispatcher d;
    //     /**
    //      * register
    //      */
    //     d.add_callable("Callable2" , std::make_shared<Callable2>());
    //     d.add_callable("Callable2" , std::make_shared<Callable2>());
    //     /* 
    //      * invoke
    //      */
    //     std::cout << d.invoke("Callable2", 3) << std::endl;
    //     std::cout << d.invoke("Callable2", 3) << std::endl;
    // }
    return 0;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */