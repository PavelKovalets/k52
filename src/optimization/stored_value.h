#ifndef STOREDVALUE_H_
#define STOREDVALUE_H_

namespace k52
{
namespace optimization
{

class StoredValue
{
public:
    StoredValue() : has_value_(false) {}

    explicit StoredValue(double fitness) : has_value_(true), value_(fitness), number_of_usage_(0) {}

    void IncrementUsage() { ++number_of_usage_; }

    bool has_value() { return has_value_; }

    double get_value() { return value_; }

    int get_number_of_usage() { return number_of_usage_; }

private:
    bool has_value_;
    double value_;
    int number_of_usage_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* STOREDVALUE_H_ */
