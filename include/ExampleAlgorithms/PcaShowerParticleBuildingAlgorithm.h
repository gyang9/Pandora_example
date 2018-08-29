/**
 *  @file   ExampleAlgorithms/PcaShowerParticleBuildingAlgorithm.h
 *
 *  @brief  Header file for the neutrino event creation algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_PCA_SHOWER_PARTICLE_BUILDING_ALGORITHM_H
#define EXAMPLE_PCA_SHOWER_PARTICLE_BUILDING_ALGORITHM_H 1

#include "ExampleAlgorithms/LArShowerPfo.h"

#include "ExampleAlgorithms/CustomParticleCreationAlgorithm.h"

namespace example_content
{

/**
 *  @brief  PcaShowerParticleBuildingAlgorithm class
 */
class PcaShowerParticleBuildingAlgorithm : public CustomParticleCreationAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    PcaShowerParticleBuildingAlgorithm();

    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };

private:
    void CreatePfo(const pandora::ParticleFlowObject *const pInputPfo, const pandora::ParticleFlowObject *&pOutputPfo) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    unsigned int    m_layerFitHalfWindow;       ///< 
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *PcaShowerParticleBuildingAlgorithm::Factory::CreateAlgorithm() const
{
    return new PcaShowerParticleBuildingAlgorithm();
}

} // namespace example_content

#endif // #ifndef EXAMPLE_PCA_SHOWER_PARTICLE_BUILDING_ALGORITHM_H
