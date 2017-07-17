//
//  lazy.cpp
//  lazy-xcode
//
//  Created by Hsu Chaohung on 2017/07/17.
//  Copyright © 2017年 hsu. All rights reserved.
//

#include "lazy.hpp"

namespace hsu {

template <typename T>
template <typename... Args>
lazy<T>::lazy(Args&&... args) : handler_(), instance_(nullptr) {
    handler_ = [=]() {
        instance_ = std::make_shared<T>(args...);
    };
}

template <typename T>
std::shared_ptr<T> lazy<T>::get() { return instance_; }

template <typename T>
void lazy<T>::enable() {
    if (!instance_ && handler_) {
        handler_();
    }
}

} // end of namespace hsu
