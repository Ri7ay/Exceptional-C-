#include <iostream>
#include <vector>

template<typename T, size_t size>
class fixed_vector {
public:
    typedef T *iterator;
    typedef const T *const_iterator;

    fixed_vector() : v_(new T[size]) {
    }
    ~fixed_vector() {
        delete[] v_;
    }

    fixed_vector(const fixed_vector &vec) {
        try {
            fixed_vector tmp{};
            std::copy(vec.begin(), vec.end(), tmp.begin());
            std::swap(tmp.v_, v_);
        } catch(...) {
            throw;
        }
    }

    template<class U, size_t u_size>
    explicit fixed_vector(const fixed_vector<U, u_size> &vec) {
        try {
            fixed_vector tmp{};
            std::copy(vec.begin(), vec.begin() + std::min(size, u_size), tmp.begin());
            std::swap(tmp.v_, v_);
        } catch(...) {
            throw;
        }
    }

    fixed_vector &operator=(const fixed_vector &vec) {
        if (this == &vec) {
            return *this;
        }
        fixed_vector tmp{vec};
        std::swap(tmp.v_, v_);
        return *this;
    }

    template<class U, size_t u_size>
    fixed_vector &operator=(const fixed_vector<U, u_size> &vec) {
        fixed_vector tmp{vec};
        std::swap(tmp.v_, v_);
        return *this;
    }

    iterator begin() {
        return v_;
    }

    iterator end() {
        return v_ + size;
    }

    [[nodiscard]] const_iterator begin() const {
        return v_;
    }

    [[nodiscard]] const_iterator end() const {
        return v_ + size;
    }

private:
    T *v_ = nullptr;
};




int main() {
    std::vector<int> vec_for_init{1, 2, 3, 4, 5, 6, 7};
    fixed_vector<int, 7> vec{};
    std::copy(vec_for_init.begin(), vec_for_init.end(), vec.begin());

    fixed_vector<int, 5> test_copy{vec};
     fixed_vector<int, 5> test_op_copy{};
     test_op_copy = vec;

    for (const auto &it : vec) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    for (const auto &it : test_copy) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    for (const auto &it : test_op_copy) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    return 0;
}
