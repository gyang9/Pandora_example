/**
 *  @file   ExampleAlgorithms/CheatingCosmicRayTaggingTool.h
 *
 *  @brief  Header file for the cheating cosmic-ray tagging tool class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_CHEATING_COSMIC_RAY_TAGGING_TOOL_H
#define EXAMPLE_CHEATING_COSMIC_RAY_TAGGING_TOOL_H 1

#include "ExampleAlgorithms/MasterAlgorithm.h"

namespace example_content
{

/**
 *  @brief  CheatingCosmicRayTaggingTool class
 */
class CheatingCosmicRayTaggingTool : public CosmicRayTaggingBaseTool
{
public:
    /**
     *  @brief  Default constructor
     */
    CheatingCosmicRayTaggingTool();

    void FindAmbiguousPfos(const pandora::PfoList &parentCosmicRayPfos, pandora::PfoList &ambiguousPfos, const MasterAlgorithm *const pAlgorithm);

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float   m_maxCosmicRayFraction;        ///< The maximum cosmic ray fraction for a pfo to be declared an ambiguous cosmic ray
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CHEATING_COSMIC_RAY_TAGGING_TOOL_H
