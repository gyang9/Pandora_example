/**
 *  @file   ExampleAlgorithms/CubeTwoDTrackMatchingAlgorithm.h
 *
 *  @brief  Header file for the cosmic ray track matching algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_CUBE_TWOD_TRACK_MATCHING_ALGORITHM_H
#define EXAMPLE_CUBE_TWOD_TRACK_MATCHING_ALGORITHM_H 1

#include "ExampleAlgorithms/CubeTwoDBaseMatchingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  CubeTwoDTrackMatchingAlgorithm class
 */
class CubeTwoDTrackMatchingAlgorithm : public CubeTwoDBaseMatchingAlgorithm{
public:
    /**
     *  @brief  Default constructor
     */
    CubeTwoDTrackMatchingAlgorithm();

    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


private:

    void SelectCleanClusters(const pandora::ClusterVector &inputVector, pandora::ClusterVector &outputVector) const;
    bool MatchClusters(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2) const;
    bool MatchClustersXY_XZ(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2) const;
    bool MatchClustersXZ_YZ(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2) const;
    bool MatchClustersXY_YZ(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2) const;
    bool CheckMatchedClusters3D(const pandora::Cluster *const pCluster1, const pandora::Cluster *const pCluster2,
	const pandora::Cluster *const pCluster3) const;

    void SetPfoParameters(const Particle &protoParticle, PandoraContentApi::ParticleFlowObject::Parameters &pfoParameters) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float          m_clusterMinLength;             ///< minimum length of clusters for this algorithm
    float          m_vtxXOverlap;                  ///< requirement on X overlap of start/end positions
    float          m_minXOverlap;                  ///< requirement on minimum X overlap for associated clusters
    float          m_minXOverlapFraction;          ///< requirement on minimum X overlap fraction for associated clusters
    float          m_maxDisplacement;              ///< requirement on 3D consistency checks
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *CubeTwoDTrackMatchingAlgorithm::Factory::CreateAlgorithm() const
{
    return new CubeTwoDTrackMatchingAlgorithm();
}



} // namespace example_content

#endif // #ifndef EXAMPLE_COSMIC_RAY_TRACK_MATCHING_ALGORITHM_H
