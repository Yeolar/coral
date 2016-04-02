/*
 * Copyright 2015 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// @author: Andrei Alexandrescu

#ifndef FOLLY_BASE_TRAITS_H_
#define FOLLY_BASE_TRAITS_H_

#include <memory>
#include <limits>
#include <type_traits>
#include <functional>

#include <folly/Portability.h>

// libc++ doesn't provide this header, nor does msvc
#ifdef FOLLY_HAVE_BITS_CXXCONFIG_H
// This file appears in two locations: inside fbcode and in the
// libstdc++ source code (when embedding fbstring as std::string).
// To aid in this schizophrenic use, two macros are defined in
// c++config.h:
//   _LIBSTDCXX_FBSTRING - Set inside libstdc++.  This is useful to
//      gate use inside fbcode v. libstdc++
#include <bits/c++config.h>
#endif

#include <boost/type_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/not.hpp>

namespace folly {

/**
 * IsRelocatable<T>::value describes the ability of moving around
 * memory a value of type T by using memcpy (as opposed to the
 * conservative approach of calling the copy constructor and then
 * destroying the old temporary. Essentially for a relocatable type,
 * the following two sequences of code should be semantically
 * equivalent:
 *
 * void move1(T * from, T * to) {
 *   new(to) T(from);
 *   (*from).~T();
 * }
 *
 * void move2(T * from, T * to) {
 *   memcpy(to, from, sizeof(T));
 * }
 *
 * Most C++ types are relocatable; the ones that aren't would include
 * internal pointers or (very rarely) would need to update remote
 * pointers to pointers tracking them. All C++ primitive types and
 * type constructors are relocatable.
 *
 * This property can be used in a variety of optimizations. Currently
 * fbvector uses this property intensively.
 *
 * The default conservatively assumes the type is not
 * relocatable. Several specializations are defined for known
 * types. You may want to add your own specializations. Do so in
 * namespace folly and make sure you keep the specialization of
 * IsRelocatable<SomeStruct> in the same header as SomeStruct.
 *
 * You may also declare a type to be relocatable by including
 *    `typedef std::true_type IsRelocatable;`
 * in the class header.
 *
 * It may be unset in a base class by overriding the typedef to false_type.
 */
/*
 * IsTriviallyCopyable describes the value semantics property. C++11 contains
 * the type trait is_trivially_copyable; however, it is not yet implemented
 * in gcc (as of 4.7.1), and the user may wish to specify otherwise.
 */
/*
 * IsZeroInitializable describes the property that default construction is the
 * same as memset(dst, 0, sizeof(T)).
 */

namespace traits_detail {

#define FOLLY_HAS_TRUE_XXX(name)                          \
  BOOST_MPL_HAS_XXX_TRAIT_DEF(name);                      \
  template <class T> struct name ## _is_true              \
    : std::is_same<typename T::name, std::true_type> {};  \
  template <class T> struct has_true_ ## name             \
    : std::conditional<                                   \
        has_ ## name <T>::value,                          \
        name ## _is_true<T>,                              \
        std::false_type                                   \
      >:: type {};

FOLLY_HAS_TRUE_XXX(IsRelocatable)
FOLLY_HAS_TRUE_XXX(IsZeroInitializable)
FOLLY_HAS_TRUE_XXX(IsTriviallyCopyable)

#undef FOLLY_HAS_TRUE_XXX
}

template <class T> struct IsTriviallyCopyable
  : std::integral_constant<bool,
      !std::is_class<T>::value ||
      // TODO: add alternate clause is_trivially_copyable, when available
      traits_detail::has_true_IsTriviallyCopyable<T>::value
    > {};

template <class T> struct IsRelocatable
  : std::integral_constant<bool,
      !std::is_class<T>::value ||
      // TODO add this line (and some tests for it) when we upgrade to gcc 4.7
      //std::is_trivially_move_constructible<T>::value ||
      IsTriviallyCopyable<T>::value ||
      traits_detail::has_true_IsRelocatable<T>::value
    > {};

