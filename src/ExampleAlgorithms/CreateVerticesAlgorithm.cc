/**
 *  @file   ExampleContent/src/ExampleAlgorithms/CreateVerticesAlgorithm.cc
 * 
 *  @brief  Implementation of the create vertices algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CreateVerticesAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode CreateVerticesAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode CreateVerticesAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
