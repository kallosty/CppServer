#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>

//thread Practice

void HelloThread()
{
    cout << "HelloThread\n";
}

void HelloTrhead_2(int32 n)
{
    cout << "HelloThread_2 " << n <<"\n";
}

int main()
{
    //리눅스 서버와 윈도우 서버를 동시에 구축할 수 있게 항상 생각해보면서..
    std::thread t(HelloThread);


    ////Thread 에서 많이쓰이는 함수들
    t.join(); //쓰레드가 끝날 때까지 대기
    //t.joinable(); //쓰레드가 살아있는 지 확인
    //t.detach(); //쓰레드 끊기?
    //int32 core = t.hardware_concurrency(); //코어 갯수 확인
    //auto t_id = t.get_id(); //쓰레드 마다의 id 가져오기

    //벡터 활용
    vector<std::thread> v;
    v.resize(10);
    for (int i = 0; i < 10; i++) {
        v[i] = std::thread(HelloTrhead_2, i);
    }

    for (int i = 0; i < 10; i++) {
        if (v[i].joinable()) v[i].join();
    }
}