#ifndef ETTOOLS_HPP_INCLUDED
#define ETTOOLS_HPP_INCLUDED

///***************************************************************
/// Copyright (C) 1999-2000 Id Software, Inc.

__attribute__((format(printf,1,2)))
char * va(char *format, ...);


char *Info_ValueForKey( const char *s, const char *key );
void Info_RemoveKey( char *s, const char *key );
void Info_SetValueForKey( char *s, const char *key, const char *value );


#endif // ETTOOLS_HPP_INCLUDED
