//  This work by Michele Caini is licensed under CC BY-NC-SA 4.0 
#include <cstdint>

class family {
    static unsigned int identifier() noexcept {
        static uint32_t value = 0;
        return value++;
    }

public:
    template<typename>
    static uint32_t type() noexcept {
        static const std::size_t value = identifier();
        return value;
    }
};
