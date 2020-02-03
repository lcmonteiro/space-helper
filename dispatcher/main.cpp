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
#include <iostream>
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
int main() {   
    using namespace std::placeholders;
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

    return 0;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */