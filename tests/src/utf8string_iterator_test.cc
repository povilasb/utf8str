#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <utf8str.hh>

SCENARIO("characters might be dereferenced", "[str_iterator]") {
    WHEN("iterator is just constructed") {
        utf8::str_iterator it("abc");

        THEN("*it returns first character") {
            REQUIRE(*it == 'a');
        }
    }

    WHEN("current character is 2 bytes long") {
        utf8::str_iterator it("ča");

        THEN("*it returns decoded character") {
            REQUIRE(*it == 0x10D);
        }
    }

    WHEN("current character is 3 bytes long") {
        // NOTE: not all editors might be able to display the character below.
        utf8::str_iterator it("王");

        THEN("*it returns decoded character") {
            REQUIRE(*it == 0x738B);
        }
    }

    WHEN("current character is 4 bytes long") {
        utf8::str_iterator it("\xF7\xBF\xBF\xBF");

        THEN("*it returns decoded character") {
            REQUIRE(*it == 0x1FFFFF);
        }
    }
}

SCENARIO("iterator can be advanced forward") {
    GIVEN("ASCII string") {
        utf8::str_iterator it("abc");

        WHEN("iterator is increased") {
            ++it;

            THEN("it points to next symbol") {
                REQUIRE(*it == 'b');
            }
        }

        GIVEN("iterator points to last symbol") {
            utf8::str_iterator it("a");

            WHEN("it is incremented") {
                ++it;

                THEN("iterator is aware that it points past the end") {
                    REQUIRE(it.past_end());
                }
            }
        }

    }

    GIVEN("UTF-8 string") {
        utf8::str_iterator it("čabc");

        WHEN("iterator is increased") {
            ++it;

            THEN("it points to next symbol") {
                REQUIRE(*it == 'a');
            }
        }
    }
}

SCENARIO("iterators can be compared") {
    GIVEN("2 iterators") {
        utf8::str s("abc");
        utf8::str_iterator it1(s);
        utf8::str_iterator it2(s);

        WHEN("they point to the same string") {
            THEN("iterators are equal") {
                REQUIRE(it1 == it2);
            }
        }

        WHEN("one iterator points to different string character") {
            ++it2;

            THEN("iterators are not equal") {
                REQUIRE(!(it1 == it2));
            }
        }
    }
}

SCENARIO("end iterators can be created") {
    WHEN("constructor argument 'end' is true") {
        utf8::str_iterator it("abc", true);

        THEN("iterator points to past the end") {
            REQUIRE(it.past_end());
        }
    }
}
