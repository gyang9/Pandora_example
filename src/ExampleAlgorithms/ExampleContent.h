/**
 *  @file   ExampleContent/include/ExampleContent.h
 * 
 *  @brief  Header file detailing example pandora content
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_CONTENT_H
#define EXAMPLE_CONTENT_H 1

#include "ExampleAlgorithms/AccessListsAlgorithm.h"
#include "ExampleAlgorithms/CreateAdditionalCaloHitsAlgorithm.h"
#include "ExampleAlgorithms/CreateClustersAlgorithm.h"
#include "ExampleAlgorithms/CreateClustersDaughterAlgorithm.h"
#include "ExampleAlgorithms/CreatePfosAlgorithm.h"
#include "ExampleAlgorithms/CreateVerticesAlgorithm.h"
#include "ExampleAlgorithms/DeleteClustersAlgorithm.h"
#include "ExampleAlgorithms/DisplayListsAlgorithm.h"
#include "ExampleAlgorithms/FragmentClustersAlgorithm.h"
#include "ExampleAlgorithms/MergeClustersAlgorithm.h"
#include "ExampleAlgorithms/ReconfigureClustersAlgorithm.h"
#include "ExampleAlgorithms/SelectHitSubsetAlgorithm.h"
#include "ExampleAlgorithms/UseAlgorithmToolAlgorithm.h"
#include "ExampleAlgorithms/UsePluginsAlgorithm.h"
#include "ExampleAlgorithms/WriteTreeAlgorithm.h"
#include "ExampleAlgorithms/PreProcessingAlgorithm.h"

#include "ExampleAlgorithms/ClusteringParentAlgorithm.h"
#include "ExampleAlgorithms/TrackClusterCreationAlgorithm.h"

#include "ExampleAlgorithms/KinkSplittingAlgorithm.h"
#include "ExampleAlgorithms/LayerSplittingAlgorithm.h"
#include "ExampleAlgorithms/LongitudinalAssociationAlgorithm.h"
#include "ExampleAlgorithms/TransverseAssociationAlgorithm.h"
#include "ExampleAlgorithms/LongitudinalExtensionAlgorithm.h"
#include "ExampleAlgorithms/TransverseExtensionAlgorithm.h"
#include "ExampleAlgorithms/TrackConsolidationAlgorithm.h"
#include "ExampleAlgorithms/DeltaRayExtensionAlgorithm.h"
#include "ExampleAlgorithms/DeltaRayGrowingAlgorithm.h"
#include "ExampleAlgorithms/DeltaRayIdentificationAlgorithm.h"
#include "ExampleAlgorithms/DeltaRayMatchingAlgorithm.h"
#include "ExampleAlgorithms/DeltaRayShowerHitsTool.h"
#include "ExampleAlgorithms/DeltaRaySplittingAlgorithm.h"
#include "ExampleAlgorithms/UnattachedDeltaRaysAlgorithm.h"

/*
#include "ExampleAlgorithms/CrossGapsAssociationAlgorithm.h"
#include "ExampleAlgorithms/CrossGapsExtensionAlgorithm.h"
#include "ExampleAlgorithms/OvershootSplittingAlgorithm.h"
#include "ExampleAlgorithms/SimpleClusterCreationAlgorithm.h"

#include "ExampleAlgorithms/BranchSplittingAlgorithm.h"
#include "ExampleAlgorithms/ClusterSplittingAlgorithm.h"
#include "ExampleAlgorithms/CrossedTrackSplittingAlgorithm.h"
#include "ExampleAlgorithms/TwoDSlidingFitConsolidationAlgorithm.h"
#include "ExampleAlgorithms/TwoDSlidingFitMultiSplitAlgorithm.h"
#include "ExampleAlgorithms/TwoDSlidingFitSplittingAlgorithm.h"
#include "ExampleAlgorithms/TwoDSlidingFitSplittingAndSplicingAlgorithm.h"
#include "ExampleAlgorithms/TwoDSlidingFitSplittingAndSwitchingAlgorithm.h"
#include "ExampleAlgorithms/VertexSplittingAlgorithm.h"
#include "ExampleAlgorithms/ClusterAssociationAlgorithm.h"
#include "ExampleAlgorithms/ClusterExtensionAlgorithm.h"
#include "ExampleAlgorithms/ClusterGrowingAlgorithm.h"
#include "ExampleAlgorithms/ClusterMergingAlgorithm.h"
#include "ExampleAlgorithms/SimpleClusterGrowingAlgorithm.h"
#include "ExampleAlgorithms/SimpleClusterMergingAlgorithm.h"
*/

