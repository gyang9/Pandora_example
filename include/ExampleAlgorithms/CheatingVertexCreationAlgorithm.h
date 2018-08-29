/**
 *  @file   ExampleAlgorithms/CheatingVertexCreationAlgorithm.h
 * 
 *  @brief  Header file for the cheating vertex creation algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_CHEATING_VERTEX_CREATION_ALGORITHM_H
#define EXAMPLE_CHEATING_VERTEX_CREATION_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  CheatingVertexCreationAlgorithm::Algorithm class
 */
class CheatingVertexCreationAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    CheatingVertexCreationAlgorithm();

private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string     m_outputVertexListName;         ///< The name under which to save the output vertex list
    bool            m_replaceCurrentVertexList;     ///< Whether to replace the current vertex list with the output list
    float           m_vertexXCorrection;            ///< The vertex x correction, added to reported mc neutrino endpoint x value, in cm
};

} // namespace example_content

#endif // #ifndef EXAMPLE_CHEATING_VERTEX_CREATION_ALGORITHM_H
