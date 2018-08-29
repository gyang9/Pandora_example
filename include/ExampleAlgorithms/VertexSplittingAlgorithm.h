/**
 *  @file   ExampleAlgorithms/VertexSplittingAlgorithm.h
 * 
 *  @brief  Header file for the vertex splitting algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_VERTEX_SPLITTING_ALGORITHM_H
#define EXAMPLE_VERTEX_SPLITTING_ALGORITHM_H 1

#include "ExampleAlgorithms/TwoDSlidingFitSplittingAlgorithm.h"

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  VertexSplittingAlgorithm class
 */
class VertexSplittingAlgorithm : public TwoDSlidingFitSplittingAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    VertexSplittingAlgorithm();

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);
    pandora::StatusCode FindBestSplitPosition(const TwoDSlidingFitResult &slidingFitResult, pandora::CartesianVector &splitPosition) const;

    float           m_splitDisplacementSquared;     ///< Maximum displacement squared
    float           m_vertexDisplacementSquared;    ///< Maximum displacement squared
};

} // namespace example_content

#endif // #ifndef EXAMPLE_VERTEX_SPLITTING_ALGORITHM_H
