#include <boost/test/unit_test.hpp>

#include <k52/dsp/transform/wavelet/linear_scale.h>
#include <k52/dsp/transform/wavelet/logarithmic_scale.h>
#include <k52/common/constants.h>

using ::k52::common::Constants;
using ::k52::dsp::LinearScale;
using ::k52::dsp::LogarithmicScale;
using ::std::vector;
using ::std::invalid_argument;

BOOST_AUTO_TEST_SUITE(scale_tests);

BOOST_AUTO_TEST_SUITE(linear);

BOOST_AUTO_TEST_CASE(min_scale_negative)
{
    BOOST_REQUIRE_THROW(LinearScale(-0.1, 10, 7), invalid_argument);
}

BOOST_AUTO_TEST_CASE(min_scale_zero)
{
    BOOST_REQUIRE_THROW(LinearScale(0, 10, 7), invalid_argument);
}

BOOST_AUTO_TEST_CASE(max_scale_negative)
{
    BOOST_REQUIRE_THROW(LinearScale(0.1, -10, 7), invalid_argument);
}

BOOST_AUTO_TEST_CASE(max_scale_zero)
{
    BOOST_REQUIRE_THROW(LinearScale(0.1, 0, 7), invalid_argument);
}

BOOST_AUTO_TEST_CASE(min_greater_than_max)
{
    BOOST_REQUIRE_THROW(LinearScale(4, 2, 7), invalid_argument);
}

BOOST_AUTO_TEST_CASE(count_zero)
{
    BOOST_REQUIRE_THROW(LinearScale(1, 2, 0), invalid_argument);
}

BOOST_AUTO_TEST_CASE(count_less_than_two)
{
    BOOST_REQUIRE_THROW(LinearScale(1, 2, 1), invalid_argument);
}

BOOST_AUTO_TEST_CASE(size)
{
    //Prepare
    LinearScale linear_scale(0.1, 10, 7);

    //Test
    vector< double > scales = linear_scale.GetScales();

    //Check
    BOOST_REQUIRE_EQUAL(scales.size(), 7);
}

BOOST_AUTO_TEST_CASE(scale_values)
{
    //Prepare
    LinearScale linear_scale(0.3, 12, 5);

    //Test
    vector< double > scales = linear_scale.GetScales();

    //Check
    BOOST_CHECK_SMALL(scales[0] - 0.3, Constants::Eps);
    BOOST_CHECK_SMALL(scales[1] - 3.225, Constants::Eps);
    BOOST_CHECK_SMALL(scales[2] - 6.15, Constants::Eps);
    BOOST_CHECK_SMALL(scales[3] - 9.075, Constants::Eps);
    BOOST_CHECK_SMALL(scales[4] - 12, Constants::Eps);
}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(logarithmic);

BOOST_AUTO_TEST_CASE(min_greater_than_max)
{
    BOOST_REQUIRE_THROW(LogarithmicScale logarithmic_scale(100, -100), invalid_argument);
}

BOOST_AUTO_TEST_CASE(min_equal_max)
{
    BOOST_REQUIRE_THROW(LogarithmicScale logarithmic_scale(7, 7), invalid_argument);
}

BOOST_AUTO_TEST_CASE(size)
{
    //Prepare
    LogarithmicScale logarithmic_scale(-10, 10);

    //Test
    vector< double > scales = logarithmic_scale.GetScales();

    //Check
    BOOST_REQUIRE_EQUAL(scales.size(), 21);
}

BOOST_AUTO_TEST_CASE(scale_values)
{
    //Prepare
    LogarithmicScale logarithmic_scale(-2, 3);

    //Test
    vector< double > scales = logarithmic_scale.GetScales();

    //Check
    BOOST_CHECK_SMALL(scales[0] - 0.25, Constants::Eps);
    BOOST_CHECK_SMALL(scales[1] - 0.5, Constants::Eps);
    BOOST_CHECK_SMALL(scales[2] - 1, Constants::Eps);
    BOOST_CHECK_SMALL(scales[3] - 2, Constants::Eps);
    BOOST_CHECK_SMALL(scales[4] - 4, Constants::Eps);
    BOOST_CHECK_SMALL(scales[5] - 8, Constants::Eps);

}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();