/**
 *  @file   ExampleContent/src/ExampleAlgorithmTools/ExampleAlgorithmTool.cc
 * 
 *  @brief  Implementation of the example algorithm tool class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithmTools/ExampleAlgorithmTool.h"

using namespace pandora;

namespace example_content
{

StatusCode ExampleAlgorithmTool::ExampleToolFunctionality(const UseAlgorithmToolAlgorithm *const /*pAlgorithm*/)
{
    // Algorithm tool code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ExampleAlgorithmTool::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
