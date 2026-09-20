# ARRWS-OS-Project
Risk-Adaptive Reader–Writer Synchronization Mechanism
A Dynamic, Security-Aware Concurrency Control Primitive for Shared Laboratory Allocation
1. Executive Summary & Core Motivation OS CONCEPT
In shared computational and experimental laboratories (comprising GPUs, IoT hardware, network switches, and
configuration registries), standard Operating System synchronization primitives—such as classical Reader–Writer (RW) locks—enforce binary concurrency rules without context. Standard locks assume that all threads operate with
equal trust. When a untrusted or compromised student thread requests access, standard access control
(RBAC/ABAC) either permits or denies the entry at the door.
This project introduces Adaptive Risk-Aware Reader–Writer Synchronization (ARRWS). ARRWS brings security
parameters directly into the OS concurrency layer. Instead of granting static access, the system dynamically modifies
the operational mode of the lock itself based on real-time security risk scores and hardware resource criticality.
Core Thesis: Security risk should not merely govern authorization (Allow/Deny); it must dynamically reconfigure the
synchronization algorithm itself (concurrency limits, writer prioritization, and mid-session lock revocation).
2. Technical Novelty & IP Differentiation CORE INNOVATION
Risk-adaptive access control is well-established in security research. To achieve true technical novelty for an OS-level
project, ARRWS focuses on five distinct architectural contributions:
Dynamic Risk-to-Lock Mode Mapping: Risk scores do not output binary decisions; they dynamically transition the lock
through distinct state modes (Normal Concurrent, Restricted Reader-Capped, Exclusive Writer, and Isolated).
Continuous Mid-Session Recalculation: Unlike static locks evaluated at acquisition, ARRWS re-evaluates risk throughout
the thread's holding period. Behavioral anomalies trigger runtime lock downgrades or immediate preemption.
Security-Aware Starvation Prevention: High security risk often leads to aggressive locking that starves benign threads.
ARRWS implements a dynamic aging queue that preserves fairness for low-risk users under high threat conditions.
Resource Criticality Cross-Matrix: Lock behavior is determined by intersecting incoming user risk with asset
vulnerability (e.g., read access to a public dataset vs. a shared router configuration).
Privacy-Preserving Slot Ownership (Identity Blindness): When a user books or locks a lab slot, lock ownership metadata
is cryptographically masked into an ephemeral pseudonymous token. Other users can query slot availability
(BUSY/FREE) without discovering who holds the lock.
Rtotal = w1
·Rauth + w2
·Rbehavior + w3
·Rdevice + w4
·Renv + w5
·Rhist
Dynamic Risk Score Equation balancing authentication, runtime telemetry, security posture, and historical metrics
3. Situation & Behavior Comparison Matrix
Operational Scenario Standard R-W Lock Behavior Proposed ARRWS Lock Behavior
Normal Operations (20 users
reading status)
Unlimited concurrent readers granted
access.
Normal Mode: Max reader concurrency enabled.
Elevated User Risk
(Untrusted device/time)
Lock unchanged (full reader access
granted).
Restricted Mode: Reader concurrency capped;
inspect payload.
Critical Threat / Attack
(Config tamper)
Lock unchanged (writer queued normally).
Exclusive Writer Pre-emption: Freeze readers;
force admin lock.
Runtime Suspicious
S i l t ith t i t ti
Runtime Downgrade: Active lock revoked midARRWS Engineering Document • Section 1–3 Page 1
4. System Execution Workflow & Architecture FLOW PIPELINE
The lifecycle of a resource access request in ARRWS flows from initial thread request through real-time risk
assessment, lock acquisition, active behavioral monitoring, and dynamic state adjustments.
Thread Request
(User/Process)
Risk Engine
Computes R_total Score
ARRWS State Primitive
• Mode Selection (Normal / Restr / Excl)
• Priority & Queue Assignment
Lab Hardware / Resource
(GPU, IoT, Switch, Config)
Continuous Monitor
Detect Anomaly → Send Signal
Mid-Session Revocation Trigger (Dynamic Lock Downgrade / Immediate Reclaim)
5. Tech Stack Recommendations per Layer IMPLEMENTATION
To deliver an authentic Operating System project, the system should be implemented using low-level, highperformance concurrency frameworks coupled with real-time signal mechanisms:
1. Security & Risk Layer
Languages: C++20 or Python
(Fast API engine)
OS Telemetry: Linux Cgroups
v2, eBPF / Auditd hooks
IPC Protocol: UNIX Domain
Sockets / Shared Memory
Libraries: nlohmann/json for
policy parsing
2. Synchronization Lock Core
Language: Pure C11 or Modern
C++20
Primitives: pthread_mutex,
pthread_cond
Atomics: C11 stdatomic.h for
lockless flags
Shared State: POSIX Shm
(shm_open, mmap)
3. Simulator & Analytics
Simulator: C++ Thread Pool (50
simulated users)
Benchmarking: Google
Benchmark / Google Test
Visualization: Python
(Matplotlib / Dash) for latency
plots
CLI Dashboard: Ncurses for
real-time state visualization
6. Lock Mode State Transition Rules
Current Mode
Risk
Threshold
Concurrency Capacity Writer Behavior Transition Action
Mode 0: Normal R < 0.30 Unlimited Readers Fair queueing
Standard concurrent read
operations.
Mode 1:
Restricted
0.30 ≤ R <
0.70
Max N Concurrent (e.g.,
N=3)
Priority elevation
Throttle reader throughput; cap
queue size.
Mode 2:
Exclusive
0.70 ≤ R <
0.90
Zero Readers Allowed
Immediate Preemption
Block all new readers; grant
exclusive writer.
Mode 3: Isolated R ≥ 0.90 Lock Freeze
Admin Recovery
Only
Revoke all active locks; force thread
eviction.
