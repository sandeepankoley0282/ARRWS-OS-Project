#ifndef RISK_ENGINE_H
#define RISK_ENGINE_H

#include "arrws_types.h"
#include "privacy_engine.h"
#include "behavior_tracker.h"

typedef struct {
    float w_auth;
    float w_behavior;
    float w_device;
    float w_env;
    float w_hist;
} RiskWeights_t;

// Computes total dynamic risk score: R_total = w1*R_auth + w2*R_behavior + w3*R_device + w4*R_env + w5*R_hist
float compute_total_risk(float r_auth, float r_behavior, float r_device, float r_env, float r_hist, RiskWeights_t weights);

// Maps total risk score (0.0 - 1.0) to dynamic LockMode enum
LockMode evaluate_risk_mode(float r_total);

// Dispatches real-time risk updates to Member 2's lock primitive
int send_risk_update(const char *socket_path, uint32_t thread_id, float new_score);

#endif // RISK_ENGINE_H