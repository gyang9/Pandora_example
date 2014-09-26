/**
 *  @file   ExampleContent/src/ExampleAlgorithms/DeleteClustersAlgorithm.cc
 * 
 *  @brief  Implementation of the delete clusters algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/DeleteClustersAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode DeleteClustersAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode DeleteClustersAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
