#ifndef K52_DISALLOW_COPY_AND_ASSIGN_H
#define K52_DISALLOW_COPY_AND_ASSIGN_H

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);               \
    void operator=(const TypeName&)

#endif //