template <class T> struct IsZeroInitializable
  : std::integral_constant<bool,
      !std::is_class<T>::value ||
      traits_detail::has_true_IsZeroInitializable<T>::value
    > {};

} // namespace folly

/**
 * Use this macro ONLY inside namespace folly. When using it with a
 * regular type, use it like this:
 *
 * // Make sure you're at namespace ::folly scope
 * template<> FOLLY_ASSUME_RELOCATABLE(MyType)
 *
 * When using it with a template type, use it like this:
 *
 * // Make sure you're at namespace ::folly scope
 * template<class T1, class T2>
 * FOLLY_ASSUME_RELOCATABLE(MyType<T1, T2>)
 */
#define FOLLY_ASSUME_RELOCATABLE(...) \
  struct IsRelocatable<  __VA_ARGS__ > : std::true_type {};

namespace folly {

// STL commonly-used types
template <class T, class U>
struct IsRelocatable<  std::pair<T, U> >
    : ::boost::mpl::and_< IsRelocatable<T>, IsRelocatable<U> > {};

// Is T one of T1, T2, ..., Tn?
template <class T, class... Ts>
struct IsOneOf {
  enum { value = false };
};

template <class T, class T1, class... Ts>
struct IsOneOf<T, T1, Ts...> {
  enum { value = std::is_same<T, T1>::value || IsOneOf<T, Ts...>::value };
};

/*
 * Complementary type traits for integral comparisons.
 *
 * For instance, `if(x < 0)` yields an error in clang for unsigned types
 *  when -Werror is used due to -Wtautological-compare
 *
 *
 * @author: Marcelo Juchem <marcelo@fb.com>
 */

namespace detail {

template <typename T, bool>
struct is_negative_impl {
  constexpr static bool check(T x) { return x < 0; }
};

template <typename T>
struct is_negative_impl<T, false> {
  constexpr static bool check(T) { return false; }
};

// folly::to integral specializations can end up generating code
// inside what are really static ifs (not executed because of the templated
// types) that violate -Wsign-compare so suppress them in order to not prevent
// all calling code from using it.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

template <typename RHS, RHS rhs, typename LHS>
bool less_than_impl(
  typename std::enable_if<
    (rhs <= std::numeric_limits<LHS>::max()
      && rhs > std::numeric_limits<LHS>::min()),
    LHS
  >::type const lhs
) {
  return lhs < rhs;
}

template <typename RHS, RHS rhs, typename LHS>
bool less_than_impl(
  typename std::enable_if<
    (rhs > std::numeric_limits<LHS>::max()),
    LHS
  >::type const
) {
  return true;
}

template <typename RHS, RHS rhs, typename LHS>
bool less_than_impl(
  typename std::enable_if<
    (rhs <= std::numeric_limits<LHS>::min()),
    LHS
  >::type const
) {
  return false;
}

#pragma GCC diagnostic pop

template <typename RHS, RHS rhs, typename LHS>
bool greater_than_impl(
  typename std::enable_if<
    (rhs <= std::numeric_limits<LHS>::max()
      && rhs >= std::numeric_limits<LHS>::min()),
    LHS
  >::type const lhs
) {
  return lhs > rhs;
}

template <typename RHS, RHS rhs, typename LHS>
bool greater_than_impl(
  typename std::enable_if<
    (rhs > std::numeric_limits<LHS>::max()),
    LHS
  >::type const
) {
  return false;
}

template <typename RHS, RHS rhs, typename LHS>
bool greater_than_impl(
  typename std::enable_if<
    (rhs < std::numeric_limits<LHS>::min()),
    LHS
  >::type const
) {
  return true;
}

} // namespace detail {

// same as `x < 0`
template <typename T>
constexpr bool is_negative(T x) {
  return folly::detail::is_negative_impl<T, std::is_signed<T>::value>::check(x);
}

// same as `x <= 0`
template <typename T>
constexpr bool is_non_positive(T x) { return !x || folly::is_negative(x); }

// same as `x > 0`
template <typename T>
constexpr bool is_positive(T x) { return !is_non_positive(x); }

// same as `x >= 0`
template <typename T>
constexpr bool is_non_negative(T x) {
  return !x || is_positive(x);
}

template <typename RHS, RHS rhs, typename LHS>
bool less_than(LHS const lhs) {
  return detail::less_than_impl<
    RHS, rhs, typename std::remove_reference<LHS>::type
  >(lhs);
}

template <typename RHS, RHS rhs, typename LHS>
bool greater_than(LHS const lhs) {
  return detail::greater_than_impl<
    RHS, rhs, typename std::remove_reference<LHS>::type
  >(lhs);
}

} // namespace folly

