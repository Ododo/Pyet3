#ifndef WRAPPER_HPP
#define WRAPPER_HPP


typedef int  (*SYSCALL)( int arg, ... );
typedef void (*UVARIADIC) (...);
typedef int  (*IVARIADIC)  (int...);


#endif
