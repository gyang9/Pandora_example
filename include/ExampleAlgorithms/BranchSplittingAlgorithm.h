/**
 *  @file   ExampleAlgorithms/BranchSplittingAlgorithm.h
 *
 *  @brief  Header file for the branch splitting algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_BRANCH_SPLITTING_ALGORITHM_H
#define EXAMPLE_BRANCH_SPLITTING_ALGORITHM_H 1

#include "ExampleAlgorithms/TwoDSlidingFitSplittingAndSplicingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  BranchSplittingAlgorithm class
 */
class BranchSplittingAlgorithm : public TwoDSlidingFitSplittingAndSplicingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    BranchSplittingAlgorithm();

private:
    void FindBestSplitPosition(const TwoDSlidingFitResult &branchSlidingFit, const TwoDSlidingFitResult &replacementSlidingFit, 
        pandora::CartesianVector &replacementStartPosition, pandora::CartesianVector &branchSplitPosition, 
        pandora::CartesianVector &branchSplitDirection) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float           m_maxTransverseDisplacement;        ///< 
    float           m_maxLongitudinalDisplacement;      ///< 
    float           m_minLongitudinalExtension;         ///< 
    float           m_minCosRelativeAngle;              ///< 
    float           m_projectionAngularAllowance;       ///< 
};

} // namespace example_content

#endif // #ifndef EXAMPLE_BRANCH_SPLITTING_ALGORITHM_H
