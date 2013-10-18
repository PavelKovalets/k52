#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <boost/property_tree/ptree.hpp>

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
    SettingsManager(int argument_count, char* argument_values[])
    {
        ParseCommandLine(argument_count, argument_values);
    }

    // Initialize from command line
    void ParseCommandLine(int argument_count, char* argument_values[])
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

    // For mandatory parameters
    template <class T>
    const T& get(const std::string& property_name) const
    {
        return T();
    }

    template <class T>
    const T& get(const std::string& property_name, const T& default_value) const
    {
        return T();
    }

private:
    boost::property_tree::ptree property_tree_;
};

} // namespace k52

#endif // SETTINGS_MANAGER_H
