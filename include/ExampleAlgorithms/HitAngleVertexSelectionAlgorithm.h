/**
 *  @file   ExampleAlgorithms/HitAngleVertexSelectionAlgorithm.h
 *
 *  @brief  Header file for the hit angle vertex selection algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_HIT_ANGLE_VERTEX_SELECTION_ALGORITHM_H
#define EXAMPLE_HIT_ANGLE_VERTEX_SELECTION_ALGORITHM_H 1

#include "ExampleAlgorithms/VertexSelectionBaseAlgorithm.h"

namespace example_content
{

/**
 *  @brief  HitAngleVertexSelectionAlgorithm class
 */
class HitAngleVertexSelectionAlgorithm : public VertexSelectionBaseAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    HitAngleVertexSelectionAlgorithm();

private:
    void GetVertexScoreList(const pandora::VertexVector &vertexVector, const BeamConstants &beamConstants, HitKDTree2D &kdTreeU,
        HitKDTree2D &kdTreeV, HitKDTree2D &kdTreeW, VertexScoreList &vertexScoreList) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    VertexFeatureTool::FeatureToolVector m_featureToolVector; ///< The feature tool map
};

} // namespace example_content

#endif // #ifndef EXAMPLE_HIT_ANGLE_VERTEX_SELECTION_ALGORITHM_H
