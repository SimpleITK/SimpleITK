/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef sitk_typelist_h_
#define sitk_typelist_h_

#include <tuple>
#include <type_traits>
#include <algorithm>

namespace typelist2
{

/** \struct typelist
 * \brief an non-instantiable holder of variadic template parameters to represent a list of types
 *
 * Can be used as a type and not an object. It enables complex compile-time manipulation of sets of types.
 */
template <typename... Ts>
struct typelist;

/** \brief Provides access to the number of types in a typelist.
 *
 * Uses std::integral_constant to define member type "value_type" and member constant "value".
 */
template <typename Typelist>
struct length;
template <typename... Ts>
struct length<typelist<Ts...>> : std::integral_constant<int, sizeof...(Ts)>
{};


/** \brief Provides access to the Nth type in the typelist
 *
 * Example:
 * \code
 * using MyTypeList = typelist<int, char, short>;
 * int len = type_at<MyTypeList>::type;
 * \endcode
 *
 * Defines the member type "type" for the Nth element in the typelist.
 */
template <typename Typelist, size_t N>
struct type_at;
template <typename... Ts, size_t N>
struct type_at<typelist<Ts...>, N> : std::tuple_element<N, std::tuple<Ts...>>
{};


/** \brief Joins a typelist and additional types or typelists into a single typelist
 *
 * Example 1:
 * \code
 * using MyTypeList1 = typelist2::typelist<int, char>;
 * using MyTypeList2 = typelist2::typelist<short, unsigned short>;
 * using MyCombinedList = typelist2::append<MyTypeList1, MyTypeList2>::type;
 * \endcode
 *
 * Example 2:
 * \code
 * using MyTypeList1 = typelist2::typelist<int, char>;
 * using MyAddedTypeList = typelist2::append<MyTypeList1, short, unsigned short>::type;
 * \endcode
 *
 * The member type `type` definition is a new typelist with the additional types appended.
 */
template <typename... Typelist>
struct append;
template <typename... Ts, typename... Us>
struct append<typelist<Ts...>, Us...>
{
  using type = typelist<Ts..., Us...>;
};
template <typename... Ts, typename... Us>
struct append<typelist<Ts...>, typelist<Us...>>
{
  using type = typelist<Ts..., Us...>;
};
template <typename... Ts, typename... Us, typename... Vs>
struct append<typelist<Ts...>, typelist<Us...>, typelist<Vs...>>
{
  using type = typelist<Ts..., Us..., Vs...>;
};
template <typename... Ts, typename... Us, typename... Vs, typename... Ws>
struct append<typelist<Ts...>, typelist<Us...>, typelist<Vs...>, typelist<Ws...>>
{
  using type = typelist<Ts..., Us..., Vs..., Ws...>;
};

/**\class index_of
 * \brief Finds the first index of a type in a typelist
 *
 * Example:
 * \code
 * using MyTypeList = typelist2::typelist<int, char>;
 * int index = typelist2::index_of<MyTypeList, int>::value;
 * \endcode
 *
 * Uses std::integral_constant to define a member constant "value".
 */
template <typename Typelist, typename T>
struct index_of;
template <typename T>
struct index_of<typelist<>, T> : std::integral_constant<int, -1>
{};
template <typename... Ts, typename T>
struct index_of<typelist<T, Ts...>, T> : std::integral_constant<int, 0>
{};
template <typename t0, typename... Ts, typename T>
struct index_of<typelist<t0, Ts...>, T>
  : std::integral_constant<int,
                           index_of<typelist<Ts...>, T>::value == -1 ? -1 : 1 + index_of<typelist<Ts...>, T>::value>
{};

/**\class has_type
 * \brief Queries the typelist for a type
 *
 * Example:
 * \code
 * using MyTypeList = typelist2::typelist<int, char>;
 * bool query = typelist2::has_type<MyTypeList, short>::value;
 * \endcode
 *
 * Uses std::integral_constant to define member type "value_type" and member constant "value".
 */
template <typename Typelist, typename T>
struct has_type;
template <typename... Ts, typename T>
struct has_type<typelist<Ts...>, T> : std::integral_constant<bool, ((std::is_same<Ts, T>::value) || ...)>
{};

/**\class visit
 * \brief Runs a templated predicate on each type in the typelist
 *
 * \code
 * struct Predicate
 * {
 *  template<class TType>
 *  void operator()( void ) const
 *     { std::cout << typeid(TType).name() << std::endl; }
 * }
 *
 * using MyTypeList = typelist2::typelist<int, char>;
 * typelist2::visit<MyTypeList> visitor;
 * visitor( Predicate() );
 *
 * \endcode
 *
 */
template <typename Typelist>
struct visit;
template <typename... Ts>
struct visit<typelist<Ts...>>
{

  template <typename Predicate>
  void
  operator()(Predicate && visitor)
  {
    ((visitor.CLANG_TEMPLATE operator()<Ts>()), ...);
  };
};


/**\class dual_visit
 * \brief Runs a templated predicate on each combination of the types
 * on the two lists
 *
 * \code
 * struct Predicate
 * {
 *  template<class TType1, TType2>
 *  void operator()( void ) const
 *     { std::cout << typeid(TType1).name() << " " << typeid(TType2.name() << std::endl; }
 * }
 *
 * using MyTypeList = typelist2::typelist<int, char>;
 * typelist2::dual_visit<MyTypeList, MyTypeList> visitor;
 * visitor( Predicate() );
 *
 * \endcode
 *
 */
template <typename TypelistLeft, typename TypelistRight>
struct dual_visit;
template <typename... Tls, typename... Trs>
struct dual_visit<typelist<Tls...>, typelist<Trs...>>
{
  template <typename Visitor>
  void
  operator()(Visitor && visitor) const
  {
    ((right_visit<Tls>(visitor)), ...);
  }

private:
  template <typename tl, typename Predicate>
  static int
  right_visit(Predicate && visitor)
  {
    ((visitor.CLANG_TEMPLATE operator()<tl, Trs>()), ...);
    return 0;
  }
};


} // namespace typelist2
#endif // typelist_h_
