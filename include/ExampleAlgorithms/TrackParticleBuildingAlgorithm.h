/**
 *  @file   ExampleAlgorithms/TrackParticleBuildingAlgorithm.h
 *
 *  @brief  Header file for the 3D track building algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_TRACK_PARTICLE_BUILDING_ALGORITHM_H
#define EXAMPLE_TRACK_PARTICLE_BUILDING_ALGORITHM_H 1

#include "ExampleAlgorithms/LArTrackPfo.h"

#include "ExampleAlgorithms/CustomParticleCreationAlgorithm.h"

namespace example_content
{

/**
 *  @brief  TrackParticleBuildingAlgorithm class
 */
class TrackParticleBuildingAlgorithm : public CustomParticleCreationAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    TrackParticleBuildingAlgorithm();

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    void CreatePfo(const pandora::ParticleFlowObject *const pInputPfo, const pandora::ParticleFlowObject*& pOutputPfo) const;

    unsigned int    m_slidingFitHalfWindow;   ///<
};

} // namespace example_content

#endif // #ifndef EXAMPLE_TRACK_PARTICLE_BUILDING_ALGORITHM_H
