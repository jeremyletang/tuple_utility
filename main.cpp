#include <tuple_utility>
#include <vector>
#include <iostream>


std::vector<int> test(int) { return {}; }
std::vector<double> test(double) { return {}; }
std::vector<std::string> test(std::string) { return {}; }

template <typename... T>
void make(const std::tuple<T...>& t) {
    namespace tt = tuple_utility::traits;
    auto f = [](const auto& e) { return test(e); };
    tt::map_result_helper_t<decltype(f), T...> t2;
}

template <typename T> struct ty;

int main () {
    namespace tu = tuple_utility;
    auto t = std::make_tuple(42, std::string{"hello world"}, 84.4);
    tu::iter(t, [](const auto& e) { std::cout << e << std::endl; });
    auto res = tu::map(t, [](const auto& e) {
        std::vector<std::remove_cv_t<std::remove_reference_t<decltype(e)>>> v{};
        v.push_back(e);
        return v;
    });

    std::cout << std::get<0>(res)[0] << std::endl;
    std::cout << std::get<1>(res)[0] << std::endl;
    std::cout << std::get<2>(res)[0] << std::endl;
    make(t);


    std::tuple<int, char, float, double> to_rev = std::make_tuple(1, 'y', 42.4, 86543.1234);
    tu::traits::tuple_rev_helper_t<decltype(to_rev)> rev = tu::rev(to_rev);
    std::cout << std::get<0>(rev) << std::endl;
    std::cout << std::get<1>(rev) << std::endl;
    std::cout << std::get<2>(rev) << std::endl;
    std::cout << std::get<3>(rev) << std::endl;

    // ty<tu::traits::tuple_concat_t<std::string, std::tuple<char, double>>> asdas;
    // ty<tu::traits::tuple_concat_t<std::tuple<int, float, short>, std::tuple<char, double>>> asdas2;
    // ty<tu::traits::tuple_concat_tuple_t<std::tuple<int, float, short>, std::tuple<char, double>>> asdas;
}