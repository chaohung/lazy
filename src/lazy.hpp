//
//  lazy.hpp
//  lazy-xcode
//
//  Created by Hsu Chaohung on 2017/07/17.
//  Copyright © 2017年 hsu. All rights reserved.
//

#ifndef lazy_hpp
#define lazy_hpp

#include <memory>
#include <functional>

namespace hsu {

template <typename T>
class lazy {
public:
    template <typename... Args>
    lazy(Args const&... args);

    std::shared_ptr<T> get();
    void enable();

private:
    std::function<void()> handler_;
    std::shared_ptr<T> instance_;
};

} // end of namespace hsu

#include "lazy.tpp"

#endif /* lazy_hpp */
