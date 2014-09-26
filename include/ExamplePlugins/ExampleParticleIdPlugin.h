/**
 *  @file   ExampleContent/include/ExamplePlugins/ExampleParticleIdPlugin.h
 * 
 *  @brief  Header file for the example particle id plugin class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_PARTICLE_ID_PLUGIN_H
#define EXAMPLE_PARTICLE_ID_PLUGIN_H 1

#include "Plugins/ParticleIdPlugin.h"

namespace example_content
{

/**
 *   @brief  ExampleParticleIdPlugin class
 */
class ExampleParticleIdPlugin : public pandora::ParticleIdPlugin
{
public:
    /**
     *  @brief  Default constructor
     */
    ExampleParticleIdPlugin();

    bool IsMatch(const pandora::Cluster *const pCluster) const;

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    unsigned int m_maxInnerLayer;                   ///< Max inner psuedo layer for fast electron id
    float        m_maxEnergy;                       ///< Max electromagnetic energy for fast electron id
    float        m_maxProfileStart;                 ///< Max shower profile start for fast electron id
    float        m_maxProfileDiscrepancy;           ///< Max shower profile discrepancy for fast electron id
    float        m_profileDiscrepancyForAutoId;     ///< Shower profile discrepancy for automatic fast electron selection
    float        m_maxResidualEOverP;               ///< Max absolute difference between unity and ratio em energy / track momentum
};

} // namespace example_content

#endif // #ifndef EXAMPLE_PARTICLE_ID_PLUGIN_H
