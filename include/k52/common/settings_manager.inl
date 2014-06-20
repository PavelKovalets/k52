/// @file
/// @brief The file contains setting manager template methods
/// @copyright

namespace k52
{

template <class PropertyType>
PropertyType SettingsManager::get(const std::string& property_name) const
try
{
    return property_tree_.get<PropertyType>(property_name);
}
catch (...)
{
    std::cerr << "Failed to get mandatory property " << property_name <<std::endl;

    // There is no way to recover missed mandatory property,
    // so just re-throw it to the caller
    // TODO: define missed-mandatory-parameter exception
    throw;
}

template <class PropertyType>
PropertyType SettingsManager::get(const std::string& property_name, const PropertyType& default_value) const
try
{
    return property_tree_.get<PropertyType>(property_name);
}
catch(...)
{
    return default_value;
}


template <class PropertyType>
bool SettingsManager::put(const std::string& property_name, const PropertyType& property_value)
try
{
    property_tree_.put(property_name, property_value);
    return true;
}
catch (...)
{
    return false;
}

} // namespace k52
