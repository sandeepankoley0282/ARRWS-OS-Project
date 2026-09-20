#ifndef PRIVACY_ENGINE_H
#define PRIVACY_ENGINE_H

#include "arrws_types.h"

// Generates a 16-byte dynamic pseudonym token from UID, slot_id, and nonce
void generate_ephemeral_token(uint32_t uid, uint32_t slot_id, uint64_t nonce, uint8_t *out_token);

// Calculates baseline static risk score: R_static = RoleWeight + DeviceTrust + TimeLocationScore
float calculate_static_risk(float role_weight, float device_trust, float time_loc_score);

#endif // PRIVACY_ENGINE_H