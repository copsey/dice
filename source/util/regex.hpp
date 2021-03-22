#ifndef DICE_UTIL_REGEX
#define DICE_UTIL_REGEX

#include <regex>
#include <string_view>

namespace dice {
	namespace util {
		// Support for using std::string_view with std::regex.

		using sv_match = std::match_results<std::string_view::const_iterator>;
		using sv_sub_match = std::sub_match<std::string_view::const_iterator>;

		inline bool regex_match(std::string_view str_view, std::regex const& rgx,
			std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
		{
			return std::regex_match(str_view.begin(), str_view.end(), rgx, flags);
		}

		inline bool regex_match(std::string_view str_view, sv_match & match, std::regex const& rgx,
			std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
		{
			return std::regex_match(str_view.begin(), str_view.end(), match, rgx, flags);
		}

		inline bool regex_search(std::string_view str_view, std::regex const& rgx,
			std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
		{
			return std::regex_search(str_view.begin(), str_view.end(), rgx, flags);
		}

		inline bool regex_search(std::string_view str_view, sv_match & match, std::regex const& rgx,
			std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
		{
			return std::regex_search(str_view.begin(), str_view.end(), match, rgx, flags);
		}

		template <typename Iter>
		std::string_view as_string_view(std::sub_match<Iter> const& match)
		{
			// Make sure the iterator returns chars.
			static_assert(std::is_same_v<typename std::iterator_traits<Iter>::value_type, char>);

			auto begin = std::addressof(*match.first);
			auto length = static_cast<std::string_view::size_type>(match.length());

			return std::string_view{begin, length};
		}
	}
}

#endif
