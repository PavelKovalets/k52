#include <boost/test/unit_test.hpp>
#include <k52/dsp/transform/inverse_fourier_transform.h>
#include <k52/dsp/transform/fourier_transform.h>

#include  <k52/common/constants.h>

#include <cmath>
#include <list>

#include "../boost_test_tools_extensions.h"

using k52::common::Constants;
using k52::dsp::FourierTransform;
using k52::dsp::IFourierTransform;
using k52::dsp::InverseFourierTransform;

struct InverseFourierTransformTestFixture
{
    InverseFourierTransformTestFixture() :
            ift(IFourierTransform::shared_ptr(new FourierTransform()))
    {}

    InverseFourierTransform ift;
    FourierTransform ft;
};

BOOST_FIXTURE_TEST_SUITE(inverse_fourier_transform_tests, InverseFourierTransformTestFixture);

void test_inverse_fourier_transform(
        const FourierTransform& ft,
        const InverseFourierTransform& ift,
        const std::vector< std::complex <double > >& samples)
{
    //Test
    std::vector< std::complex <double > > result = ift.Transform(ft.Transform(samples));

    //Check
    BOOST_REQUIRE_EQUAL(samples.size(), result.size());

    for (size_t n = 0; n < samples.size(); ++n)
    {
        CheckComplexEqual(samples[n], result[n]);
    }
}

BOOST_AUTO_TEST_CASE(zero)
{
    //Prepare
    std::vector< std::complex <double >> zeros(10);

    test_inverse_fourier_transform(ft, ift, zeros);
}

BOOST_AUTO_TEST_CASE(simple_impulse)
{
    //Prepare
    std::vector< std::complex <double >> impulse_samples(4);
    impulse_samples[0] = 1;

    test_inverse_fourier_transform(ft, ift, impulse_samples);
}

BOOST_AUTO_TEST_CASE(impulse)
{
    //Prepare
    std::vector< std::complex <double >> impulse_samples(11);
    impulse_samples[2] = 1;

    test_inverse_fourier_transform(ft, ift, impulse_samples);
}

BOOST_AUTO_TEST_CASE(ladder)
{
    std::vector< std::complex <double >> ladder_samples(9);
    for (size_t n = 0; n < ladder_samples.size(); ++n)
    {
        ladder_samples[n] = n;
    }
    test_inverse_fourier_transform(ft, ift, ladder_samples);
}

BOOST_AUTO_TEST_CASE(complex)
{
    std::vector< std::complex <double >> complex_samples(14);
    for (size_t n = 0; n < complex_samples.size(); ++n)
    {
        complex_samples[n] = (double)n * Constants::ImaginaryUnit;
    }
    test_inverse_fourier_transform(ft, ift, complex_samples);
}

BOOST_AUTO_TEST_SUITE_END();
