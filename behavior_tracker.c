#include "behavior_tracker.h"
#include <stdio.h>

void init_thread_behavior(ThreadBehaviorState_t *state, uint32_t thread_id) {
    state->thread_id = thread_id;
    state->config_writes_count = 0;
    state->last_window_timestamp = 0.0;
    state->r_behavior = 0.0f;
}

void record_thread_action(ThreadBehaviorState_t *state, bool is_config_write, double current_time) {
    // Reset window every 1.0 second
    if (current_time - state->last_window_timestamp >= 1.0) {
        state->config_writes_count = 0;
        state->last_window_timestamp = current_time;
    }

    if (is_config_write) {
        state->config_writes_count++;
    }

    // Anomaly condition: >20 config writes per second triggers +0.35 score penalty
    if (state->config_writes_count > 20) {
        state->r_behavior += 0.35f;
        if (state->r_behavior > 1.0f) {
            state->r_behavior = 1.0f; // Cap max score at 1.0
        }
    }
}