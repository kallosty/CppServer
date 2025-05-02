#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

vector<int32> v;
//기본적으로 STL 라이브러리는 thread에서 문제가 있다고 가정하고 시작해야 함

// Mutual Exclusive(상호 배타적)
mutex m;


//RAII (Resource Acquisition is Initialization)
template<typename T>
class LockGuard
{
public:
    LockGuard(T& m)
    {
        this->_mutex = &m;
        _mutex->lock();
    }

    ~LockGuard()
    {
        _mutex->unlock();
    }

private:
    T* _mutex;
};

void Push()
{
    for (int32 i = 0; i < 10000; i++)
    {
        //객체가 삭제될때 자동으로 락을 해제해줌
        //LockGuard<std::mutex> lockGuard(m);

        std::lock_guard<std::mutex> lockGuard(m);
        //std::unique_lock<std::mutex> uniqueLock(m, std::defer_lock); //좀 더 변수를 입력받아 락을 걸어줌
        //uniqueLock.lock();


        //자물쇠 잠그기
        //m.lock();

        v.push_back(i);

        if (i == 5000)
        {
            //m.unlock();
            break;
        }

        //자물쇠 풀기
        //m.unlock();
    }
}

int main()
{
    std::thread t1(Push);
    std::thread t2(Push);

    t1.join();
    t2.join();

    cout << v.size() << endl;
}