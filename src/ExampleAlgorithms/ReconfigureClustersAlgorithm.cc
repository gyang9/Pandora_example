/**
 *  @file   ExampleContent/src/ExampleAlgorithms/ReconfigureClustersAlgorithm.cc
 * 
 *  @brief  Implementation of the reconfigure clusters algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/ReconfigureClustersAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode ReconfigureClustersAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ReconfigureClustersAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
