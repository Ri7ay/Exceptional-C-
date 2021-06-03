auto List = [](auto... xs) {
    return [=](auto access) { return access(xs...); };
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

int main() {
    auto pair = [](auto i) { return List(-i, i); };
    auto l4 = List(1, 2, 3);
    auto l5 = flatmap(pair)(l4); // List{List{-1; 1}, List{-2; 2}; List{-3; 3}}
    return 0;
}
