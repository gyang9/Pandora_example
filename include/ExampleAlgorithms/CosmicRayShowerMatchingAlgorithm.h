/**
 *  @file   ExampleAlgorithms/CosmicRayShowerMatchingAlgorithm.h
 *
 *  @brief  Header file for the cosmic ray shower matching algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_COSMIC_RAY_SHOWER_MATCHING_ALGORITHM_H
#define EXAMPLE_COSMIC_RAY_SHOWER_MATCHING_ALGORITHM_H 1

#include "ExampleAlgorithms/CosmicRayBaseMatchingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  CosmicRayShowerMatchingAlgorithm class
 */
class CosmicRayShowerMatchingAlgorithm : public CosmicRayBaseMatchingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    CosmicRayShowerMatchingAlgorithm();

    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };

private:

    void SelectCleanClusters(const pandora::ClusterVector &inputVector, pandora::ClusterVector &outputVector) const;
    bool MatchClusters(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2) const;
    bool CheckMatchedClusters3D(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2,
        const pandora::Cluster *const pCluster3) const;
    void SetPfoParameters(const Particle &particle, PandoraContentApi::ParticleFlowObject::Parameters &pfoParameters) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float          m_minCaloHitsPerCluster;        ///< minimum size of clusters for this algorithm
    float          m_minXOverlap;                  ///< requirement on minimum X overlap for associated clusters
    float          m_minXOverlapFraction;          ///< requirement on minimum X overlap fraction for associated clusters
    float          m_pseudoChi2Cut;                ///< The selection cut on the matched chi2
};


//------------------------------------------------------------------------------------------------------------------------------------------

//inline pandora::Algorithm *CosmicRayShowerMatchingAlgorithm::Factory::CreateAlgorithm() const
//{
//    return new CosmicRayShowerMatchingAlgorithm();
//}


} // namespace example_content

#endif // #ifndef EXAMPLE_COSMIC_RAY_SHOWER_MATCHING_ALGORITHM_H
