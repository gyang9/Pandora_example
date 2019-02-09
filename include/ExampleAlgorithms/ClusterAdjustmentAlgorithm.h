/**
 *  @file   ExampleAlgorithms/ClusterAdjustmentAlgorithm.h
 *
 *  @brief  Header file for the 2D sliding fit consolidation algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_CLUSTER_ADJUSTMENT_ALGORITHM_H
#define EXAMPLE_CLUSTER_ADJUSTMENT_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

//#include "ExampleAlgorithms/LArTwoDSlidingFitResult.h"

#include <unordered_map>

namespace example_content
{

/**
 *  @brief  ClusterAdjustmentAlgorithm class
 */
class ClusterAdjustmentAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    ClusterAdjustmentAlgorithm();

    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


//protected:
private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    typedef std::unordered_map<const pandora::Cluster*, pandora::CaloHitList> ClusterToHitMap;

    /**
     *  @brief Get the list of hits to be added or removed from clusters
     *
     *  @param slidingFitResultList  the list of sliding linear fits to track clusters
     *  @param showerClusters  the vector of shower clusters
     *  @param caloHitsToAdd   the output map of hits to be added to clusters
     *  @param caloHitsToRemove   the output map of hits to be removed from clusters
     */
    //virtual void GetReclusteredHits(const TwoDSlidingFitResultList &slidingFitResultList, const pandora::ClusterVector &showerClusters,
    //    ClusterToHitMap &caloHitsToAdd, ClusterToHitMap &caloHitsToRemove) const = 0;

//private:
    /**
     *  @brief Sort input cluster list into track-like clusters and shower-like clusters
     *
     *  @param pClusterList  the input cluster list
     *  @param trackClusters  the output vector of track-like clusters
     *  @param showerClusters  the output vector of shower-like clusters
     */
    void SortInputClusters(const pandora::ClusterList *const pClusterList, pandora::ClusterVector &trackClusters,
        pandora::ClusterVector &showerClusters) const;

    /**
     *  @brief Apply sliding linear fits to track clusters
     *
     *  @param trackClusters  the input vector of track-like clusters
     *  @param slidingFitResultList  the output list of sliding linear fits
     */
    //void BuildSlidingLinearFits(const pandora::ClusterVector &trackClusters, TwoDSlidingFitResultList &slidingFitResultList) const;
    void BuildSlidingLinearFits(pandora::ClusterVector &trackClusters, ClusterToHitMap &clustersToExpand, ClusterToHitMap &clustersToContract, const int splitGrouping, const double splitTolerance) const;

    void ClusterExpandwLinearFits(pandora::ClusterVector &trackClusters, ClusterToHitMap &clustersToExpand, const double splitTolerance) const;

    void ClusterContractwLinearFits(pandora::ClusterVector &trackClusters, ClusterToHitMap &clustersToContract, const int splitGrouping, const double splitTolerance) const;

    void ClusterExpandwLinearFits(pandora::ClusterList &trackClusters, ClusterToHitMap &clustersToExpand, const double splitTolerance) const;

    void ClusterContractwLinearFits(pandora::ClusterList &trackClusters, ClusterToHitMap &clustersToContract, const int splitGrouping, const double splitTolerance) const;

    /**
     *  @brief Remove hits from clusters
     *
     *  @param clustersToRebuild  the list of hits to be removed from clusters
     *  @param unavailableClusters  the list of deleted clusters
     */
    pandora::StatusCode RemoveHitsFromClusters(const ClusterToHitMap &clustersToRebuild, pandora::ClusterSet &unavailableClusters) const;
    pandora::StatusCode RemoveHitsFromClusters(const ClusterToHitMap &clustersToRebuild, pandora::ClusterSet &unavailableClusters, pandora::ClusterList clusterList) const;

    /**
     *  @brief Add hits to clusters
     *
     *  @param clustersToRebuild  the list of hits to be added to clusters
     *  @param unavailableClusters the list of modified clusters
     */
    pandora::StatusCode AddHitsToClusters(const ClusterToHitMap &clustersToRebuild, pandora::ClusterSet &unavailableClusters) const;
    pandora::StatusCode AddHitsToClusters(const ClusterToHitMap &clustersToRebuild, pandora::ClusterSet &unavailableClusters, pandora::ClusterList clusterList) const;

    /**
     *  @brief Re-build clusters
     *
     *  @param clustersAtStart  the initial mapping of clusters to hits
     *  @param unavailableClusters  the list of unavailable clusters
     */
    pandora::StatusCode RebuildClusters(const ClusterToHitMap &clustersAtStart, const pandora::ClusterSet &unavailableClusters) const;

    std::string  m_reclusteringAlgorithmName;  ///< Name of daughter algorithm to use for cluster re-building
    float        m_minTrackLength;             ///< Minimum length of track clusters to consolidate
    float        m_maxClusterLength;           ///< Maximum length of shower clusters to use in re-building
    unsigned int m_halfWindowLayers;           ///< Size of layer window for sliding fit results
    std::string  m_outputClusterListName;
    std::string  m_inputClusterListName;
    float        m_groupingContract;
    float	 m_toleranceContract;
    float	 m_toleranceMerge;
};

//---------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *ClusterAdjustmentAlgorithm::Factory::CreateAlgorithm() const
{
    return new ClusterAdjustmentAlgorithm();
}

} // namespace example_content

#endif // #ifndef EXAMPLE_CLUSTER_ADJUSTMENT_ALGORITHM_H
