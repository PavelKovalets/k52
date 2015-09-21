#include <boost/test/unit_test.hpp>
#include <k52/dsp/fourier/fourier_transform.h>
#include <cmath>

using k52::dsp::FourierTransform;

//TODO to constants
double eps = 1e-10;
double pi = 2 * asin(1);

BOOST_AUTO_TEST_CASE(zero)
{
    //Prepare
    FourierTransform ft;

    size_t N = 11;

    std::vector< std::complex <double >> samples(N);

    //Test
    std::vector< std::complex <double >> result = ft.Transform(samples);

    //Check
    BOOST_REQUIRE(result.size() == N);

    for (int k = 0; k < N; ++k)
    {
        BOOST_REQUIRE_CLOSE(result[k].real(), 0, eps);
        BOOST_REQUIRE_CLOSE(result[k].imag(), 0, eps);
    }
}

BOOST_AUTO_TEST_CASE(impulse)
{
    //Prepare
    FourierTransform ft;

    size_t N = 11;
    size_t n0 = 2;

    //TODO to constants
    std::complex< double > i;
    i = -1;
    i = sqrt(i);

    std::vector< std::complex <double >> samples(N);
    samples[n0] = 1;

    //Test
    std::vector< std::complex <double >> result = ft.Transform(samples);

    //Check
    BOOST_REQUIRE(result.size() == N);

    for (int k = 0; k < N; ++k)
    {
        std::complex <double > w = exp( -2 * pi * i * (double)k * (double)n0 / (double)N);

        BOOST_REQUIRE_CLOSE(result[k].real(), w.real(), eps);
        BOOST_REQUIRE_CLOSE(result[k].imag(), w.imag(), eps);
    }
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    //Prepare
    FourierTransform ft;

    size_t N = 11;
    size_t k0 = 5;

    //TODO to constants
    std::complex< double > i;
    i = -1;
    i = sqrt(i);

    std::vector< std::complex <double >> samples(N);

    for (int n = 0; n < N; ++n)
    {
        samples[n] = exp( -2 * pi * i * (double)k0 * (double)n / (double)N);
    }

    //Test
    std::vector< std::complex <double >> result = ft.Transform(samples);

    //Check
    BOOST_REQUIRE(result.size() == N);

    for (int k = 0; k < N; ++k)
    {
        BOOST_REQUIRE_CLOSE(result[k].real(), k == k0 ? 1 : 0, eps);
        BOOST_REQUIRE_CLOSE(result[k].imag(), 0, eps);
    }
}