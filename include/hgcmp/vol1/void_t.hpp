/*
 * void_t.hpp
 *
 *  Created on: 3 февр. 2017 г.
 *      Author: sergey.fedorov
 */

#ifndef HGCMP_VOL1_VOID_T_HPP_
#define HGCMP_VOL1_VOID_T_HPP_

namespace hgcmp {
template < typename ... T >
struct make_void_t { using type = void; };

template < typename ... T >
using void_t = typename make_void_t<T...>::type;
}  /* namespace hgcmp */

#endif /* HGCMP_VOL1_VOID_T_HPP_ */
