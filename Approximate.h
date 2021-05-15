#pragma once

#include <cmath>

template <class T>
class Approximate
{
public:
    static constexpr T epsilon = static_cast<T>(0.001);

	static inline bool equal(T a, T b) noexcept {
		return (std::abs(a - b) <= epsilon);
	}

	static inline bool greater(T a, T b) noexcept {
		return (a - b > epsilon);
	}
	static inline bool less(T a, T b) noexcept {
		return (b - a > epsilon);
	}

	static inline bool greaterEqual(T a, T b) noexcept {
		return (a - b >= -epsilon);
	}
	static inline bool lessEqual(T a, T b) noexcept {
		return (b - a >= -epsilon);
	}
};