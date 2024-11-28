#include "Utils/Noise.hpp"

int Noise::octaves = 4;
float Noise::persistence = 0.5;
float Noise::lacunarity = 2.0;

float Noise::get(float x) {
    return fractalNoise(
        static_cast<int>(x),
        x - static_cast<int>(x)
    );
}

float Noise::get(const vec1& v) {
    return fractalNoise(
        static_cast<int>(v.x),
        v.x - static_cast<int>(v.x)
    );
}


float Noise::get(float x, float y) {
    return fractalNoise(x, y);
}

float Noise::get(const vec2& v) {
    return fractalNoise(v.x, v.y);
}

float Noise::getUniform(float x) {
    return uniformDistribution(get(x));
}

float Noise::getUniform(const vec1& v) {
    return uniformDistribution(get(v));
}

float Noise::getUniform(float x, float y) {
    return uniformDistribution(get(x, y));
}

float Noise::getUniform(const vec2& v) {
    return uniformDistribution(get(v));
}

int Noise::getRange(float x, int start, int end) {
    return std::clamp<float>(
        Noise::getUniform(x),
        start,
        end
    );
}

int Noise::getRange(const vec1& v, int start, int end) {
    return std::clamp<float>(
        Noise::getUniform(v),
        start,
        end
    );
}

int Noise::getRange(float x, float y, int start, int end) {
    return std::clamp<float>(
        Noise::getUniform(x, y),
        start,
        end
    );
}

int Noise::getRange(const vec2& v, int start, int end) {
    return std::clamp<float>(
        Noise::getUniform(v),
        start,
        end
    );
}

float Noise::noise(float x, float y) {
    const double F2 = 0.5 * (sqrt(3.0) - 1.0); // Skew factor
    const double G2 = (3.0 - sqrt(3.0)) / 6.0; // Unskew factor

    // Skew the input space to determine the simplex cell
    double s = (x + y) * F2;
    int i = fastfloor(x + s);
    int j = fastfloor(y + s);

    // Unskew the cell origin back to (x, y) space
    double t = (i + j) * G2;
    double X0 = i - t;
    double Y0 = j - t;

    // The distance from the cell origin
    double x0 = x - X0;
    double y0 = y - Y0;

    // Determine which simplex we are in
    int i1, j1; // Offsets for the second (middle) corner of simplex
    if (x0 > y0) {
        i1 = 1; j1 = 0; // Lower triangle
    }
    else {
        i1 = 0; j1 = 1; // Upper triangle
    }

    // Offsets for the remaining simplex corners
    double x1 = x0 - i1 + G2;
    double y1 = y0 - j1 + G2;
    double x2 = x0 - 1.0 + 2.0 * G2;
    double y2 = y0 - 1.0 + 2.0 * G2;

    // Hash the corners of the simplex
    int ii = i & 255;
    int jj = j & 255;
    int g0 = s_perm[ii + s_perm[jj]] % 12;
    int g1 = s_perm[ii + i1 + s_perm[jj + j1]] % 12;
    int g2 = s_perm[ii + 1 + s_perm[jj + 1]] % 12;

    // Calculate the contribution from each corner
    double t0 = 0.5 - x0 * x0 - y0 * y0;
    double n0 = t0 < 0 ? 0.0 : pow(t0, 4) * dot(s_grad3[g0], x0, y0);

    double t1 = 0.5 - x1 * x1 - y1 * y1;
    double n1 = t1 < 0 ? 0.0 : pow(t1, 4) * dot(s_grad3[g1], x1, y1);

    double t2 = 0.5 - x2 * x2 - y2 * y2;
    double n2 = t2 < 0 ? 0.0 : pow(t2, 4) * dot(s_grad3[g2], x2, y2);

    // Scale the result to return values in the range [-1, 1]
    return 70.0 * (n0 + n1 + n2);
}

float Noise::fractalNoise(float x, float y) {
    float total = 0,
        frequencyInv = 1.0 / pow(2, octaves),
        amplitude = 1;
    for (int i = 0; i < octaves; ++i) {
        frequencyInv *= lacunarity;
        amplitude *= persistence;
        total += noise(x * frequencyInv, y * frequencyInv) * amplitude;
    }
    return total * frequencyInv;

    //for (int i = 0; i < octaves; ++i) {
    //    total += noise(x * frequency, y * frequency) * amplitude;

    //    maxAmplitude += amplitude;
    //    amplitude *= persistence;  // Decrease amplitude
    //    frequency *= lacunarity;   // Increase frequency
    //}

    //// Normalize to range [-1, 1]
    //return total / maxAmplitude;
}

float Noise::uniformDistribution(float value) {
    if (value < -0.729) {
        return 0;
    }
    if (value > 0.751) {
        return 1;
    }
    return ((((1.0616674f * value - 4.779669e-2f) * value - 1.5704816f) * value + 2.3737413e-2f) * value + 1.2176103f) * value + 4.9882874e-1f;
}

int Noise::fastfloor(double x) {
    return x > 0 ? static_cast<int>(x) : static_cast<int>(x) - 1;
}

double Noise::dot(const std::array<int, 2>& g, double x, double y) {
    return g[0] * x + g[1] * y;
}