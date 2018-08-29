/**
 *  @file   ExampleAlgorithms/VertexAssociatedPfosTool.h
 * 
 *  @brief  Header file for the vertex associated pfos tool class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_VERTEX_ASSOCIATED_PFOS_TOOL_H
#define EXAMPLE_VERTEX_ASSOCIATED_PFOS_TOOL_H 1

#include "ExampleAlgorithms/NeutrinoHierarchyAlgorithm.h"

namespace example_content
{

/**
 *  @brief  VertexAssociatedPfosTool class
 */
class VertexAssociatedPfosTool : public PfoRelationTool
{
public:
    /**
     *  @brief  Default constructor
     */
    VertexAssociatedPfosTool();

    void Run(NeutrinoHierarchyAlgorithm *const pAlgorithm, const pandora::Vertex *const pNeutrinoVertex, NeutrinoHierarchyAlgorithm::PfoInfoMap &pfoInfoMap);

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    float       m_minVertexLongitudinalDistance;        ///< Vertex association check: min longitudinal distance cut
    float       m_maxVertexLongitudinalDistance;        ///< Vertex association check: max longitudinal distance cut
    float       m_maxVertexTransverseDistance;          ///< Vertex association check: max transverse distance cut
    float       m_vertexAngularAllowance;               ///< Vertex association check: pointing angular allowance in degrees
};

} // namespace example_content

#endif // #ifndef EXAMPLE_VERTEX_ASSOCIATED_PFOS_TOOL_H
