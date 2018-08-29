/**
 *  @file   ExampleAlgorithms/ListMergingAlgorithm.h
 * 
 *  @brief  Header file for the list merging algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_LIST_MERGING_ALGORITHM_H
#define EXAMPLE_LIST_MERGING_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

namespace example_content
{

/**
 *  @brief  ListMergingAlgorithm class
 */
class ListMergingAlgorithm : public pandora::Algorithm
{
private:
    pandora::StatusCode Run();
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    pandora::StringVector   m_sourceClusterListNames;   ///< The source cluster list names
    pandora::StringVector   m_targetClusterListNames;   ///< The target cluster list names

    pandora::StringVector   m_sourcePfoListNames;       ///< The source pfo list names
    pandora::StringVector   m_targetPfoListNames;       ///< The target pfo list names
};

} // namespace example_content

#endif // #ifndef EXAMPLE_LIST_MERGING_ALGORITHM_H
