#include <boost/test/unit_test.hpp>
#include <k52/dsp/transform/fourier_transform.h>

#include  <k52/common/constants.h>

#include <cmath>

using k52::common::Constants;
using k52::dsp::FourierTransform;

struct FourierTransformTestFixture
{
    FourierTransform ft;
};

BOOST_FIXTURE_TEST_SUITE(fourier_transform_tests, FourierTransformTestFixture);

BOOST_AUTO_TEST_CASE(zero)
{
    //Prepare
    size_t N = 11;

    std::vector< std::complex <double >> samples(N);

    //Test
    std::vector< std::complex <double >> result = ft.Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        BOOST_CHECK_SMALL(result[k].real(), Constants::Eps);
        BOOST_CHECK_SMALL(result[k].imag(), Constants::Eps);
    }
}

BOOST_AUTO_TEST_CASE(impulse)
{
    //Prepare
    size_t N = 11;
    size_t n0 = 2;

    std::vector< std::complex <double >> samples(N);
    samples[n0] = 1;

    //Test
    std::vector< std::complex <double >> result = ft.Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        std::complex <double > w = exp( -2 * Constants::Pi * Constants::ImaginaryUnit * (double)k * (double)n0 / (double)N);

        BOOST_CHECK_SMALL(result[k].real() - w.real(), Constants::Eps);
        BOOST_CHECK_SMALL(result[k].imag() - w.imag(), Constants::Eps);
    }
}

BOOST_AUTO_TEST_CASE(complex_harmonic)
{
    //Prepare
    size_t N = 128;
    size_t k0 = 5;

    std::vector< std::complex <double >> samples(N);

    for (size_t n = 0; n < N; ++n)
    {
        samples[n] = exp( 2 * Constants::Pi * Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    //Test
    std::vector< std::complex <double >> result = ft.Transform(samples);

    //Check
    BOOST_REQUIRE_EQUAL(result.size(), N);

    for (size_t k = 0; k < N; ++k)
    {
        BOOST_CHECK_SMALL(result[k].real() - (k == k0 ? N : 0), Constants::Eps);
        BOOST_CHECK_SMALL(result[k].imag(), Constants::Eps);
    }
}

BOOST_AUTO_TEST_SUITE_END();