#include "ExampleAlgorithmTools/ExampleAlgorithmTool.h"

#include "ExamplePlugins/ExampleEnergyCorrectionPlugin.h"
#include "ExamplePlugins/ExampleParticleIdPlugin.h"
#include "ExamplePlugins/ExamplePseudoLayerPlugin.h"

/**
 *  @brief  ExampleContent class
 */
class ExampleContent
{
public:
    #define EXAMPLE_ALGORITHM_LIST(d)                                                                                   \
        d("AccessListsExample",                         example_content::AccessListsAlgorithm::Factory)                 \
        d("CreateAdditionalCaloHitsExample",            example_content::CreateAdditionalCaloHitsAlgorithm::Factory)    \
        d("CreateClustersExample",                      example_content::CreateClustersAlgorithm::Factory)              \
        d("CreateClustersDaughterExample",              example_content::CreateClustersDaughterAlgorithm::Factory)      \
        d("CreatePfosExample",                          example_content::CreatePfosAlgorithm::Factory)                  \
        d("CreateVerticesExample",                      example_content::CreateVerticesAlgorithm::Factory)              \
        d("DeleteClustersExample",                      example_content::DeleteClustersAlgorithm::Factory)              \
        d("DisplayListsExample",                        example_content::DisplayListsAlgorithm::Factory)                \
        d("FragmentClustersExample",                    example_content::FragmentClustersAlgorithm::Factory)            \
        d("MergeClustersExample",                       example_content::MergeClustersAlgorithm::Factory)               \
        d("ReconfigureClustersExample",                 example_content::ReconfigureClustersAlgorithm::Factory)         \
        d("SelectHitSubsetExample",                     example_content::SelectHitSubsetAlgorithm::Factory)             \
        d("UseAlgorithmToolExample",                    example_content::UseAlgorithmToolAlgorithm::Factory)            \
        d("UsePluginsExample",                          example_content::UsePluginsAlgorithm::Factory)                  \
        d("WriteTreeExample",                           example_content::WriteTreeAlgorithm::Factory)			\
        d("ClusteringParentExample",                    example_content::ClusteringParentAlgorithm::Factory)		\
	d("PreProcessingExample",                       example_content::PreProcessingAlgorithm::Factory)               \
	d("TrackClusterCreationExample",                example_content::TrackClusterCreationAlgorithm::Factory)        \
	d("KinkSplittingExample",                       example_content::KinkSplittingAlgorithm::Factory)               \
	d("LayerSplittingExample",                      example_content::LayerSplittingAlgorithm::Factory)              \
	d("LongitudinalExtensionExample",               example_content::LongitudinalExtensionAlgorithm::Factory)       \
        d("LongitudinalAssociationExample",             example_content::LongitudinalAssociationAlgorithm::Factory)     \
        d("TransverseAssociationExample",               example_content::TransverseAssociationAlgorithm::Factory)       \
        d("TransverseExtensionExample",                 example_content::TransverseExtensionAlgorithm::Factory)         \
	d("TrackConsolidationExample",                  example_content::TrackConsolidationAlgorithm::Factory)          \
        d("DeltaRaySplittingExample",                   example_content::DeltaRaySplittingAlgorithm::Factory)           \
        d("DeltaRayExtensionExample",                   example_content::DeltaRayExtensionAlgorithm::Factory)           \
        d("DeltaRayGrowingExample",                     example_content::DeltaRayGrowingAlgorithm::Factory)             \
        d("DeltaRayIdentificationExample",              example_content::DeltaRayIdentificationAlgorithm::Factory)      \
        d("DeltaRayMatchingExample",                    example_content::DeltaRayMatchingAlgorithm::Factory)            \
        d("DeltaRayUnattachedExample",                  example_content::UnattachedDeltaRaysAlgorithm::Factory)           


