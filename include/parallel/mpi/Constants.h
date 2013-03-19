#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

namespace k52
{
namespace parallel
{
namespace mpi
{
//TODO incapsulate and hide from user - !!! to remove using namespace k52::parallel::mpi::constants;
namespace constants
{

    static const int kServerRank = 0;

    static const int kCommonTag = 0;

    //TODO do not use class constants
    static const std::string kEndOfWorkTaskId = "TheIdOfTheTaskThatMeanThatWorkerShouldEndItsWork";

} /* constants */
} /* mpi */
} /* parallel */
} /* k52 */

#endif /* CONSTANTS_H_ */
