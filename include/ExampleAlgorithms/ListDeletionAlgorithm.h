/**
 *  @file   ExampleAlgorithms/ListDeletionAlgorithm.h
 * 
 *  @brief  Header file for the list deletion algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_LIST_DELETION_ALGORITHM_H
#define EXAMPLE_LIST_DELETION_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  ListDeletionAlgorithm class
 */
class ListDeletionAlgorithm : public pandora::Algorithm
{
private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    pandora::StringVector   m_pfoListNames;         ///< The list of pfo list names
    pandora::StringVector   m_clusterListNames;     ///< The list of cluster list names
    pandora::StringVector   m_vertexListNames;      ///< The list of vertex list names
};

} // namespace example_content

#endif // #ifndef EXAMPLE_LIST_DELETION_ALGORITHM_H
