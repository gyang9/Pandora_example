/**
 *  @file   ExampleAlgorithms/CheatingClusterCharacterisationAlgorithm.h
 * 
 *  @brief  Header file for the cheating cluster characterisation algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_CHEATING_CLUSTER_CHARACTERISATION_ALGORITHM_H
#define EXAMPLE_CHEATING_CLUSTER_CHARACTERISATION_ALGORITHM_H 1

#include "ExampleAlgorithms/ClusterCharacterisationBaseAlgorithm.h"

namespace example_content
{

/**
 *  @brief  CheatingClusterCharacterisationAlgorithm class
 */
class CheatingClusterCharacterisationAlgorithm : public ClusterCharacterisationBaseAlgorithm
{
private:
    bool IsClearTrack(const pandora::Cluster *const pCluster) const;
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CHEATING_CLUSTER_CHARACTERISATION_ALGORITHM_H
