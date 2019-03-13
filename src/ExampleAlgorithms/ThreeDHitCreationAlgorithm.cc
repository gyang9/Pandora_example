/**
 *  @file   ExampleAlgorithms/ThreeDHitCreationAlgorithm.cc
 *
 *  @brief  Implementation of the three dimensional hit creation algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CubeClusterHelper.h"
#include "ExampleAlgorithms/CubePfoHelper.h"
#include "ExampleAlgorithms/ThreeDHitCreationAlgorithm.h"

#include <algorithm>

using namespace pandora;

namespace example_content
{
ThreeDHitCreationAlgorithm::ThreeDHitCreationAlgorithm() :
    m_NofBoxesX(200),
    m_NofBoxesY(200),
    m_NofBoxesZ(200),
    m_cubeSize(10.f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::FilterCaloHitsByType(const CaloHitVector &inputCaloHitVector, const HitType hitType, CaloHitVector &outputCaloHitVector) const
{
    for (const CaloHit *const pCaloHit : inputCaloHitVector)
    {
        if (hitType == pCaloHit->GetHitType())
            outputCaloHitVector.push_back(pCaloHit);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ThreeDHitCreationAlgorithm::Run()
{
    const PfoList *pPfoList(nullptr);
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_INITIALIZED, !=, PandoraContentApi::GetList(*this, m_inputPfoListName, pPfoList));

    if (!pPfoList || pPfoList->empty())
    {
        if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
            std::cout << "ThreeDHitCreationAlgorithm: unable to find pfo list " << m_inputPfoListName << std::endl;

        return STATUS_CODE_SUCCESS;
    }

    CaloHitList allNewThreeDHits;

    PfoVector pfoVector(pPfoList->begin(), pPfoList->end());
    std::sort(pfoVector.begin(), pfoVector.end(), CubePfoHelper::SortByNHits);

    for (const ParticleFlowObject *const pPfo : pfoVector)
    {
	ClusterList twoDClusterList;
        CubePfoHelper::GetTwoDClusterList(pPfo, twoDClusterList);

	CartesianVector innerCoordinate(0.f, 0.f, 0.f);
	CartesianVector outerCoordinate(0.f, 0.f, 0.f);
        CubeClusterHelper::GetExtremalCoordinates(twoDClusterList, innerCoordinate, outerCoordinate);
	std::cout<<"innerCoordinate: "<<innerCoordinate.GetX()<<" "<<innerCoordinate.GetY()<<" "<<innerCoordinate.GetZ()<<" "<<std::endl;
        std::cout<<"outerCoordinate: "<<outerCoordinate.GetX()<<" "<<outerCoordinate.GetY()<<" "<<outerCoordinate.GetZ()<<" "<<std::endl;

        CaloHitList newThreeDHits;
	this->CreateThreeDHitsList(pPfo, newThreeDHits, innerCoordinate, outerCoordinate);
	//std::cout<<"adding to pPfo "<<std::endl;
        std::cout<<"caloHit middle size: "<<newThreeDHits.size()<<std::endl;
	//std::cout<<"almost end "<<std::endl;
        allNewThreeDHits.insert(allNewThreeDHits.end(), newThreeDHits.begin(), newThreeDHits.end());
    }

    std::cout<<"caloHit size: "<<allNewThreeDHits.size()<<std::endl;
    std::cout<<"lastly check 3D list "<<std::endl;
    if (!allNewThreeDHits.empty())
        PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList(*this, allNewThreeDHits, m_outputCaloHitListName));

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::CreateThreeDHitsList(const ParticleFlowObject *const pPfo, CaloHitList &newThreeDHits, pandora::CartesianVector &innerCoordinate, pandora::CartesianVector &outerCoordinate) const
{
    int xSize = (int)m_NofBoxesX; //(int)(outerCoordinate.GetX()/10);
    int ySize = (int)m_NofBoxesY; //(int)(outerCoordinate.GetY()/10);
    int zSize = (int)m_NofBoxesZ; //(int)(outerCoordinate.GetZ()/10);

    int mulXYZ = xSize * ySize * zSize;
    int mulXY  = ySize * zSize;

    //std::cout<<"check point 1 "<<std::endl;
    //std::vector<std::vector<std::vector<double>>> cubeArray (zSize, std::vector<std::vector<double>> (200, std::vector <double> (200, 0.)) );
    
    float* cubeArray = (float*)malloc(mulXYZ* sizeof(float));
    float* nCellRadiationLengthsArray = (float*)malloc(mulXYZ* sizeof(float));
    float* nCellInteractionLengthsArray = (float*)malloc(mulXYZ* sizeof(float));
    float* timeArray = (float*)malloc(mulXYZ* sizeof(float));
    float* inputEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    float* mipEquivalentEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    float* electromagneticEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    float* hadronicEnergyArray = (float*)malloc(mulXYZ* sizeof(float));

    for (int i=0;i<mulXYZ;i++)
    {
	cubeArray[i] = 0.;
        nCellRadiationLengthsArray[i] = 0.;
        nCellInteractionLengthsArray[i] = 0.;
        timeArray[i] = 0.;
        inputEnergyArray[i] = 0.;
        mipEquivalentEnergyArray[i] = 0.;
        electromagneticEnergyArray[i] = 0.;
        hadronicEnergyArray[i] = 0.;
    }

    bool firstLoopDone = false;
    double threeMatching, twoMatching, oneMatching;
    ClusterList twoDClusterList;
    CubePfoHelper::GetTwoDClusterList(pPfo, twoDClusterList);

    OrderedCaloHitList orderedCaloHitList;

    for (const Cluster *const pCluster : twoDClusterList)
    {
        std::cout<<"looping point of pCluster "<<std::endl;
        std::cout<<"============== hit type: "<<CubeClusterHelper::GetClusterHitType(pCluster)<<std::endl;
        std::cout<<"============== N calo hits : "<<pCluster->GetNCaloHits()<<std::endl;
	
	threeMatching = 0;
	//twoMatching   = 0;
	//oneMatching   = 0;

	if(4 == CubeClusterHelper::GetClusterHitType(pCluster))
	{
            orderedCaloHitList = pCluster->GetOrderedCaloHitList();

            for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
	    {
    		for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                   const CartesianVector &positionVector((*hIter)->GetPositionVector());
                   std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
	 	   for(int iArray = 0; iArray < zSize; iArray ++ ){
			cubeArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] ++;
    			nCellRadiationLengthsArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetNCellRadiationLengths();
    			nCellInteractionLengthsArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetNCellInteractionLengths();
    			timeArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetTime();
    			inputEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetInputEnergy();
    			mipEquivalentEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetMipEquivalentEnergy();
    			electromagneticEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetElectromagneticEnergy();
    			hadronicEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetHadronicEnergy();
     		    }
                }
	    }
	firstLoopDone = true;
	}


	if(5 == CubeClusterHelper::GetClusterHitType(pCluster) && firstLoopDone)
        {
        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

            for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
	    {
    		for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                    const CartesianVector &positionVector((*hIter)->GetPositionVector());
                    std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
                    for(int iArray = 0; iArray < ySize; iArray ++ ){
                        cubeArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] ++;
                        nCellRadiationLengthsArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellRadiationLengths();
                        nCellInteractionLengthsArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellInteractionLengths();
                        timeArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetTime();
                        inputEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetInputEnergy();
                        mipEquivalentEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetMipEquivalentEnergy();
                        electromagneticEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetElectromagneticEnergy();
                        hadronicEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetHadronicEnergy();
    		    }
                }
    	    }
	}	    

        if(6 == CubeClusterHelper::GetClusterHitType(pCluster) && firstLoopDone)
        {
        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

            for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
	    {
    		for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                    const CartesianVector &positionVector((*hIter)->GetPositionVector());
                    std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
                    for(int iArray = 0; iArray < xSize; iArray ++ ){
                        cubeArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] ++;
                        nCellRadiationLengthsArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellRadiationLengths();
                        nCellInteractionLengthsArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellInteractionLengths();
                        timeArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetTime();
                        inputEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetInputEnergy();
                        mipEquivalentEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetMipEquivalentEnergy();
                        electromagneticEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetElectromagneticEnergy();
                        hadronicEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetHadronicEnergy();
		    }
                }
	    }
        }

    }

	std::cout<<"went through 3D list "<<std::endl;

	const CaloHit *pCaloHit3D;
	
	for(int iArray = 0 ; iArray < xSize; iArray ++)
	{
	    for(int jArray = 0 ; jArray < ySize; jArray ++)
	    {
	        for(int kArray = 0 ; kArray < zSize; kArray ++)
		{
		    if(cubeArray[iArray* mulXY + jArray* zSize +kArray] == 3)
	            { 
		        threeMatching ++;

                        PandoraContentApi::CaloHit::Parameters parameters;
                        parameters.m_positionVector = pandora::CartesianVector(iArray*10.f, jArray*10.f, kArray*10.f);
                        parameters.m_hitType = pandora::HIT_CUSTOM;
			parameters.m_pParentAddress = (void*)(static_cast<uintptr_t>(threeMatching));

                        // TODO Check these parameters, especially new cell dimensions
                        parameters.m_cellThickness = m_cubeSize; //cellThicknessArray[iArray][jArray][kArray];
                        parameters.m_cellGeometry = pandora::RECTANGULAR;
                        parameters.m_cellSize0 = m_cubeSize; //cellSize0Array[iArray][jArray][kArray];
                        parameters.m_cellSize1 = m_cubeSize; //cellSize1Array[iArray][jArray][kArray];
                        parameters.m_cellNormalVector = pandora::CartesianVector(0.f,0.f,1.f);
                        parameters.m_expectedDirection = pandora::CartesianVector(0.f,0.f,1.f);
                        parameters.m_nCellRadiationLengths = 1.f; //nCellRadiationLengthsArray[iArray][jArray][kArray];
                        parameters.m_nCellInteractionLengths = 1.f; //nCellInteractionLengthsArray[iArray][jArray][kArray];
                        parameters.m_time = 0.f; //timeArray[iArray][jArray][kArray];
                        parameters.m_inputEnergy = inputEnergyArray[iArray* mulXY + jArray* zSize +kArray]; //inputEnergyArray[iArray][jArray][kArray];
                        parameters.m_mipEquivalentEnergy = mipEquivalentEnergyArray[iArray* mulXY + jArray* zSize +kArray]; //mipEquivalentEnergyArray[iArray][jArray][kArray];
                        parameters.m_electromagneticEnergy = electromagneticEnergyArray[iArray* mulXY + jArray* zSize +kArray]; //electromagneticEnergyArray[iArray][jArray][kArray];
                        parameters.m_hadronicEnergy = hadronicEnergyArray[iArray* mulXY + jArray* zSize +kArray]; //hadronicEnergyArray[iArray][jArray][kArray];
                        parameters.m_isDigital = false;
                        parameters.m_hitRegion = pandora::SINGLE_REGION; //hitRegionArray[iArray][jArray][kArray];
                        parameters.m_layer = 0; //layerArray[iArray][jArray][kArray];
                        parameters.m_isInOuterSamplingLayer = false;
                        PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CaloHit::Create(*this, parameters, pCaloHit3D));
			std::cout<<"generated one 3D hit "<<(pCaloHit3D->GetPositionVector()).GetX()<<" " <<(pCaloHit3D->GetPositionVector()).GetY()<< " "<< (pCaloHit3D->GetPositionVector()).GetZ() << std::endl;
        		newThreeDHits.push_back(pCaloHit3D);
		    }
		}
	    }
	}
	std::cout<<"*****************************************************"<<std::endl;
	//std::cout<<"****three matching is "<<threeMatching<<"*************"<<std::endl;
	//std::cout<<"****three matching is "<<twoMatching<<"*************"<<std::endl;
	//std::cout<<"****three matching is "<<oneMatching<<"*************"<<std::endl;
	//std::cout<<"*****************************************************"<<std::endl;
	std::cout<<"fist test of size of generated 3D CaloHits : "<<newThreeDHits.size()<<std::endl;
}


//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ThreeDHitCreationAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "InputPfoListName", m_inputPfoListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "OutputCaloHitListName", m_outputCaloHitListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "OutputClusterListName", m_outputClusterListName));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "CubeSize", m_cubeSize));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "NofBoxesX", m_NofBoxesX));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "NofBoxesY", m_NofBoxesY));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "NofBoxesZ", m_NofBoxesZ));    

    return STATUS_CODE_SUCCESS;
    //return ThreeDHitCreationAlgorithm::ReadSettings(xmlHandle);
}

} // namespace example_content
