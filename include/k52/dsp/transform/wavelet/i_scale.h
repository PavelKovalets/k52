#ifndef I_SCALE_H
#define I_SCALE_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include <vector>

namespace k52
{
namespace dsp
{

class IScale
{
public :
    typedef boost::shared_ptr< IScale > shared_ptr;
    virtual ~IScale() {}

    virtual std::vector< double > GetScales () const = 0;
};

} // namespace dsp
} // namespace k52

#endif //I_SCALE_H
