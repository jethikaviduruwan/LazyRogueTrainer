#include "LRT/Events/EventBus.h"

// EventBus is fully inline/header-only,
// this compilation unit ensures the static instance is linked.
namespace LRT {
    // Intentionally empty — EventBus::Get() is defined inline in the header.
}
