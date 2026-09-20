#ifndef ARRWS_TYPES_H
#define ARRWS_TYPES_H

#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MODE_NORMAL = 0,
    MODE_RESTRICTED = 1,
    MODE_EXCLUSIVE = 2,
    MODE_ISOLATED = 3
} LockMode;

typedef struct {
    uint32_t user_id;
    uint8_t dynamic_token[16];
    float role_weight;
    bool is_scheduled_lab;
} UserContext_t;

typedef struct {
    uint32_t thread_id;
    uint8_t ephemeral_token[16]; // Cryptographic pseudonym
    float user_risk_score;       // Dynamic risk score (0.0 to 1.0) calculated by Member 1
    float resource_criticality;  // Defined by Member 3
    float effective_risk;        // Combined metric
} RiskPayload_t;

#endif // ARRWS_TYPES_H
