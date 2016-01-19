#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>

#include <k52/common/constants.h>
#include <k52/dsp/transform/i_fourier_transform.h>
#include <k52/dsp/transform/fast_fourier_transform.h>

void complex_harmonic_transform(const k52::dsp::IFourierTransform* ft)
{
    //Prepare
    size_t N = 128;
    size_t k0 = 5;

    std::vector< std::complex <double> > samples(N);

    for (size_t n = 0; n < N; ++n)
    {
        samples[n] = exp( 2 * k52::common::Constants::Pi *
                          k52::common::Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    //Test
    std::vector< std::complex <double> > result = ft->Transform(samples);
}

BOOST_AUTO_TEST_SUITE(fourier_transform_functional_tests);

void test_function ()
{
    k52::dsp::FastFourierTransform fft(10000000);
    complex_harmonic_transform(&fft);
}

BOOST_AUTO_TEST_CASE(multithread_test)
{
    for (int i = 0; i < 10; ++i)
    {
        boost::thread th(test_function);
    }
}

BOOST_AUTO_TEST_SUITE_END();
