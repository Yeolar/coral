
#include <folly/Portability.h>

#if FOLLY_X64 || defined(__i386__)
#include <stdint.h>
#include <x86intrin.h>

namespace folly {
namespace detail {

extern const __m128i groupVarintSSEMasks[] = {
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffffff03ffffff02)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffffff04ffffff03)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffffff05ffffff04)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffffff06ffffff05)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffffff04ffffff03)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffffff05ffffff04)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffffff06ffffff05)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffffff07ffffff06)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffffff05ffffff04)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffffff06ffffff05)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffffff07ffffff06)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffffff08ffffff07)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffffff06ffffff05)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffffff07ffffff06)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffffff08ffffff07)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffffff09ffffff08)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffffff04ffff0302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffffff05ffff0403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffffff06ffff0504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffffff07ffff0605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffffff05ffff0403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffffff06ffff0504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffffff07ffff0605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffffff08ffff0706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffffff06ffff0504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffffff07ffff0605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffffff08ffff0706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffffff09ffff0807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffffff07ffff0605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffffff08ffff0706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffffff09ffff0807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffffff0affff0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffffff05ff040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffffff06ff050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffffff07ff060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffffff08ff070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffffff06ff050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffffff07ff060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffffff08ff070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffffff09ff080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffffff07ff060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffffff08ff070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffffff09ff080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffffff0aff090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffffff08ff070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffffff09ff080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffffff0aff090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffffff0bff0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffffff0605040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffffff0706050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffffff0807060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffffff0908070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffffff0706050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffffff0807060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffffff0908070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffffff0a09080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffffff0807060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffffff0908070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffffff0a09080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffffff0b0a090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffffff0908070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffffff0a09080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffffff0b0a090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffffff0c0b0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffff0403ffffff02)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffff0504ffffff03)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffff0605ffffff04)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffff0706ffffff05)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffff0504ffffff03)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffff0605ffffff04)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffff0706ffffff05)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffff0807ffffff06)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffff0605ffffff04)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffff0706ffffff05)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffff0807ffffff06)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffff0908ffffff07)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffff0706ffffff05)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffff0807ffffff06)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffff0908ffffff07)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffff0a09ffffff08)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffff0504ffff0302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffff0605ffff0403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffff0706ffff0504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffff0807ffff0605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffff0605ffff0403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffff0706ffff0504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffff0807ffff0605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffff0908ffff0706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffff0706ffff0504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffff0807ffff0605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffff0908ffff0706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffff0a09ffff0807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffff0807ffff0605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffff0908ffff0706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffff0a09ffff0807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffff0b0affff0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffff0605ff040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffff0706ff050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffff0807ff060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffff0908ff070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffff0706ff050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffff0807ff060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffff0908ff070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffff0a09ff080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffff0807ff060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffff0908ff070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffff0a09ff080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffff0b0aff090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffff0908ff070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffff0a09ff080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffff0b0aff090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffff0c0bff0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xffff070605040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xffff080706050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xffff090807060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xffff0a0908070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xffff080706050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xffff090807060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xffff0a0908070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xffff0b0a09080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xffff090807060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xffff0a0908070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xffff0b0a09080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xffff0c0b0a090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xffff0a0908070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xffff0b0a09080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xffff0c0b0a090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xffff0d0c0b0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xff050403ffffff02)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xff060504ffffff03)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xff070605ffffff04)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xff080706ffffff05)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xff060504ffffff03)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xff070605ffffff04)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xff080706ffffff05)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xff090807ffffff06)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xff070605ffffff04)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xff080706ffffff05)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xff090807ffffff06)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xff0a0908ffffff07)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xff080706ffffff05)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xff090807ffffff06)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xff0a0908ffffff07)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xff0b0a09ffffff08)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xff060504ffff0302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xff070605ffff0403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xff080706ffff0504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xff090807ffff0605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xff070605ffff0403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xff080706ffff0504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xff090807ffff0605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xff0a0908ffff0706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xff080706ffff0504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xff090807ffff0605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xff0a0908ffff0706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xff0b0a09ffff0807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xff090807ffff0605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xff0a0908ffff0706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xff0b0a09ffff0807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xff0c0b0affff0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xff070605ff040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xff080706ff050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xff090807ff060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xff0a0908ff070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xff080706ff050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xff090807ff060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xff0a0908ff070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xff0b0a09ff080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xff090807ff060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xff0a0908ff070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xff0b0a09ff080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xff0c0b0aff090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xff0a0908ff070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xff0b0a09ff080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xff0c0b0aff090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xff0d0c0bff0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0xff08070605040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0xff09080706050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0xff0a090807060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0xff0b0a0908070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0xff09080706050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0xff0a090807060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0xff0b0a0908070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0xff0c0b0a09080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0xff0a090807060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0xff0b0a0908070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0xff0c0b0a09080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0xff0d0c0b0a090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0xff0b0a0908070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0xff0c0b0a09080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0xff0d0c0b0a090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0xff0e0d0c0b0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0x06050403ffffff02)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0x07060504ffffff03)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0x08070605ffffff04)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0x09080706ffffff05)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0x07060504ffffff03)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0x08070605ffffff04)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0x09080706ffffff05)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0x0a090807ffffff06)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0x08070605ffffff04)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0x09080706ffffff05)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0x0a090807ffffff06)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0x0b0a0908ffffff07)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0x09080706ffffff05)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0x0a090807ffffff06)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0x0b0a0908ffffff07)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0x0c0b0a09ffffff08)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0x07060504ffff0302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0x08070605ffff0403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0x09080706ffff0504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0x0a090807ffff0605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0x08070605ffff0403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0x09080706ffff0504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0x0a090807ffff0605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0x0b0a0908ffff0706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0x09080706ffff0504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0x0a090807ffff0605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0x0b0a0908ffff0706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0x0c0b0a09ffff0807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0x0a090807ffff0605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0x0b0a0908ffff0706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0x0c0b0a09ffff0807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0x0d0c0b0affff0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0x08070605ff040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0x09080706ff050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0x0a090807ff060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0x0b0a0908ff070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0x09080706ff050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0x0a090807ff060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0x0b0a0908ff070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0x0c0b0a09ff080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0x0a090807ff060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0x0b0a0908ff070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0x0c0b0a09ff080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0x0d0c0b0aff090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0x0b0a0908ff070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0x0c0b0a09ff080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0x0d0c0b0aff090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0x0e0d0c0bff0a0908)},
  {static_cast<int64_t>(0xffffff01ffffff00), static_cast<int64_t>(0x0908070605040302)},
  {static_cast<int64_t>(0xffffff02ffff0100), static_cast<int64_t>(0x0a09080706050403)},
  {static_cast<int64_t>(0xffffff03ff020100), static_cast<int64_t>(0x0b0a090807060504)},
  {static_cast<int64_t>(0xffffff0403020100), static_cast<int64_t>(0x0c0b0a0908070605)},
  {static_cast<int64_t>(0xffff0201ffffff00), static_cast<int64_t>(0x0a09080706050403)},
  {static_cast<int64_t>(0xffff0302ffff0100), static_cast<int64_t>(0x0b0a090807060504)},
  {static_cast<int64_t>(0xffff0403ff020100), static_cast<int64_t>(0x0c0b0a0908070605)},
  {static_cast<int64_t>(0xffff050403020100), static_cast<int64_t>(0x0d0c0b0a09080706)},
  {static_cast<int64_t>(0xff030201ffffff00), static_cast<int64_t>(0x0b0a090807060504)},
  {static_cast<int64_t>(0xff040302ffff0100), static_cast<int64_t>(0x0c0b0a0908070605)},
  {static_cast<int64_t>(0xff050403ff020100), static_cast<int64_t>(0x0d0c0b0a09080706)},
  {static_cast<int64_t>(0xff06050403020100), static_cast<int64_t>(0x0e0d0c0b0a090807)},
  {static_cast<int64_t>(0x04030201ffffff00), static_cast<int64_t>(0x0c0b0a0908070605)},
  {static_cast<int64_t>(0x05040302ffff0100), static_cast<int64_t>(0x0d0c0b0a09080706)},
  {static_cast<int64_t>(0x06050403ff020100), static_cast<int64_t>(0x0e0d0c0b0a090807)},
  {static_cast<int64_t>(0x0706050403020100), static_cast<int64_t>(0x0f0e0d0c0b0a0908)},
};

extern const uint8_t groupVarintLengths[] = {
  5,
  6,
  7,
  8,
  6,
  7,
  8,
  9,
  7,
  8,
  9,
  10,
  8,
  9,
  10,
  11,
  6,
  7,
  8,
  9,
  7,
  8,
  9,
  10,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  7,
  8,
  9,
  10,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  6,
  7,
  8,
  9,
  7,
  8,
  9,
  10,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  7,
  8,
  9,
  10,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  12,
  13,
  14,
  15,
  7,
  8,
  9,
  10,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  12,
  13,
  14,
  15,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  12,
  13,
  14,
  15,
  13,
  14,
  15,
  16,
  8,
  9,
  10,
  11,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  9,
  10,
  11,
  12,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  12,
  13,
  14,
  15,
  10,
  11,
  12,
  13,
  11,
  12,
  13,
  14,
  12,
  13,
  14,
  15,
  13,
  14,
  15,
  16,
  11,
  12,
  13,
  14,
  12,
  13,
  14,
  15,
  13,
  14,
  15,
  16,
  14,
  15,
  16,
  17,

};

}  // namespace detail
}  // namespace folly
#endif /* FOLLY_X64 || defined(__i386__) */
