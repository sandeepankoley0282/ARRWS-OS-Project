#ifndef BEHAVIOR_TRACKER_H
#define BEHAVIOR_TRACKER_H

#include "arrws_types.h"

typedef struct {
    uint32_t thread_id;
    uint32_t config_writes_count;
    double last_window_timestamp;
    float r_behavior;
} ThreadBehaviorState_t;

// Initializes tracking state for a thread
void init_thread_behavior(ThreadBehaviorState_t *state, uint32_t thread_id);

// Records thread action; adds penalty (r_behavior += 0.35) if >20 ops/sec
void record_thread_action(ThreadBehaviorState_t *state, bool is_config_write, double current_time);

#endif // BEHAVIOR_TRACKER_H