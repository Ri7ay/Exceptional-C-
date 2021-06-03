#include <iostream>

auto List = [](auto... xs) {
    return [=](auto access) { return access(xs...); };
};

auto head = [](auto xs) {
    return xs([](auto first, auto... rest) { return first; });
};

auto tail = [](auto xs) {
    return xs([](auto first, auto... rest) { return List(rest...); });
};

auto length = [](auto xs) {
    return xs([](auto... z) { return sizeof...(z); });
};

auto flatten = [](auto func, auto... xs) {
    return List(func(xs)...);
};

auto flatmap = [](auto func) {
    return [func](auto alist) {
        return alist([func](auto... xs) {
            return flatten(func, xs...);
        });
    };
};

auto fmap = [](auto func) {
    return [func](auto alist) {
        return alist([func](auto... xs) {
            return List(func(xs)...);
        });
    };
};

template<class LIST, class Func>
auto operator>(LIST l, Func f) {
    return fmap(f)(l);
}

template<class LIST, class Func>
auto operator>=(LIST l, Func f) {
    return flatmap(f)(l);
}

int main() {
    auto pair = [](auto i) { return List(-i, i); };
    auto l4 = List(1, 2, 3);
    auto l5 = flatmap(pair)(l4); // List{List{-1; 1}, List{-2; 2}; List{-3; 3}}

    std::cout << "Len of l4: " << length(l4) << std::endl;
    std::cout << "Len of l5: " << length(l5) << std::endl;
    return 0;
}
