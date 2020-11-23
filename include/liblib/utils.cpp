#include "utils.h"

#include <thread>

namespace ll {

/**
 * The amount of trust we have in the accuracy of the sleep method. This is an exponentially weighted moving average of
 * the observed discrepancy in sleep timing.
 */
spin_sleep_clock::duration sleep_trust = spin_sleep_clock::duration();
int sleep_samples = 30;

void spin_sleep_for(spin_sleep_clock::duration duration) {
    spin_sleep_until(spin_sleep_clock::now() + duration);
}

void spin_sleep_until(spin_sleep_clock::time_point target) {
    auto start = spin_sleep_clock::now();
    if(start >= target) {
        return;
    }
    auto duration = target - start;

    if(duration > sleep_trust) {
        auto thread_sleep_duration = duration - sleep_trust;
        std::this_thread::sleep_for(thread_sleep_duration);
        auto actual_thread_sleep_duration = spin_sleep_clock::now() - start;

        sleep_trust -= sleep_trust / sleep_samples;
        if(actual_thread_sleep_duration < thread_sleep_duration) {
            // if somehow we under slept, the discrepancy is zero, so we don't add anything
            // sleep_trust += spin_sleep_clock::duration() / sleep_samples;
        } else {
            sleep_trust += (actual_thread_sleep_duration - thread_sleep_duration) / sleep_samples;
        }
    }
    while(spin_sleep_clock::now() < target) {
        // spin
    }
}

}
