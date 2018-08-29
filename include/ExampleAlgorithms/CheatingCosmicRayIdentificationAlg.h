/**
 *  @file   ExampleAlgorithms/CheatingCosmicRayIdentificationAlg.h
 * 
 *  @brief  Header file for the cosmic ray identification cheater class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_CHEATING_COSMIC_RAY_IDENTIFICATION_ALG_H
#define EXAMPLE_CHEATING_COSMIC_RAY_IDENTIFICATION_ALG_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  CheatingCosmicRayIdentificationAlg class
 */
class CheatingCosmicRayIdentificationAlg : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    CheatingCosmicRayIdentificationAlg();

private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string     m_inputPfoListName;             ///< The input pfo list name
    std::string     m_outputPfoListName;            ///< The output pfo list name
    std::string     m_inputDaughterPfoListName;     ///< The input daughter pfo list name (if not specified, will assume same as main input list)
    std::string     m_outputDaughterPfoListName;    ///< The output daughter pfo list name (if not specified, will assume same as main output list)
    float           m_maxNeutrinoFraction;          ///< The maximum true neutrino fraction in a particle to be labelled as a cosmic ray
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CHEATING_COSMIC_RAY_IDENTIFICATION_ALG_H
