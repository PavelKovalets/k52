#include <iostream>
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

} // namespace k52

void print_tree(const std::string& line_prefix, const boost::property_tree::ptree& tree)
{
    for (boost::property_tree::ptree::const_iterator it(tree.begin()); it != tree.end(); ++it)
    {
        std::cout << line_prefix << it->first << ": "
                  << it->second.get_value<std::string>() << std::endl;
        print_tree(line_prefix+"   ", it->second);
    }
}

int main(int argc, char* argv[])
{
    boost::property_tree::ptree tree_1;
    tree_1.put("genetic_algorithm.population_size", 1000);
    tree_1.put("genetic_algorithm.elitizm_pairs", 10);
    tree_1.put("genetic_algorithm.log.enable", true);
    tree_1.put("genetic_algorithm.log.level", 1);

    boost::property_tree::ptree tree_2;
    tree_2.put("genetic_algorithm.population_size", 10);
    tree_2.put("genetic_algorithm.elitizm_pairs", 1);
    tree_2.put("genetic_algorithm.log.enable", false);
    tree_2.put("genetic_algorithm.log.file", "log_file");
    tree_2.put("genetic_algorithm.not_existed_in_first", 999.9);
    tree_2.put("database", "a.wav;b.wav");

    std::cout << "k52::SettingsManagerMock::Merge(tree_1, tree_2)" << std::endl;
    print_tree("", k52::SettingsManagerMock::Merge(tree_1, tree_2));
    std::cout << "\n\nk52::SettingsManagerMock::Merge(tree_2, tree_1)" << std::endl;
    print_tree("", k52::SettingsManagerMock::Merge(tree_2, tree_1));

    return 0;
}
