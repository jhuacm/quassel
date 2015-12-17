#ifndef VIRTUALMETACLASS_H
#define VIRTUALMETACLASS_H

#include <QMetaType>

/**
 * Helper functions for managing virtual metatypes.
 *
 * @see virtualMetaTypeOf for determining the MetaTypeId of an instance.
 * If the declared type passed is not a virtual type, the MetaTypeId is
 * simply the MetaTypeId of that declared type.
 */

// Declare in public section of all leaf metatypes deriving from a virtual metatype
#define DECLARE_LEAF_METATYPE_PROTO(Type) int virtualMetaType() const;
// Declare in public section of all virtual metatypes
#define DECLARE_VIRTUAL_METATYPE_PROTO(Type) virtual DECLARE_LEAF_METATYPE_PROTO(Type)

// Use:
// - DECLARE_VIRTUAL_METATYPE on each virtual class in header.
// - DEFINE_VIRTUAL_METATYPE on each virtual class in the source file.
// - DEFINE_LEAF_METATYPE on each leaf class in the source file.

#define DECLARE_VIRTUAL_METATYPE(Type) \
namespace VirtualMetaClass { \
    template<> \
    int virtualMetaTypeOf<Type>(const void *i); \
}

#define DEFINE_VIRTUAL_METATYPE(Type) \
namespace VirtualMetaClass { \
    template<> \
    int virtualMetaTypeOf<Type>(const void *i) \
    { return ((Type *) i)->virtualMetaType(); } \
} \
DEFINE_LEAF_METATYPE(Type)

#define DEFINE_LEAF_METATYPE(Type) \
int Type::virtualMetaType() const \
{ \
    return qMetaTypeId<Type>(); \
}

// Default template. The virtualMetaTypeOf a non-virtual metatype is the qMetaType of the declared type.
namespace VirtualMetaClass {
    template<typename T>
    inline int virtualMetaTypeOf(const void *i)
    { Q_UNUSED(i); return qMetaTypeId<T>(); }
}

#endif // VIRTUALMETACLASS_H
