#include "pch.h"
<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <chrono>
#include <future>
#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

<<<<<<< HEAD
class TestLock
=======

#include "RefCounting.h"

class Wraight : public RefCountable
>>>>>>> Stashed changes
=======

#include "RefCounting.h"

class Wraight : public RefCountable
>>>>>>> Stashed changes
{
public:
    int _hp = 150;
    int _posX = 0;
    int _posY = 0;
};

using WraightRef = TSharedPtr<Wraight>;

class Missile : public RefCountable
{
public:
    void SetTarget(WraightRef target)
    {
        _target = target;
        //target->AddRef();
        //Test(target);
    }

    /*void Test(WraightRef& target)
    {
<<<<<<< Updated upstream
<<<<<<< Updated upstream
        int32 value = testLock.TestRead();
        cout << value << endl;
        this_thread::sleep_for(1ms);
=======
LockQueue<int32> q;
LockFreeStack<int32> s;

void Push()
{
    while (true)
    {
        int32 value = rand() % 100;
        s.Push(value);

        //this_thread::sleep_for(100ms);
=======

    }*/

    bool Update()
    {
        if (_target == nullptr)
            return true;

        int posX = _target->_posX;
        int posY = _target->_posY;

        //TODO : 쫓아간다.
        if (_target->_hp == 0)
        {
            _target->ReleaseRef();
            _target = nullptr;
            return true;
        }

        return false;
>>>>>>> Stashed changes
    }

    WraightRef _target = nullptr;
};

using MissileRef = TSharedPtr<Missile>;

void Pop()
{
    while (true) {
        auto data = s.TryPop();
        if (data != nullptr) cout << *data << endl;
>>>>>>> parent of 36864ab (Thread_ThreadManager)
=======

    }*/

    bool Update()
    {
        if (_target == nullptr)
            return true;

        int posX = _target->_posX;
        int posY = _target->_posY;

        //TODO : 쫓아간다.
        if (_target->_hp == 0)
        {
            _target->ReleaseRef();
            _target = nullptr;
            return true;
        }

        return false;
>>>>>>> Stashed changes
    }

    WraightRef _target = nullptr;
};

using MissileRef = TSharedPtr<Missile>;

int main()
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< HEAD
    for (int32 i = 0; i < 2; i++)
    {
        GThreadManager->Launch(ThreadWrite);
    }

    for (int32 i = 0; i < 5; i++)
    {
        GThreadManager->Launch(ThreadRead);
    }
=======
    shared_ptr<int32> ptr;
    bool value = atomic_is_lock_free(&ptr);
>>>>>>> parent of 36864ab (Thread_ThreadManager)

    thread t1(Push);
    thread t2(Pop);
    thread t3(Pop);



    t1.join();
    t2.join();
    t3.join();
=======
    WraightRef wraight(new Wraight());
    wraight->ReleaseRef();
    MissileRef missile(new Missile());
    missile->ReleaseRef();

    missile->SetTarget(wraight);
    // 레이스가 피격 당함
    wraight->_hp = 0;
    //delete wraight;
    //wraight->ReleaseRef();
    wraight = nullptr;

=======
    WraightRef wraight(new Wraight());
    wraight->ReleaseRef();
    MissileRef missile(new Missile());
    missile->ReleaseRef();

    missile->SetTarget(wraight);
    // 레이스가 피격 당함
    wraight->_hp = 0;
    //delete wraight;
    //wraight->ReleaseRef();
    wraight = nullptr;

>>>>>>> Stashed changes
    while (true)
    {
        if (missile)
        {
            if (missile->Update())
            {
                missile->ReleaseRef();
                missile = nullptr;
            }
        }
    }
    
    //delete missile;
    //missile->ReleaseRef();
    missile = nullptr;
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}