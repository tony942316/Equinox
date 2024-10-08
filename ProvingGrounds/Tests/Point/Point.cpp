export module Eqx.Tests.Point;

import <Eqx/std.hpp>;

import :Core;

import Eqx.Lib.Misc;
import Eqx.Lib.Point;
import Eqx.UnitTester;

using namespace eqx::literals;

namespace test::point
{
    export inline UnitTester all() noexcept;
    inline void toString(UnitTester& tester) noexcept;
}

// Implementations

namespace test::point
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        toString(tester);
        return tester;
    }

    inline void toString(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto expected_actual =
            std::vector<std::pair<std::string, std::string>>{
                { "(0, 0)"s, eqx::toString(eqx::Point<int>{0, 0}) },
                { "(0.000000, 0.000000)"s,
                    eqx::toString(eqx::Point<float>{0.0F, 0.0F}) },
                { "(0.000000, 0.000000)"s,
                    eqx::toString(eqx::Point<double>{0.0, 0.0}) },
                { "(0.000000, 0.000000)"s,
                    eqx::toString(eqx::Point<long double>{0.0L, 0.0L}) },
                { "(1.500000, 3.900000)"s,
                    eqx::toString(eqx::Point<double>{1.5, 3.9}) },
                { "(1.000000, 1.000000)"s,
                    eqx::toString(eqx::Point<double>{1.0, 1.0}) },
                { "(-10.000000, 10.000000)"s,
                    eqx::toString(eqx::Point<double>{-10.0, 10.0}) },
                { "(1.234000, 7.654000)"s,
                    eqx::toString(eqx::Point<double>{1.234, 7.654}) }
            };

        tester.addTests(expected_actual);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
}
