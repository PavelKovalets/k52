# Contributing to k52 #

:+1::tada: First off, thanks for taking the time to contribute! :tada::+1:

The following is a set of guidelines for contributing to k52.
 These are just guidelines, not rules, use your best judgment
 and feel free to propose changes to this document in a pull request.

## Code style ##

### C++ ###

- Do not use C++11 features yet - see [this issue](https://github.com/PavelKovalets/k52/issues/12)
- Do not use raw pointers, we use [boost::scoped_ptr](http://www.boost.org/doc/libs/1_61_0/libs/smart_ptr/scoped_ptr.htm)
 and [boost::shared_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/shared_ptr.htm) instead.
 Ideally we even do not use `new` keyword, but use [boost::make_shared](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/make_shared.html) instead.
 For details see [here](http://www.rsdn.ru/article/cpp/smartptr.xml) and [here](http://meetingcpp.ru/?page_id=608)
- Do not use plain arrays, we use `std::vector` instead
- Use [Google Code Style](https://google.github.io/styleguide/cppguide.html)
 as the main naming and style convention but with following exceptions:
 - **4 spaces** as indent, tab symbol is prohibited. You should set corresponding option in you IDE to avoid tab checkins.
 For example in Visual Studio go to `Tools -> Options -> Text Editor -> C/C++ -> Tabs` and set `Insert spaces` option and both sizes to 4.
 - 1 class = 1 `.h` file + 1 `.cpp` file, exceptions are RAII, PImpl
 - C++ exceptions are allowed to use only where they are really necessary
 - RTTI is allowed to use only where it is really necessary
 - Prefix `k` for enum and constants names - `kMyEnymName`, `kMyConstant`
 - Classes-interfaces with only pure virtual functions are called `IClassName`, not `ClassNameInterface`
 - Always move `{` to the new line, do not leave on the same line with code
 - The `public:`, `protected:`, and `private:` keywords without indent
 - Wrap statement bodies (`if`, `for` ...) with `{}` even if it is only 1 line of code
 - Any constructor which accepts single parameter should be marked with `explicit` keyword

### Comments ###
- Comment for all public classes/methods that will be visible to the end-user of k52 lib are required. 
- For helper classes - only in places where it is necessary (e.g. explanation of a complex algorithm).
- Comments should be in [doxygen](https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html) format.
- Please, **no** captain-comments, like following 
```C++
//Function that returns an integer number of items
int GetNumberOfItems();
```

### Best practice ###

- Tend to do a cross-platform implementation. Usually math algorithms are platform-independent without any extra work.
- Use only latin symbols - 7bit ASCII characters encoding.
 This can be checked with the help of [encoding.sh](https://github.com/PavelKovalets/k52/blob/develop/tools/encoding.sh) or `enca` tool.
- Try to avoid copy-paste of existing code from k52. Instead you should use such techniques as inheritance or do some refactoring to reuse existing code. 
- A few unit tests which covers your basic functionality are always great.

### OPP ###

We try to implement k52 in an OOP way. This means that we appreciate suchcode features as readability,
 flexibility and being-easily-reusable most of all.
 This doesn't mean that we do not care of the performance at all -
 we also do all the optimisations that do not ruin the features above. 

- Any algorithm or numerical method should have main class which is responsible for the encapsulation of the logic.
 It also often implements corresponding interface.
- Helper classes should have only 1 logical area of responsibility, which should be reflected in the name of the class.
- Use OOP patterns only in places where they are really appropriate.

## Things to check when submitting a pull request ##
- All above :)
- Travis CI build is passed
- You've signed the [Contributor License Agreement on CLAHub](https://www.clahub.com/agreements/PavelKovalets/k52)
- For both Windows and Linux platforms:
 - Clean build from freshly cloned repo
 - Unit tests should pass
 - k52 examples should run ok