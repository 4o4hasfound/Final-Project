#pragma once
#include <array>
#include <utility>
#include <cstddef>

#include "Math/Vector.hpp"

namespace {
    template<typename T>
    constexpr void constexprSwap(T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    constexpr unsigned int constexprRand(unsigned int seed, unsigned int min, unsigned int max) {
        seed = (1664525 * seed + 1013904223) % 0xFFFFFFFF;
        return min + (seed % (max - min + 1));
    }

    template <std::size_t N>
    constexpr std::array<int, N * 2+1> generateRandomSequence(unsigned int seed) {
        std::array<int, N> sequence = {};
        for (std::size_t i = 0; i < N; ++i) {
            sequence[i] = static_cast<int>(i + 1);
        }

        for (std::size_t i = N - 1; i > 0; --i) {
            unsigned int j = ::constexprRand(seed + i, 0, i);
            ::constexprSwap(sequence[i], sequence[j]);
        }

        std::array<int, N * 2+1> result = {};
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = result[i + 256] = sequence[i];
        }

        return result;
    }
}

class Noise {
public:
	Noise() = delete;

    static float get(float x);
    static float get(const vec1& v);
    static float get(float x, float y);
    static float get(const vec2& v);

    static float getUniform(float x);
    static float getUniform(const vec1& v);
    static float getUniform(float x, float y);
    static float getUniform(const vec2& v);

    static int getRange(float x, int start, int end);
    static int getRange(const vec1& v, int start, int end);
    static int getRange(float x, float y, int start, int end);
    static int getRange(const vec2& v, int start, int end);

    static int octaves;
    static float persistence;
    static float lacunarity;
private:
    inline constexpr static std::array<int, 513> s_perm = ::generateRandomSequence<256>(42);

    inline constexpr static std::array<std::array<int, 2>, 12> s_grad3{ {
         {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
         {1, 0}, {-1, 0}, {1, 0}, {-1, 0},
         {0, 1}, {0, -1}, {0, 1}, {0, -1}
    } };

    static int fastfloor(double x);
    static double dot(const std::array<int, 2>& g, double x, double y);
    static float noise(float x, float y);
    static float fractalNoise(float x, float y);
    static float uniformDistribution(float value);
};