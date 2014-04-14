#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

namespace
{
const std::string kArgPrefix("--");
const size_t kArgPrefixStart = 0;
const size_t kArgPrefixLenght = kArgPrefix.length();
}

namespace k52
{

class SettingsManager
{
public:
    SettingsManager(int argument_count, const char* argument_values[])
    {
        ParseCommandLine(argument_count, argument_values);
    }

    // Load config file
    SettingsManager(const std::string& config_filename)
    {
        if (!ParseXmlConfigFile(config_filename))
        {
            std::cerr << "Configuration file is not supported" << std::endl;
        }
    }

    // Initialize from command line
    void ParseCommandLine(size_t argument_count, const char* argument_values[])
    {
        for (size_t i = 0; i < argument_count; ++i)
        {
            std::string argument(argument_values[i]);
            if (kArgPrefix == argument.substr(kArgPrefixStart, kArgPrefixLenght))
            {
                // split argument name and value
                argument.erase(kArgPrefixStart, kArgPrefixLenght);
                std::string argument_name(argument.substr(0, argument.find("=")));
                std::string argument_value(argument.substr(argument.find("=") + 1));

                property_tree_.put(argument_name, argument_value);
            }
        }
    }

    // Initialize from configuration xml
    bool ParseXmlConfigFile(const std::string& filename)
    try
    {
        boost::property_tree::xml_parser::read_xml(filename, property_tree_);
        return true;
    }
    catch (...)
    {
        std::cerr << "Failed to parse configuration from xml file " << filename << std::endl;
        return false;
    }

    // @note For mandatory property
    // if property doesn't exist it will throw
    template <class T>
    T get(const std::string& property_name) const
    try
    {
        return property_tree_.get<T>(property_name);
    }
    catch (...)
    {
        std::cerr << "Failed to get mandatory property " << property_name <<std::endl;

        // There is no way to recover missed mandatory property,
        // so just re-throw it to the caller
        // TODO: define missed-mandatory-parameter exception
        throw;
    }

    template <class T>
    T get(const std::string& property_name, const T& default_value) const
    try
    {
        return property_tree_.get<T>(property_name);
    }
    catch(...)
    {
        return default_value;
    }

    template <class T>
    bool put(const std::string& property_name, const T& property_value)
    try
    {
        property_tree_.put(property_name, property_value);
        return true;
    }
    catch (...)
    {
        return false;
    }

protected:
    // @note Still not in boost :( - hope it will be added soon so implementation is fast,
    // straightforward and not efficient
    // Current implementation respects properties from the left tree - if the same property exists in both trees
    // merged will contain value from the left one => Merge(l,r) != Merge(r,l)

    static boost::property_tree::ptree Merge(const boost::property_tree::ptree& left_tree,
                                             const boost::property_tree::ptree& right_tree)
    {
        boost::property_tree::ptree merged_tree(left_tree);
        for(boost::property_tree::ptree::const_iterator it(right_tree.begin());
            right_tree.end() != it; ++it)
        {
            boost::property_tree::ptree::iterator found(merged_tree.to_iterator(merged_tree.find(it->first)));
            if (merged_tree.end() != found)
            {
                // Do not overload value of existed property, just add subtrees
                merged_tree.get_child(it->first) = Merge(found->second, it->second);
            }
            else
            {
                merged_tree.put_child(it->first, it->second);
            }
        }
        return merged_tree;
    }

private:
    boost::property_tree::ptree property_tree_;
};

} // namespace k52

#endif // SETTINGS_MANAGER_H
