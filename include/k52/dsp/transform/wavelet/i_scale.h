#ifndef I_SCALE_H
#define I_SCALE_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include <vector>

#include <k52/common/disallow_copy_and_assign.h>

namespace k52
{
namespace dsp
{

class IScale
{
public :
    typedef boost::shared_ptr< IScale > shared_ptr;

    ///Default constructor should be explicitly defined if DISALLOW_COPY_AND_ASSIGN used
    IScale() {}
    virtual ~IScale() {}

    virtual std::vector< double > GetScales () const = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(IScale);
};

} // namespace dsp
} // namespace k52

#endif //I_SCALE_H
