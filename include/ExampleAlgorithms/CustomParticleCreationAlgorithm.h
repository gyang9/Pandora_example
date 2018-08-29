/**
 *  @file   ExampleAlgorithms/CustomParticleCreationAlgorithm.h
 *
 *  @brief  Header file for the 3D particle creation algorithm class.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_CUSTOM_PARTICLE_CREATION_ALGORITHM_H
#define EXAMPLE_CUSTOM_PARTICLE_CREATION_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  CustomParticleCreationAlgorithm class
 */
class CustomParticleCreationAlgorithm : public pandora::Algorithm
{
protected:
    virtual pandora::StatusCode Run();
    virtual pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    /**
     *  @brief  Create specialised Pfo from an generic input Pfo
     *
     *  @param  pInputPfo the address of the input Pfo
     *  @param  pOutputPfo the address of the output Pfo
     */
    virtual void CreatePfo(const pandora::ParticleFlowObject *const pInputPfo, const pandora::ParticleFlowObject*& pOutputPfo) const = 0;

private:
    std::string  m_pfoListName;      ///< The name of the input pfo list
    std::string  m_vertexListName;   ///< The name of the input vertex list
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CUSTOM_PARTICLE_CREATION_ALGORITHM_H
