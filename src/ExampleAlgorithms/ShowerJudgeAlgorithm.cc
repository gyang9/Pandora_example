/*
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


ShowerJudgeAlgorithm::ShowerJudgeAlgorithm() 
{
}

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
    CaloHitList hCaloHitList;
    this->GetPreprocessedListOfClusters(unsortedVector, clusterVector);

    std::pair<int, double> showerInfo;
    this->PopulateInformation(clusterVector, hCaloHitList);

    if (!hCaloHitList.empty())
        PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList(*this, hCaloHitList, m_outputCaloHitListName));
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ReplaceCurrentList<CaloHit>(*this, m_outputCaloHitListName));

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ShowerJudgeAlgorithm::GetPreprocessedListOfClusters(ClusterVector &unsortedVector, ClusterVector &sortedVector) const
{

    OrderedCaloHitList orderedCaloHitList;

    for (const Cluster *const pSeedCluster : unsortedVector)
    {
	if (pSeedCluster ->GetElectromagneticEnergy() + pSeedCluster ->GetHadronicEnergy() > 0 || pSeedCluster ->GetNCaloHits() > 3)
	    sortedVector.push_back(pSeedCluster);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
void ShowerJudgeAlgorithm::PopulateInformation(ClusterVector &sortedVector, CaloHitList &hCaloHitList) const
{
    OrderedCaloHitList orderedCaloHitList;
    
    pandora::Cluster* iCluster;

    for (const Cluster *const pSeedCluster : sortedVector)
    {
	orderedCaloHitList = pSeedCluster->GetOrderedCaloHitList();
        for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter){
            for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
            {
                if ((*hIter) -> GetInputEnergy() > 0)
                    hCaloHitList.push_back(*hIter);
	    }
        }
    }

    for (const CaloHit *const pCaloHit : hCaloHitList)
    {
        PandoraContentApi::AddToCluster(*this, iCluster, pCaloHit);
    }

    std::cout<<"size of caloHitList "<<hCaloHitList.size()<<std::endl;
}
//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ShowerJudgeAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputClusterListName", m_inputClusterListName));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputCaloHitListName", m_outputCaloHitListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
