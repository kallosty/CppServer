#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h> //for Event Lock
#include <chrono>


mutex m;
queue<int32> q;
HANDLE handle;

void Producer()
{
    while (true) {
        {
            unique_lock<mutex> lcok(m);
            q.push(100);
        }

        ::SetEvent(handle); //이벤트를 signal 상태로 바꿔주세요.

        this_thread::sleep_for(100ms);
    }
}

void Consumer()
{
    while (true) {
        ::WaitForSingleObject(handle, INFINITE); //handle 시그널 상태를 확인
        //::ResetEvent(handle); -> Manual, bManaulReset 쪽이 true이면 설정해줘야 함
        //Non-Signal

        unique_lock<mutex> lock(m);
        if (q.empty() == false) {
            int32 data = q.front();
            q.pop();
            cout << data << endl;
        }
    }
}

int main()
{
    //HANDLE은 식별자
    //커널 오브젝트 - 프로세스나 이러한 핸들 오브젝트들, 커널에서 관리하는 또는 할당되는 오브젝트들..
    //Usage Count
    //Signal (green light) / Non-Signal (red light) << bool
    //Auto / Manual << bool

    handle = ::CreateEvent(NULL/*보안속성*/, FALSE/*bManualReset*/, FALSE/*bInitialState*/, NULL);

    thread t1(Producer);
    thread t2(Consumer);

    t1.join();
    t2.join();

    ::CloseHandle(handle); //해제해주는 것
}