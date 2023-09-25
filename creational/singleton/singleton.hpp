#include <memory>
#include <iostream>

class Singleton;
class ThreadSafeSingleton;
using SingletonPtr = std::unique_ptr<Singleton>;
using SingletonCPtr = Singleton*;
using SingletonRef = Singleton&;
using ThreadSafeSingletonPtr = std::unique_ptr<ThreadSafeSingleton>;
using ThreadSafeSingletonCPtr = ThreadSafeSingleton*;
using ThreadSafeSingletonRef = ThreadSafeSingleton&;

class Singleton {
public:
    friend class std::unique_ptr<Singleton>;
    friend std::unique_ptr<Singleton> std::make_unique<Singleton>(uint32_t&);
    friend std::unique_ptr<Singleton> std::make_unique<Singleton>(uint32_t&&);

    Singleton(Singleton&) = delete;
    void operator=(Singleton&) = delete;

    static SingletonCPtr instance(uint32_t value);

    uint32_t getValue() const { return value_; }

protected:
    explicit Singleton(uint32_t value): value_(value) {}

    static SingletonPtr instance_;
    uint32_t value_;
};

SingletonPtr Singleton::instance_ = nullptr;

SingletonCPtr Singleton::instance(uint32_t value) {
    if (!instance_)
        instance_ = std::make_unique<Singleton>(value);
    return instance_.get();
}

class ThreadSafeSingleton {
public:
    ThreadSafeSingleton(ThreadSafeSingleton&) = delete;
    void operator=(ThreadSafeSingleton&) = delete;

    static ThreadSafeSingletonCPtr instance(uint32_t value);

    uint32_t getValue() const { return value_; }

protected:
    explicit ThreadSafeSingleton(uint32_t value): value_(value) {}

    static ThreadSafeSingletonPtr instance_;
    static std::mutex mu_;
    uint32_t value_;
};

ThreadSafeSingletonPtr ThreadSafeSingleton::instance_ = nullptr;
std::mutex ThreadSafeSingleton::mu_;

ThreadSafeSingletonCPtr ThreadSafeSingleton::instance(uint32_t value) {
    std::lock_guard<std::mutex> lock(mu_);
    if (!instance_)
        instance_ = std::unique_ptr<ThreadSafeSingleton>(new ThreadSafeSingleton(value));
    return instance_.get();
}
