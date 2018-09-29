/**
 *  @file   ExampleAlgorithms/ClusterAssociationAlgorithm.cc
 * 
 *  @brief  Implementation of the cluster association algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/LArClusterHelper.h"

#include "ExampleAlgorithms/ClusterAssociationAlgorithm.h"

using namespace pandora;

namespace example_content
{

ClusterAssociationAlgorithm::ClusterAssociationAlgorithm() :
    m_mergeMade(false),
    m_resolveAmbiguousAssociations(true)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ClusterAssociationAlgorithm::Run()
{
    const ClusterList *pClusterList = NULL;
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pClusterList));

    ClusterVector clusterVector;
    this->GetListOfCleanClusters(pClusterList, clusterVector);

    ClusterAssociationMap clusterAssociationMap;
    this->PopulateClusterAssociationMap(clusterVector, clusterAssociationMap);

    m_mergeMade = true;

    while (m_mergeMade)
    {
        // Unambiguous propagation
        while (m_mergeMade)
        {
            m_mergeMade = false;

            for (const Cluster *const pCluster : clusterVector)
            {
                // ATTN The clusterVector may end up with dangling pointers; only protected by this check against managed cluster list
                if (pClusterList->end() == std::find(pClusterList->begin(), pClusterList->end(), pCluster))
                    continue;

                this->UnambiguousPropagation(pCluster, true,  clusterAssociationMap);
                this->UnambiguousPropagation(pCluster, false, clusterAssociationMap);
            }
        }

        if (!m_resolveAmbiguousAssociations)
            continue;

        // Propagation with ambiguities
        for (const Cluster *const pCluster : clusterVector)
        {
            // ATTN The clusterVector may end up with dangling pointers; only protected by this check against up-to-date association list
            ClusterAssociationMap::const_iterator mapIter = clusterAssociationMap.find(pCluster);

            if (clusterAssociationMap.end() == mapIter)
                continue;

            if (mapIter->second.m_backwardAssociations.empty() && !mapIter->second.m_forwardAssociations.empty())
                this->AmbiguousPropagation(pCluster, true, clusterAssociationMap);

            if (mapIter->second.m_forwardAssociations.empty() && !mapIter->second.m_backwardAssociations.empty())
                this->AmbiguousPropagation(pCluster, false, clusterAssociationMap);
        }
    }

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAssociationAlgorithm::UnambiguousPropagation(const Cluster *const pCluster, const bool isForward, ClusterAssociationMap &clusterAssociationMap) const
{
    const Cluster *const pClusterToEnlarge = pCluster;
    ClusterAssociationMap::iterator iterEnlarge = clusterAssociationMap.find(pClusterToEnlarge);

    if (clusterAssociationMap.end() == iterEnlarge)
        return;

    ClusterSet &clusterSetEnlarge(isForward ? iterEnlarge->second.m_forwardAssociations : iterEnlarge->second.m_backwardAssociations);

    if (clusterSetEnlarge.size() != 1)
        return;

    const Cluster *const pClusterToDelete = *(clusterSetEnlarge.begin());
    ClusterAssociationMap::iterator iterDelete = clusterAssociationMap.find(pClusterToDelete);

    if (clusterAssociationMap.end() == iterDelete)
        return;

    ClusterSet &clusterSetDelete(isForward ? iterDelete->second.m_backwardAssociations : iterDelete->second.m_forwardAssociations);

    if (clusterSetDelete.size() != 1)
        return;

    this->UpdateForUnambiguousMerge(pClusterToEnlarge, pClusterToDelete, isForward, clusterAssociationMap);
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::MergeAndDeleteClusters(*this, pClusterToEnlarge, pClusterToDelete));
    m_mergeMade = true;

    this->UnambiguousPropagation(pClusterToEnlarge, isForward, clusterAssociationMap);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAssociationAlgorithm::AmbiguousPropagation(const Cluster *const pCluster, const bool isForward, ClusterAssociationMap &clusterAssociationMap) const
{
    ClusterAssociationMap::iterator cIter = clusterAssociationMap.find(pCluster);

    if (clusterAssociationMap.end() == cIter)
        throw StatusCodeException(STATUS_CODE_FAILURE);

    const Cluster *pExtremalCluster = pCluster;

    ClusterSet firstClusterSet;
    this->NavigateAlongAssociations(clusterAssociationMap, pCluster, isForward, pExtremalCluster, firstClusterSet);

    ClusterSet secondClusterSet;
    this->NavigateAlongAssociations(clusterAssociationMap, pExtremalCluster, !isForward, pExtremalCluster, secondClusterSet);

    ClusterVector daughterClusterVector;

    if (pCluster == pExtremalCluster)
    {
        for (const Cluster *const pFirstCluster : firstClusterSet)
        {
            if ((pCluster != pFirstCluster) && (secondClusterSet.count(pFirstCluster)) &&
                (daughterClusterVector.end() == std::find(daughterClusterVector.begin(), daughterClusterVector.end(), pFirstCluster)))
            {
                daughterClusterVector.push_back(pFirstCluster);
            }
        }
    }

    std::sort(daughterClusterVector.begin(), daughterClusterVector.end(), LArClusterHelper::SortByNHits);

    for (ClusterVector::iterator dIter = daughterClusterVector.begin(), dIterEnd = daughterClusterVector.end(); dIter != dIterEnd; ++dIter)
    {
        this->UpdateForAmbiguousMerge(pCluster, *dIter, isForward, clusterAssociationMap);
        PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::MergeAndDeleteClusters(*this, pCluster, *dIter));
        m_mergeMade = true;
        *dIter = NULL;
    } 
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAssociationAlgorithm::UpdateForUnambiguousMerge(const Cluster *const pClusterToEnlarge, const Cluster *const pClusterToDelete, const bool isForwardMerge,
    ClusterAssociationMap &clusterAssociationMap) const
{
    ClusterAssociationMap::iterator iterEnlarge = clusterAssociationMap.find(pClusterToEnlarge);
    ClusterAssociationMap::iterator iterDelete = clusterAssociationMap.find(pClusterToDelete);

    if ((clusterAssociationMap.end() == iterEnlarge) || (clusterAssociationMap.end() == iterDelete))
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    ClusterSet &clusterSetToMove(isForwardMerge ? iterDelete->second.m_forwardAssociations : iterDelete->second.m_backwardAssociations);
    ClusterSet &clusterSetToReplace(isForwardMerge ? iterEnlarge->second.m_forwardAssociations : iterEnlarge->second.m_backwardAssociations);
    clusterSetToReplace = clusterSetToMove;
    clusterAssociationMap.erase(iterDelete);

    for (ClusterAssociationMap::iterator iter = clusterAssociationMap.begin(), iterEnd = clusterAssociationMap.end(); iter != iterEnd; ++iter)
    {
        ClusterSet &forwardClusters = iter->second.m_forwardAssociations;
        ClusterSet &backwardClusters = iter->second.m_backwardAssociations;

        ClusterSet::iterator forwardIter = forwardClusters.find(pClusterToDelete);
        ClusterSet::iterator backwardIter = backwardClusters.find(pClusterToDelete);

        if (forwardClusters.end() != forwardIter)
        {
            forwardClusters.erase(forwardIter);
            forwardClusters.insert(pClusterToEnlarge);
        }

        if (backwardClusters.end() != backwardIter)
        {
            backwardClusters.erase(backwardIter);
            backwardClusters.insert(pClusterToEnlarge);
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAssociationAlgorithm::UpdateForAmbiguousMerge(const Cluster *const pClusterToEnlarge, const Cluster *const pClusterToDelete, const bool isForwardMerge,
    ClusterAssociationMap &clusterAssociationMap) const
{
    ClusterAssociationMap::iterator iterEnlarge = clusterAssociationMap.find(pClusterToEnlarge);
    ClusterAssociationMap::iterator iterDelete = clusterAssociationMap.find(pClusterToDelete);

    if ((clusterAssociationMap.end() == iterEnlarge) || (clusterAssociationMap.end() == iterDelete))
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    ClusterSet &clusterSetEnlarge(isForwardMerge ? iterEnlarge->second.m_forwardAssociations : iterEnlarge->second.m_backwardAssociations);
    ClusterSet &clusterSetDelete(isForwardMerge ? iterDelete->second.m_backwardAssociations : iterDelete->second.m_forwardAssociations);

    for (ClusterSet::iterator iter = clusterSetEnlarge.begin(); iter != clusterSetEnlarge.end();)
    {
        if ((*iter) != pClusterToDelete)
        {
            ClusterAssociationMap::iterator iterAssociation = clusterAssociationMap.find(*iter);

            if (clusterAssociationMap.end() == iterAssociation)
                throw StatusCodeException(STATUS_CODE_NOT_FOUND);

            ClusterSet &associatedClusterSet(isForwardMerge ? iterAssociation->second.m_backwardAssociations : iterAssociation->second.m_forwardAssociations);

            ClusterSet::iterator enlargeIter = associatedClusterSet.find(pClusterToEnlarge);

            if (associatedClusterSet.end() == enlargeIter)
                throw StatusCodeException(STATUS_CODE_NOT_FOUND);

            associatedClusterSet.erase(enlargeIter);
            clusterSetEnlarge.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }

    for (ClusterSet::iterator iter = clusterSetDelete.begin(); iter != clusterSetDelete.end();)
    {
        if ((*iter) != pClusterToEnlarge)
        {
            ClusterAssociationMap::iterator iterAssociation = clusterAssociationMap.find(*iter);

            if (clusterAssociationMap.end() == iterAssociation)
                throw StatusCodeException(STATUS_CODE_NOT_FOUND);

            ClusterSet &associatedClusterSet(isForwardMerge ? iterAssociation->second.m_forwardAssociations : iterAssociation->second.m_backwardAssociations);

            ClusterSet::iterator deleteIter = associatedClusterSet.find(pClusterToDelete);

            if (associatedClusterSet.end() == deleteIter)
                throw StatusCodeException(STATUS_CODE_NOT_FOUND);

            associatedClusterSet.erase(deleteIter);
            clusterSetDelete.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }

    return this->UpdateForUnambiguousMerge(pClusterToEnlarge, pClusterToDelete, isForwardMerge, clusterAssociationMap);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAssociationAlgorithm::NavigateAlongAssociations(const ClusterAssociationMap &clusterAssociationMap, const Cluster *const pCluster,
    const bool isForward, const Cluster *&pExtremalCluster, ClusterSet &clusterSet) const
{
    ClusterAssociationMap::const_iterator iterAssociation = clusterAssociationMap.find(pCluster);

    if (clusterAssociationMap.end() == iterAssociation)
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    (void) clusterSet.insert(pCluster);

    if ((pCluster != pExtremalCluster) && this->IsExtremalCluster(isForward, pExtremalCluster, pCluster))
          pExtremalCluster = pCluster;

    const ClusterSet &associatedClusterSet(isForward ? iterAssociation->second.m_forwardAssociations : iterAssociation->second.m_backwardAssociations);

    for (ClusterSet::const_iterator iter = associatedClusterSet.begin(), iterEnd = associatedClusterSet.end(); iter != iterEnd; ++iter)
    {
        this->NavigateAlongAssociations(clusterAssociationMap, *iter, isForward, pExtremalCluster, clusterSet);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ClusterAssociationAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "ResolveAmbiguousAssociations", m_resolveAmbiguousAssociations));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content