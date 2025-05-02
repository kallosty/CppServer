#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;
//Spin Lock

class SpinLock
{
public:
    void lock()
    {
        //CAS (Compare-Add-Swap)

        bool expected = false;
        bool desired = true;

        ////CAS 의사 코드 : _locked.compare_exchange_strong(expected, desired);
        //if (_locked == expected)
        //{
        //    expected = _locked;
        //    _locked = desired;
        //    return true;
        //}
        //else {
        //    expected = _locked;
        //    return false;
        //}

        while (_locked.compare_exchange_strong(expected, desired) == false) //Spin Lock
        {
            expected = false;

            //Sleep
            //this_thread::sleep_for(std::chrono::milliseconds(100)); //언제까지 자고 있어라. 실행 시간을 변수로
            //this_thread::yield(); //양보한다. -> 커널모드로 넘어가라
            
            this_thread::sleep_for(0ms); // 0ms 하기 위해서 include <chrono> 와 using namespace std::chrono_literals; 가 필요
        }

        /*while (_locked)
        {

        }

        _locked = true;*/
    }

    void unlock()
    {
        //_locked = false;
        _locked.store(false);
    }

private:
    atomic<bool> _locked = false;
    //volatile c++ : 컴파일러에게 최적화를 하지 말라달라고 요청
};


mutex m;
int32 sum = 0;
SpinLock spinLock;

void Add()
{
    for (int32 i = 0; i < 100'000; i++)
    {
        lock_guard<SpinLock> gaurd(spinLock);
        sum++;
    }
}

void Sub()
{
    for (int32 i = 0; i < 100'000; i++)
    {
        lock_guard<SpinLock> gaurd(spinLock); 
        sum--;
    }
}

int main()
{
    thread t1(Add);
    thread t2(Sub);

    t1.join();
    t2.join();

    cout << sum << endl;
}