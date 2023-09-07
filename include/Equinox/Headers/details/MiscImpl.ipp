/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EQUINOX_DETAILS_MISCIMPL_IPP
#define EQUINOX_DETAILS_MISCIMPL_IPP

#include "MiscDecl.hpp"

#ifndef NDEBUG

constexpr void eqx_debugOnly_runtimeAssert(bool expr, std::string_view msg)
    noexcept
{
    eqx::runtimeAssert(expr, msg);
}

#endif // NDEBUG

namespace eqx
{
    [[nodiscard]] inline std::string toString(const char* cstring)
    {
        return std::string(cstring);
    }

    template <typename T>
        requires Stringable<T>
    [[nodiscard]] std::string toString(const T& val)
    {
        return std::to_string(val);
    }

    template <typename T>
        requires StringType<T>
    [[nodiscard]] std::string toString(const T& val)
    {
        return std::string(val);
    }

    template <typename T, typename U>
    [[nodiscard]] std::string toString(const std::pair<T, U>& val)
    {
        return std::string("(") + toString(val.first) + std::string(", ") +
            toString(val.second) + std::string(")");
    }

    template <typename T>
        requires ConstCollection<T>
    [[nodiscard]] std::string toString(const T& val)
    {
        auto result = std::string("");
        result += "{ ";
        std::ranges::for_each(val,
            [&result](const auto& x)
            {
                result += toString(x);
                result += ", ";
            });
        result.pop_back();
        result.pop_back();
        result += " }";
        return result;
    }

    namespace pairPrint
    {
        template <typename T, typename U>
        std::ostream& operator<< (std::ostream& os, std::pair<T, U> p)
        {
            return os << toString(p);
        }
    }

    namespace literals
    {
        consteval std::size_t operator""_size (unsigned long long x) noexcept
        {
            return static_cast<std::size_t>(x);
        }

        consteval short operator""_short (unsigned long long x) noexcept
        {
            return static_cast<short>(x);
        }

        consteval unsigned short operator""_ushort (unsigned long long x)
            noexcept
        {
            return static_cast<unsigned short>(x);
        }

        constexpr unsigned long long operator""_KB (unsigned long long x)
            noexcept
        {
            return x * 1024ULL;
        }
    }

    inline void print(std::string_view msg, std::ostream& out) noexcept
    {
        out.write(msg.data(),
            static_cast<std::streamsize>(std::ranges::size(msg)));
    }

    inline void println(std::string_view msg, std::ostream& out) noexcept
    {
        print(msg, out);
        print("\n", out);
    }

    constexpr void runtimeAssert(bool expr, std::string_view msg) noexcept
    {
        if (!expr)
        {
            // If you got here because of a constexpr evaluation
            // go up the call stack to where this assert was called
            // and ideally there is a message in the msg parameter
            (void)std::fprintf(stderr, "%s", msg.data());
            std::abort();
        }
    }

    template <typename C1, typename C2>
        requires ConstCollection<C1> && ConstCollection<C2>
    [[nodiscard]] auto zip(const C1& x, const C2& y)
    {
        runtimeAssert(std::ranges::size(x) == std::ranges::size(y),
            "eqx::zip std::ranges::size(x) != std::ranges::size(y)!");

        using C1HeldValue =
            std::remove_cvref_t<decltype(*std::ranges::cbegin(x))>;
        using C2HeldValue =
            std::remove_cvref_t<decltype(*std::ranges::cbegin(y))>;

        auto zippedRange =
            std::vector<std::pair<C1HeldValue, C2HeldValue>>();
        zippedRange.reserve(std::ranges::size(x));

        auto xIter = std::ranges::cbegin(x);
        auto yIter = std::ranges::cbegin(y);
        for (; xIter != std::ranges::cend(x); xIter++, yIter++)
        {
            zippedRange.emplace_back(*xIter, *yIter);
        }

        return zippedRange;
    }

    template <typename T, typename... Args>
        requires requires(Args&&... args)
            {  new T(std::forward<Args>(args)...); }
    [[nodiscard]] inline T* newAlloc(Args&&... args) noexcept
    {
        return new T(std::forward<Args>(args)...);
    }

    template <typename T>
        requires requires(T* ptr) { delete ptr; }
    inline void deleteDealloc(T* ptr) noexcept
    {
        delete ptr;
    }
}


#endif // EQUINOX_DETAILS_MISCIMPL_IPP
