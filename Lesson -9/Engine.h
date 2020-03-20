#pragma once
#ifndef SGE_ENGINE_H
#define SGE_ENGINE_H


#ifdef  _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif //  _WIN32


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <new>


#ifdef SGE_DEBUG
  #define SGE_ASSERT(a)assert(a)
#else
  #define SGE_ASSERT(a)
#endif


#define SGE_DISABLE_COPY_ASSIGN(Class)   \
       Class(Class const&) = delete;     \
       Class operator=(Class const&) = delete;



#define newnothrow new(std::nothrow)






#endif // !SGE_ENGINE_H
