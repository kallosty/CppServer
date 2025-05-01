#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>

//실습2

// atomic : All-Or-Nothing

//DB - 거래했을 때
//A라는 유저 인벤에서 집행검 빼고
//B라는 유저 인벤에 집행검을 추가
//크래시 났을 때 A라는 유저 인벤에서 집행검만 빼질 수 있음
// 그래서 atomic 연산으로.. 최소단위로 계산해야함

std::atomic<int32> sum = 0;
//아토믹 연산은 매우 느리므로 막 사용하면 안 된다. -> 공유 데이터를 건드리는 실습

void Add()
{
    for (int32 i = 0; i < 1'000'000; i++)
    {
        sum.fetch_add(1);
        //sum++;
    }
}

void Sub()
{
    for (int32 i = 0; i < 1'000'000; i++)
    {
        sum.fetch_sub(1);
        //sum--;
    }
}

int main()
{
    Add();
    Sub();

    cout << sum << endl;

    std::thread t1(Add);
    std::thread t2(Sub);

    t1.join();
    t2.join();

    cout << sum << endl;
}