/**
 *  @file   ExampleContent/src/ExampleAlgorithms/CreateClustersAlgorithm.cc
 * 
 *  @brief  Implementation of the create clusters algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CreateClustersAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode CreateClustersAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode CreateClustersAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
