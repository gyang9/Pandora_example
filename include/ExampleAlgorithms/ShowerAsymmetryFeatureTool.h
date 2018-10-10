/**
 *  @file   ExampleAlgorithms/ShowerAsymmetryFeatureTool.h
 *
 *  @brief  Header file for the shower asymmetry feature tool class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_SHOWER_ASYMMETRY_FEATURE_TOOL_H
#define EXAMPLE_SHOWER_ASYMMETRY_FEATURE_TOOL_H 1

#include "ExampleAlgorithms/VertexSelectionBaseAlgorithm.h"

#include "ExampleAlgorithms/LArTwoDSlidingFitResult.h"

namespace example_content
{

/**
 *  @brief  ShowerAsymmetryFeatureTool class
 */
class ShowerAsymmetryFeatureTool : public VertexSelectionBaseAlgorithm::VertexFeatureTool
{
public:
    /**
     *  @brief  Default constructor
     */
    ShowerAsymmetryFeatureTool();

    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmToolFactory
    {
    public:
        pandora::AlgorithmTool *CreateAlgorithmTool() const;
    };
    

    /**
     *  @brief  Run the tool
     *
     *  @param  pAlgorithm address of the calling algorithm
     *  @param  pVertex address of the vertex
     *  @param  showerClusterListMap map of the shower cluster lists
     *
     *  @return the shower asymmetry feature
     */
    void Run(LArMvaHelper::MvaFeatureVector &featureVector, const VertexSelectionBaseAlgorithm * const pAlgorithm, const pandora::Vertex * const pVertex,
        const VertexSelectionBaseAlgorithm::SlidingFitDataListMap &, const VertexSelectionBaseAlgorithm::ClusterListMap &,
        const VertexSelectionBaseAlgorithm::KDTreeMap &, const VertexSelectionBaseAlgorithm::ShowerClusterListMap &showerClusterListMap,
        const float, float &);

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    /**
     *  @brief  Get the shower asymmetry feature for a given view
     *
     *  @param  vertexPosition2D the projected vertex position
     *  @param  showerClusterList the list of shower clusters in this view
     *
     *  @return the shower asymmetry feature
     */
    float GetShowerAsymmetryForView(const pandora::CartesianVector &vertexPosition2D, const VertexSelectionBaseAlgorithm::ShowerClusterList &showerClusterList) const;

    /**
     *  @brief  Get whether we should use a given shower cluster for asymmetry calculation
     *
     *  @param  vertexPosition the projected vertex position
     *  @param  showerCluster the shower cluster
     *
     *  @return whether the shower cluster should be considered
     */
    bool ShouldUseShowerCluster(const pandora::CartesianVector &vertexPosition, const VertexSelectionBaseAlgorithm::ShowerCluster &showerCluster) const;

    /**
     *  @brief  Calculate the parameters for the asymmetry calculation
     *
     *  @param  showerCluster the shower cluster
     *  @param  projectedVtxPosition the projected vertex position
     *  @param  showerDirection the direction of the shower axis
     *  @param  beforeVtxEnergy the shower energy before the vertex position
     *  @param  afterVtxEnergy the shower energy after the vertex position
     */
    void CalculateAsymmetryParameters(const VertexSelectionBaseAlgorithm::ShowerCluster &showerCluster, const float projectedVtxPosition,
        const pandora::CartesianVector &showerDirection, float &beforeVtxEnergy, float &afterVtxEnergy) const;

    float   m_vertexClusterDistance;    ///< The distance around the vertex to look for shower clusters
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::AlgorithmTool *ShowerAsymmetryFeatureTool::Factory::CreateAlgorithmTool() const
{
    return new ShowerAsymmetryFeatureTool();
}


} // namespace example_content

#endif // #ifndef EXAMPLE_SHOWER_ASYMMETRY_FEATURE_TOOL_H
