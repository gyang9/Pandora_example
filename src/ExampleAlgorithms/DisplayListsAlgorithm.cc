/**
 *  @file   ExampleContent/src/ExampleAlgorithms/DisplayListsAlgorithm.cc
 * 
 *  @brief  Implementation of the display lists algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/DisplayListsAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode DisplayListsAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode DisplayListsAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
