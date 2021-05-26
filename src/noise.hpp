#ifndef NOISE_HPP
#define NOISE_HPP

#include <algorithm>
#include <array>
#include <iostream>
#include <math.h>
#include <random>

class Noise {
public:
  double noise(double x, double y, double z) {
    int X = static_cast<int>(floor(x)) & 255, // FIND UNIT CUBE THAT
        Y = static_cast<int>(floor(y)) & 255, // CONTAINS POINT.
        Z = static_cast<int>(floor(z)) & 255;
    x -= floor(x); // FIND RELATIVE X,Y,Z
    y -= floor(y); // OF POINT IN CUBE.
    z -= floor(z);
    double u = fade(x), // COMPUTE FADE CURVES
        v = fade(y),    // FOR EACH OF X,Y,Z.
        w = fade(z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z, // HASH COORDINATES OF
        B = p[X + 1] + Y, BA = p[B] + Z,
        BB = p[B + 1] + Z; // THE 8 CUBE CORNERS,

    return lerp(w,
                lerp(v,
                     lerp(u, grad(p[AA], x, y, z),        // AND ADD
                          grad(p[BA], x - 1, y, z)),      // BLENDED
                     lerp(u, grad(p[AB], x, y - 1, z),    // RESULTS
                          grad(p[BB], x - 1, y - 1, z))), // FROM  8
                lerp(v,
                     lerp(u, grad(p[AA + 1], x, y, z - 1),   // CORNERS
                          grad(p[BA + 1], x - 1, y, z - 1)), // OF CUBE
                     lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                          grad(p[BB + 1], x - 1, y - 1, z - 1))));
  }
  double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); };
  double lerp(double t, double a, double b) { return a + t * (b - a); }
  double grad(int hash, double x, double y, double z) {
    int h = hash & 15;        // CONVERT LO 4 BITS OF HASH CODE
    double u = h < 8 ? x : y, // INTO 12 GRADIENT DIRECTIONS.
        v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }

  Noise(unsigned int seed) {
    for (int i = 0; i < 256; ++i) {
      p[i] = i;
    }

    std::shuffle(p.begin(), p.begin() + 256, std::default_random_engine(seed));

    for (int i = 0; i < 256; ++i) {
      p[i + 256] = p[i];
    }
  }

private:
  std::array<int, 512> p;
};
#endif
