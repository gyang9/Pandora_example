/**
 *  @file   ExampleContent/src/ExamplePlugins/ExampleParticleIdPlugin.cc
 * 
 *  @brief  Implementation of the example particle id plugin class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExamplePlugins/ExampleParticleIdPlugin.h"

using namespace pandora;

namespace example_content
{

ExampleParticleIdPlugin::ExampleParticleIdPlugin() :
    m_maxInnerLayer(4),
    m_maxEnergy(5.f),
    m_maxProfileStart(4.5f),
    m_maxProfileDiscrepancy(0.6f),
    m_profileDiscrepancyForAutoId(0.5f),
    m_maxResidualEOverP(0.2f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool ExampleParticleIdPlugin::IsMatch(const Cluster *const /*pCluster*/) const
{
    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ExampleParticleIdPlugin::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxInnerLayer", m_maxInnerLayer));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxEnergy", m_maxEnergy));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxProfileStart", m_maxProfileStart));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxProfileDiscrepancy", m_maxProfileDiscrepancy));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "ProfileDiscrepancyForAutoId", m_profileDiscrepancyForAutoId));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxResidualEOverP", m_maxResidualEOverP));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
