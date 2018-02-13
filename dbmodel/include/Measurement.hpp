#ifndef MEASUREMENT_HPP_
#define MEASUREMENT_HPP_

#include <cstdint>
#include <ctime>
#include <map>
#include <memory>

#include <SensorNode.hpp>

/**
    A Measurement-object contains all measurements of a single SensorNode at a
    given time. It uses a key-value-map to store the values of different sensors
    in the node (e.g. humidity, temperature, pH value, ...)
*/
#pragma db object
struct Measurement {
    #pragma db id auto
    uint64_t id;

    SensorNode::Ptr sensor;
    std::map<std::string, float> keyValueMap;
    time_t time;

    using Ptr = std::shared_ptr<Measurement>;

};


#endif /* end of include guard: MEASUREMENT_HPP_ */
