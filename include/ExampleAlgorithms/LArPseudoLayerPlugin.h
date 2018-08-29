/**
 *  @file   ExampleAlgorithms/LArPseudoLayerPlugin.h
 *
 *  @brief  Header file for the lar pseudo layer plugin class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_PSEUDO_LAYER_PLUGIN_H
#define EXAMPLE_PSEUDO_LAYER_PLUGIN_H 1

#include "Plugins/PseudoLayerPlugin.h"

namespace example_content
{

/**
 *  @brief  LarPandoraPseudoLayerPlugin class
 */
class LArPseudoLayerPlugin : public pandora::PseudoLayerPlugin
{
public:
    /**
     *  @brief  Constructor
     */
    LArPseudoLayerPlugin();

    unsigned int GetPseudoLayer(const pandora::CartesianVector &positionVector) const;
    unsigned int GetPseudoLayerAtIp() const;

private:
    pandora::StatusCode Initialize();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float           m_zPitch;       ///< The z pitch
    float           m_zOffset;      ///< The z offset
    unsigned int    m_zerothLayer;  ///< The zeroth layer
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline unsigned int LArPseudoLayerPlugin::GetPseudoLayerAtIp() const
{
    return 0;
}

} // namespace lar

#endif // #ifndef EXAMPLE_PSEUDO_LAYER_PLUGIN_H
