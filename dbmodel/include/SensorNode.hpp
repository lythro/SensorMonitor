#ifndef SENSORNODE_HPP
#define SENSORNODE_HPP

#include <cstdint>
#include <memory>
#include <odb/forward.hxx>

/**
    This class models a single physical sensor-node. It uses the id as
    transmitted by the device (hence not automatically set). It does not
    store its measurements directly: Every "Measurement" keepts a pointer to
    the SensorNode that created it. That way, we don't load all measurements
    when accessing a SensorNode.
*/
#pragma db object
class SensorNode {
    friend class odb::access;
    #pragma db id
    uint64_t id_;

public:
    using Ptr = std::shared_ptr<SensorNode>;
    // TODO: addMeasurement, getMeasurements, ... something like that.
};


#endif /* end of include guard: SENSORNODE_HPP */
