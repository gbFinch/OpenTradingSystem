//
// Created by glebb on 12/23/2021.
//
#include <OTSLibrary/Types/Uuid.h>
#include <random>
#include <iomanip>
#include <array>
#include <iostream>

namespace OTSLibrary
{
    Uuid Uuid::create() {
        static thread_local std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<unsigned long long> distribution(
                std::numeric_limits<std::uint64_t>::min(),
                std::numeric_limits<std::uint64_t>::max()
        );
        return Uuid(std::make_pair(distribution(generator),distribution(generator)));
    }
    std::pair<uint64_t, uint64_t> Uuid::getIntPair() const { return std::make_pair(first, second); }
    std::ostream & Uuid::print(std::ostream & strm) const {
        return strm << to_string();
    }

    size_t Uuid::get_hash() const {
        auto h1 = std::hash<uint64_t>{}(first);
        auto h2 = std::hash<uint64_t>{}(second);
        return h1^ h2;
    }

    Uuid::Uuid(const char *value) {
        uint64_t candidate1{}, candidate2{};
        bool nextByte = true;
        auto it = value;
        size_t index = 0;
        while (*it != '\0')
        {
            if (index > 16) return;
            const auto& digit = *it;

            it++;
            if (digit == '-') {
                continue;
            }
            auto& candidate = index < 8 ? candidate1 : candidate2;
            uint64_t hexDigit = detail::hex2char(digit);
            if (nextByte) {
                candidate |= hexDigit << (index * 8 + 4);
                nextByte = false;
            } else {
                candidate |= hexDigit << (index * 8);
                index++;
                nextByte = true;
            }
        }
        if (index < 16) return;;

        first = candidate1;
        second = candidate2;
    }

    bool Uuid::operator<(const Uuid & value) const {
        return first != value.first ? first < value.first : second < value.second;
    }

    std::string Uuid::to_string() const {
        std::stringstream stream;
        stream << std::hex << std::setfill('0')
               << std::setw(2) << ((first >> 0)& 0xFF)
               << std::setw(2) << ((first >> 8)& 0xFF)
               << std::setw(2) << ((first >> 16)& 0xFF)
               << std::setw(2) << ((first >> 24)& 0xFF)
               << '-'
               << std::setw(2) << ((first >> 32)& 0xFF)
               << std::setw(2) << ((first >> 40)& 0xFF)
               << '-'
               << std::setw(2) << ((first >> 48)& 0xFF)
               << std::setw(2) << ((first >> 56)& 0xFF)
               << '-'
               << std::setw(2) << ((second >> 0)& 0xFF)
               << std::setw(2) << ((second >> 8)& 0xFF)
               << '-'
               << std::setw(2) << ((second >> 16)& 0xFF)
               << std::setw(2) << ((second >> 24)& 0xFF)
               << std::setw(2) << ((second >> 32)& 0xFF)
               << std::setw(2) << ((second >> 40)& 0xFF)
               << std::setw(2) << ((second >> 48)& 0xFF)
               << std::setw(2) << ((second >> 56)& 0xFF);
        return stream.str();
    }
}
