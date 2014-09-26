/**
 *  @file   ExampleContent/include/ExamplePlugins/ExampleEnergyCorrectionPlugin.h
 * 
 *  @brief  Header file for the example energy correction plugin class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_ENERGY_CORRECTION_PLUGIN_H
#define EXAMPLE_ENERGY_CORRECTION_PLUGIN_H 1

#include "Plugins/EnergyCorrectionsPlugin.h"

namespace example_content
{

/**
 *   @brief  ExampleEnergyCorrectionPlugin class.
 */
class ExampleEnergyCorrectionPlugin : public pandora::EnergyCorrectionPlugin
{
public:
    /**
     *  @brief  Default constructor
     */
    ExampleEnergyCorrectionPlugin();

    pandora::StatusCode MakeEnergyCorrections(const pandora::Cluster *const pCluster, float &correctedEnergy) const;

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float           m_muonHitEnergy;                    ///< The energy for a digital muon calorimeter hit, units GeV
    float           m_coilEnergyLossCorrection;         ///< Energy correction due to missing energy deposited in coil, units GeV
    unsigned int    m_minMuonHitsInInnerLayer;          ///< Min muon hits in muon inner layer to correct charged cluster energy
    float           m_coilEnergyCorrectionChi;          ///< Track-cluster chi value used to assess need for coil energy correction
};

} // namespace example_content

#endif // #ifndef EXAMPLE_ENERGY_CORRECTION_PLUGIN_H
