module;

#include <Equinox/Macros.hpp>

export module Equinox.Random;

import Eqx.Stdm;
import Equinox.Misc;

namespace eqx
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    auto rd = stdm::random_device{};
    auto eng = stdm::mt19937_64{rd()};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
}

export namespace eqx
{
    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept;

    [[nodiscard]] inline unsigned int flipCoin() noexcept;

    [[nodiscard]] inline unsigned int rollDice(unsigned int sides) noexcept;

    [[nodiscard]] constexpr unsigned int generateSeed(
        const stdm::string_view timeMacro = "10:10:10"sv) noexcept;
}

// Implementations

export namespace eqx
{
    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept
    {
        eqx::ENSURE_HARD(lb <= ub, "Upper Bound Less Than Lower Bound!!!"sv);
        return stdm::uniform_int_distribution<T>{lb, ub}(eng);
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept
    {
        eqx::ENSURE_HARD(lb < ub, "Upper Bound Less Than Lower Bound!!!"sv);
        eqx::ENSURE_HARD(ub < stdm::numeric_limits<T>::max(),
            "Upper Bound Too Large!!!"sv);
        return stdm::uniform_real_distribution<T>{
            lb, stdm::nextafter(ub, stdm::numeric_limits<T>::max())}(eng);
    }

    [[nodiscard]] inline unsigned int flipCoin() noexcept
    {
        return randomNumber(0U, 1U);
    }

    [[nodiscard]] inline unsigned int rollDice(unsigned int sides) noexcept
    {
        eqx::ENSURE_HARD(sides >= 3, "Too Few Sides!!!"sv);
        return randomNumber(1U, sides);
    }


    [[nodiscard]] constexpr unsigned int generateSeed(
        const stdm::string_view timeMacro) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return static_cast<unsigned int>(timeMacro[0]) +
                static_cast<unsigned int>(timeMacro[1]) +
                static_cast<unsigned int>(timeMacro[2]) +
                static_cast<unsigned int>(timeMacro[3]) +
                static_cast<unsigned int>(timeMacro[4]) +
                static_cast<unsigned int>(timeMacro[5]) +
                static_cast<unsigned int>(timeMacro[6]) +
                static_cast<unsigned int>(timeMacro[7]);
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            return static_cast<unsigned int>(rd());
        }
    }
}