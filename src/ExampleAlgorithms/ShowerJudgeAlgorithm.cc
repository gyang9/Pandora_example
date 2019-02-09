/**
 *  @file   ExampleAlgorithms/ShowerJudgeAlgorithm.cc
 *
 *  @brief  Implementation of the cluster merging algorithm class.
 *
 *  $Log: $
 */ 
#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/LArClusterHelper.h"
#include "ExampleAlgorithms/ExampleClusterHelper.h"
#include "ExampleAlgorithms/LArGeometryHelper.h"
#include "ExampleAlgorithms/LArPfoHelper.h"

#include "ExampleAlgorithms/LArThreeDSlidingFitResult.h"

#include "ExampleAlgorithms/HitCreationBaseTool.h"
#include "ExampleAlgorithms/ThreeDHitCreationAlgorithm.h"
#include "ExampleAlgorithms/ShowerJudgeAlgorithm.h"

using namespace pandora;

namespace example_content
{


ShowerJudgeAlgorithm::ShowerJudgeAlgorithm() 
{
}

StatusCode ShowerJudgeAlgorithm::Run()
{
	
    const ClusterList *pClusterList;

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

    this->GetPreprocessedListOfClusters(*pClusterList, clusterVector);
    std::cout<<"finished GetPreprocessedListOfClusters(), number of clusters "<< clusterVector.size()<<std::endl;

    ClusterVector selectedClusterVector;
    ParticleFlowObject* pPfo;  // pPfo is not used here!
    this->PopulateInformation(pPfo, clusterVector, selectedClusterVector);

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------
void ShowerJudgeAlgorithm::GetPreprocessedListOfClusters(const ClusterList &unsortedList, ClusterVector &sortedVector) const
{
    for (ClusterList::const_iterator pSeedCluster = unsortedList.begin(), iterEnd = unsortedList.end(); pSeedCluster != iterEnd; ++pSeedCluster)	
    {
       if((*pSeedCluster)->GetElectromagneticEnergy()+(*pSeedCluster)->GetHadronicEnergy()>0 || (*pSeedCluster)->GetNCaloHits() > 3)
          sortedVector.push_back(*pSeedCluster);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------

void ShowerJudgeAlgorithm::PopulateInformation(ParticleFlowObject* pPfo, ClusterVector &clusterVector, ClusterVector &selectedClusterVector) const
{
    double TotalEnergy = 0;
    CaloHitList hCaloHitList;

    std::cout<<"inside ShowerJudgeAlgorithm::PopulateInformation "<<std::endl;
    for (const Cluster *const pCluster : clusterVector){

        const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());
        std::cout<<"check point 1 "<<std::endl;

        for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
        {
           for (CaloHitList::const_iterator hitIter = iter->second->begin(), hitIterEnd = iter->second->end(); hitIter != hitIterEnd; ++hitIter)
           {
              TotalEnergy += (*hitIter)->GetInputEnergy();
              hCaloHitList.push_back(*hitIter);
           }
        }

        if(3*TotalEnergy/LArClusterHelper::GetLength(pCluster)> 0 && 3*TotalEnergy/LArClusterHelper::GetLength(pCluster)< 3.)
	    selectedClusterVector.push_back(pCluster);
    }
}      

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ShowerJudgeAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputClusterListName", m_inputClusterListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputClusterVectorName", m_outputClusterVectorName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
