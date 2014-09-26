/**
 *  @file   ExampleContent/src/ExampleAlgorithms/FragmentClustersAlgorithm.cc
 * 
 *  @brief  Implementation of the fragment clusters algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/FragmentClustersAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode FragmentClustersAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode FragmentClustersAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
