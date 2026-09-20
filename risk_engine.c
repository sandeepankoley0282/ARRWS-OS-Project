#include "risk_engine.h"
#include <stdio.h>

float compute_total_risk(float r_auth, float r_behavior, float r_device, float r_env, float r_hist, RiskWeights_t weights) {
    float r_total = (weights.w_auth * r_auth) +
                    (weights.w_behavior * r_behavior) +
                    (weights.w_device * r_device) +
                    (weights.w_env * r_env) +
                    (weights.w_hist * r_hist);

    if (r_total > 1.0f) return 1.0f;
    if (r_total < 0.0f) return 0.0f;
    return r_total;
}

LockMode evaluate_risk_mode(float r_total) {
    if (r_total < 0.30f) {
        return MODE_NORMAL;
    } else if (r_total < 0.70f) {
        return MODE_RESTRICTED;
    } else if (r_total < 0.90f) {
        return MODE_EXCLUSIVE;
    } else {
        return MODE_ISOLATED;
    }
}

int send_risk_update(const char *socket_path, uint32_t thread_id, float new_score) {
    LockMode mode = evaluate_risk_mode(new_score);
    printf("[IPC DISPATCHER] Thread %u | Score: %.2f | Target Lock Mode: %d\n",
           thread_id, new_score, mode);
    return 0;
}