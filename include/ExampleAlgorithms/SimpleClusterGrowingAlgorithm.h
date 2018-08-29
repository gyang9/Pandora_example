/**
 *  @file   ExampleAlgorithms/SimpleClusterGrowingAlgorithm.h
 *
 *  @brief  Header file for the simple cluster growing algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_SIMPLE_CLUSTER_GROWING_ALGORITHM_H
#define EXAMPLE_SIMPLE_CLUSTER_GROWING_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

#include "ExampleAlgorithms/ClusterGrowingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  SimpleClusterGrowingAlgorithm class
 */
class SimpleClusterGrowingAlgorithm : public ClusterGrowingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    SimpleClusterGrowingAlgorithm();

private:
    void GetListOfCleanClusters(const pandora::ClusterList *const pClusterList, pandora::ClusterVector &cleanClusters) const;
    void GetListOfSeedClusters(const pandora::ClusterVector &inputClusters, pandora::ClusterVector &seedClusters) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    unsigned int m_minCaloHitsPerCluster;    ///< The minimum number of calo hits per seed cluster
};

} // namespace example_content

#endif // #ifndef EXAMPLE_SIMPLE_CLUSTER_GROWING_ALGORITHM_H
