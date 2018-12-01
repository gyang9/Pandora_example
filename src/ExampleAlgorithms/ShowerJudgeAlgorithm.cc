/**
 *  @file   ExampleAlgorithms/ShowerJudgeAlgorithm.cc
 *
 *  @brief  Implementation of the cluster merging algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/LArClusterHelper.h"

#include "ExampleAlgorithms/ShowerJudgeAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode ShowerJudgeAlgorithm::Run()
{
    const ClusterList *pClusterList = NULL;

    if (m_inputClusterListName.empty())
    {
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pClusterList));
    }
    else
    {
        PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_INITIALIZED, !=, PandoraContentApi::GetList(*this, m_inputClusterListName, pClusterList));
    }

    if (!pClusterList || pClusterList->empty())
    {
        if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
            std::cout << "ShowerJudgeAlgorithm: unable to find cluster list " << m_inputClusterListName << std::endl;

        return STATUS_CODE_SUCCESS;
    }

    ClusterVector unsortedVector, clusterVector;
    this->GetPreprocessedListOfClusters(unsortedVector, clusterVector);

    std::pair<int, double> showerInfo;
    this->PopulateInformation(clusterVector, showerInfo);

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ShowerJudgeAlgorithm::GetPreprocessedListOfClusters(ClusterVector &unsortedVector, ClusterVector &sortedVector) const
{
    for (const Cluster *const pSeedCluster : unsortedVector)
    {

    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
void ShowerJudgeAlgorithm::PopulateInformation(ClusterVector &sortedVector, std::pair<int, double> showerInfo) const
{
    for (const Cluster *const pSeedCluster : sortedVector)
    {

    }
}
//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ShowerJudgeAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputClusterListName", m_inputClusterListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
