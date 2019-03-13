/**
 *  @file   ExampleContent/include/ExampleContent.h
 * 
 *  @brief  Header file detailing example pandora content
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_CONTENT_H
#define EXAMPLE_CONTENT_H 1

#include "ExampleAlgorithms/PreProcessingAlgorithm.h"
#include "ExampleAlgorithms/ThreeDHitCreationAlgorithm.h"
#include "ExampleAlgorithms/VisualMonitoringAlgorithm.h"
#include "ExampleAlgorithms/ClusteringParentAlgorithm.h"
#include "ExampleAlgorithms/SimpleClusterCreationAlgorithm.h"
#include "ExampleAlgorithms/CubeTwoDTrackMatchingAlgorithm.h"
#include "ExampleAlgorithms/CubeTwoDBaseMatchingAlgorithm.h"

/**
 *  @brief  ExampleContent class
 */
class ExampleContent
{
public:
    #define EXAMPLE_ALGORITHM_LIST(d)                                                                                   \
	d("PreProcessingExample",                       example_content::PreProcessingAlgorithm::Factory)               \
        d("ThreeDHitCreationExample",                   example_content::ThreeDHitCreationAlgorithm::Factory)		\
	d("VisualMonitoring",                           example_content::VisualMonitoringAlgorithm::Factory)            \
        d("SimpleClusterCreationExample",               example_content::SimpleClusterCreationAlgorithm::Factory)       \
	d("CubeTwoDTrackMatching",                  	example_content::CubeTwoDTrackMatchingAlgorithm::Factory)	\
	d("ClusteringParentExample",		    	example_content::ClusteringParentAlgorithm::Factory)

    #define EXAMPLE_ALGORITHM_TOOL_LIST(d)                                                                              

    #define EXAMPLE_ENERGY_CORRECTION_LIST(d)                                                                           

    #define EXAMPLE_PARTICLE_ID_LIST(d)                                                                                 


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
    //PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::SetPseudoLayerPlugin(pandora, new example_content::ExamplePseudoLayerPlugin));

    return pandora::STATUS_CODE_SUCCESS;
}

#endif // #ifndef EXAMPLE_CONTENT_H
