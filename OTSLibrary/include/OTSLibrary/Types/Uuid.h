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
    namespace detail {
        template <typename TChar>
        constexpr inline unsigned char hex2char(TChar const ch)
        {
            if (ch >= static_cast<TChar>('0') && ch <= static_cast<TChar>('9'))
                return static_cast<unsigned char>(ch - static_cast<TChar>('0'));
            if (ch >= static_cast<TChar>('a') && ch <= static_cast<TChar>('f'))
                return static_cast<unsigned char>(10 + ch - static_cast<TChar>('a'));
            if (ch >= static_cast<TChar>('A') && ch <= static_cast<TChar>('F'))
                return static_cast<unsigned char>(10 + ch - static_cast<TChar>('A'));
            return 0;
        }
    }

    class Uuid : public AnyType
    {
    public:
        constexpr Uuid() = default;
        constexpr Uuid(const Uuid & uuid) : first(uuid.first), second(uuid.second) {}
        constexpr explicit Uuid(const std::pair<uint64_t, uint64_t> & value) : first(value.first), second(value.second) {}
        explicit Uuid(const char * value);

        Uuid & operator=(const Uuid & uuid)
        {
            first = uuid.first;
            second = uuid.second;
            return *this;
        }

        static Uuid create();

        [[nodiscard]]
        bool empty() const override { return (first == 0 && second == 0); }
        void clear()
        {
            first = 0;
            second = 0;
        }
        [[nodiscard]]
        std::pair<uint64_t, uint64_t> getIntPair() const;

    public:
        bool operator==(const Uuid & value) const { return (first == value.first) && (second == value.second); }
        bool operator!=(const Uuid & value) const { return !operator==(value); }

        bool operator<(const Uuid & value) const;
        bool operator>(const Uuid & value) const { return value < *this; }

        bool operator<=(const Uuid & value) const { return !(value < *this); }
        bool operator>=(const Uuid & value) const { return !operator<(value); }
    public:
        std::ostream & print(std::ostream & strm) const override;

        [[nodiscard]]
        size_t get_hash() const override;

        [[nodiscard]]
        std::string to_string() const override;
    private:
        uint64_t first{};
        uint64_t second{};
    };
}

#endif //OPENTRADINGSYSTEM_UUID_H
