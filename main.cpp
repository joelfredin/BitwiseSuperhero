#include<iostream>
#include<cstdint>
#include<functional>

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


struct Superhero
{
    Powers powers{Powers::HUMAN};
};

void enablePower(Superhero& hero, Powers power)
{
    hero.powers = bitwise_operator(hero.powers, power, std::bit_or<>{});
}



void printBinary(Powers superpower)
{
    for(int i = 7; i >=0; --i)
    {
        std::cout <<((static_cast<int>(superpower) >> i) & 1);
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

int main()
{
    Superhero hero1;

    //Powers result_or = bitwise_operator(Powers::FLIGHT, Powers::TELEKINESIS, std::bit_or<>{});
    printBinary(hero1.powers);

    enablePower(hero1, Powers::FLIGHT);
    enablePower(hero1, Powers::TELEKINESIS);

    //hero1.powers = result_or;

    //std::cout << static_cast<std::underlying_type_t<std::uint8_t>>(result_or) << std::endl;

    //std::cout << static_cast<int>(result_or) << std::endl;
    printBinary(hero1.powers);

    return 0;
}