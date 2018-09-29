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

public:

    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string     m_pfoListName;                ///< The pfo list name
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *UnattachedDeltaRaysAlgorithm::Factory::CreateAlgorithm() const
{
    return new UnattachedDeltaRaysAlgorithm();
}


} // namespace example_content

#endif // #ifndef EXAMPLE_UNATTACHED_DELTA_RAYS_ALGORITHM_H
