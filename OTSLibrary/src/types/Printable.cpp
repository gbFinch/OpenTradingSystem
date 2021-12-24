//
// Created by glebb on 12/23/2021.
//
//#include "../../include/Types/Printable.h"
#include <OTSLibrary/types/Printable.h>
#include <string>

namespace OTSLibrary
{
    std::ostream & operator<<(std::ostream & strm, const Printable & printable)
    {
        return printable.print(strm);
    }
}
