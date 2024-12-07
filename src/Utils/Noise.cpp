#include "Utils/Noise.hpp"

float Noise::noise(float x, float y) {
    constexpr double sqrt3 = 1.73205080757;
    constexpr double F2 = 0.5 * (sqrt3 - 1.0); // Skew factor
    constexpr double G2 = (3.0 - sqrt3) / 6.0; // Unskew factor

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
    int g0 = s_gradient[ii + s_perm[jj]];
    int g1 = s_gradient[ii + i1 + s_perm[jj + j1]];
    int g2 = s_gradient[ii + 1 + s_perm[jj + 1]];

    // Calculate the contribution from each corner
    double t0 = 0.5 - x0 * x0 - y0 * y0;
    double n0 = t0 < 0 ? 0.0 : t0*t0*t0*t0 * dot(s_grad3[g0], x0, y0);

    double t1 = 0.5 - x1 * x1 - y1 * y1;
    double n1 = t1 < 0 ? 0.0 : t1*t1*t1*t1 * dot(s_grad3[g1], x1, y1);

    double t2 = 0.5 - x2 * x2 - y2 * y2;
    double n2 = t2 < 0 ? 0.0 : t2*t2*t2*t2 * dot(s_grad3[g2], x2, y2);

    // Scale the result to return values in the range [-1, 1]
    return 70.0 * (n0 + n1 + n2);
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
    return x > 0 ? (int)x : (int)(x - 1);
}

int Noise::fastMod(int x, int ceil) {
    return x >= ceil? x % ceil: x;
}

double Noise::dot(const std::array<int, 2>& g, double x, double y) {
    return g[0] * x + g[1] * y;
}