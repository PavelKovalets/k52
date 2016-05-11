#ifndef STOREDVALUE_H_
#define STOREDVALUE_H_

namespace k52
{
namespace common
{

template <typename TValue>
class StoredValue
{
public:
    StoredValue() : has_value_(false), value_(), number_of_usage_(0) {}

    explicit StoredValue(TValue value) : has_value_(true), value_(value), number_of_usage_(0) {}

    void IncrementUsage() { ++number_of_usage_; }

    bool has_value() { return has_value_; }

    TValue get_value() { return value_; }

    int get_number_of_usage() { return number_of_usage_; }

private:
    bool has_value_;
    TValue value_;
    int number_of_usage_;
};

}/* namespace common */
}/* namespace k52 */

#endif /* STOREDVALUE_H_ */
