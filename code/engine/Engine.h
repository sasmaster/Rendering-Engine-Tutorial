#ifndef SGE_ENGINE_H
#define SGE_ENGINE_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h> //prevent Win API complains for re-includes in 3rd party libs
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <new>




#ifdef SGE_DEBUG
  #define SGE_ASSERT(a)assert(a)
#else
  #define SGE_ASSERT(a)
#endif // SGE_DEBUG


#define SGE_DISABLE_COPY_ASSIGN(Class)        \
    Class(Class const&) = delete;             \
    Class& operator=(Class const&) = delete;

#endif

#define newnothrow new(std::nothrow)