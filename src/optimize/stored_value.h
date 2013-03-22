#ifndef STOREDVALUE_H_
#define STOREDVALUE_H_

namespace k52
{
namespace optimize
{

class StoredValue
{
public:
    StoredValue() : has_value_(false) {}

    StoredValue(double fitness) : has_value_(true), value_(fitness) {}

    bool has_value() { return has_value_; }

    double get_value() { return value_; }

private:
    bool has_value_;
    double value_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* STOREDVALUE_H_ */