#define FOLLY_CREATE_HAS_MEMBER_TYPE_TRAITS(classname, type_name) \
  template <typename T> \
  struct classname { \
    template <typename C> \
    constexpr static bool test(typename C::type_name*) { return true; } \
    template <typename> \
    constexpr static bool test(...) { return false; } \
    constexpr static bool value = test<T>(nullptr); \
  }

#define FOLLY_CREATE_HAS_MEMBER_FN_TRAITS_IMPL(classname, func_name, cv_qual) \
  template <typename TTheClass_, typename RTheReturn_, typename... TTheArgs_> \
  class classname<TTheClass_, RTheReturn_(TTheArgs_...) cv_qual> { \
    template < \
      typename UTheClass_, RTheReturn_ (UTheClass_::*)(TTheArgs_...) cv_qual \
    > struct sfinae {}; \
    template <typename UTheClass_> \
    constexpr static bool test(sfinae<UTheClass_, &UTheClass_::func_name>*) \
    { return true; } \
    template <typename> \
    constexpr static bool test(...) { return false; } \
  public: \
    constexpr static bool value = test<TTheClass_>(nullptr); \
  }

/*
 * The FOLLY_CREATE_HAS_MEMBER_FN_TRAITS is used to create traits
 * classes that check for the existence of a member function with
 * a given name and signature. It currently does not support
 * checking for inherited members.
 *
 * Such classes receive two template parameters: the class to be checked
 * and the signature of the member function. A static boolean field
 * named `value` (which is also constexpr) tells whether such member
 * function exists.
 *
 * Each traits class created is bound only to the member name, not to
 * its signature nor to the type of the class containing it.
 *
 * Say you need to know if a given class has a member function named
 * `test` with the following signature:
 *
 *    int test() const;
 *
 * You'd need this macro to create a traits class to check for a member
 * named `test`, and then use this traits class to check for the signature:
 *
 * namespace {
 *
 * FOLLY_CREATE_HAS_MEMBER_FN_TRAITS(has_test_traits, test);
 *
 * } // unnamed-namespace
 *
 * void some_func() {
 *   cout << "Does class Foo have a member int test() const? "
 *     << boolalpha << has_test_traits<Foo, int() const>::value;
 * }
 *
 * You can use the same traits class to test for a completely different
 * signature, on a completely different class, as long as the member name
 * is the same:
 *
 * void some_func() {
 *   cout << "Does class Foo have a member int test()? "
 *     << boolalpha << has_test_traits<Foo, int()>::value;
 *   cout << "Does class Foo have a member int test() const? "
 *     << boolalpha << has_test_traits<Foo, int() const>::value;
 *   cout << "Does class Bar have a member double test(const string&, long)? "
 *     << boolalpha << has_test_traits<Bar, double(const string&, long)>::value;
 * }
 *
 * @author: Marcelo Juchem <marcelo@fb.com>
 */
#define FOLLY_CREATE_HAS_MEMBER_FN_TRAITS(classname, func_name) \
  template <typename, typename> class classname; \
  FOLLY_CREATE_HAS_MEMBER_FN_TRAITS_IMPL(classname, func_name, ); \
  FOLLY_CREATE_HAS_MEMBER_FN_TRAITS_IMPL(classname, func_name, const); \
  FOLLY_CREATE_HAS_MEMBER_FN_TRAITS_IMPL( \
      classname, func_name, /* nolint */ volatile); \
  FOLLY_CREATE_HAS_MEMBER_FN_TRAITS_IMPL( \
      classname, func_name, /* nolint */ volatile const)

#endif //FOLLY_BASE_TRAITS_H_