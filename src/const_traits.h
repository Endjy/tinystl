#ifndef _CONST_TRAITS_H_
#define _CONST_TRAITS_H_

namespace TinySTL{
    template<typename T, T v>
    struct intergral_constant {
        using value_type = T;
        using type       = intergral_constant<T, v>;

        static constexpr T value = v;
    };

    using _true_type = intergral_constant<bool, true>;
    using _false_type = intergral_constant<bool, false>;

    // 接受普通类型时继承 false_type ,此时其静态成员 value 为 false
    template<typename T>
    struct is_const: public _false_type { };

    // 偏特化使得接受 const 类型时继承 true_type，此时其静态成员 value 为 true
    template<typename T>
    struct is_const<const T>: public _true_type { };
}

#endif