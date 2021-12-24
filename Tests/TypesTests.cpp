//
// Created by glebb on 12/24/2021.
//

#include "catch.hpp"
#include <OTSLibrary/Types/Uuid.h>

TEST_CASE("UUID tests", "[UUID]") {
    OTSLibrary::Uuid uuid;
    REQUIRE(uuid == OTSLibrary::Uuid(std::make_pair(0,0)));
    REQUIRE(uuid.to_string() == std::string("00000000-0000-0000-0000-000000000000"));
    REQUIRE(uuid.empty());

    SECTION( "Not empty" ) {
        uuid = OTSLibrary::Uuid(std::make_pair(0x123456789abcdef0, 0x123456789abcdef0));
        REQUIRE(uuid.getIntPair() == std::make_pair<uint64_t, uint64_t>(0x123456789abcdef0, 0x123456789abcdef0));
        REQUIRE(uuid.to_string() == std::string("f0debc9a-7856-3412-f0de-bc9a78563412"));
        REQUIRE(uuid == OTSLibrary::Uuid("f0debc9a-7856-3412-f0de-bc9a78563412"));
        REQUIRE_FALSE(uuid.empty());
        uuid.clear();
        REQUIRE(uuid.empty());
    }

    SECTION( "Comparison operators" ) {
        uuid = OTSLibrary::Uuid(std::make_pair(0,1));
        SECTION( "EQUAL uuids" ) {
            OTSLibrary::Uuid uuidEqual = OTSLibrary::Uuid(std::make_pair(0,1));
            REQUIRE(uuid == uuidEqual);
            REQUIRE_FALSE(uuid != uuidEqual );
            REQUIRE(uuid <= uuidEqual);
            REQUIRE(uuid >= uuidEqual);
        }

        SECTION( "NOT EQUAL uuids" ) {
            OTSLibrary::Uuid uuidBigger = OTSLibrary::Uuid(std::make_pair(1,0));
            REQUIRE_FALSE(uuid == uuidBigger);
            REQUIRE(uuid != uuidBigger );
            REQUIRE(uuid < uuidBigger);
            REQUIRE(uuidBigger > uuid);
            REQUIRE(uuid <= uuidBigger);
            REQUIRE(uuidBigger >= uuid);
            REQUIRE_FALSE(uuid >= uuidBigger);
            REQUIRE_FALSE(uuidBigger <= uuid);
        }
    }
}

