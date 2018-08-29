/**
 *  @file   ExampleAlgorithms/KinkSplittingAlgorithm.h
 *
 *  @brief  Header file for the kink splitting algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_KINK_SPLITTING_ALGORITHM_H
#define EXAMPLE_KINK_SPLITTING_ALGORITHM_H 1

#include "ExampleAlgorithms/TwoDSlidingFitSplittingAlgorithm.h"

namespace example_content
{

/**
 *  @brief  KinkSplittingAlgorithm class
 */
class KinkSplittingAlgorithm : public TwoDSlidingFitSplittingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    KinkSplittingAlgorithm();

    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    /**
     *  @brief  Use sliding linear fit to identify the best split position
     *
     *  @param  slidingFitResult the input sliding fit result
     *  @param  splitPosition the best split position
     *
     *  @return pandora::StatusCode
     */
    pandora::StatusCode FindBestSplitPosition(const TwoDSlidingFitResult &slidingFitResult, pandora::CartesianVector &splitPosition) const;

    float           m_maxScatterRms;          ///<
    float           m_maxScatterCosTheta;     ///<
    float           m_maxSlidingCosTheta;     ///<
};

//---------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *KinkSplittingAlgorithm::Factory::CreateAlgorithm() const
{
    return new KinkSplittingAlgorithm();
}


} // namespace example_content

#endif // #ifndef EXAMPLE_KINK_SPLITTING_ALGORITHM_H
