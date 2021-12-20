#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>
#include <tuple>


using color = std::tuple<int, int, int>;

const color kBlack{0, 0, 0};

auto mandelbrot_pixel(float x, float y, float xdim, float ydim, int max_iter)
    -> color {
    std::complex<float> c{x, y};
    c *= 2.4f / ydim;
    c -= std::complex<float>(1.2f * xdim / ydim + 0.5f, 1.2f);
    std::complex<float> z = c;
    int iter = 0;
    for (; iter < max_iter && std::norm(z) <= 4.0f; iter++) {
        z = z * z + c;
    }
    if (iter == max_iter) {
        return kBlack;
    }
    const int ci = 512 * iter / max_iter;
    return iter < max_iter / 2 ? color{ci, 0, 0}
                               : color{255, ci - 255, ci - 255};
}

auto main() -> int {

    const int image_width = 256;
    const int image_height = 256;

    std::ofstream out_file("output.ppm");

    // Render

    out_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto [ir, ig, ib] =
                mandelbrot_pixel(j, i, image_width, image_height, 30);

            out_file << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
