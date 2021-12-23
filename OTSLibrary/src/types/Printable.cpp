//
// Created by glebb on 12/23/2021.
//
//#include "../../include/types/Printable.h"
#include <types/Printable.h>

#include <string>

namespace OTSLibrary
{
    std::ostream & operator<<(std::ostream & strm, const Printable & printable)
    {
        return printable.Print(strm);
    }
}
