/**
 *  @file   ExampleAlgorithms/DeltaRaySplittingAlgorithm.h
 *
 *  @brief  Header file for the delta ray splitting algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_DELTA_RAY_SPLITTING_ALGORITHM_H
#define EXAMPLE_DELTA_RAY_SPLITTING_ALGORITHM_H 1

#include "ExampleAlgorithms/TwoDSlidingFitSplittingAndSplicingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  DeltaRaySplittingAlgorithm class
 */
class DeltaRaySplittingAlgorithm : public TwoDSlidingFitSplittingAndSplicingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    DeltaRaySplittingAlgorithm();

private:
    void FindBestSplitPosition(const TwoDSlidingFitResult &branchSlidingFit, const TwoDSlidingFitResult &replacementSlidingFit, 
        pandora::CartesianVector &replacementStartPosition, pandora::CartesianVector &branchSplitPosition, 
        pandora::CartesianVector &branchSplitDirection) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float         m_stepSize;                       ///<
    float         m_maxTransverseDisplacement;      ///<
    float         m_maxLongitudinalDisplacement;    ///<
    float         m_minCosRelativeAngle;            ///<
};

} // namespace example_content

#endif // #ifndef EXAMPLE_DELTA_RAY_SPLITTING_ALGORITHM_H
