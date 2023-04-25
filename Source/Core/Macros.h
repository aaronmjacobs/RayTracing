#pragma once

#if defined(__clang__)
#  define PRAGMA_BEGIN_DISABLE_WARNINGS _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Weverything\"")
#  define PRAGMA_END_DISABLE_WARNINGS _Pragma("clang diagnostic pop")
#elif defined(__GNUC__) || defined(__GNUG__)
#  define PRAGMA_BEGIN_DISABLE_WARNINGS _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Weverything\"")
#  define PRAGMA_END_DISABLE_WARNINGS _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
#  define PRAGMA_BEGIN_DISABLE_WARNINGS __pragma(warning(push, 0))
#  define PRAGMA_END_DISABLE_WARNINGS __pragma(warning(pop))
#endif
