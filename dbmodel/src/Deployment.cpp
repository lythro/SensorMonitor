#include <Deployment.hpp>

Deployment::Deployment()
{
    std::time(&begin_);
    active_ = true;
}
