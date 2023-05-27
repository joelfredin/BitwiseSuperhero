#include<iostream>
#include<cstdint>
#include<functional>
#include<type_traits>
#include"BitwiseOperators.hpp"

/*
POSSIBLE SUPERPOWERS
*/
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

struct Superhero
{
    Powers powers{Powers::HUMAN};
};


void enablePower(Superhero& hero, Powers power)
{
    hero.powers = bitwise_operator(hero.powers, power, std::bit_or<>{});
}

void revokePower(Superhero& hero, Powers power)
{
    hero.powers = bitwise_operator(hero.powers, bitwise_complement(power, std::bit_not<>{}), std::bit_and<>{});
}

bool hasPower(Superhero hero, Powers power)
{
    if(static_cast<int>(bitwise_operator(hero.powers,power, std::bit_and<>{})))
    {
        return true;
    }
    return false;
}

void printBinary(Powers superpower)
{
    for(int i = 7; i >=0; --i)
    {
        std::cout <<((static_cast<int>(superpower) >> i) & 1);
    }
    std::cout << std::endl;
}

int main()
{
    Superhero hero1;

    printBinary(hero1.powers);

    enablePower(hero1, Powers::FLIGHT);
    enablePower(hero1, Powers::TELEKINESIS);

    printBinary(hero1.powers);

    revokePower(hero1, Powers::TELEKINESIS);

    printBinary(hero1.powers);

    std::cout << hasPower(hero1, Powers::FLIGHT) << std::endl;

    return 0;
}