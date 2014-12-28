#ifndef K52_COMMON_SETTINGS_MANAGER_H
#define K52_COMMON_SETTINGS_MANAGER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <stdexcept>

namespace k52
{

/// @brief SettingsManager
/// The one stores <property name, value> pairs with different type of properties. I.e. it can store strings,
/// ints, doubles etc. For complete list of the supported type @see boost::property_tree
class SettingsManager
{
public:
    /// @brief Constructor
    /// It parses command line arguments array as it arrives into main(int, const char*[])
    /// @param argument count
    /// @param argument values
    SettingsManager(int argument_count, const char* argument_values[])
    {
        ParseCommandLine(argument_count, argument_values);
    }

    /// @brief Constructor
    /// It loads configuration form file
    /// @param configuration file
    SettingsManager(const std::string& config_filename)
    {
        ParseXmlConfigFile(config_filename);
    }

    /// @brief Get property value
    /// @note For mandatory properties - if property doesn't exist it will throw
    /// @param property name
    template <class PropertyType>
    PropertyType get(const std::string& property_name) const;

    /// @brief Get property value
    /// @note if requested property doesn't exist default_value will be returned
    /// @param property name
    /// @param default property value
    /// @return property value if the property exists
    /// @return passed default value if the property doesn't exist
    template <class PropertyType>
    PropertyType get(const std::string& property_name, const PropertyType& default_value) const;

    /// @brief Set property value
    /// @param property name
    /// @param property value
    /// @return true if succeeded
    /// @return false if failed
    template <class T>
    bool put(const std::string& property_name, const T& property_value);

protected:
    const std::string& ArgPrefix()
    {
        static const std::string kArgPrefix("--");
        return kArgPrefix;
    }

    /// @brief It parses command line arguments array as it arrives into main(int, const char*[])
    /// @param argument count
    /// @param argument values
    void ParseCommandLine(size_t argument_count, const char* argument_values[])
    {
        for (size_t i = 0; i < argument_count; ++i)
        {
            std::string argument(argument_values[i]);
            if (ArgPrefix() == argument.substr(0, ArgPrefix().length()))
            {
                // split argument name and value
                argument.erase(0, ArgPrefix().length());
                std::string argument_name(argument.substr(0, argument.find("=")));
                std::string argument_value(argument.substr(argument.find("=") + 1));

                property_tree_.put(argument_name, argument_value);
            }
        }
    }

    /// @brief Load configuration from xml
    /// @param filename - xml file to be loaded
    /// @return true if configuration loading succeeded
    /// @return false otherwise
    void ParseXmlConfigFile(const std::string& filename) throw (std::runtime_error)
    try
    {
        boost::property_tree::xml_parser::read_xml(filename, property_tree_);
    }
    catch (...)
    {
        throw std::runtime_error("Failed to parse configuration from xml file");
    }

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

#include <k52/common/settings_manager.inl>

#endif // K52_COMMON_SETTINGS_MANAGER_H
