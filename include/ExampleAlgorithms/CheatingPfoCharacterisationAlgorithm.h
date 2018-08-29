/**
 *  @file   ExampleAlgorithms/CheatingPfoCharacterisationAlgorithm.h
 * 
 *  @brief  Header file for the cheating pfo characterisation algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_CHEATING_PFO_CHARACTERISATION_ALGORITHM_H
#define EXAMPLE_CHEATING_PFO_CHARACTERISATION_ALGORITHM_H 1

#include "ExampleAlgorithms/PfoCharacterisationBaseAlgorithm.h"

namespace example_content
{

/**
 *  @brief  CheatingPfoCharacterisationAlgorithm class
 */
class CheatingPfoCharacterisationAlgorithm : public PfoCharacterisationBaseAlgorithm
{
private:
    bool IsClearTrack(const pandora::ParticleFlowObject *const pPfo) const;
    bool IsClearTrack(const pandora::Cluster *const pCluster) const;
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CHEATING_PFO_CHARACTERISATION_ALGORITHM_H
