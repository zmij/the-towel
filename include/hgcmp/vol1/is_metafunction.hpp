/*
 * is_metafunction.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: zmij
 */

#ifndef HGCMP_VOL1_IS_METAFUNCTION_HPP_
#define HGCMP_VOL1_IS_METAFUNCTION_HPP_

#include <hgcmp/vol1/void_t.hpp>
#include <type_traits>

namespace hgcmp {
inline namespace first {
template < typename T >
class is_metafunction {
    template < typename U = T >
    static ::std::true_type test(typename U::type*);
    static ::std::false_type test(...);
public:
    using type = decltype(test(nullptr));
    static constexpr bool value = type::value;
};
}  /* namespace first */
namespace second {
template < typename T, typename = void_t<> >
struct is_metafunction : ::std::false_type {};

template < typename T >
struct is_metafunction<T, void_t<typename T::type>> : ::std::true_type {};

}  /* namespace second */
}  /* namespace hgcm */



#endif /* HGCMP_VOL1_IS_METAFUNCTION_HPP_ */
