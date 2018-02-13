#ifndef SENSORINTERPRETATION_HPP_
#define SENSORINTERPRETATION_HPP_

#include <cstdint>
#include <string>
#include <memory>

#include <SensorNode.hpp>
#include <Measurement.hpp>

#include <odb/forward.hxx>

/**
    A sensor-interpretation describes the usage of a sensor.
    In this very basic case it maps one variable measured by one
    sensornode (e.g. node7["temp"]) to a user defined description
    (e.g. "fishtank-temperature").

    SensorInterpretations are used in Deployments, which in case are restricted
    to a time interval.
*/
#pragma db object
class SensorInterpretation {
    friend class odb::access;
    
    #pragma db id auto
    uint64_t id;

    SensorNode::Ptr sensor;
    std::string variable;
    std::string description;
public:
    using Ptr = std::shared_ptr<SensorInterpretation>;
    // TODO getter/setter/stuff, or make it a struct with everything public?
};


#endif /* end of include guard: SENSORINTERPRETATION_HPP_ */
