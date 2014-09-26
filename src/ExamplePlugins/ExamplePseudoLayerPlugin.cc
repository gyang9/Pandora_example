/**
 *  @file   ExampleContent/src/ExamplePlugins/ExamplePseudoLayerPlugin.cc
 * 
 *  @brief  Implementation of the example pseudo layer plugin class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExamplePlugins/ExamplePseudoLayerPlugin.h"

using namespace pandora;

namespace example_content
{

ExamplePseudoLayerPlugin::ExamplePseudoLayerPlugin() :
    m_zPitch(1.f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

unsigned int ExamplePseudoLayerPlugin::GetPseudoLayer(const CartesianVector &positionVector) const
{
    const float zLayer((positionVector.GetZ()) / m_zPitch);

    if (zLayer < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_FAILURE);

    return static_cast<unsigned int>(zLayer);
}

//------------------------------------------------------------------------------------------------------------------------------------------

unsigned int ExamplePseudoLayerPlugin::GetPseudoLayerAtIp() const
{
    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ExamplePseudoLayerPlugin::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "ZPitch", m_zPitch));

    if (m_zPitch < std::numeric_limits<float>::epsilon())
        return STATUS_CODE_INVALID_PARAMETER;

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
