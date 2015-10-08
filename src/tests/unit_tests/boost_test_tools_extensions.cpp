#include "boost_test_tools_extensions.h"

#include <boost/test/unit_test.hpp>
#include <k52/common/constants.h>

void CheckComplexEqual(std::complex< double > a, std::complex< double > b)
{
    BOOST_CHECK_SMALL(a.real() - b.real(), ::k52::common::Constants::Eps);
    BOOST_CHECK_SMALL(a.imag() - b.imag(), ::k52::common::Constants::Eps);
}