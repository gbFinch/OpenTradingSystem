//
// Created by glebb on 12/23/2021.
//
#include <OTSLibrary/Types/Uuid.h>
#include <random>
#include <iomanip>

namespace OTSLibrary
{
    void Uuid::Generate() {}
    Uuid Uuid::Create() {
        static thread_local std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<unsigned long long> distribution(
                std::numeric_limits<std::uint64_t>::min(),
                std::numeric_limits<std::uint64_t>::max()
        );
        return Uuid(std::make_pair(distribution(generator),distribution(generator)));
    }
    std::pair<uint64_t, uint64_t> Uuid::GetIntPair() const { return std::make_pair(first, second); }
    std::ostream & Uuid::Print(std::ostream & strm) const {
        //return strm << std::string("Uuid<") << std::to_string(first) << std::string(";") << std::to_string(second) << std::string(">");
        return strm << ToString();
    }

    size_t Uuid::GetHash() const {
        auto h1 = std::hash<uint64_t>{}(first);
        auto h2 = std::hash<uint64_t>{}(second);
        return h1^h2;
    }

    Uuid::Uuid(const char *value) {

    }

    Uuid::Uuid(const char *value, size_t size) {

    }

    std::string Uuid::ToString() const {
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
