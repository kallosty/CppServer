#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <chrono>
#include <future>
#include "CoreMacro.h"
#include "ThreadManager.h"

CoreGlobal Core;

void ThreadMain()
{
    while(true)
    {
        cout << "hello! I am thread ... " << LThreadId << "\n";
        this_thread::sleep_for(1s);
    }
}


int main()
{
    for (int32 i = 0; i < 5; i++) {
        GThreadManager->Launch(ThreadMain);
    }

    GThreadManager->Join();
}