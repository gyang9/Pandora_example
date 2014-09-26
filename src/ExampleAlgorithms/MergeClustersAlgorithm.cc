/**
 *  @file   ExampleContent/src/ExampleAlgorithms/MergeClustersAlgorithm.cc
 * 
 *  @brief  Implementation of the merge clusters algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/MergeClustersAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode MergeClustersAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode MergeClustersAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
