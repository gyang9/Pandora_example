/**
 *  @file   ExampleContent/src/ExamplePlugins/ExampleEnergyCorrectionPlugin.cc
 * 
 *  @brief  Implementation of the example energy correction plugin class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExamplePlugins/ExampleEnergyCorrectionPlugin.h"

using namespace pandora;

namespace example_content
{

ExampleEnergyCorrectionPlugin::ExampleEnergyCorrectionPlugin() :
    m_muonHitEnergy(0.5f),
    m_coilEnergyLossCorrection(10.f),
    m_minMuonHitsInInnerLayer(3),
    m_coilEnergyCorrectionChi(3.f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ExampleEnergyCorrectionPlugin::MakeEnergyCorrections(const Cluster *const /*pCluster*/, float &/*correctedHadronicEnergy*/) const
{
    

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ExampleEnergyCorrectionPlugin::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MuonHitEnergy", m_muonHitEnergy));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "CoilEnergyLossCorrection", m_coilEnergyLossCorrection));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MinMuonHitsInInnerLayer", m_minMuonHitsInInnerLayer));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "CoilEnergyCorrectionChi", m_coilEnergyCorrectionChi));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
