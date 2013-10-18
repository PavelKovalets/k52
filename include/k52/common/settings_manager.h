#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <boost/property_tree/ptree.hpp>

namespace k52
{

class SettingsManager
{
public:
    SettingsManager(int argc, char* argv[])
    {
        Initialize(argc, argv);
    }

    // Initialize from command line
    void Initialize(int argc, char* argv[])
    {
        property_tree_ =
        return;
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

protected:
    SettingsManager(){}

private:
    boost::property_tree::ptree property_tree_;
};

} // namespace k52

#endif // SETTINGS_MANAGER_H
