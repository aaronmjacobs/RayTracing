#pragma once

#define PPK_ASSERT_DISABLE_STL // Reduce compile times

#include <ppk_assert.h>

#if defined(ASSERT)
#  error "ASSERT already defined"
#endif

#define ASSERT                PPK_ASSERT
#define ASSERT_WARNING        PPK_ASSERT_WARNING
#define ASSERT_DEBUG          PPK_ASSERT_DEBUG
#define ASSERT_ERROR          PPK_ASSERT_ERROR
#define ASSERT_FATAL          PPK_ASSERT_FATAL
#define ASSERT_CUSTOM         PPK_ASSERT_CUSTOM
#define ASSERT_USED           PPK_ASSERT_USED
#define ASSERT_USED_WARNING   PPK_ASSERT_USED_WARNING
#define ASSERT_USED_DEBUG     PPK_ASSERT_USED_DEBUG
#define ASSERT_USED_ERROR     PPK_ASSERT_USED_ERROR
#define ASSERT_USED_FATAL     PPK_ASSERT_USED_FATAL
#define ASSERT_USED_CUSTOM    PPK_ASSERT_USED_CUSTOM
