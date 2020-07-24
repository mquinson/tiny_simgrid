#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <string>

namespace app {

const std::string ISEND = "Isend";
const std::string IRECEIVE = "Ireceive";
const std::string TEST = "Test";
const std::string WAIT = "Wait";
const std::string TransitionTypeName[] = { ISEND, IRECEIVE, TEST, WAIT };

enum class TransitionType {
    Isend = 0,
    Ireceive,
    test,
    wait
};

template<typename T, typename... Rest>
void unpack_params(std::vector<T>& vec, T&& t, Rest&&... rest) {
    vec.push_back(t);
    unpack_params(vec, std::forward<Rest>(rest)...);
}

template<typename T>
void unpack_params(std::vector<T>& vec, T&& t) {
    vec.push_back(t);
}

} // namespace app

#endif // CONFIG_HPP
