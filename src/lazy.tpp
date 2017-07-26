//
//  lazy.cpp
//  lazy-xcode
//
//  Created by Hsu Chaohung on 2017/07/17.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include <tuple>

#include "lazy.hpp"

namespace hsu {

template <int N>
struct Expand {
    template <typename F, typename Tuple, typename... Args>
    static void apply(F& f, Tuple& t, Args&... args) {
        Expand<N - 1>::apply(f, t, std::get<N - 1>(t), args...);
    }
};

template <>
struct Expand<0> {
    template <typename F, typename Tuple, typename... Args>
    static void apply(F& f, Tuple t, Args&... args) {
        f(args...);
    }
};

template <typename F, typename Tuple>
void apply(F const& f, Tuple const& t) {
    Expand<std::tuple_size<Tuple>::value>::apply(f, t);
}

template <typename T>
template <typename... Args>
lazy<T>::lazy(Args const&... args) : handler_(), instance_(nullptr) {
    auto t = std::tuple<Args...>(args...);
    auto f = [&](Args... args) {
        instance_ = std::make_shared<T>(args...);
    };
    handler_ = [=]() {
        apply(f, t);
    };
}

template <typename T>
std::shared_ptr<T> lazy<T>::get() { return instance_; }

template <typename T>
void lazy<T>::enable() {
    if (!instance_) {
        handler_();
    }
}

} // end of namespace hsu
