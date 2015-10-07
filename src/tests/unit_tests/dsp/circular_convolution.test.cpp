#include <boost/test/unit_test.hpp>
#include <k52/dsp/transform/circular_convolution.h>

#include  <k52/common/constants.h>

using k52::common::Constants;
using k52::dsp::CircularConvolution;

struct CircularConvolutionTestFixture
{
    CircularConvolution convolution;
};

BOOST_FIXTURE_TEST_SUITE(circular_convolution_tests, CircularConvolutionTestFixture);

BOOST_AUTO_TEST_CASE(not_equal_size)
{
    //Prepare
    std::vector< std::complex <double >> a(13);
    std::vector< std::complex <double >> b(15);

    //Test
    //Check
    BOOST_REQUIRE_THROW(convolution.EvaluateConvolution(a, b), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(zero)
{
    //Prepare
    size_t N = 17;

    std::vector< std::complex <double >> a(N);
    std::vector< std::complex <double >> b(N);

    //Test
    std::vector< std::complex <double >> result = convolution.EvaluateConvolution(a, b);

    //Check
    BOOST_REQUIRE(result.size() == N);

    for (size_t n = 0; n < N; ++n)
    {
        BOOST_CHECK_SMALL(result[n].real(), Constants::Eps);
        BOOST_CHECK_SMALL(result[n].imag(), Constants::Eps);
    }
}

BOOST_AUTO_TEST_CASE(impulse)
{
    //Prepare
    size_t N = 29;

    size_t n_a = 2;
    size_t n_b = 7;

    std::vector< std::complex <double >> a(N);
    a[n_a] = 1;

    std::vector< std::complex <double >> b(N);
    b[n_b] = 1;

    //Test
    std::vector< std::complex <double >> result = convolution.EvaluateConvolution(a, b);

    //Check
    BOOST_REQUIRE(result.size() == N);

    for (size_t n = 0; n < N; ++n)
    {
        bool is_impulse_index = (n_b + n_a) == n;
        BOOST_CHECK_SMALL(result[n].real() - (is_impulse_index ? 1 : 0), Constants::Eps);
        BOOST_CHECK_SMALL(result[n].imag(), Constants::Eps);
    }
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    //Prepare
    size_t N = 136;
    size_t k0 = 17;

    std::vector< std::complex <double >> complex_harmonic(N);
    std::vector< std::complex <double >> b(N);

    for (size_t n = 0; n < N; ++n)
    {
        complex_harmonic[n] = exp( 2 * Constants::Pi * Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
        b[n] = n;
    }

    //Test
    std::vector< std::complex <double >> result = convolution.EvaluateConvolution(complex_harmonic, b);

    //Check
    BOOST_REQUIRE(result.size() == N);

    std::complex <double> eigen_value = 0;
    for (size_t n = 0; n < N; ++n)
    {
        //Fourier transform is eigenvalue for complex harmonic (eigenvector)
        eigen_value += b[n] * exp(  -2 * Constants::Pi * Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    for (size_t n = 0; n < N; ++n)
    {
        std::complex <double> out = eigen_value * complex_harmonic[n];
        BOOST_CHECK_SMALL(result[n].real() - out.real(), Constants::Eps);
        BOOST_CHECK_SMALL(result[n].imag() - out.imag(), Constants::Eps);
    }
}

BOOST_AUTO_TEST_SUITE_END();