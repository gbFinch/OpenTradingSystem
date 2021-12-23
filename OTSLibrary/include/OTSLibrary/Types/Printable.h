//
// Created by glebb on 12/23/2021.
//

#ifndef OPENTRADINGSYSTEM_PRINTABLE_H
#define OPENTRADINGSYSTEM_PRINTABLE_H

#include <iosfwd>
#include <string>

namespace OTSLibrary
{
    class Printable {
    public:
        Printable() = default;
        Printable(const Printable &) = default;
        virtual ~Printable() = default;
        friend std::ostream & operator<<(std::ostream & strm, const Printable & printable);
        virtual std::ostream & Print(std::ostream & strm) const = 0;
        virtual std::string ToString() const = 0;
    };
}

#endif //OPENTRADINGSYSTEM_PRINTABLE_H
