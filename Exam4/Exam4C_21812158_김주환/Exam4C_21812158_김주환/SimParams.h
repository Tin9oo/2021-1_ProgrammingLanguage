/* SimParam.h Simulation Parameters */

#define NUM_EVENT_GENERATORS 3
#define NUM_EVENTS_PER_GEN 20
#define NUM_EVENT_HANDLERS 2
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN) * (NUM_EVENT_GENERATORS)
#define MAX_ROUND 10000

#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3 // 0 ~ 2: High Priority, 3 ~ 9: low priority
#define EVENT_PER_LINE 5