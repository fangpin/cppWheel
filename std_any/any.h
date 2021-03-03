#ifndef _ANY_H_
#define _ANY_H_

#include <typeinfo>
#include <utility>
#include <exception>
#include <functional>

class bad_any_cast: public std::exception {
public:
    const char* what() const throw() {
        return "bad any cast";
    }
};

struct Any {
    void* data_;
    std::function<const std::type_info&()> get_type_func_;
    std::function<void*(void*)> clone_func_;
    std::function<void(void*)> destroy_func_;

    template<typename T>
    explicit Any(T&& val): 
        data_{new T{std::forward<T>(val)}},
        get_type_func_{[]() -> const std::type_info& {return typeid(T);}},
        clone_func_{[](void* data) -> void* {return new T{*static_cast<T*>(data)};}},
        destroy_func_{[](void* const data){delete static_cast<T*>(data);}} 
    { }

    Any(const Any& other):
        data_{other.clone_func_(other.data_)},
        get_type_func_(other.get_type_func_),
        clone_func_(other.clone_func_),
        destroy_func_(other.destroy_func_)
    { }

    ~Any() {
        destroy_func_(data_);
    }

    void* data() const { return data_; }

    template<typename T>
    friend T any_cast(const Any& aAny);
};

template<typename T>
T any_cast(const Any& aAny) {
    if (typeid(T) == aAny.get_type_func_()) {
        return *static_cast<T*>(aAny.data());
    } else {
        throw bad_any_cast();
    }
}
#endif // ifndef _ANY_H_
