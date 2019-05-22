#ifndef _ANY_H_
#define _ANY_H_

#include <typeinfo>
#include <memory>
#include <type_traits>

namespace fp {

    class Any {
    private:
        struct BaseType {};

        template<typename T>
        struct SomeType: public BaseType {
            using type = T;
            T value_;
        };

        std::shared_ptr<BaseType> content_;

    public:
        template<typename T>
        friend const T& AnyCast(const Any& rhs);

        Any(){}

        template<typename T>
        Any(const T& rhs) : content_(new SomeType<T>(rhs)) {}

    };

    template<typename T>
    const T& AnyCast(const Any& any) {
        static_assert(std::is_same<T, >)
            return static_cast<T>(any.content_);
    }

} // namespace fp
#endif // ifndef _ANY_H_
