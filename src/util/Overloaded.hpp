#ifndef OVERLOADED
#define OVERLOADED

namespace Powder::Util
{

// Utility class for pattern matching std::variant instances with std::visit
template <typename... Types> struct Overloaded : Types...
{
    using Types::operator()...;
};

// Deduction guide allows inline instantiation of Overloaded instances (not needed since c++20)
template <typename... Types> Overloaded(Types...) -> Overloaded<Types...>;

} // namespace Powder::Util

#endif // OVERLOADED
