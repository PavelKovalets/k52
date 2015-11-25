#include <boost/test/unit_test.hpp>
#include <k52/common/helpers.h>
#include <k52/common/constants.h>

#include "../boost_test_tools_extensions.h"

using ::k52::common::Helpers;
using ::k52::common::Constants;
using ::std::complex;
using ::std::vector;

BOOST_AUTO_TEST_SUITE(helpers_tests);

BOOST_AUTO_TEST_SUITE(conjugate_tests);

BOOST_AUTO_TEST_CASE(size)
{
    //Prepare
    vector< complex < double> > sequence(4);

    //Test
    vector< complex < double> > conjugate = Helpers::Conjugate(sequence);

    //Check
    BOOST_REQUIRE_EQUAL(sequence.size(), conjugate.size());
}

BOOST_AUTO_TEST_CASE(conjugate)
{
    //Prepare
    vector< complex < double> > sequence;
    sequence.push_back(Constants::ImaginaryUnit);
    sequence.push_back(1);
    sequence.push_back(2. + 3. * Constants::ImaginaryUnit);

    //Test
    vector< complex < double> > conjugate = Helpers::Conjugate(sequence);

    //Check
    CheckComplexEqual(conjugate[0], -Constants::ImaginaryUnit);
    CheckComplexEqual(conjugate[1], 1);
    CheckComplexEqual(conjugate[2], 2. - 3. * Constants::ImaginaryUnit);
}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();