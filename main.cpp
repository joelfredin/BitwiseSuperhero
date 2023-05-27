#include<iostream>
#include<cstdint>
#include<functional>
#include<type_traits>

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

template<typename EnumType>
constexpr bool enable_bitwise_operator()
{
    return true;
}

template<typename EnumType>
constexpr bool enable_bitwise_operator(std::integral_constant<EnumType, EnumType::last_>)
{
    return false;
}

template<typename EnumType>
constexpr bool has_bitwise_operator = enable_bitwise_operator<EnumType>();

template<typename EnumType, typename BitwiseOp>
std::enable_if_t<has_bitwise_operator<EnumType>, EnumType> bitwise_operator(EnumType lhs, EnumType rhs, BitwiseOp op)
{
    using Underlying = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(op(static_cast<Underlying>(lhs),static_cast<Underlying>(rhs)));
}

template<typename EnumType, typename BitwiseOp>
std::enable_if_t<has_bitwise_operator<EnumType>, EnumType> bitwise_complement(EnumType lhs, BitwiseOp op)
{
    using Underlying = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(op(static_cast<Underlying>(lhs)));
}


void enablePower(Superhero& hero, Powers power)
{
    hero.powers = bitwise_operator(hero.powers, power, std::bit_or<>{});
}

void revokePower(Superhero& hero, Powers power)
{
    hero.powers = bitwise_operator(hero.powers, bitwise_complement(power, std::bit_not<>{}), std::bit_and<>{});
}



void printBinary(Powers superpower)
{
    for(int i = 7; i >=0; --i)
    {
        std::cout <<((static_cast<int>(superpower) >> i) & 1);
    }
    std::cout << std::endl;
}

bool hasPower(Superhero hero, Powers power)
{
    if(static_cast<int>(bitwise_operator(hero.powers,power, std::bit_and<>{})))
    {
        return true;
    }
    return false;
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