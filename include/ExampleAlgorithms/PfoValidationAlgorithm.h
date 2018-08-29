/**
 *  @file   ExampleAlgorithms/PfoValidationAlgorithm.h
 *
 *  @brief  Header file for the pfo validation algorithm.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_PFO_VALIDATION_ALGORITHM_H
#define EXAMPLE_PFO_VALIDATION_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  PfoValidationAlgorithm class
 */
class PfoValidationAlgorithm: public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    PfoValidationAlgorithm();

private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string                                 m_caloHitListName;          ///< Name of input calo hit list
    std::string                                 m_pfoListName;              ///< Name of input pfo list
    LArMCParticleHelper::PrimaryParameters      m_parameters;               ///< Parameters used to decide when an MCParticle is reconstructable
    unsigned int                                m_nMatchesToShow;           ///< The maximum number of MCParticle to Pfo matches to show
};

} // namespace example_content

#endif // EXAMPLE_PFO_VALIDATION_ALGORITHM_H
