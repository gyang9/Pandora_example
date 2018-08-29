/**
 *  @file   ExampleAlgorithms/ClusterExtensionAlgorithm.cc
 *
 *  @brief  Implementation of the cluster extension algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/ClusterExtensionAlgorithm.h"

using namespace pandora;

namespace example_content
{

void ClusterExtensionAlgorithm::PopulateClusterMergeMap(const ClusterVector &clusterVector, ClusterMergeMap &clusterMergeMap) const
{
    ClusterAssociationMatrix clusterAssociationMatrix;
    this->FillClusterAssociationMatrix(clusterVector, clusterAssociationMatrix);
    this->FillClusterMergeMap(clusterAssociationMatrix, clusterMergeMap);
}

} // namespace example_content
