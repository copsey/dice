#ifndef DICE_UTIL_REGEX
#define DICE_UTIL_REGEX

#include <regex>
#include <string_view>

namespace dice {
	namespace util {
        // Support for std::string_view in std::regex.

        using sv_match = std::match_results<std::string_view::const_iterator>;
		using sv_sub_match = std::sub_match<std::string_view::const_iterator>;

        inline bool regex_match(std::string_view sv, sv_match & m, std::regex const& e,
            std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
        {
            return std::regex_match(sv.begin(), sv.end(), m, e, flags);
        }

        inline std::string_view to_string_view(sv_sub_match const& m) {
            auto begin = m.first;
            auto length = static_cast<std::string_view::size_type>(m.length());
            
            return std::string_view{begin, length};
        }
	}
}

#endif
