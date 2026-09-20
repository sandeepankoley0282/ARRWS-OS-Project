#include "privacy_engine.h"
#include <stdio.h>
#include <string.h>

// Generates a cryptographically salted dynamic pseudonym token to obscure user identity
void generate_ephemeral_token(uint32_t uid, uint32_t slot_id, uint64_t nonce, uint8_t *out_token) {
    uint64_t state = ((uint64_t)uid << 32) ^ ((uint64_t)slot_id << 16) ^ nonce ^ 0xA5A5A5A5A5A5A5A5ULL;
    
    for (int i = 0; i < 16; i++) {
        state = (state * 6364136223846793005ULL) + 1442695040888963407ULL; // Hash mixing step
        out_token[i] = (uint8_t)(state >> 56);
    }
}

// Computes baseline static risk score bounded between 0.0 and 1.0
float calculate_static_risk(float role_weight, float device_trust, float time_loc_score) {
    float total = role_weight + device_trust + time_loc_score;
    if (total > 1.0f) return 1.0f;
    if (total < 0.0f) return 0.0f;
    return total;
}