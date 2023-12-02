#include <cstdint>
#include <iostream>
#include <optional>

using u64 = std::uint64_t;
using u8 = std::uint8_t;
auto &in = std::cin;

constexpr const char *numbers[] {
    nullptr,
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

u8 parser_state[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

constexpr auto reset_state() -> void {
    for ( int i = 1; i < 10; ++i ) {
        parser_state[ i ] = 0;
    }
}

constexpr auto to_uint( char c ) -> u64 {
    return ( c - '0' );
}

constexpr auto is_digit( char c ) -> bool {
    return ( c >= '0' ) && ( c <= '9' );
}

constexpr auto parse_character( char c ) -> std::optional< u64 > {
    if ( is_digit( c ) ) {
        reset_state();
        return to_uint( c );
    }
    u64 result = 0;
    for ( u64 i = 1; i < 10; ++i ) {
        const char *n = numbers[ i ];
        u8 &nstate = parser_state[ i ];
        if ( n[ nstate ] == c ) {
            if ( n[ ++nstate ] == '\0' ) {
                result = i;
            }
        } else if ( nstate > 0 ) {
            nstate = 0;
            --i;
        }
    }
    return ( result == 0 ) ? std::nullopt : std::optional< u64 >{ result };
}

auto process_line() -> std::optional< u64 > {
    reset_state();
    char c1 = in.get();
    if ( in.eof() ) {
        return {};
    }
    std::optional< u64 > d1 = parse_character( c1 );
    while ( !d1 ) {
        c1 = in.get();
        d1 = parse_character( c1 );
    }
    u64 d2 = d1.value();
    for ( ;; ) {
        char c = in.get();
        if ( c == '\n' ) {
            break;
        } else if ( auto temp = parse_character( c ) ) {
            d2 = temp.value();
        }
    }
    return d1.value() * u64( 10 ) + d2;
}

auto main() -> int {
    u64 total{ 0 };
    for ( ;; ) {
        std::optional< u64 > line_value = process_line();
        if ( line_value ) {
            total += line_value.value();
        } else {
            break;
        }
    }
    std::cout << total;
    return 0;
}
