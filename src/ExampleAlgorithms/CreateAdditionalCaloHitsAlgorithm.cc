/**
 *  @file   ExampleContent/src/ExampleAlgorithms/CreateAdditionalCaloHitsAlgorithm.cc
 * 
 *  @brief  Implementation of the create additional calo hits algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CreateAdditionalCaloHitsAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode CreateAdditionalCaloHitsAlgorithm::Run()
{
    // Algorithm code here

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode CreateAdditionalCaloHitsAlgorithm::ReadSettings(const TiXmlHandle /*xmlHandle*/)
{
    // Read settings from xml file here

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
