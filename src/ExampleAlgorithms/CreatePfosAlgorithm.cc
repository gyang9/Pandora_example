/**
 *  @file   ExampleContent/src/ExampleAlgorithms/CreatePfosAlgorithm.cc
 * 
 *  @brief  Implementation of the create pfos algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CreatePfosAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode CreatePfosAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode CreatePfosAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
