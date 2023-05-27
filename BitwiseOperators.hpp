#include<iostream>
#include<cstdint>
#include<functional>
#include<type_traits>

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