/**
 *  @file   ExampleAlgorithms/ClusterAdjustmentAlgorithm.cc
 *
 *  @brief  Implementation of the 2D sliding fit adjustment algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/LArClusterHelper.h"
#include "ExampleAlgorithms/LArGeometryHelper.h"

#include "ExampleAlgorithms/ClusterAdjustmentAlgorithm.h"

using namespace pandora;

namespace example_content
{

ClusterAdjustmentAlgorithm::ClusterAdjustmentAlgorithm() :
    m_minTrackLength(75.f),
    m_maxClusterLength(150.f),
    m_halfWindowLayers(25),
    m_groupingContract(2),
    m_toleranceContract(0.001f),
    m_toleranceMerge(0.001f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ClusterAdjustmentAlgorithm::Run()
{
    const ClusterList *pClusterList = NULL;
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pClusterList));
    //const ClusterList *pClusterList(nullptr);
    //PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_INITIALIZED, !=, PandoraContentApi::GetList(*this, m_inputClusterListName, pClusterList));
    std::cout<<"Got List of input clusters"<<std::endl;

    // Select tracks and showers for re-clustering (Note: samples not mutually exclusive)
    ClusterVector trackClusters, showerClusters;
    this->SortInputClusters(pClusterList, trackClusters, showerClusters);
    std::cout<<"sorted input cluseters"<<std::endl;

    // Build sliding linear fits from track clusters
    //TwoDSlidingFitResultList slidingFitResultList;
    ClusterToHitMap clustersToExpand, clustersToContract;
    ClusterSet unavailableClusters;
    //this->ClusterExpandwLinearFits(trackClusters, clustersToExpand, 0.00001);

    ClusterList clusterListFirstSplit, clusterListSecondSplit;
    this->ClusterContractwLinearFits(trackClusters, clustersToContract, (const int) m_groupingContract, (const double ) m_toleranceContract);
    std::cout<<"done first Cluster contract"<<std::endl;
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->RemoveHitsFromClusters(clustersToContract, unavailableClusters, clusterListFirstSplit));
    this->ClusterContractwLinearFits(clusterListFirstSplit, clustersToContract, (const int) m_groupingContract, (const double) m_toleranceContract);
    std::cout<<"done second Cluster contract"<<std::endl;
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->RemoveHitsFromClusters(clustersToContract, unavailableClusters, clusterListSecondSplit));

    std::cout<<"starting cluster expansion "<<std::endl;
    ClusterList clusterListFirstMerge;
    this->ClusterExpandwLinearFits(trackClusters, clustersToExpand, m_toleranceMerge);
    std::cout<<"done cluster expansion "<<std::endl;
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->AddHitsToClusters(clustersToExpand, unavailableClusters, clusterListFirstMerge));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Cluster>(*this, m_outputClusterListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ReplaceCurrentList<Cluster>(*this, m_outputClusterListName));

    //PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->RebuildClusters(clustersToContract, unavailableClusters));

    // Recluster the hits
    //ClusterToHitMap clustersToExpand, clustersToContract;
    //this->GetReclusteredHits(slidingFitResultList, showerClusters, clustersToExpand, clustersToContract);

    // Consolidate and re-build clusters
    //ClusterList clusterList1, clusterList2;
    //ClusterSet unavailableClusters;
    //PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->RemoveHitsFromClusters(clustersToContract, unavailableClusters, clusterList1));
    //PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->AddHitsToClusters(clustersToExpand, unavailableClusters, clusterList2));
    //PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->RebuildClusters(clustersToContract, unavailableClusters));

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAdjustmentAlgorithm::SortInputClusters(const ClusterList *const pClusterList, ClusterVector &trackClusters,
    ClusterVector &showerClusters) const
{
    std::cout<<"in sortInputClusters() "<<pClusterList->size()<<std::endl;
    for (ClusterList::const_iterator iter = pClusterList->begin(), iterEnd = pClusterList->end(); iter != iterEnd; ++iter)
    {
	std::cout<<"in the loop "<<std::endl;
        const Cluster *const pCluster = *iter;

        const float thisLengthSquared(LArClusterHelper::GetLengthSquared(pCluster));
	std::cout<<thisLengthSquared<<std::endl;

        if (thisLengthSquared < m_maxClusterLength * m_maxClusterLength)
            showerClusters.push_back(pCluster);

        if (thisLengthSquared > m_minTrackLength * m_minTrackLength)
            trackClusters.push_back(pCluster);
    }

    std::cout<<"finished loop of sorting based on length"<<std::endl;
    std::sort(trackClusters.begin(), trackClusters.end(), LArClusterHelper::SortByNHits);
    std::sort(showerClusters.begin(), showerClusters.end(), LArClusterHelper::SortByNHits);
}

//------------------------------------------------------------------------------------------------------------------------------------------

//void ClusterAdjustmentAlgorithm::BuildSlidingLinearFits(const ClusterVector &trackClusters, TwoDSlidingFitResultList &slidingFitResultList) const
void ClusterAdjustmentAlgorithm::ClusterExpandwLinearFits(ClusterVector &trackClusters, ClusterToHitMap &clustersToExpand, const double tolerance) const
{
    // loop the clusters to see some have same directions
   
    for (ClusterVector::const_iterator iter = trackClusters.begin(), iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
    {
	const Cluster *const pCluster = *iter;
	for (ClusterVector::const_iterator jter = iter, iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
    	{
	    if ((*iter)->GetNCaloHits()>3 && (*jter)->GetNCaloHits()>3)
	    {
	        if (LArClusterHelper::CombiningTwoDClusters(*iter, *jter, tolerance))
		{
		    CaloHitList tempCaloHitList;
        	    (*jter)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList);
		    for (const CaloHit *const pCaloHit : tempCaloHitList)
	  	    {
		        clustersToExpand[pCluster].push_back(pCaloHit);
		    }
		    trackClusters.erase(jter);
		}
	    }
	}
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAdjustmentAlgorithm::ClusterExpandwLinearFits(ClusterList &trackClusters, ClusterToHitMap &clustersToExpand, const double tolerance) const
{
    // loop the clusters to see some have same directions

    for (ClusterList::const_iterator iter = trackClusters.begin(), iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
    {
        const Cluster *const pCluster = *iter;
        for (ClusterList::const_iterator jter = iter, iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
        {
            if ((*iter)->GetNCaloHits()>3 && (*jter)->GetNCaloHits()>3)
            {
                if (LArClusterHelper::CombiningTwoDClusters(*iter, *jter, tolerance))
                {
                    CaloHitList tempCaloHitList;
                    (*jter)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList);
                    for (const CaloHit *const pCaloHit : tempCaloHitList)
                    {
                        clustersToExpand[pCluster].push_back(pCaloHit);
                    }
                    trackClusters.erase(jter);
                }
            }
        }
    }

}


//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAdjustmentAlgorithm::ClusterContractwLinearFits(ClusterVector &trackClusters, ClusterToHitMap &clustersToContract, const int splitGrouping, const double splitTolerance) const
{
    // loop the hits in one clusters to see some have different directions, require at least 10 hits
    int icount = 0;
    for (ClusterVector::const_iterator iter = trackClusters.begin(), iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
    {
        if ((*iter)->GetNCaloHits()>10)
        {
	    CaloHitList tempCaloHitList;
	    int hitPerGroup = (*iter)->GetNCaloHits()/splitGrouping;
	    pandora::ClusterVector tempClusterList;

            (*iter)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList);
            for (const CaloHit *const pCaloHit : tempCaloHitList)
	    {
		icount++;
		for(int i=0; i< splitGrouping; i++){
		    if (icount>i*hitPerGroup && icount<=(i+1)*hitPerGroup) 
			PandoraContentApi::AddToCluster(*this, tempClusterList.at(i), pCaloHit);
		}    

	    }	

	    std::map<int, int> splitMapping;
	    for(int i=0 ; i<splitGrouping; i++){
		for(int j=i; j<splitGrouping; j++){
		    if ( i != j && !LArClusterHelper::CombiningTwoDClusters(tempClusterList.at(i),tempClusterList.at(j), splitTolerance) )
			std::cout<<"splitted cluster number "<<i << " and "<< j<< " ... splitted succesfully ... "<<std::endl;	
			splitMapping[i] = j;
			break;
		}
	    }

	    //iterate split mapping here
	    for ( const auto &p : splitMapping ){
		CaloHitList tempCaloHitList1;
		CaloHitList tempCaloHitList2;
		for(int i=0;i<p.second;i++)
	            tempClusterList.at(i)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList1);
		for(int i=p.second;i<splitGrouping; i++)
		    tempClusterList.at(i)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList2);
                for (const CaloHit *const pCaloHit : tempCaloHitList1)
                {
                    clustersToContract[*iter].push_back(pCaloHit);
                }
                for (const CaloHit *const pCaloHit : tempCaloHitList2)
                {
		    const pandora::Cluster* tempCluster = *iter;
                    clustersToContract[tempCluster].push_back(pCaloHit);
                }
		std::cout<<"size of the clustersToContract (should be even number, probably 2 ) "<<clustersToContract.size()<<std::endl;
	    }

/*
                if (LArClusterHelper::CombiningTwoDClusters(*iter, *jter, (const double )0.0001))
                {
                    CaloHitList tempCaloHitList;
                    (*jter)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList);
                    for (const CaloHit *const pCaloHit : tempCaloHitList)
                    {
                        clustersToExpand[pCluster].push_back(pCaloHit);
                    }
                    trackClusters.erase(jter);
                }
*/
    	    
        }
    }
}
/*

    const float slidingFitPitch(LArGeometryHelper::GetWireZPitch(this->GetPandora()));

    for (ClusterVector::const_iterator iter = trackClusters.begin(), iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
    {
        try
        {
            const TwoDSlidingFitResult slidingFitResult(*iter, m_halfWindowLayers, slidingFitPitch);
            slidingFitResultList.push_back(slidingFitResult);
        }
        catch (StatusCodeException &statusCodeException)
        {
            if (STATUS_CODE_FAILURE == statusCodeException.GetStatusCode())
                throw statusCodeException;
        }
    }
}
*/

