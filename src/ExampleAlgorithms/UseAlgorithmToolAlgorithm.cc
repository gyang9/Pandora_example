/**
 *  @file   ExampleContent/src/ExampleAlgorithms/UseAlgorithmToolAlgorithm.cc
 * 
 *  @brief  Implementation of the use algorithm tool algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/UseAlgorithmToolAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode UseAlgorithmToolAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode UseAlgorithmToolAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
