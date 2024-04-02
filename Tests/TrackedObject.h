#ifndef TRACKED_OBJECT_H
#define TRACKED_OBJECT_H

#include <cstddef>

class TrackedObject {
public:
    TrackedObject() { ++instances_created; }
    TrackedObject(const TrackedObject&) { ++instances_created; }
    TrackedObject& operator=(const TrackedObject&) = default;
    ~TrackedObject() { ++instances_destroyed; }

    static void reset_counters() {
        instances_created = 0;
        instances_destroyed = 0;
    }

    static std::size_t created() { return instances_created; }
    static std::size_t destroyed() { return instances_destroyed; }

private:
    inline static std::size_t instances_created = 0;
    inline static std::size_t instances_destroyed = 0;
};

#endif // TRACKED_OBJECT_H