#ifndef CHAOSEQUATIONS_UTILS_H
#define CHAOSEQUATIONS_UTILS_H

#include <chrono>

namespace ll {

using spin_sleep_clock = std::chrono::high_resolution_clock;

void spin_sleep_for(spin_sleep_clock::duration duration);
void spin_sleep_until(spin_sleep_clock::time_point target);

}

#endif // CHAOSEQUATIONS_UTILS_H
