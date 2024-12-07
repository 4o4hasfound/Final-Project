#pragma once
#include <array>
#include <utility>
#include <cstddef>

#include "Math/Vector.hpp"

// Some constexpr helper functions
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

    template <std::size_t N>
    constexpr std::array<int, N> generateGradient(std::array<int, N> arr) {
        std::array<int, N> sequence = {};
        for (int i = 0; i < N; ++i) {
            sequence[i] = arr[i] % 12;
        }

        return sequence;
    }
}

class Noise {
public:
	Noise() = delete;

    // Get a noise value that ranges from [-1, 1]
    template<int octaves>
    static float get(float x, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static float get(const vec1& v, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static float get(float x, float y, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static float get(const vec2& v, float persistence = 0.5, float lacunarity = 2.0);

    // Get an uniform noise value that ranges from [0, 1]
    template<int octaves>
    static float getUniform(float x, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static float getUniform(const vec1& v, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static float getUniform(float x, float y, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static float getUniform(const vec2& v, float persistence = 0.5, float lacunarity = 2.0);

    // Get an uniform noise value that ranges from [start, end]
    template<int octaves>
    static int getRange(float x, int start, int end, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static int getRange(const vec1& v, int start, int end, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static int getRange(float x, float y, int start, int end, float persistence = 0.5, float lacunarity = 2.0);
    template<int octaves>
    static int getRange(const vec2& v, int start, int end, float persistence = 0.5, float lacunarity = 2.0);

private:
    inline constexpr static std::array<int, 513> s_perm = ::generateRandomSequence<256>(42);
    inline constexpr static std::array<int, 513> s_gradient = ::generateGradient(s_perm);

    inline constexpr static std::array<std::array<int, 2>, 12> s_grad3{ {
         {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
         {1, 0}, {-1, 0}, {1, 0}, {-1, 0},
         {0, 1}, {0, -1}, {0, 1}, {0, -1}
    } };

    static int fastfloor(double x);
    static int fastMod(int x, int ceil);
    static double dot(const std::array<int, 2>& g, double x, double y);
    static float noise(float x, float y);
    template<int octaves>
    static float fractalNoise(float x, float y, float persistence = 0.5, float lacunarity = 2.0);
    static float uniformDistribution(float value);
};

template<int octaves>
float Noise::fractalNoise(float x, float y, float persistence, float lacunarity) {
    float total = 0,
        frequencyInv = 1.0 / pow(2, octaves),
        amplitude = 1;

    for (int i = 0; i < octaves; ++i) {
        frequencyInv *= lacunarity;
        amplitude *= persistence;
        total += noise(x * frequencyInv, y * frequencyInv) * amplitude;
    }
    return total * frequencyInv;
}


template<int octaves>
float Noise::get(float x, float persistence, float lacunarity) {
    return fractalNoise<octaves>(
        static_cast<int>(x),
        x - static_cast<int>(x),
        persistence, lacunarity
    );
}

template<int octaves>
float Noise::get(const vec1& v, float persistence, float lacunarity) {
    return fractalNoise<octaves>(
        static_cast<int>(v.x),
        v.x - static_cast<int>(v.x),
        persistence, lacunarity
    );
}


template<int octaves>
float Noise::get(float x, float y, float persistence, float lacunarity) {
    return fractalNoise<octaves>(x, y, persistence, lacunarity);
}

template<int octaves>
float Noise::get(const vec2& v, float persistence, float lacunarity) {
    return fractalNoise<octaves>(v.x, v.y, persistence, lacunarity);
}

template<int octaves>
float Noise::getUniform(float x, float persistence, float lacunarity) {
    return uniformDistribution(get<octaves>(x, persistence, lacunarity));
}

template<int octaves>
float Noise::getUniform(const vec1& v, float persistence, float lacunarity) {
    return uniformDistribution(get<octaves>(v, persistence, lacunarity));
}

template<int octaves>
float Noise::getUniform(float x, float y, float persistence, float lacunarity) {
    return uniformDistribution(get<octaves>(x, y, persistence, lacunarity));
}

template<int octaves>
float Noise::getUniform(const vec2& v, float persistence, float lacunarity) {
    return uniformDistribution(get<octaves>(v, persistence, lacunarity));
}

template<int octaves>
int Noise::getRange(float x, int start, int end, float persistence, float lacunarity) {
    return std::clamp<float>(
        Noise::getUniform<octaves>(x, persistence, lacunarity),
        start,
        end
    );
}

template<int octaves>
int Noise::getRange(const vec1& v, int start, int end, float persistence, float lacunarity) {
    return std::clamp<float>(
        Noise::getUniform<octaves>(v, persistence, lacunarity),
        start,
        end
    );
}

template<int octaves>
int Noise::getRange(float x, float y, int start, int end, float persistence, float lacunarity) {
    return std::clamp<float>(
        Noise::getUniform<octaves>(x, y, persistence, lacunarity),
        start,
        end
    );
}

template<int octaves>
int Noise::getRange(const vec2& v, int start, int end, float persistence, float lacunarity) {
    return std::clamp<float>(
        Noise::getUniform<octaves>(v, persistence, lacunarity),
        start,
        end
    );
}