module;

#include <Equinox/Macros.hpp>

export module Equinox.Math.Trig;

export import :Decl;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;
import Equinox.Math.Modulator;

export namespace eqx
{
    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr
        eqx::Radians<T> degreesToRadians(const eqx::Degrees<T> degrees) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return eqx::Radians<T>{
            degrees.get()
            * (stdm::numbers::pi_v<T> / static_cast<T>(180.0))};
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr
        eqx::Degrees<T> radiansToDegrees(const eqx::Radians<T> radians) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return eqx::Degrees<T>{
            radians.get()
            * (static_cast<T>(180.0) / stdm::numbers::pi_v<T>)};
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sin(const eqx::Radians<T> radians) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            constexpr auto terms = 7;
            constexpr auto taylordeg = (terms * 4) + 1;
            auto result = eqx::c_Zero<T>;

            for (auto i = 1; i < taylordeg; i += 4)
            {
                result -= eqx::pow(radians.get() - stdm::numbers::pi_v<T>,
                    static_cast<T>(i)) / static_cast<T>(eqx::factorial(i));
                result += eqx::pow(radians.get() - stdm::numbers::pi_v<T>,
                    static_cast<T>(i + 2))
                    / static_cast<T>(eqx::factorial(i + 2));
            }

            return result;
        }
        else
        {
            return stdm::sin(radians.get());
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T cos(const eqx::Radians<T> radians) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            return eqx::sin(eqx::Radians<T>{radians.get()
                + (stdm::numbers::pi_v<T> / static_cast<T>(2))});
        }
        else
        {
            return stdm::cos(radians.get());
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T tan(const eqx::Radians<T> radians) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            return eqx::sin(radians) / eqx::cos(radians);
        }
        else
        {
            return stdm::tan(radians.get());
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> asin(const T val) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return eqx::Radians<T>{-eqx::acos(val).get()
                + (stdm::numbers::pi_v<T> / static_cast<T>(2.0))};
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);
            return eqx::Radians<T>{stdm::asin(val)};
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> acos(const T val) noexcept
    {
        using namespace eqx::literals;
        if (stdm::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);

            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return eqx::Radians<T>{eqx::newtonsMethod(
                static_cast<T>(-0.95) * eqx::tan(eqx::Radians<T>{val})
                    + (stdm::numbers::pi_v<T> / static_cast<T>(2.0)),
                14_uz,
                [val](const T x)
                    { return x - ((eqx::cos(eqx::Radians<T>{x}) - val)
                        / -eqx::sin(eqx::Radians<T>{x})); })};
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);
            return eqx::Radians<T>{stdm::acos(val)};
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan(const T val) noexcept
    {
        using namespace eqx::literals;
        if (stdm::is_constant_evaluated())
        {
            const auto comp = static_cast<T>(1.0)
                / eqx::sqrt(static_cast<T>(1.0) + (val * val));

            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return eqx::Radians<T>{eqx::newtonsMethod(
                eqx::acos(comp).get() * eqx::sign(val),
                1_uz,
                [val](const T x)
                    { return x - ((eqx::tan(eqx::Radians<T>{x}) - val)
                        * eqx::cos(eqx::Radians<T>{x})
                        * eqx::cos(eqx::Radians<T>{x})); })};
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            return eqx::Radians<T>{stdm::atan(val)};
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan2(const T x, const T y) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(eqx::hypot(x, y) != eqx::c_Zero<T>);
            return eqx::Radians<T>{
                eqx::acos(x / eqx::hypot(x, y)).get()
                    * static_cast<T>(eqx::sign(y))};
        }
        else
        {
            return eqx::Radians<T>{stdm::atan2(x, y)};
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<eqx::Radians<T>, eqx::Radians<T>> arcsin(
        const T val) noexcept
    {
        auto result = asin(val);
        return stdm::make_pair(result,
            eqx::Radians<T>{stdm::numbers::pi_v<T>
                + (eqx::c_2Pi<T> - result.get())});
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<eqx::Radians<T>, eqx::Radians<T>> arccos(
        const T val) noexcept
    {
        auto result = acos(val);
        return stdm::make_pair(result, eqx::Radians<T>{-result.get()});
    }
}
