#include <boost/test/unit_test.hpp>
#include <k52/common/random.h>

using ::k52::common::Random;

BOOST_AUTO_TEST_SUITE(random_tests);

BOOST_AUTO_TEST_SUITE(validate_probability);

BOOST_AUTO_TEST_CASE(validation_fail)
{
    BOOST_REQUIRE_THROW( Random::ValidateProbability(-12.34) , std::invalid_argument);
    BOOST_REQUIRE_THROW( Random::ValidateProbability(-0.001) , std::invalid_argument);
    BOOST_REQUIRE_THROW( Random::ValidateProbability(1.001) , std::invalid_argument);
    BOOST_REQUIRE_THROW( Random::ValidateProbability(4.56) , std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(validation_pass)
{
    BOOST_REQUIRE_NO_THROW( Random::ValidateProbability(0) );
    BOOST_REQUIRE_NO_THROW( Random::ValidateProbability(0.1234) );
    BOOST_REQUIRE_NO_THROW( Random::ValidateProbability(1) );
}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();