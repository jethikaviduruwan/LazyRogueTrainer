#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <cassert>

namespace LRT {

    // Type aliases
    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using i8  = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    using f32 = float;
    using f64 = double;

    // Smart pointer aliases
    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;

    template<typename T, typename... Args>
    constexpr Unique<T> MakeUnique(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    constexpr Shared<T> MakeShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    // Entity ID type
    using EntityID = u64;
    constexpr EntityID NullEntity = 0;

    // Component type ID
    using ComponentTypeID = u32;

} // namespace LRT

// Assertion macros
#ifdef LRT_DEBUG
    #define LRT_ASSERT(expr) assert(expr)
    #define LRT_ASSERT_MSG(expr, msg) assert((expr) && (msg))
#else
    #define LRT_ASSERT(expr) ((void)0)
    #define LRT_ASSERT_MSG(expr, msg) ((void)0)
#endif

#define LRT_NON_COPYABLE(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;

#define LRT_NON_MOVABLE(ClassName) \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete;