//------------------------------------------------------------------------------------------------------------------------------------------

void ClusterAdjustmentAlgorithm::ClusterContractwLinearFits(ClusterList &trackClusters, ClusterToHitMap &clustersToContract, const int splitGrouping, const double splitTolerance) const
{
    // loop the hits in one clusters to see some have different directions, require at least 10 hits
    int icount = 0;
    for (ClusterList::const_iterator iter = trackClusters.begin(), iterEnd = trackClusters.end(); iter != iterEnd; ++iter)
    {
        if ((*iter)->GetNCaloHits()>10)
        {
            CaloHitList tempCaloHitList;
            int hitPerGroup = (*iter)->GetNCaloHits()/splitGrouping;
            pandora::ClusterVector tempClusterList;

            (*iter)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList);
            for (const CaloHit *const pCaloHit : tempCaloHitList)
            {
                icount++;
                for(int i=0; i< splitGrouping; i++){
                    if (icount>i*hitPerGroup && icount<=(i+1)*hitPerGroup)
                        PandoraContentApi::AddToCluster(*this, tempClusterList.at(i), pCaloHit);
                }

            }

            std::map<int, int> splitMapping;
            for(int i=0 ; i<splitGrouping; i++){
                for(int j=i; j<splitGrouping; j++){
                    if ( i != j && !LArClusterHelper::CombiningTwoDClusters(tempClusterList.at(i),tempClusterList.at(j), splitTolerance) )
                        std::cout<<"splitted cluster number "<<i << " and "<< j<< " ... splitted succesfully ... "<<std::endl;
                        splitMapping[i] = j;
                        break;
                }
            }

            for ( const auto &p : splitMapping ){
                CaloHitList tempCaloHitList1;
                CaloHitList tempCaloHitList2;
                for(int i=0;i<p.second;i++)
                    tempClusterList.at(i)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList1);
                for(int i=p.second;i<splitGrouping; i++)
                    tempClusterList.at(i)->GetOrderedCaloHitList().FillCaloHitList(tempCaloHitList2);
                for (const CaloHit *const pCaloHit : tempCaloHitList1)
                {
                    clustersToContract[*iter].push_back(pCaloHit);
                }
                for (const CaloHit *const pCaloHit : tempCaloHitList2)
                {
                    const pandora::Cluster* tempCluster = *iter;
                    clustersToContract[tempCluster].push_back(pCaloHit);
                }
                std::cout<<"size of the clustersToContract (should be even number, probably 2 ) "<<clustersToContract.size()<<std::endl;
            }
        }
    }
}