	/*
	d("CrossGapsAssociationExample",                example_content::CrossGapsAssociationAlgorithm::Factory)        \
        d("CrossGapsExtensionExample",                  example_content::CrossGapsExtensionAlgorithm::Factory)          \
	d("OvershootSplittingExample",                  example_content::OvershootSplittingAlgorithm::Factory)          \
	d("TrackConsolidationExample",                  example_content::TrackConsolidationAlgorithm::Factory)          \
	d("SimpleClusterCreationExample",               example_content::SimpleClusterCreationAlgorithm::Factory)       \
	d("BranchSplittingExample",                     example_content::BranchSplittingAlgorithm::Factory)             \
	d("ClusterAssociationExample",                  example_content::ClusterAssociationAlgorithm::Factory)          \
        d("ClusterExtensionExample",                    example_content::ClusterExtensionAlgorithm::Factory)            \
        d("ClusterGrowingExample",                      example_content::ClusterGrowingAlgorithm::Factory)              \
        d("ClusterMergingExample",                      example_content::ClusterMergingAlgorithm::Factory)              \
        d("SimpleClusterGrowingExample",                example_content::SimpleClusterGrowingAlgorithm::Factory)        \
        d("SimpleClusterMergingExample",                example_content::SimpleClusterMergingAlgorithm::Factory)        \
        d("ClusterSplittingExample",                    example_content::ClusterSplittingAlgorithm::Factory)            \
        d("CrossedTrackSplittingExample",               example_content::CrossedTrackSplittingAlgorithm::Factory)       \
        d("DeltaRaySplittingExample",                   example_content::DeltaRaySplittingAlgorithm::Factory)           \
        d("TwoDSlidingFitConsolidationExample",         example_content::TwoDSlidingFitConsolidationAlgorithm::Factory) \
        d("TwoDSlidingFitMultiSplitExample",            example_content::TwoDSlidingFitMultiSplitAlgorithm::Factory)    \
        d("TwoDSlidingFitSplittingExample",             example_content::TwoDSlidingFitSplittingAlgorithm::Factory)     \
        d("TwoDSlidingFitSplittingAndSplicingExample",  example_content::TwoDSlidingFitSplittingAndSplicingAlgorithm::Factory)        \
        d("TwoDSlidingFitSplittingAndSwitchingExample", example_content::TwoDSlidingFitSplittingAndSwitchingAlgorithm::Factory)       \
        d("VertexSplittingExample",                     example_content::VertexSplittingAlgorithm::Factory)         
	*/

    #define EXAMPLE_ALGORITHM_TOOL_LIST(d)                                                                              \
        d("AlgorithmToolExample",                       example_content::ExampleAlgorithmTool::Factory)

    #define EXAMPLE_ENERGY_CORRECTION_LIST(d)                                                                           \
        d("EnergyCorrectionExample", pandora::HADRONIC, example_content::ExampleEnergyCorrectionPlugin)

    #define EXAMPLE_PARTICLE_ID_LIST(d)                                                                                 \
        d("ParticleIdExample",                          example_content::ExampleParticleIdPlugin)

    /**
     *  @brief  Register all the example content algorithms and tools with pandora
     * 
     *  @param  pandora the pandora instance with which to register content
     */
    static pandora::StatusCode RegisterExampleAlgorithms(const pandora::Pandora &pandora);

    /**
     *  @brief  Register the example content plugins with pandora
     * 
     *  @param  pandora the pandora instance with which to register content
     */
    static pandora::StatusCode RegisterExamplePlugins(const pandora::Pandora &pandora);
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::StatusCode ExampleContent::RegisterExampleAlgorithms(const pandora::Pandora &pandora)
{
    EXAMPLE_ALGORITHM_LIST(PANDORA_REGISTER_ALGORITHM);
    EXAMPLE_ALGORITHM_TOOL_LIST(PANDORA_REGISTER_ALGORITHM_TOOL);

    return pandora::STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::StatusCode ExampleContent::RegisterExamplePlugins(const pandora::Pandora &pandora)
{
    EXAMPLE_ENERGY_CORRECTION_LIST(PANDORA_REGISTER_ENERGY_CORRECTION);
    EXAMPLE_PARTICLE_ID_LIST(PANDORA_REGISTER_PARTICLE_ID);
    PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::SetPseudoLayerPlugin(pandora, new example_content::ExamplePseudoLayerPlugin));

    return pandora::STATUS_CODE_SUCCESS;
}

#endif // #ifndef EXAMPLE_CONTENT_H
