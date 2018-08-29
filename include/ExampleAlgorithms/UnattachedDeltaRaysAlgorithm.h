/**
 *  @file   ExampleAlgorithms/UnattachedDeltaRaysAlgorithm.h
 *
 *  @brief  Header file for the unattached delta rays algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_UNATTACHED_DELTA_RAYS_ALGORITHM_H
#define EXAMPLE_UNATTACHED_DELTA_RAYS_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  UnattachedDeltaRaysAlgorithm class
 */
class UnattachedDeltaRaysAlgorithm : public pandora::Algorithm
{
private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string     m_pfoListName;                ///< The pfo list name
};

} // namespace example_content

#endif // #ifndef EXAMPLE_UNATTACHED_DELTA_RAYS_ALGORITHM_H
