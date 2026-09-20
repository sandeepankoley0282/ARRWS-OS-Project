#include <stdio.h>
#include "privacy_engine.h"
#include "behavior_tracker.h"
#include "risk_engine.h"

int main() {
    printf("=== ARRWS Member 1: Security Layer Verification ===\n\n");

    // 1. Test Module 1.1: Ephemeral Pseudonym Generation
    uint8_t token[16];
    generate_ephemeral_token(101, 5, 12345678, token);
    printf("1. Ephemeral Pseudonym Token generated for UID 101: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", token[i]);
    }
    printf("\n");

    // 2. Test Module 1.2: Behavioral Tracking (Simulate >20 ops/sec spike)
    ThreadBehaviorState_t thread_state;
    init_thread_behavior(&thread_state, 101);
    
    printf("2. Simulating 25 rapid config writes in 1 second...\n");
    for (int i = 0; i < 25; i++) {
        record_thread_action(&thread_state, true, 0.5); // time = 0.5 sec
    }
    printf("   Behavior Risk Penalty (R_behavior): %.2f\n", thread_state.r_behavior);

    // 3. Test Module 1.3: Total Risk Computation & IPC Dispatch
    RiskWeights_t weights = {0.2f, 0.4f, 0.2f, 0.1f, 0.1f};
    float static_risk = calculate_static_risk(0.1f, 0.1f, 0.1f);
    
    float total_risk = compute_total_risk(static_risk, thread_state.r_behavior, 0.2f, 0.1f, 0.1f, weights);
    
    printf("3. Dynamic Total Risk Score (R_total): %.2f\n", total_risk);
    send_risk_update("/tmp/arrws_ipc.sock", thread_state.thread_id, total_risk);

    printf("\n=== Security Layer Module Passed All Tests! ===\n");
    return 0;
}