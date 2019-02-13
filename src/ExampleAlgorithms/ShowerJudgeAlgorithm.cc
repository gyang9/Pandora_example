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
    //ParticleFlowObject* pPfo;  // pPfo is not used here!
    ClusterList clusterList;
    this->PopulateInformation(clusterList, clusterVector);

    const PfoList *pPfoList = nullptr; std::string pfoListName;
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CreateTemporaryListAndSetCurrent<PfoList>(*this, pPfoList, pfoListName));

    const Pfo *pPfo(nullptr);
    PandoraContentApi::ParticleFlowObject::Parameters pfoParameters;
    pfoParameters.m_charge = 0;
    pfoParameters.m_energy = 0.f;
    pfoParameters.m_mass = 0.f;
    pfoParameters.m_momentum = CartesianVector(0.f, 0.f, 0.f);
    pfoParameters.m_particleId = 0;
    pfoParameters.m_clusterList.insert(pfoParameters.m_clusterList.end(), clusterList.begin(), clusterList.end());
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ParticleFlowObject::Create(*this, pfoParameters, pPfo));

    //for (ClusterList::const_iterator iter = pClusterList->begin(), iterEnd = pClusterList->end(); iter != iterEnd; ++iter)
    //    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::AddToPfo(*this, pPfo, *iter));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Pfo>(*this, m_outputPfoName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Cluster>(*this, m_outputClusterListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ReplaceCurrentList<Cluster>(*this, m_outputClusterListName));

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

void ShowerJudgeAlgorithm::PopulateInformation(ClusterList &clusterList, ClusterVector &clusterVector) const
{
    double TotalEnergy = 0;
    CaloHitList hCaloHitList;

    std::cout<<"inside ShowerJudgeAlgorithm::PopulateInformation "<<std::endl;
    for (const Cluster *const pCluster : clusterVector){

        const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());

        for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
        {
           for (CaloHitList::const_iterator hitIter = iter->second->begin(), hitIterEnd = iter->second->end(); hitIter != hitIterEnd; ++hitIter)
           {
              TotalEnergy += (*hitIter)->GetInputEnergy();
              hCaloHitList.push_back(*hitIter);
           }
        }

        if(3*TotalEnergy/LArClusterHelper::GetLength(pCluster)> 0 && 3*TotalEnergy/LArClusterHelper::GetLength(pCluster)< 3.){
	    //selectedClusterVector.push_back(pCluster);
	    clusterList.push_back(pCluster);
	}
    }

}      

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ShowerJudgeAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputClusterListName", m_inputClusterListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputClusterListName", m_outputClusterListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputPfoName", m_outputPfoName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
