#ifndef DEPLOYMENT_HPP_
#define DEPLOYMENT_HPP_

#include <cstdint>
#include <ctime>

#include <odb/forward.hxx>

/**
    A Deployment is a set of SensorInterpretations that are restricted to a
    given time interval for which those interpretations are valid.
*/
#pragma db object
class Deployment {
    friend class odb::access;
    #pragma db id auto
    uint64_t id_;
    std::time_t begin_;
    std::time_t end_;
    bool active_;

public:
    Deployment();
    // TODO: addInterpretation / removeInterpretation / query stuff
};


#endif /* end of include guard: DEPLOYMENT_HPP_ */
