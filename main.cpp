#include<iostream>
#include<cstdint>
#include<functional>

// Possible superpowers
enum class Powers : std::uint8_t
{
    HUMAN = 0,
    SUPER_STRENGTH = 1 << 0,
    FLIGHT = 1 << 1,
    INVISIBLE = 1 << 2,
    FIRE_SHOOTING = 1 << 3,
    ICE_SHOOTING = 1 << 4,
    TELEPORTATION = 1 << 5,
    TRANSFORMATION = 1 << 6,
    TELEKINESIS = 1 << 7
};


Powers operator|(Powers lhs, Powers rhs)
{
    using underlying = std::underlying_type_t<Powers>;
    return static_cast<Powers>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

Powers operator&(Powers lhs, Powers rhs)
{
    using underlying = std::underlying_type_t<Powers>;
    return static_cast<Powers>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}


struct Superhero
{
    Powers powers{Powers::HUMAN};
};

void printBinary(std::uint8_t superpower)
{
   for(int i = 7; i >= 0; --i)
   {
        std::cout << ((superpower >> i) & 1);
   }
   std::cout << std::endl;
}

/*
bool checkSuperpower(Superhero hero, Powers superpower_to_check)
{
    if((hero.powers & superpower_to_check) != 0)
    {
        return 1;
    }
    return 0;
}
*/

void performAction(const std::function<void()>& func)
{
    func();
}

int main()
{
    /*
    Superhero my_first_hero;

    std::cout << my_first_hero.powers << std::endl;

    printBinary(my_first_hero.powers);

    */


    return 0;
}