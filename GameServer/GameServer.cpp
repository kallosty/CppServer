#include "pch.h"

#include "RefCounting.h"
#include "Memory.h"
#include "Allocator.h"

using TL = TypeList<class Palyer, class Mage, class Knight, class Archer>;

class Player
{
public:
    Player()
    {
        INIT_TL(Player);
    }

    virtual ~Player() {}

    DECLARE_TL;
};

class Knight : public Player
{
public:
    Knight() { INIT_TL(Knight); }
};

class Mage : public Player
{
public:
    Mage() { INIT_TL(Mage); }
};

class Archer : public Player
{
public:
    Archer() { INIT_TL(Archer); }
};


int main()
{
    {
        /*Player* player = new Player();

        bool canCast = CanCast<Knight*>(player);
        Knight* knight = TypeCast<Knight*>(player);



        delete player;*/
    }

    {
        shared_ptr<Knight> knight = MakeShared<Knight>();

        shared_ptr<Player> player = TypeCast<Player>(knight);
        bool canCast = CanCast<Player>(knight);
    }

    for (int32 i = 0; i < 2; i++)
    {
        GThreadManager->Launch([]()
            {
                while (true)
                {
                    
                }
            });
    }

    GThreadManager->Join();
}