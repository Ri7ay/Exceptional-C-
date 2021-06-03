#include <iostream>

auto wrap_state = [](auto x) {
    return [=](auto access) {
        return access(x);
    };
};

template<class STATE, class Func>
auto operator>(STATE s, Func f) {
    return s(f);
}

template<class STATE, class Func>
auto operator>=(STATE s, Func f) {
    // return wrap_state(s(f));
    return s([f](auto sprime) { return wrap_state(f(sprime)); });
}

int foo() {
    return 3;
}

int bar() {
    return 6;
};

int buz(int x, int z) {
    std::cout << "x: " << x << " + " << "z: " << z << std::endl;
    return x + z;
}

void TEST_WRAP_STATE() {
    auto nfoo = [](auto xz) {
        return std::make_pair(foo(), xz.second);
    };

    auto nbar = [](auto xz) {
        return std::make_pair(xz.first, bar());
    };

    auto nbuz = [](auto xz) {
        return buz(xz.first, xz.second);
    };

    std::cout << (wrap_state(std::make_pair(0, 0)) >= nfoo >= nbar > nbuz) << std::endl;
}

int main() {
    TEST_WRAP_STATE();
    return 0;
}