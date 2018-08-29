/**
 *  @file   ExampleAlgorithms/CheatingClusterCharacterisationAlgorithm.cc
 * 
 *  @brief  Implementation of the cheating cluster characterisation algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CheatingClusterCharacterisationAlgorithm.h"

#include "ExampleAlgorithms/LArMCParticleHelper.h"

using namespace pandora;

namespace example_content
{

bool CheatingClusterCharacterisationAlgorithm::IsClearTrack(const Cluster *const pCluster) const
{
    try
    {
        // ATTN Slightly curious definition of a clear track, but this is most-likely what is needed for shower-growing
        const MCParticle *const pMCParticle(MCParticleHelper::GetMainMCParticle(pCluster));

        if ((PHOTON != pMCParticle->GetParticleId()) && (E_MINUS != std::abs(pMCParticle->GetParticleId())))
            return true;
    }
    catch (const StatusCodeException &) {}

    return false;
}

} // namespace example_content
