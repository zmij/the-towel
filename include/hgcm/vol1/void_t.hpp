/*
 * void_t.hpp
 *
 *  Created on: 3 февр. 2017 г.
 *      Author: sergey.fedorov
 */

#ifndef HGCM_VOL1_VOID_T_HPP_
#define HGCM_VOL1_VOID_T_HPP_

namespace hgcmp {
template < typename ... T >
struct make_void_t { using type = void; };

template < typename ... T >
using void_t = typename make_void_t<T...>::type;
}  /* namespace hgcmp */

#endif /* HGCM_VOL1_VOID_T_HPP_ */
