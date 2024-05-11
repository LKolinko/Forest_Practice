#pragma once

template <class T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton&) = default;
    ~Singleton() = default;
public:
    static T* GetInstance() {
        static T instance;
        return &instance;
    }
};