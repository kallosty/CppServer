#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include "AccountManager.h"
#include "UserManager.h"

void Func1()
{
    for (int32 i = 0; i < 1000; i++) {
        UserManager::Instance()->ProcessSave();
    }
}

void Func2()
{
    for (int32 i = 0; i < 1000; i++) {
        AccountManager::Instance()->ProcessLogin();
    }
}

int main()
{
    std::thread t1(Func1);
    std::thread t2(Func2);

    t1.join();
    t2.join();

    cout << "Jobs Done" << endl;

    //add
    mutex m1;
    mutex m2;

    std::lock(m1, m2);//m1.lock(); m2.lock();

    //adopt_lock : 이미 Lock 상태니까 나중에 소멸될 때 자동해제 해줘
    lock_guard<mutex> g1(m1, adopt_lock);
    lock_guard<mutex> g2(m2, adopt_lock);
}