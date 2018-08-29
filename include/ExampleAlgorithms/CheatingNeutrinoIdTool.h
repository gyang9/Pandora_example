/**
 *  @file   ExampleAlgorithms/CheatingNeutrinoIdTool.h
 *
 *  @brief  Header file for the cheating neutrino id tool class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_CHEATING_NEUTRINO_ID_TOOL_H
#define EXAMPLE_CHEATING_NEUTRINO_ID_TOOL_H 1

#include "ExampleAlgorithms/CheatingSliceIdBaseTool.h"
#include "ExampleAlgorithms/MasterAlgorithm.h"

namespace example_content
{

/**
 *  @brief  CheatingNeutrinoIdTool class
 */
class CheatingNeutrinoIdTool : public CheatingSliceIdBaseTool
{
public:
    void SelectOutputPfos(const pandora::Algorithm *const pAlgorithm, const SliceHypotheses &nuSliceHypotheses, const SliceHypotheses &crSliceHypotheses, pandora::PfoList &selectedPfos);

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CHEATING_NEUTRINO_ID_TOOL_H
