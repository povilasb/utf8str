#pragma once

#include <cstddef>
#include <cstdint>

namespace utf8
{

/**
 * @return UTF-8 character size in bytes.
 */
unsigned int char_size(unsigned char first_byte);

class str_iterator;

class str
{
private:
    unsigned char* buff;
    size_t len;

public:
    str();
    str(const char* s);

    const unsigned char* data() const noexcept;
    size_t size() const;
    str_iterator begin() const noexcept;
    str_iterator end() const noexcept;
};

class str_iterator
{
private:
    const str& str_;
    size_t str_offset;
    bool past_end_;

public:
    str_iterator(const str& str_, bool end=false) noexcept;

    bool past_end() const noexcept;

    str_iterator& operator++() noexcept;
    /**
     * Compares whether the iterators point to the same character in the
     * same string.
     */
    bool operator==(const str_iterator& rhs) const noexcept;
    bool operator!=(const str_iterator& rhs) const noexcept;
    uint32_t operator*() noexcept;
};

} // namespace utf8
