/**
 *  @file   ExampleAlgorithms/ShowerPfoMopUpAlgorithm.h
 * 
 *  @brief  Header file for the shower pfo mop up algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_SHOWER_PFO_MOP_UP_ALGORITHM_H
#define EXAMPLE_SHOWER_PFO_MOP_UP_ALGORITHM_H 1

#include "ExampleAlgorithms/VertexBasedPfoMopUpAlgorithm.h"

namespace example_content
{

/**
 *  @brief  ShowerPfoMopUpAlgorithm::Algorithm class
 */
class ShowerPfoMopUpAlgorithm : public VertexBasedPfoMopUpAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    ShowerPfoMopUpAlgorithm();

private:
    bool IsVertexAssociated(const pandora::CartesianVector &vertex2D, const LArPointingCluster &pointingCluster) const;
    PfoAssociation GetPfoAssociation(const pandora::Pfo *const pVertexPfo, const pandora::Pfo *const pDaughterPfo, HitTypeToAssociationMap &hitTypeToAssociationMap) const;
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float                   m_maxVertexLongitudinalDistance;    ///< Vertex association check: max longitudinal distance cut
    float                   m_vertexAngularAllowance;           ///< Vertex association check: pointing angular allowance in degrees
};

} // namespace example_content

#endif // #ifndef EXAMPLE_SHOWER_PFO_MOP_UP_ALGORITHM_H
