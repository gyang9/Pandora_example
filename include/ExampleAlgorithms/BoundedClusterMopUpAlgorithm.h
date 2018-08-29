/**
 *  @file   ExampleAlgorithms/BoundedClusterMopUpAlgorithm.h
 * 
 *  @brief  Header file for the bounded cluster mop up algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_BOUNDED_CLUSTER_MOP_UP_ALGORITHM_H
#define EXAMPLE_BOUNDED_CLUSTER_MOP_UP_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

#include "ExampleAlgorithms/LArTwoDSlidingShowerFitResult.h"

#include "ExampleAlgorithms/ClusterMopUpBaseAlgorithm.h"

namespace example_content
{

/**
 *  @brief  BoundedClusterMopUpAlgorithm class
 */

class BoundedClusterMopUpAlgorithm : public ClusterMopUpBaseAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    BoundedClusterMopUpAlgorithm();

private:
    /**
     *  @brief  XSampling class
     */
    class XSampling
    {
    public:
        /**
         *  @brief  Constructor
         * 
         *  @param  fitResult the sliding fit result
         */
        XSampling(const TwoDSlidingFitResult &fitResult);

        /**
         *  @brief  Convert an x position into a sampling bin
         *
         *  @param  x  the input x coordinate
         */
        int GetBin(const float x) const; 

        float     m_minX;          ///< The min x value
        float     m_maxX;          ///< The max x value
        int       m_nPoints;       ///< The number of sampling points to be used
    };

    void ClusterMopUp(const pandora::ClusterList &pfoClusters, const pandora::ClusterList &remnantClusters) const;

    /**
     *  @brief  Get the shower position map containing high and low edge z positions in bins of x
     * 
     *  @param  fitResult the sliding shower fit result
     *  @param  xSampling the x sampling details
     *  @param  showerPositionMap to receive the shower position map
     */
    void GetShowerPositionMap(const TwoDSlidingShowerFitResult &fitResult, const XSampling &xSampling, ShowerPositionMap &showerPositionMap) const;

    /**
     *  @brief  Get the fraction of hits in a cluster bounded by a specified shower position map
     * 
     *  @param  pCluster address of the cluster
     *  @param  xSampling the x sampling details
     *  @param  showerPositionMap the shower position map
     * 
     *  @return the fraction of bounded hits
     */
    float GetBoundedFraction(const pandora::Cluster *const pCluster, const XSampling &xSampling, const ShowerPositionMap &showerPositionMap) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    unsigned int    m_slidingFitWindow;             ///< The layer window for the sliding linear fits
    float           m_showerEdgeMultiplier;         ///< Artificially tune width of shower envelope so as to make it more/less inclusive
    float           m_minBoundedFraction;           ///< The minimum cluster bounded fraction for merging
};

} // namespace example_content

#endif // #ifndef EXAMPLE_BOUNDED_CLUSTER_MOP_UP_ALGORITHM_H
