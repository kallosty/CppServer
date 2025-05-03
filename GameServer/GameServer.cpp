#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <chrono>
#include <future>

//atomic<bool> flag;

atomic<bool> ready;
int32 value;

void Producer()
{
    value = 10;

    ready.store(true, memory_order::memory_order_release);
}

void Consumer()
{
    while (ready.load(memory_order::memory_order_acquire) == false)
        ;

    cout << value << endl;
}

int main()
{
    ready = false;
    value = 0;
    thread t1(Producer);
    thread t2(Consumer);

    t1.join();
    t2.join();
    

    // Memory Model (정책)
    // 1) Sequentially Consistent(seq_cst)
    // 2) Acquire-Release(acquire, release)
    // 3) Relaxed (relaxed)

    // 1) seq_cst(가장 엄격 = 컴파일러 최적화 여지 적음 = 직관적)
    // 2) acquire-release
    // 3) relaxed (자유롭다 = 컴파일러 최적화 여지 많음 = 직관적이지 않음)
    
    // 1) seq_cst 이것의 경우 가시성, 코드 재배치성에 대해서 해결이 가능하다.

    // 2) 의 경우 딱중간!
    // release 명령 이전의 메모리 명령들이, 해당 명령 이후로 재배치 되는 것을 금지 -> 절취선을 두고 경계선을 나누는 느낌
    // 그리고 acquire로 같은 변수를 읽는 쓰레드가 있다면 release 이전 명령들이 -> acquire 하는 순간에 관찰 가능 (가시성 보장)

    // 3) 의 경우 너무나도 자유롭다!
    // 코드 재배치도 멋대로 가능! 가시성 해결 NO!
    // 가장 기본 조건 (동일 객체에 대한 동일 관전 순서만 보장)

    // 인텔, AMD 는 기본적으로 seq_cst로 되어있기 때문에 생략해도 문제가 되지 않는다.
}

void Memo() {
    /*Memo 1
    //flag = false;
    //flag.store(true, memory_order::memory_order_seq_cst);
    //bool val = flag.load(memory_order::memory_order_seq_cst);

    ////이전 flag 값을 prev 에 넣고, flag 값을 수정
    //{
    //    bool prev = flag.exchange(true); //한번에 실행. 아토믹

    //    /*bool prev = flag;
    //    flag = true;*/
    //}

    ////CAS(Compare-And-Swap) 조건부 수정
    //{
    //    bool expected = false;
    //    bool desired = true;

    //    flag.compare_exchange_strong(expected,desired);
    //    //위의 의사코드로 아래와 같음. 이게 한 번에 실행됨.
    //    // Spurious Failure
    //    /*if (flag == expected)
    //    {
    //        //다른 쓰레드의 interruption을 받아서 중간에 실패할 수 있음
    //        //if(묘한 상황) return false; //하드웨어나 로직에 따라서 이렇게 실패했으면 weak로 나오고,
    //                                        //strong은 될때까지 기다림
    //        flag = desired;
    //        return true;
    //    }
    //    else {
    //        expected = flag;
    //        return false;
    //    }*/

    //    //bool expected = false;
    //    //bool desired = true;
    //    //flag.compare_exchange_weak(expected, desired);//무조건 while 루프랑 사용하는게 좋음.
    //    
    //}
}
