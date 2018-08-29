/**
 *  @file   ExampleAlgorithms/TwoDSlidingFitSplittingAlgorithm.h
 *
 *  @brief  Header file for the two dimensional sliding fit splitting algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_TWO_D_SLIDING_FIT_SPLITTING_ALGORITHM_H
#define EXAMPLE_TWO_D_SLIDING_FIT_SPLITTING_ALGORITHM_H 1

#include "ExampleAlgorithms/LArTwoDSlidingFitResult.h"

#include "ExampleAlgorithms/ClusterSplittingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  TwoDSlidingFitSplittingAlgorithm class
 */
class TwoDSlidingFitSplittingAlgorithm : public ClusterSplittingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    TwoDSlidingFitSplittingAlgorithm();

protected:
    virtual pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    /**
     *  @brief  Use sliding linear fit to identify the best split position
     *
     *  @param  slidingFitResult the input sliding fit result
     *  @param  splitPosition the best split position
     *
     *  @return pandora::StatusCode
     */
    virtual pandora::StatusCode FindBestSplitPosition(const TwoDSlidingFitResult &slidingFitResult, 
        pandora::CartesianVector& splitPosition) const = 0;

    unsigned int    m_slidingFitHalfWindow;   ///<
    float           m_minClusterLength;       ///<

private:
    pandora::StatusCode DivideCaloHits(const pandora::Cluster *const pCluster, pandora::CaloHitList &firstCaloHitList,
        pandora::CaloHitList &secondCaloHitList) const;

    /**
     *  @brief  Use sliding linear fit to separate cluster into two fragments
     *
     *  @param  slidingFitResult the input sliding fit result
     *  @param  splitPosition the split position
     *  @param  firstCaloHitList the hits in the first cluster fragment
     *  @param  secondCaloHitList the hits in the second cluster fragment
     *
     *  @return pandora::StatusCode
     */
    pandora::StatusCode DivideCaloHits(const TwoDSlidingFitResult &slidingFitResult, const pandora::CartesianVector& splitPosition, 
        pandora::CaloHitList &firstCaloHitList, pandora::CaloHitList &secondCaloHitList) const;
};

} // namespace example_content

#endif // #ifndef EXAMPLE_TWO_D_SLIDING_FIT_SPLITTING_ALGORITHM_H
