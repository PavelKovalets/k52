#include <boost/test/unit_test.hpp>
#include <k52/dsp/transform/circular_convolution.h>
#include <k52/dsp/transform/fourier_transform.h>
#include <k52/dsp/transform/fourier_based_circular_convolution.h>

#include  <k52/common/constants.h>

#include "../boost_test_tools_extensions.h"

using k52::common::Constants;
using k52::dsp::CircularConvolution;
using k52::dsp::ICircularConvolution;
using k52::dsp::IFourierTransform;
using k52::dsp::FourierTransform;
using k52::dsp::FourierBasedCircularConvolution;

/**
 * Definition of test methods
 */

void test_not_equal_size(const ICircularConvolution* convolution)
{
    //Prepare
    std::vector< std::complex <double > > a(13);
    std::vector< std::complex <double > > b(15);

    //Test
    //Check
    BOOST_REQUIRE_THROW(convolution->EvaluateConvolution(a, b), std::runtime_error);
}

void test_zero(const ICircularConvolution* convolution)
{
    //Prepare
    size_t N = 17;

    std::vector< std::complex <double > > a(N);
    std::vector< std::complex <double > > b(N);

    //Test
    std::vector< std::complex <double > > result = convolution->EvaluateConvolution(a, b);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t n = 0; n < N; ++n)
    {
        CheckComplexEqual(result[n], 0);
    }
}

void test_simple_impulse(const ICircularConvolution* convolution)
{
    //Prepare
    size_t N = 4;
    std::vector< std::complex <double > > a(N);
    a[0] = 1;
    std::vector< std::complex <double > > b(N);
    b[0] = 1;

    //Test
    std::vector< std::complex <double > > result = convolution->EvaluateConvolution(a, b);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t n = 0; n < N; ++n)
    {
        CheckComplexEqual(result[n], n == 0 ? 1 : 0);
    }
}

void test_impulse(const ICircularConvolution* convolution)
{
    //Prepare
    size_t N = 29;

    size_t n_a = 2;
    size_t n_b = 7;

    std::vector< std::complex <double > > a(N);
    a[n_a] = 1;

    std::vector< std::complex <double > > b(N);
    b[n_b] = 1;

    //Test
    std::vector< std::complex <double > > result = convolution->EvaluateConvolution(a, b);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t n = 0; n < N; ++n)
    {
        bool is_impulse_index = (n_b + n_a) == n;
        CheckComplexEqual(result[n], is_impulse_index ? 1 : 0);
    }
}

void test_constant(const ICircularConvolution* convolution)
{
    //Prepare
    size_t N = 12;

    std::vector< std::complex <double > > a(N, 1);
    std::vector< std::complex <double > > b(N, 1);

    //Test
    std::vector< std::complex <double > > result = convolution->EvaluateConvolution(a, b);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t n = 0; n < N; ++n)
    {
        CheckComplexEqual(result[n], N);
    }
}

void test_complex_harmonic(const ICircularConvolution* convolution)
{
    //Prepare
    size_t N = 136;
    size_t k0 = 17;

    std::vector< std::complex <double > > complex_harmonic(N);
    std::vector< std::complex <double > > b(N);

    for (size_t n = 0; n < N; ++n)
    {
        complex_harmonic[n] = exp( 2 * Constants::Pi * Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
        b[n] = n;
    }

    std::complex <double> eigen_value = 0;
    for (size_t n = 0; n < N; ++n)
    {
        //Fourier transform is eigenvalue for complex harmonic (eigenvector)
        eigen_value += b[n] * exp(  -2 * Constants::Pi * Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    //Test
    std::vector< std::complex <double > > result = convolution->EvaluateConvolution(complex_harmonic, b);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t n = 0; n < N; ++n)
    {
        std::complex <double> out = eigen_value * complex_harmonic[n];
        CheckComplexEqual(result[n], out);
    }
}

/**
 * Actual tests are below
 */


BOOST_AUTO_TEST_SUITE(circular_convolution_tests);


struct CircularConvolutionTestFixture
{
    CircularConvolution convolution;
};

BOOST_FIXTURE_TEST_SUITE(circular_convolution, CircularConvolutionTestFixture);

BOOST_AUTO_TEST_CASE(not_equal_size)
{
    test_not_equal_size(&convolution);
}

BOOST_AUTO_TEST_CASE(zero)
{
    test_zero(&convolution);
}

BOOST_AUTO_TEST_CASE(simple_impulse)
{
    test_simple_impulse(&convolution);
}

BOOST_AUTO_TEST_CASE(impulse)
{
    test_impulse(&convolution);
}

BOOST_AUTO_TEST_CASE(constant)
{
    test_constant(&convolution);
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    test_complex_harmonic(&convolution);
}

BOOST_AUTO_TEST_SUITE_END();



struct FourierBasedCircularConvolutionTestFixture
{
    FourierBasedCircularConvolutionTestFixture() :
            fourierBasedConvolution(IFourierTransform::shared_ptr(new FourierTransform()))
    {
    }
    FourierBasedCircularConvolution fourierBasedConvolution;
};

BOOST_FIXTURE_TEST_SUITE(fourier_based_circular_convolution, FourierBasedCircularConvolutionTestFixture);

BOOST_AUTO_TEST_CASE(not_equal_size)
{
    test_not_equal_size(&fourierBasedConvolution);
}

BOOST_AUTO_TEST_CASE(zero)
{
    test_zero(&fourierBasedConvolution);
}

BOOST_AUTO_TEST_CASE(simple_impulse_fourier)
{
    test_simple_impulse(&fourierBasedConvolution);
}

BOOST_AUTO_TEST_CASE(impulse)
{
    test_impulse(&fourierBasedConvolution);
}

BOOST_AUTO_TEST_CASE(constant)
{
    test_constant(&fourierBasedConvolution);
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    test_complex_harmonic(&fourierBasedConvolution);
}

BOOST_AUTO_TEST_SUITE_END();



BOOST_AUTO_TEST_SUITE_END();
