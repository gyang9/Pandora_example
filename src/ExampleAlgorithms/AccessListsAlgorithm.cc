/**
 *  @file   ExampleContent/src/ExampleAlgorithms/AccessListsAlgorithm.cc
 * 
 *  @brief  Implementation of the access lists algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/AccessListsAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode AccessListsAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode AccessListsAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
