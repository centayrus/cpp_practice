#pragma once

#include "graph.h"
#include "json.h"
#include "ranges.h"
#include "router.h"
#include "transport_catalogue.h"

namespace router {

class TransportRouter {
public:
    TransportRouter();

private:
    const json::Dict routing_sets_;
};

} // namespace router
