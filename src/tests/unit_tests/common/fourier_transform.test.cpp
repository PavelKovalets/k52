#include <boost/test/unit_test.hpp>
#include <k52/dsp/fourier/fourier_transform.h>

using k52::dsp::FourierTransform;

BOOST_AUTO_TEST_CASE(zero)
{
    FourierTransform ft;

    size_t N = 11;

    std::vector< std::complex <double >> samples(N);

    std::vector< std::complex <double >> result = ft.Transform(samples);

    BOOST_REQUIRE(result.size() == N);

    for (int i = 0; i < N; ++i)
    {
        BOOST_REQUIRE_CLOSE(result[i].real(), 0, 1e-14);
        BOOST_REQUIRE_CLOSE(result[i].imag(), 0, 1e-14);
    }
}