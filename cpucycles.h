#ifndef CPUCYCLES_H
#define CPUCYCLES_H

#include <stdint.h>
#include <time.h>

static inline uint64_t cpucycles(void) {
    return clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
}

uint64_t cpucycles_overhead(void);

#endif
