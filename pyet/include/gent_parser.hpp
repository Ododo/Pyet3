#ifndef GENT_PARSER_HPP_INCLUDED
#define GENT_PARSER_HPP_INCLUDED

#include <boost/python.hpp>
#include <map>
#include "../../common/include/etdef.hpp"


#define GetAttrByOfs(type, ent, ofs) *(type *) (ent + ofs)

#define ArrayToList(imax, array, list) for(int i=0 ; i<imax ; i++){ list.append((array)[i]);}

#define ListToArray(imax, array, list)  for(int i=0 ; i<imax ; i++){ \
                                           float f = python::extract<float>(list[i]); \
                                           (array)[i]=f;}

#define TrajectoryToList(array) \
        list.append(ent->array.trType); \
        list.append(ent->array.trTime); \
        list.append(ent->array.trDuration); \
        python::list base, delta; \
        ArrayToList(3, ent->array.trBase, base); \
        ArrayToList(3, ent->array.trDelta, delta); \
        list.append(base); \
        list.append(delta); \

typedef enum
{
    //type of the data
    F_INT,
    F_FLOAT,
    F_LSTRING,
    F_GSTRING,
    F_VECTOR,
    F_INTARRAY,
    F_ENTITY,
    F_CLIENT,
} pfieldtype_t;

typedef enum
{
    //just to know if it is ent->client related or not
    FL_NONE,
    FL_CLIENT,
   // FL_READONLY, ~
} pflags_t;


typedef struct
{
        int ofs;
        pfieldtype_t type;
        int flags;
        unsigned int array_size;
}pfield_t;


using namespace boost;

python::object
GetValueForString(gentity_t* entities,gentity_t *ent, std::string field);
int SetValueForString(gentity_t *ent, std::string field, python::object value);

#endif // GENT_PARSER_HPP_INCLUDED
