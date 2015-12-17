#include <boost/test/unit_test.hpp>

#include <boost/thread.hpp>

#include <k52/dsp/transform/fourier_transform.h>
#include <k52/dsp/transform/fast_fourier_transform.h>

#include  <k52/common/constants.h>

#include <cmath>

#include "../boost_test_tools_extensions.h"

using std::vector;
using std::complex;
using std::invalid_argument;
using k52::common::Constants;
using k52::dsp::IFourierTransform;
using k52::dsp::FourierTransform;
using k52::dsp::FastFourierTransform;

/**
 * Definition of test methods
 */

void test_zero(const IFourierTransform* ft)
{
    //Prepare
    size_t N = 11;

    vector< complex <double> > samples(N);

    //Test
    vector< complex <double> > result = ft->Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        CheckComplexEqual(result[k], 0);
    }
}

void test_simple_impulse(const IFourierTransform* ft)
{
    //Prepare
    size_t N = 4;

    vector< complex <double> > samples(N);
    samples[0] = 1;

    //Test
    vector< complex <double> > result = ft->Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        CheckComplexEqual(result[k], 1);
    }
}

void test_impulse(const IFourierTransform* ft)
{
    //Prepare
    size_t N = 11;
    size_t n0 = 2;

    vector< complex <double> > samples(N);
    samples[n0] = 1;

    //Test
    vector< complex <double> > result = ft->Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        complex< double > w = exp( -2 * Constants::Pi * Constants::ImaginaryUnit * (double)k * (double)n0 / (double)N);

        CheckComplexEqual(result[k], w);
    }
}

void test_complex_harmonic(const IFourierTransform* ft)
{
    //Prepare
    size_t N = 128;
    size_t k0 = 5;

    vector< complex <double> > samples(N);

    for (size_t n = 0; n < N; ++n)
    {
        samples[n] = exp( 2 * Constants::Pi * Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    //Test
    vector< complex <double> > result = ft->Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        CheckComplexEqual(result[k], k == k0 ? N : 0);
    }
}

/**
 * Actual tests are below
 */

struct FourierTransformTestFixture
{
    FourierTransform ft;
};

BOOST_AUTO_TEST_SUITE(fourier_transform_tests);

BOOST_FIXTURE_TEST_SUITE(fourier_transform, FourierTransformTestFixture);

BOOST_AUTO_TEST_CASE(zero)
{
    test_zero(&ft);
}

BOOST_AUTO_TEST_CASE(simple_impulse)
{
    test_simple_impulse(&ft);
}


BOOST_AUTO_TEST_CASE(impulse)
{
    test_impulse(&ft);
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    test_complex_harmonic(&ft);
}

BOOST_AUTO_TEST_SUITE_END();



BOOST_AUTO_TEST_SUITE(fft);

BOOST_AUTO_TEST_CASE(zero_size)
{
    BOOST_REQUIRE_THROW(FastFourierTransform fft(0), invalid_argument);
}

BOOST_AUTO_TEST_CASE(not_equal_size)
{
    //Prepare
    FastFourierTransform fft(10);
    vector<complex<double> > data(12);

    //Test
    //Check
    BOOST_REQUIRE_THROW(fft.Transform(data), invalid_argument);
}

BOOST_AUTO_TEST_CASE(zero)
{
    FastFourierTransform fft(11);
    test_zero(&fft);
}

BOOST_AUTO_TEST_CASE(simple_impulse)
{
    FastFourierTransform fft(4);
    test_simple_impulse(&fft);
}

BOOST_AUTO_TEST_CASE(impulse)
{
    FastFourierTransform fft(11);
    test_impulse(&fft);
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    FastFourierTransform fft(128);
    test_complex_harmonic(&fft);
}

// Functional test
// @todo - move it out from unittests
void test_function ()
{
    FastFourierTransform fft(10000000);
    test_complex_harmonic(&fft);
}

BOOST_AUTO_TEST_CASE(multithread_test)
{
    for (int i = 0; i < 10; ++i)
    {
        boost::thread th(test_function);
    }
}


BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();
