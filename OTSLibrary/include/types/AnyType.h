//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_ANYTYPE_H
#define OPENTRADINGSYSTEM_ANYTYPE_H

#include "Printable.h"

namespace OTSLibrary
{
    class AnyType : public Printable{
    public:
        virtual ~AnyType() = default;
        virtual bool Empty() const = 0;
        virtual size_t GetHash() const = 0;
    };

    inline size_t hash_value(const AnyType & value)
    {
        return value.GetHash();
    }

    inline size_t hash_value(int value)
    {
        return (size_t)value;
    }

    template <typename T>
    inline size_t hash_value(T * const & value)
    {
        return (size_t)value;
    }
}

#endif //OPENTRADINGSYSTEM_ANYTYPE_H
