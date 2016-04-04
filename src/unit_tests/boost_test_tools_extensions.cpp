#include "boost_test_tools_extensions.h"

#include <boost/test/unit_test.hpp>
#include <k52/common/constants.h>

void CheckComplexEqual(std::complex< double > a, std::complex< double > b)
{
    CheckDoubleEqual(a.real(), b.real());
    CheckDoubleEqual(a.imag(), b.imag());
}

void CheckDoubleEqual(double a, double b)
{
    BOOST_CHECK_SMALL(a - b, ::k52::common::Constants::Eps);
}