//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ClusterAdjustmentAlgorithm::RemoveHitsFromClusters(const ClusterToHitMap &clustersToContract, ClusterSet &unavailableClusters, ClusterList clusterList) const
{
    //ClusterList clusterList;
    for (const auto &mapEntry : clustersToContract) clusterList.push_back(mapEntry.first);
    clusterList.sort(LArClusterHelper::SortByNHits);

    for (const Cluster *const pCluster : clusterList)
    {
        const CaloHitList &caloHitListToRemove(clustersToContract.at(pCluster));

        if (caloHitListToRemove.empty())
            continue;

        if (unavailableClusters.count(pCluster))
            continue;

        CaloHitList caloHitList, caloHitListToKeep;
        pCluster->GetOrderedCaloHitList().FillCaloHitList(caloHitList);

        for (const CaloHit *const pCaloHit : caloHitList)
        {
            if (caloHitListToRemove.end() == std::find(caloHitListToRemove.begin(), caloHitListToRemove.end(), pCaloHit))
                caloHitListToKeep.push_back(pCaloHit);
        }

        if (caloHitListToKeep.empty())
        {
            // ATTN clustersToContract and unavailable clusters now contain dangling pointers
            unavailableClusters.insert(pCluster);
            PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::Delete<Cluster>(*this, pCluster));
            continue;
        }

        for (const CaloHit *const pCaloHit : caloHitListToRemove)
        {
            PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::RemoveFromCluster(*this, pCluster, pCaloHit));
        }
    }

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ClusterAdjustmentAlgorithm::AddHitsToClusters(const ClusterToHitMap &clustersToExpand, ClusterSet &unavailableClusters, ClusterList clusterList) const
{
    //ClusterList clusterList;
    for (const auto &mapEntry : clustersToExpand) clusterList.push_back(mapEntry.first);
    clusterList.sort(LArClusterHelper::SortByNHits);

    for (const Cluster *const pCluster : clusterList)
    {
        const CaloHitList &caloHitList(clustersToExpand.at(pCluster));

        if (caloHitList.empty())
            continue;

        if (unavailableClusters.count(pCluster))
            continue;

        unavailableClusters.insert(pCluster);

        for (const CaloHit *const pCaloHit : caloHitList)
        {
            PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::AddToCluster(*this, pCluster, pCaloHit));
        }
    }

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------
/*
StatusCode ClusterAdjustmentAlgorithm::RebuildClusters(const ClusterToHitMap &clustersToRebuild, const ClusterSet &unavailableClusters) const
{
    if (clustersToRebuild.empty())
        return STATUS_CODE_SUCCESS;

    ClusterVector sortedClusters;
    for (const auto &mapEntry : clustersToRebuild)
    {
        if (!unavailableClusters.count(mapEntry.first))
            sortedClusters.push_back(mapEntry.first);
    }

    std::sort(sortedClusters.begin(), sortedClusters.end(), LArClusterHelper::SortByNHits);

    for (const Cluster *const pCluster : sortedClusters)
    {
        const CaloHitList &caloHitList(clustersToRebuild.at(pCluster));
        const Cluster *const pClusterToDelete(pCluster);

        if (caloHitList.empty())
            continue;

        std::string currentClusterListName;
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentListName<Cluster>(*this, currentClusterListName));
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::Delete<Cluster>(*this, pClusterToDelete));

        const ClusterList *pClusterList = NULL;
        std::string newClusterListName;
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::RunClusteringAlgorithm(*this, m_reclusteringAlgorithmName,
            pClusterList, newClusterListName));

        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Cluster>(*this, newClusterListName, currentClusterListName));
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ReplaceCurrentList<Cluster>(*this, currentClusterListName));
    }

    return STATUS_CODE_SUCCESS;
}
*/
//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ClusterAdjustmentAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
/*
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ProcessAlgorithm(*this, xmlHandle,
        "ClusterRebuilding", m_reclusteringAlgorithmName));
*/
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MinTrackLength", m_minTrackLength));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxClusterLength", m_maxClusterLength));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "SlidingFitHalfWindow", m_halfWindowLayers));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputClusterListName", m_outputClusterListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "InputClusterListName", m_inputClusterListName));    

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "GroupingContract", m_groupingContract));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "ToleranceContract", m_toleranceContract));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "ToleranceMerge", m_toleranceMerge));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
