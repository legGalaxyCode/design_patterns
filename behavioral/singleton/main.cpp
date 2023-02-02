#include "singleton.hpp"

#include <thread>

void singleSingleton1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    auto singleton = Singleton::instance(1);
    std::cout << "Value = " << singleton->getValue() << '\n';
    // do not need to free pointer here
}

void singleSingleton2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    auto singleton = Singleton::instance(2);
    std::cout << "Value = " << singleton->getValue() << '\n';
}

void threadSafeSingleton1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    auto singleton = ThreadSafeSingleton::instance(10);
    std::cout << "Value = " << singleton->getValue() << '\n';
    // do not need to free pointer here
}

void threadSafeSingleton2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    auto singleton = ThreadSafeSingleton::instance(20);
    std::cout << "Value = " << singleton->getValue() << '\n';
}

void clientCode() {
    std::thread single1(singleSingleton1);
    std::thread single2(singleSingleton2);
    std::thread multi1(threadSafeSingleton1);
    std::thread multi2(threadSafeSingleton2);

    single1.join();
    single2.join();

    multi1.join();
    multi2.join();
}

int main() {
    std::cout << "Hello, singleton pattern!\n";
    std::cout <<"If you see the same value, then singleton was reused\n" <<
                "If you see different values, then 2 singletons were created\n\n" <<
                "RESULT:\n";

    clientCode();

    return 0;
}