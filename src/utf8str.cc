#include <utf8str.hh>

#include <cstring>

namespace utf8
{

unsigned int char_size(unsigned char first_byte)
{
    if (first_byte >> 7 == 0) {
        return 1;
    }
    if (first_byte >> 5 == 0b110) {
        return 2;
    }
    if (first_byte >> 4 == 0b1110) {
        return 3;
    }
    if (first_byte >> 3 == 0b11110) {
        return 4;
    }
    // TODO: return error.
    return 0;
}

str::str() : buff(nullptr), len(0)
{
}

str::str(const char* s)
{
    auto s_len = strlen(s);
    this->buff = new unsigned char[s_len];
    memcpy(this->buff, s, s_len);
    this->len = s_len;
}

const unsigned char* str::data() const noexcept
{
    return this->buff;
}

size_t str::size() const
{
    return this->len;
}

str_iterator str::begin() const noexcept
{
    return str_iterator(*this);
}

str_iterator str::end() const noexcept
{
    return str_iterator(*this, true);
}

str_iterator::str_iterator(const str& str_, bool end) noexcept : str_(str_),
    str_offset(0), past_end_(false)
{
    if (end) {
        this->str_offset = str_.size();
        this->past_end_ = true;
    }
}

bool str_iterator::past_end() const noexcept
{
    return this->past_end_;
}

unsigned char byten_value(unsigned char b)
{
    return b & 0x3F;
}

uint32_t str_iterator::operator*() noexcept
{
    const unsigned char* buff = &this->str_.data()[this->str_offset];
    auto byte1 = buff[0];
    auto char_len = char_size(byte1);
    if (char_len == 1) {
        return byte1;
    }

    uint32_t char_code = byte1 & (0xFF >> (char_len + 1));
    for (auto i = 1u; i < char_len; ++i) {
        char_code <<= 6;
        char_code |= byten_value(buff[i]);
    }
    return char_code;
}

str_iterator& str_iterator::operator++() noexcept
{
    if (!this->past_end()) {
        this->str_offset += char_size(this->str_.data()[this->str_offset]);
        this->past_end_ = this->str_offset >= this->str_.size();
    }
    return *this;
}

bool str_iterator::operator==(const str_iterator& rhs) const noexcept
{
    return this->str_.data() == rhs.str_.data() &&
        this->str_offset == rhs.str_offset;
}

bool str_iterator::operator!=(const str_iterator& rhs) const noexcept
{
    return !(*this == rhs);
}

}
