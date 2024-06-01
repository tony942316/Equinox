module Eqx.Tests.Math:Range;

import Eqx.Stdm;
import Equinox.Math.Range;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(eqx::median(stdm::vector<int>{ 1 }) == 1.0);
static_assert(eqx::median(stdm::vector<unsigned int>{ 1U }) == 1.0);
static_assert(eqx::median(stdm::vector<long>{ 1L }) == 1.0);
static_assert(eqx::median(stdm::vector<unsigned long>{ 1UL }) == 1.0);
static_assert(eqx::median(stdm::vector<long long>{ 1LL }) == 1.0);
static_assert(eqx::median(stdm::vector<unsigned long long>{ 1ULL }) == 1.0);
static_assert(eqx::median(stdm::vector<float>{ 1.0F }) == 1.0);
static_assert(eqx::median(stdm::vector<double>{ 1.0 }) == 1.0);
static_assert(eqx::median(stdm::vector<long double>{ 1.0L }) == 1.0);
static_assert(eqx::median(stdm::vector<int>{ 0, 1 }) == 0.5);
static_assert(eqx::median(stdm::vector<int>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::median(stdm::vector<int>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::median(stdm::vector<int>{ 0, 1, 2, 3, 4 }) == 2.0);
static_assert(eqx::median(stdm::array<int, 1>{ 1 }) == 1.0);
static_assert(eqx::median(stdm::array<unsigned int, 1>{ 1U }) == 1.0);
static_assert(eqx::median(stdm::array<long, 1>{ 1L }) == 1.0);
static_assert(eqx::median(stdm::array<unsigned long, 1>{ 1UL }) == 1.0);
static_assert(eqx::median(stdm::array<long long, 1>{ 1LL }) == 1.0);
static_assert(eqx::median(stdm::array<unsigned long long, 1>{ 1ULL }) == 1.0);
static_assert(eqx::median(stdm::array<float, 1>{ 1.0F }) == 1.0);
static_assert(eqx::median(stdm::array<double, 1>{ 1.0 }) == 1.0);
static_assert(eqx::median(stdm::array<long double, 1>{ 1.0L }) == 1.0);
static_assert(eqx::median(stdm::array<int, 2>{ 0, 1 }) == 0.5);
static_assert(eqx::median(stdm::array<int, 3>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::median(stdm::array<int, 4>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::median(stdm::array<int, 5>{ 0, 1, 2, 3, 4 }) == 2.0);

static_assert(eqx::average(stdm::vector<int>{ 1 }) == 1.0);
static_assert(eqx::average(stdm::vector<unsigned int>{ 1U }) == 1.0);
static_assert(eqx::average(stdm::vector<long>{ 1L }) == 1.0);
static_assert(eqx::average(stdm::vector<unsigned long>{ 1UL }) == 1.0);
static_assert(eqx::average(stdm::vector<long long>{ 1LL }) == 1.0);
static_assert(eqx::average(stdm::vector<unsigned long long>{ 1ULL }) == 1.0);
static_assert(eqx::average(stdm::vector<float>{ 1.0F }) == 1.0);
static_assert(eqx::average(stdm::vector<double>{ 1.0 }) == 1.0);
static_assert(eqx::average(stdm::vector<long double>{ 1.0L }) == 1.0);
static_assert(eqx::average(stdm::vector<int>{ 0, 1 }) == 0.5);
static_assert(eqx::average(stdm::vector<int>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::average(stdm::vector<int>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::average(stdm::vector<int>{ 0, 1, 2, 3, 4 }) == 2.0);
static_assert(eqx::average(stdm::array<int, 1>{ 1 }) == 1.0);
static_assert(eqx::average(stdm::array<unsigned int, 1>{ 1U }) == 1.0);
static_assert(eqx::average(stdm::array<long, 1>{ 1L }) == 1.0);
static_assert(eqx::average(stdm::array<unsigned long, 1>{ 1UL }) == 1.0);
static_assert(eqx::average(stdm::array<long long, 1>{ 1LL }) == 1.0);
static_assert(eqx::average(stdm::array<unsigned long long, 1>{ 1ULL }) == 1.0);
static_assert(eqx::average(stdm::array<float, 1>{ 1.0F }) == 1.0);
static_assert(eqx::average(stdm::array<double, 1>{ 1.0 }) == 1.0);
static_assert(eqx::average(stdm::array<long double, 1>{ 1.0L }) == 1.0);
static_assert(eqx::average(stdm::array<int, 2>{ 0, 1 }) == 0.5);
static_assert(eqx::average(stdm::array<int, 3>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::average(stdm::array<int, 4>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::average(stdm::array<int, 5>{ 0, 1, 2, 3, 4 }) == 2.0);
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
