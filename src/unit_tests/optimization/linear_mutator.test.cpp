#include <boost/test/unit_test.hpp>
#include <k52/optimization/linear_mutator.h>
#include "../boost_test_tools_extensions.h"

using ::k52::optimization::LinearMutator;
using ::k52::optimization::MutationContext;

BOOST_AUTO_TEST_SUITE(linear_mutator_tests);

class LinearMutatorMock : public LinearMutator
{
public:
    LinearMutatorMock(
        double start_gen_mutation_probability,
        double end_gen_mutation_probability)
        : LinearMutator(
            start_gen_mutation_probability, end_gen_mutation_probability)
    { }

    double GetCurrentGenMutationProbability()
    {
        return LinearMutator::GetCurrentGenMutationProbability();
    }
};

BOOST_AUTO_TEST_CASE(invalid_probabilities)
{
    BOOST_REQUIRE_THROW( LinearMutator (-0.1, 0.5) , std::invalid_argument);
    BOOST_REQUIRE_THROW( LinearMutator (0.1, 1.5) , std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(start_probability)
{
    //Prepare
    LinearMutatorMock mutatorMock(0.5, 0.7);
    MutationContext context;
    context.current_generation = 0;
    context.max_number_of_generations = 100;

    mutatorMock.ApplyNewMutationContext(context);

    //Test
    double probability = mutatorMock.GetCurrentGenMutationProbability();

    //Check
    CheckDoubleEqual(probability, 0.5);
}

BOOST_AUTO_TEST_CASE(middle_probability)
{
    //Prepare
    LinearMutatorMock mutatorMock(0.5, 0.7);
    MutationContext context;
    context.current_generation = 2;
    context.max_number_of_generations = 5;

    mutatorMock.ApplyNewMutationContext(context);

    //Test
    double probability = mutatorMock.GetCurrentGenMutationProbability();

    //Check
    CheckDoubleEqual(probability, 0.6);
}

BOOST_AUTO_TEST_CASE(end_probability)
{
    //Prepare
    LinearMutatorMock mutatorMock(0.5, 0.7);
    MutationContext context;
    context.current_generation = 10;
    context.max_number_of_generations = 11;

    mutatorMock.ApplyNewMutationContext(context);

    //Test
    double probability = mutatorMock.GetCurrentGenMutationProbability();

    //Check
    CheckDoubleEqual(probability, 0.7);
}

BOOST_AUTO_TEST_SUITE_END();