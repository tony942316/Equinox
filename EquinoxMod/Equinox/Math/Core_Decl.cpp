export module Equinox.Math.Core:Decl;

import Eqx.Stdm;

export namespace eqx
{
    template <typename T>
        requires requires() { static_cast<T>(0); }
    inline constexpr auto c_Zero = static_cast<T>(0);

    template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_FPT = static_cast<T>(0.00001);

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T abs(const T val) noexcept;

    template <typename T>
        requires requires(const T& x, const T& y)
            { x == y; }
            && (!stdm::floating_point<T>)
    [[nodiscard]] constexpr bool equals(const T& x, const T& y) noexcept;

    template <typename T>
    [[nodiscard]] constexpr bool equals(const stdm::pair<T, T>& x,
        const stdm::pair<T, T>& y) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y,
        const T error) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isPositive(const T val) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isNegative(const T val) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
            && (!stdm::unsigned_integral<T>)
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept;

    template <typename T>
        requires stdm::unsigned_integral<T>
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T trunc(const T x) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T floor(const T x) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T ceil(const T x) noexcept;

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr double factorial(const T val) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T pow(const T val, const T deg) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T fmod(const T val, const T mod) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sqrt(const T val) noexcept;
}