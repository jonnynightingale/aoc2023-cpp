#include <cstdint>
#include <iostream>
#include <optional>

using u64 = std::uint64_t;
auto &in = std::cin;

constexpr auto to_uint( char c ) -> u64 {
    return ( c - '0' );
}

constexpr auto is_digit( char c ) -> bool {
    return ( c >= '0' ) && ( c <= '9' );
}

auto process_line() -> std::optional< u64 > {
    char c1 = in.get();
    if ( in.eof() ) {
        return {};
    }
    while ( !is_digit( c1 ) ) {
        c1 = in.get();
    }
    char c2 = c1;
    for ( ;; ) {
        char temp = in.get();
        if ( is_digit( temp ) ) {
            c2 = temp;
        } else if ( temp == '\n' ) {
            break;
        }
    }
    return to_uint( c1 ) * u64( 10 ) + to_uint( c2 );
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
