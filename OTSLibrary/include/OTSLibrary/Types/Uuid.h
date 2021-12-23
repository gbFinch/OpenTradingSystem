//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_UUID_H
#define OPENTRADINGSYSTEM_UUID_H

#include "AnyType.h"
#include <utility>
#include <cstddef>
#include <cstdint>

namespace OTSLibrary
{
    class Uuid : public AnyType
    {
    public:
        Uuid() : first(0), second(0) {}
        Uuid(const Uuid & uuid) : first(uuid.first), second(uuid.second) {}
        Uuid(const std::pair<uint64_t, uint64_t> & value) : first(value.first), second(value.second) {}
        Uuid(const char * value);
        Uuid(const char * value, size_t size);
        ~Uuid() override {}

        void Generate();

        Uuid & operator=(const Uuid & uuid)
        {
            first = uuid.first;
            second = uuid.second;
            return *this;
        }

        static Uuid Create();

        bool Empty() const override { return (first == 0 && second == 0); }
        void Clear()
        {
            first = 0;
            second = 0;
        }
        std::pair<uint64_t, uint64_t> GetIntPair() const;

    public:
        bool operator==(const Uuid & value) const { return (first == value.first) && (second == value.second); }
        bool operator!=(const Uuid & value) const { return !operator==(value); }

        bool operator<(const Uuid & value) const;
        bool operator>(const Uuid & value) const { return value < *this; }

        bool operator<=(const Uuid & value) const { return !(value < *this); }
        bool operator>=(const Uuid & value) const { return !operator<(value); }
    public:
        virtual std::ostream & Print(std::ostream & strm) const override;
        virtual size_t GetHash() const override;
        virtual std::string ToString() const override;
    private:
        uint64_t first;
        uint64_t second;
    };
}

#endif //OPENTRADINGSYSTEM_UUID_H
