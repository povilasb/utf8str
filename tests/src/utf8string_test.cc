#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <utf8str.hh>


SCENARIO("empty string can be constructed", "[utf8str]") {
    WHEN("constructor has no arguments") {
        utf8::str str;

        THEN("string length is 0") {
            REQUIRE(str.size() == 0);
        }
    }
}

SCENARIO("string can be constructed from string literal", "[utf8str]") {
    WHEN("constructor has ASCII string literal argument") {
        utf8::str str("abc");

        THEN("string length is the same as literal one") {
            REQUIRE(str.size() == 3);
        }
    }
}

SCENARIO("one can access UTF-8 string bytes") {
    WHEN("string is constructed with initial content"){
        utf8::str str(u8"š");

        THEN(".data() returns pointer to internal buffer") {
            const unsigned char* buff = str.data();
            REQUIRE(buff[0] == 0xC5);
            REQUIRE(buff[1] == 0xA1);
        }
    }
}

SCENARIO("one can iterate over string characters") {
    GIVEN("some string") {
        utf8::str str(u8"abč");

        WHEN("it's iterated") {
            std::vector<uint32_t> chars;
            for (auto c : str) {
                chars.push_back(c);
            }

            THEN("all characters are visited") {
                REQUIRE(chars[0] == 'a');
                REQUIRE(chars[1] == 'b');
                REQUIRE(chars[2] == 0x10D);
            }
        }
    }
}
