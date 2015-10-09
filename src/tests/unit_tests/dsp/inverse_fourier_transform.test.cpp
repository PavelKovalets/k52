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

BOOST_AUTO_TEST_CASE(multiple_inverse)
{
    //Prepare
    std::list< std::vector< std::complex <double > > > samples_list;
    std::list< std::vector< std::complex <double > > > transformed_samples_list;

    //Zeros
    samples_list.push_back(std::vector< std::complex <double >> (10));
    //Impulse
    std::vector< std::complex <double >> impulse_samples(11);
    impulse_samples[2] = 1;
    samples_list.push_back(impulse_samples);
    //Ladder
    std::vector< std::complex <double >> ladder_samples(123);
    for (size_t n = 0; n < ladder_samples.size(); ++n)
    {
        ladder_samples[n] = exp( 2 * Constants::Pi * Constants::ImaginaryUnit * (double)n);
    }
    samples_list.push_back(ladder_samples);

    //Test
    for (std::list< std::vector< std::complex <double > > >::const_iterator it = samples_list.begin();
         it != samples_list.end();
         ++it)
    {
        transformed_samples_list.push_back(ift.Transform(ft.Transform(*it)));
    }

    //Check
    for (std::list< std::vector< std::complex <double > > >::const_iterator
                 it_samples = samples_list.begin(),
                 it_transformed = samples_list.begin();
         it_samples != samples_list.end();
         ++it_samples, ++it_transformed
            )
    {
        BOOST_REQUIRE_EQUAL(it_samples->size(), it_transformed->size());

        for (size_t n = 0; n < it_samples->size(); ++n)
        {
            CheckComplexEqual((*it_samples)[n], (*it_transformed)[n]);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END();
