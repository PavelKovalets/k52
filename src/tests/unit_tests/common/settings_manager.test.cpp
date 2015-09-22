#define BOOST_TEST_MODULE settings_manager
#include <boost/test/unit_test.hpp>
#include <k52/common/settings_manager.h>

namespace k52
{

class SettingsManagerMock : public SettingsManager
{
public:
    static boost::property_tree::ptree Merge(const boost::property_tree::ptree& left_tree,
                                             const boost::property_tree::ptree& right_tree)
    {
        return SettingsManager::Merge(left_tree, right_tree);
    }
};

BOOST_AUTO_TEST_CASE(constructors)
{
    BOOST_REQUIRE_NO_THROW(SettingsManager sm(0, NULL));           // Empty Parameters
    BOOST_REQUIRE_THROW(SettingsManager sm(std::string("non_existed.config")), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(init_from_cmd)
{
    boost::shared_ptr<SettingsManager> sm_ptr;
    const char* argv[] = {"--config-file=config.xml", "--database=a.wav,b.wav", "--genetic_algorithm.population_size=2000"};
    BOOST_REQUIRE_NO_THROW(sm_ptr.reset(new SettingsManager(3, argv)));

    std::string config_filename;
    BOOST_REQUIRE_NO_THROW(config_filename = sm_ptr->get<std::string>("config-file"));
    BOOST_REQUIRE(config_filename == std::string("config.xml"));

    std::string database;
    BOOST_REQUIRE_NO_THROW(database = sm_ptr->get<std::string>("database"));
    BOOST_REQUIRE(database == std::string("a.wav,b.wav"));

    int population_size(0);
    BOOST_REQUIRE_NO_THROW(population_size = sm_ptr->get<int>("genetic_algorithm.population_size"));
    BOOST_REQUIRE(population_size == 2000);
}

BOOST_AUTO_TEST_CASE(set_property)
{
    boost::shared_ptr<SettingsManager> sm;
    BOOST_REQUIRE_NO_THROW(sm.reset(new SettingsManager(0, NULL)));
    BOOST_REQUIRE_NO_THROW(sm->put("test_property.string", "test_string_value"));
    BOOST_REQUIRE_NO_THROW(sm->put("test_property.int",    42));
    BOOST_REQUIRE_NO_THROW(sm->put("test_property.double", 42.42));
    BOOST_REQUIRE_NO_THROW(sm->put("test_property.bool",   false));

    std::string test_value;
    BOOST_REQUIRE_NO_THROW(test_value = sm->get<std::string>("test_property.string"));
    BOOST_REQUIRE(test_value == std::string("test_string_value"));

    int test_int_value(0);
    BOOST_REQUIRE_NO_THROW(test_int_value = sm->get<int>("test_property.int"));
    BOOST_REQUIRE(test_int_value == 42);

    double test_double_value(0);
    BOOST_REQUIRE_NO_THROW(test_double_value = sm->get<double>("test_property.double"));
    BOOST_REQUIRE(test_double_value == 42.42);

    bool test_bool_value(true);
    BOOST_REQUIRE_NO_THROW(test_bool_value = sm->get<bool>("test_property.bool"));
    BOOST_REQUIRE(test_bool_value == false);
}

BOOST_AUTO_TEST_CASE(merging_empty_trees)
{
    boost::property_tree::ptree tr1, tr2, merged;
    BOOST_REQUIRE_NO_THROW(merged = SettingsManagerMock::Merge(tr1, tr2));
    BOOST_REQUIRE(merged.begin() == merged.end()); // check that result is still empty
}

BOOST_AUTO_TEST_CASE(merging_different_properties)
{
    boost::property_tree::ptree tr1, tr2, merged;
    BOOST_REQUIRE_NO_THROW(
      tr1.put("some_example_property_1", 19);
      tr2.put("some_example_property_2", 21)
    );

    BOOST_REQUIRE_NO_THROW(merged = SettingsManagerMock::Merge(tr1, tr2));
    BOOST_REQUIRE(merged.begin() != merged.end());
    int p1 = 0, p2 = 0;
    BOOST_REQUIRE_NO_THROW(p1 = merged.get<int>("some_example_property_1"));
    BOOST_REQUIRE_NO_THROW(p2 = merged.get<int>("some_example_property_2"));
    BOOST_REQUIRE(p1 == 19);
    BOOST_REQUIRE(p2 == 21);
}

BOOST_AUTO_TEST_CASE(merging_property)
{
    boost::property_tree::ptree tr1, tr2, merged1, merged2;
    BOOST_REQUIRE_NO_THROW(
      tr1.put("some_example_property", 19);
      tr2.put("some_example_property", 21)
    );

    BOOST_REQUIRE_NO_THROW(merged1 = SettingsManagerMock::Merge(tr1, tr2));
    BOOST_REQUIRE(merged1.begin() != merged1.end());
    int p = 0;
    BOOST_REQUIRE_NO_THROW(p = merged1.get<int>("some_example_property"));
    BOOST_REQUIRE(p == 19);

    BOOST_REQUIRE_NO_THROW(merged2 = SettingsManagerMock::Merge(tr2, tr1));
    BOOST_REQUIRE(merged2.begin() != merged2.end());
    BOOST_REQUIRE_NO_THROW(p = merged2.get<int>("some_example_property"));
    BOOST_REQUIRE(p == 21);
}

BOOST_AUTO_TEST_CASE(merging_subtree_with_different_properties)
{
    boost::property_tree::ptree tr1, tr2, merged;
    BOOST_REQUIRE_NO_THROW(
      tr1.put("some.example.property_1", 19);
      tr2.put("some.exampleproperty_2", 21)
    );

    BOOST_REQUIRE_NO_THROW(merged = SettingsManagerMock::Merge(tr1, tr2));
    BOOST_REQUIRE(merged.begin() != merged.end());
    int p1 = 0, p2 = 0;
    BOOST_REQUIRE_NO_THROW(p1 = merged.get<int>("some.example.property_1"));
    BOOST_REQUIRE_NO_THROW(p2 = merged.get<int>("some.exampleproperty_2"));
    BOOST_REQUIRE(p1 == 19);
    BOOST_REQUIRE(p2 == 21);
}

BOOST_AUTO_TEST_CASE(merging_subtree)
{
    boost::property_tree::ptree tr1, tr2, merged1, merged2;
    BOOST_REQUIRE_NO_THROW(
      tr1.put("some.example.property", 19);
      tr2.put("some.example.property", 21)
    );

    BOOST_REQUIRE_NO_THROW(merged1 = SettingsManagerMock::Merge(tr1, tr2));
    BOOST_REQUIRE(merged1.begin() != merged1.end());
    int p = 0;
    BOOST_REQUIRE_NO_THROW(p = merged1.get<int>("some.example.property"));
    BOOST_REQUIRE(p == 19);

    BOOST_REQUIRE_NO_THROW(merged2 = SettingsManagerMock::Merge(tr2, tr1));
    BOOST_REQUIRE(merged2.begin() != merged2.end());
    BOOST_REQUIRE_NO_THROW(p = merged2.get<int>("some.example.property"));
    BOOST_REQUIRE(p == 21);
}

} // namespace k52
