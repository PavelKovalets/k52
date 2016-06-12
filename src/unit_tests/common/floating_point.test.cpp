#include <boost/test/unit_test.hpp>
#include <k52/common/floating_point.h>

using ::k52::common::FloatingPoint;

BOOST_AUTO_TEST_SUITE(floating_point_tests);

BOOST_AUTO_TEST_CASE(are_equal_true)
{
    //Prepare
    double x = -123.000000000004;
    double y = -123.000000000001;

    //Test
    bool result = FloatingPoint::AreEqual(x, y);

    //Check
    BOOST_REQUIRE_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(are_equal_false)
{
    //Prepare
    double x = -123.0000004;
    double y = -123.0000001;

    //Test
    bool result = FloatingPoint::AreEqual(x, y);

    //Check
    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(vectors_are_equal_true)
{
    //Prepare
    std::vector<double> x(1, -123.000000000004);
    std::vector<double> y(1, -123.000000000001);

    //Test
    bool result = FloatingPoint::AreEqual(x, y);

    //Check
    BOOST_REQUIRE_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(vectors_are_equal_false)
{
    //Prepare
    std::vector<double> x(1, -123.0000004);
    std::vector<double> y(1, -123.0000001);

    //Test
    bool result = FloatingPoint::AreEqual(x, y);

    //Check
    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(vectors_are_equal_size_false)
{
    //Prepare
    std::vector<double> x(1, -123.000000000004);
    std::vector<double> y(2, -123.000000000001);

    //Test
    bool result = FloatingPoint::AreEqual(x, y);

    //Check
    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(is_zero_true)
{
    //Prepare
    double x = -0.000000000001;

    //Test
    bool result = FloatingPoint::IsZero(x);

    //Check
    BOOST_REQUIRE_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(is_zero_false)
{
    //Prepare
    double x = -0.000001;
    //Test
    bool result = FloatingPoint::IsZero(x);

    //Check
    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_SUITE_END();
