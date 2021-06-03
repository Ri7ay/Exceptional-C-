#include <iostream>
#include <utility>

template<class S>
class wrap_state {
    S x_; // not working for S&&;
public:
    explicit wrap_state(S &&x) : x_(std::move(x)) {
    }

    template<class F>
    wrap_state then(F f) &&{
        return wrap_state{f(x_)};
    }

    template<class F>
    auto final(F f) &&{
        return f(x_);
    }
};

template<class S>
wrap_state(S &&) -> wrap_state<S>;

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

    std::cout << wrap_state(std::make_pair(0, 0)).then(nfoo).then(nbar).final(nbuz) << std::endl;
}

int main() {
    TEST_WRAP_STATE();
    return 0;
}

