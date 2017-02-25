/*
 * is_numeric_metafunction.hpp
 *
 *  Created on: 2 февр. 2017 г.
 *      Author: sergey.fedorov
 */

#ifndef HGCMP_EXPERIMENTAL_IS_NUMERIC_METAFUNCTION_HPP_
#define HGCMP_EXPERIMENTAL_IS_NUMERIC_METAFUNCTION_HPP_

#include <type_traits>

namespace hgcmp {

template < typename T >
struct is_numeric_metafunction : ::std::false_type {};

template < typename T, T V>
struct is_numeric_metafunction< ::std::integral_constant<T, V> > : ::std::true_type {};

}  /* namespace hgcmp */


#endif /* HGCMP_EXPERIMENTAL_IS_NUMERIC_METAFUNCTION_HPP_ */
