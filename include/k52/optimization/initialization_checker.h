#ifndef INITIALIZATIONCHECKER_H_
#define INITIALIZATIONCHECKER_H_

namespace k52
{
namespace optimize
{

/**
@class Individual
Manages initialization checking process.
Has two states - not initialized and initialized.
*/
class InitializationChecker
{
public:
    ///InitializationChecker is created in not initialized state
    InitializationChecker();

    ///Checks for being in initialized state.
    ///If not in initialized state - throws an logic_error exception.
    void InitializationCheck() const;

    ///Sets InitializationChecker into initialized state.
    ///If already in initialized state - throws an logic_error exception.
    void SetInitialized();

private:
    bool was_initialized_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* INITIALIZATIONCHECKER_H_ */
