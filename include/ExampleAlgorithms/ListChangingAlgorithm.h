/**
 *  @file   ExampleAlgorithms/ListChangingAlgorithm.h
 * 
 *  @brief  Header file for the list changing algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_LIST_CHANGING_ALGORITHM_H
#define EXAMPLE_LIST_CHANGING_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  ListChangingAlgorithm::Algorithm class
 */
class ListChangingAlgorithm : public pandora::Algorithm
{
private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    std::string     m_caloHitListName;  ///< The calo hit list name to set as the current calo hit list
    std::string     m_clusterListName;  ///< The cluster list name to set as the current cluster list
    std::string     m_vertexListName;   ///< The vertex list name to set as the current vertex list
    std::string     m_pfoListName;      ///< The pfo list name to set as the current pfo list
};

} // namespace example_content

#endif // #ifndef EXAMPLE_LIST_CHANGING_ALGORITHM_H
