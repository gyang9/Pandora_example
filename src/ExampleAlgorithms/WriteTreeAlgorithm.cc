/**
 *  @file   ExampleContent/src/ExampleAlgorithms/WriteTreeAlgorithm.cc
 * 
 *  @brief  Implementation of the write tree algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/WriteTreeAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode WriteTreeAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode WriteTreeAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
