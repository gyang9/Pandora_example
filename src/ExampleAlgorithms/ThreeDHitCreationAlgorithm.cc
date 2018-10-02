/**
 *  @file   ExampleAlgorithms/ThreeDHitCreationAlgorithm.cc
 *
 *  @brief  Implementation of the three dimensional hit creation algorithm class.
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

#include <algorithm>

using namespace pandora;

namespace example_content
{

ThreeDHitCreationAlgorithm::ThreeDHitCreationAlgorithm() :
    m_iterateTrackHits(true),
    m_iterateShowerHits(false),
    m_slidingFitHalfWindow(10),
    m_nHitRefinementIterations(10),
    m_sigma3DFitMultiplier(0.2),
    m_iterationMaxChi2Ratio(1.),
    m_sigmaUVW(10.),
    m_wirePitch(10.)
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
    std::sort(pfoVector.begin(), pfoVector.end(), LArPfoHelper::SortByNHits);

    for (const ParticleFlowObject *const pPfo : pfoVector)
    {

	ClusterList twoDClusterList;
        LArPfoHelper::GetTwoDClusterList(pPfo, twoDClusterList);

	CartesianVector innerCoordinate(0.f, 0.f, 0.f);
	CartesianVector outerCoordinate(0.f, 0.f, 0.f);
        LArClusterHelper::GetExtremalCoordinates(twoDClusterList, innerCoordinate, outerCoordinate);
	std::cout<<"innerCoordinate: "<<innerCoordinate.GetX()<<" "<<innerCoordinate.GetY()<<" "<<innerCoordinate.GetZ()<<" "<<std::endl;
        std::cout<<"outerCoordinate: "<<outerCoordinate.GetX()<<" "<<outerCoordinate.GetY()<<" "<<outerCoordinate.GetZ()<<" "<<std::endl;

/*    
        ProtoHitVector protoHitVector;

        ClusterList twoDClusterList;
        LArPfoHelper::GetTwoDClusterList(pPfo, twoDClusterList);

	std::cout<<"looping point of pPfo "<<std::endl;

        OrderedCaloHitList orderedCaloHitList;

    for (const Cluster *const pCluster : twoDClusterList)
    {
	std::cout<<"looping point of pCluster "<<std::endl;
	std::cout<<"============== hit type: "<<LArClusterHelper::GetClusterHitType(pCluster)<<std::endl;
	std::cout<<"============== N calo hits : "<<pCluster->GetNCaloHits()<<std::endl;

	orderedCaloHitList = pCluster->GetOrderedCaloHitList();

	for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
        	for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
        	{
		   const CartesianVector &positionVector((*hIter)->GetPositionVector());
		   std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
	        }
    }

    //void ExampleClusterHelper::GetExtremalCoordinates(const ClusterList &clusterList, CartesianVector &innerCoordinate, CartesianVector &outerCoordinate)
 
        if (TPC_3D == LArClusterHelper::GetClusterHitType(pCluster))
            throw StatusCodeException(STATUS_CODE_FAILURE);

        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

    for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
    {
	std::cout<<"looping point of orderedCaloHitList "<<std::endl;
        for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
        {
	    std::cout<<"-------------- hit type: "<<(*hIter)->GetHitType()<<std::endl;
	    std::cout<<"looping point of iter->second "<<std::endl;
            const CartesianVector &positionVector((*hIter)->GetPositionVector());
	    std::cout<<"cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<" "<<std::endl; 
	}
    }
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    CaloHitList allNewThreeDHits;

    PfoVector pfoVector(pPfoList->begin(), pPfoList->end());
    std::sort(pfoVector.begin(), pfoVector.end(), LArPfoHelper::SortByNHits);

    for (const ParticleFlowObject *const pPfo : pfoVector)
    {

        ProtoHitVector protoHitVector;

        for (HitCreationBaseTool *const pHitCreationTool : m_algorithmToolVector)
        {
            CaloHitVector remainingTwoDHits;
            this->SeparateTwoDHits(pPfo, protoHitVector, remainingTwoDHits);

            if (remainingTwoDHits.empty())
                break;

            pHitCreationTool->Run(this, pPfo, remainingTwoDHits, protoHitVector);
        }

        if ((m_iterateTrackHits && LArPfoHelper::IsTrack(pPfo)) || (m_iterateShowerHits && LArPfoHelper::IsShower(pPfo)))
            this->IterativeTreatment(protoHitVector);

        if (protoHitVector.empty())
            continue;
*/
        CaloHitList newThreeDHits;
        //this->CreateThreeDHits(protoHitVector, newThreeDHits);
	this->CreateThreeDHitsList(pPfo, newThreeDHits, innerCoordinate, outerCoordinate);
	std::cout<<"adding to pPfo "<<std::endl;
	//this->AddThreeDHitsToPfo(pPfo, newThreeDHits);
        std::cout<<"caloHit middle size: "<<newThreeDHits.size()<<std::endl;
	std::cout<<"almost end "<<std::endl;
        allNewThreeDHits.insert(allNewThreeDHits.end(), newThreeDHits.begin(), newThreeDHits.end());

        //}
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

    std::cout<<"check point 1 "<<std::endl;
    //std::vector<std::vector<std::vector<double>>> cubeArray (zSize, std::vector<std::vector<double>> (200, std::vector <double> (200, 0.)) );
    
    float* cubeArray = (float*)malloc(mulXYZ* sizeof(float));
    //float* cellThicknessArray = (float*)malloc(mulXYZ* sizeof(float));
    //float* cellSize0Array = (float*)malloc(mulXYZ* sizeof(float));
    //float* cellSize1Array = (float*)malloc(mulXYZ* sizeof(float));
    float* nCellRadiationLengthsArray = (float*)malloc(mulXYZ* sizeof(float));
    float* nCellInteractionLengthsArray = (float*)malloc(mulXYZ* sizeof(float));
    float* timeArray = (float*)malloc(mulXYZ* sizeof(float));
    float* inputEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    float* mipEquivalentEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    float* electromagneticEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    float* hadronicEnergyArray = (float*)malloc(mulXYZ* sizeof(float));
    //unsigned int layerArray = (float*)malloc(mulXYZ* sizeof(float)) ;

    for (int i=0;i<mulXYZ;i++)
    {
	cubeArray[i] = 0.;
	//cellThicknessArray[i] = 0.;
        //cellSize0Array[i] = 0.;0
        //cellSize1Array[i] = 0.;
        nCellRadiationLengthsArray[i] = 0.;
        nCellInteractionLengthsArray[i] = 0.;
        timeArray[i] = 0.;
        inputEnergyArray[i] = 0.;
        mipEquivalentEnergyArray[i] = 0.;
        electromagneticEnergyArray[i] = 0.;
        hadronicEnergyArray[i] = 0.;
        //layerArray[i] = 0.;
    }
/*
    float cellThicknessArray[xSize][ySize][zSize];
    float cellSize0Array[xSize][ySize][zSize];
    float cellSize1Array[xSize][ySize][zSize];
    float nCellRadiationLengthsArray[xSize][ySize][zSize];
    float nCellInteractionLengthsArray[xSize][ySize][zSize];
    float timeArray[xSize][ySize][zSize];
    float inputEnergyArray[xSize][ySize][zSize];
    float mipEquivalentEnergyArray[xSize][ySize][zSize];
    float electromagneticEnergyArray[xSize][ySize][zSize];
    float hadronicEnergyArray[xSize][ySize][zSize];
    std::cout<<"check point 2 "<<std::endl;
    HitRegion hitRegionArray[xSize][ySize][zSize] ;
    unsigned int layerArray[xSize][ySize][zSize] ;
    std::cout<<"check point 3 "<<std::endl;
*/
    bool firstLoopDone = false;
    double threeMatching, twoMatching, oneMatching;
    ClusterList twoDClusterList;
    LArPfoHelper::GetTwoDClusterList(pPfo, twoDClusterList);

    OrderedCaloHitList orderedCaloHitList;

    for (const Cluster *const pCluster : twoDClusterList)
    {
        std::cout<<"looping point of pCluster "<<std::endl;
        std::cout<<"============== hit type: "<<LArClusterHelper::GetClusterHitType(pCluster)<<std::endl;
        std::cout<<"============== N calo hits : "<<pCluster->GetNCaloHits()<<std::endl;
	
	threeMatching = 0;
	twoMatching   = 0;
	oneMatching   = 0;

	if(4 == LArClusterHelper::GetClusterHitType(pCluster))
	{
        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

        for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
            for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                   const CartesianVector &positionVector((*hIter)->GetPositionVector());
                   std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
	 	   for(int iArray = 0; iArray < zSize; iArray ++ ){
			cubeArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] ++;
			//std::cout<<"in aaa test "<<std::endl;

			//cellThicknessArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetCellThickness();
    			//cellSize0Array[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetCellLengthScale();
    			//cellSize1Array[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetCellLengthScale();
    			nCellRadiationLengthsArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetNCellRadiationLengths();
    			nCellInteractionLengthsArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetNCellInteractionLengths();
    			timeArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetTime();
    			inputEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetInputEnergy();
    			mipEquivalentEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetMipEquivalentEnergy();
    			electromagneticEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetElectromagneticEnergy();
    			hadronicEnergyArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetHadronicEnergy();
    			//hitRegionArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetHitRegion();
    			//layerArray[mulXY * (int)(positionVector.GetX()/10) + zSize * (int)(positionVector.GetZ()/10) + iArray] = (*hIter)->GetLayer();

     		    }
                }
	firstLoopDone = true;
	}


	if(5 == LArClusterHelper::GetClusterHitType(pCluster) && firstLoopDone)
        {
        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

        for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
            for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                   const CartesianVector &positionVector((*hIter)->GetPositionVector());
                   std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
                   for(int iArray = 0; iArray < ySize; iArray ++ ){
                        cubeArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] ++;

                        //cellThicknessArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetCellThickness();
                        //cellSize0Array[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetCellLengthScale();
                        //cellSize1Array[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetCellLengthScale();
                        nCellRadiationLengthsArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellRadiationLengths();
                        nCellInteractionLengthsArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellInteractionLengths();
                        timeArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetTime();
                        inputEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetInputEnergy();
                        mipEquivalentEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetMipEquivalentEnergy();
                        electromagneticEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetElectromagneticEnergy();
                        hadronicEnergyArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetHadronicEnergy();
                        //hitRegionArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetHitRegion();
                        //layerArray[ mulXY * (int)(positionVector.GetX()/10) + zSize * iArray + (int)(positionVector.GetZ()/10)] = (*hIter)->GetLayer();

    		    }
                }

        }



        if(6 == LArClusterHelper::GetClusterHitType(pCluster) && firstLoopDone)
        {
        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

        for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
            for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                   const CartesianVector &positionVector((*hIter)->GetPositionVector());
                   std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
                   for(int iArray = 0; iArray < xSize; iArray ++ ){
                        cubeArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] ++;

                        //cellThicknessArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetCellThickness();
                        //cellSize0Array[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetCellLengthScale();
                        //cellSize1Array[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetCellLengthScale();
                        nCellRadiationLengthsArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellRadiationLengths();
                        nCellInteractionLengthsArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetNCellInteractionLengths();
                        timeArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetTime();
                        inputEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetInputEnergy();
                        mipEquivalentEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetMipEquivalentEnergy();
                        electromagneticEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetElectromagneticEnergy();
                        hadronicEnergyArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetHadronicEnergy();
                        //hitRegionArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetHitRegion();
                        //layerArray[ mulXY * iArray + zSize * (int)(positionVector.GetX()/10) + (int)(positionVector.GetZ()/10)] = (*hIter)->GetLayer();

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
                        parameters.m_cellThickness = 10.f; //cellThicknessArray[iArray][jArray][kArray];
                        parameters.m_cellGeometry = pandora::RECTANGULAR;
                        parameters.m_cellSize0 = 10.f; //cellSize0Array[iArray][jArray][kArray];
                        parameters.m_cellSize1 = 10.f; //cellSize1Array[iArray][jArray][kArray];
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
		    //if(cubeArray[iArray][jArray][kArray] == 2) twoMatching ++;
		    //if(cubeArray[iArray][jArray][kArray] == 1) oneMatching ++;
		}
	    }
	}
	
	std::cout<<"*****************************************************"<<std::endl;
	std::cout<<"****three matching is "<<threeMatching<<"*************"<<std::endl;
	std::cout<<"****three matching is "<<twoMatching<<"*************"<<std::endl;
	std::cout<<"****three matching is "<<oneMatching<<"*************"<<std::endl;
	std::cout<<"*****************************************************"<<std::endl;

	std::cout<<"fist test of size of generated 3D CaloHits : "<<newThreeDHits.size()<<std::endl;
/*
    for (const Cluster *const pCluster : twoDClusterList)
    {

        orderedCaloHitList = pCluster->GetOrderedCaloHitList();

        for(OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(); iter != orderedCaloHitList.end(); ++iter)
            for (CaloHitList::const_iterator hIter = iter->second->begin(), hIterEnd = iter->second->end(); hIter != hIterEnd; ++hIter)
                {
                   const CartesianVector &positionVector((*hIter)->GetPositionVector());
                   std::cout<<"Cartesian vector for 3D hits: "<<positionVector.GetX()<<" "<<positionVector.GetY()<<" "<<positionVector.GetZ()<<std::endl;
                   for(int iArray = 0; iArray < zSize; iArray ++ )
		   {
                        cubeArray[positionVector.GetX()][positionVector.GetY()][iArray] ++;

		    	if (!this->CheckThreeDHit(protoHit))
		        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

		        PandoraContentApi::CaloHit::Parameters parameters;
    			parameters.m_positionVector = protoHit.GetPosition3D();
    			parameters.m_hitType = TPC_3D;

    			const CaloHit *const pCaloHit2D(protoHit.GetParentCaloHit2D());
    			parameters.m_pParentAddress = static_cast<const void*>(pCaloHit2D);

    			// TODO Check these parameters, especially new cell dimensions
    			parameters.m_cellThickness = pCaloHit2D->GetCellThickness();
    			parameters.m_cellGeometry = RECTANGULAR;
    			parameters.m_cellSize0 = pCaloHit2D->GetCellLengthScale();
    			parameters.m_cellSize1 = pCaloHit2D->GetCellLengthScale();
    			parameters.m_cellNormalVector = pCaloHit2D->GetCellNormalVector();
    			parameters.m_expectedDirection = pCaloHit2D->GetExpectedDirection();
    			parameters.m_nCellRadiationLengths = pCaloHit2D->GetNCellRadiationLengths();
    			parameters.m_nCellInteractionLengths = pCaloHit2D->GetNCellInteractionLengths();
    			parameters.m_time = pCaloHit2D->GetTime();
    			parameters.m_inputEnergy = pCaloHit2D->GetInputEnergy();
    			parameters.m_mipEquivalentEnergy = pCaloHit2D->GetMipEquivalentEnergy();
    			parameters.m_electromagneticEnergy = pCaloHit2D->GetElectromagneticEnergy();
    			parameters.m_hadronicEnergy = pCaloHit2D->GetHadronicEnergy();
    			parameters.m_isDigital = pCaloHit2D->IsDigital();
    			parameters.m_hitRegion = pCaloHit2D->GetHitRegion();
    			parameters.m_layer = pCaloHit2D->GetLayer();
    			parameters.m_isInOuterSamplingLayer = pCaloHit2D->IsInOuterSamplingLayer();
    			PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CaloHit::Create(*this, parameters, pCaloHit3D));
		   }
                }

    }
*/
}


//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::SeparateTwoDHits(const ParticleFlowObject *const pPfo, const ProtoHitVector &protoHitVector, CaloHitVector &remainingHitVector) const
{
    ClusterList twoDClusterList;
    LArPfoHelper::GetTwoDClusterList(pPfo, twoDClusterList);
    CaloHitList remainingHitList;

    for (const Cluster *const pCluster : twoDClusterList)
    {
        if (TPC_3D == LArClusterHelper::GetClusterHitType(pCluster))
            throw StatusCodeException(STATUS_CODE_FAILURE);

        pCluster->GetOrderedCaloHitList().FillCaloHitList(remainingHitList);
    }

    CaloHitSet remainingHitSet(remainingHitList.begin(), remainingHitList.end());

    for (const ProtoHit &protoHit : protoHitVector)
    {
        CaloHitSet::iterator eraseIter = remainingHitSet.find(protoHit.GetParentCaloHit2D());

        if (remainingHitSet.end() == eraseIter)
            throw StatusCodeException(STATUS_CODE_FAILURE);

        remainingHitSet.erase(eraseIter);
    }

    remainingHitVector.insert(remainingHitVector.end(), remainingHitSet.begin(), remainingHitSet.end());
    std::sort(remainingHitVector.begin(), remainingHitVector.end(), LArClusterHelper::SortHitsByPosition);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::IterativeTreatment(ProtoHitVector &protoHitVector) const
{
    const float layerPitch(m_wirePitch); //LArGeometryHelper::GetWireZPitch(this->GetPandora()));
    const unsigned int layerWindow(m_slidingFitHalfWindow);

    double originalChi2(0.);
    CartesianPointVector currentPoints3D;
    this->ExtractResults(protoHitVector, originalChi2, currentPoints3D);

    try
    {
        const ThreeDSlidingFitResult originalSlidingFitResult(&currentPoints3D, layerWindow, layerPitch);
        //const double originalChi2WrtFit(this->GetChi2WrtFit(originalSlidingFitResult, protoHitVector));
        double currentChi2(originalChi2 + 0 ) ; //+ originalChi2WrtFit);

        unsigned int nIterations(0);

        while (nIterations++ < m_nHitRefinementIterations)
        {
            ProtoHitVector newProtoHitVector(protoHitVector);
            const ThreeDSlidingFitResult newSlidingFitResult(&currentPoints3D, layerWindow, layerPitch);
            this->RefineHitPositionsCheating(newSlidingFitResult, newProtoHitVector);

            double newChi2(0.);
            CartesianPointVector newPoints3D;
            this->ExtractResults(newProtoHitVector, newChi2, newPoints3D);

            if (newChi2 > m_iterationMaxChi2Ratio * currentChi2)
                break;

            currentChi2 = newChi2;
            currentPoints3D = newPoints3D;
            protoHitVector = newProtoHitVector;
        }
    }
    catch (const StatusCodeException &)
    {
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::ExtractResults(const ProtoHitVector &protoHitVector, double &chi2, CartesianPointVector &pointVector) const
{
    chi2 = 0.;
    pointVector.clear();

    for (const ProtoHit &protoHit : protoHitVector)
    {
        chi2 += protoHit.GetChi2();
        pointVector.push_back(protoHit.GetPosition3D());
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
// NTMF
double ThreeDHitCreationAlgorithm::GetChi2WrtFit(const ThreeDSlidingFitResult &slidingFitResult, const ProtoHitVector &protoHitVector) const
{
    const double sigmaUVW(m_sigmaUVW);  //LArGeometryHelper::GetSigmaUVW(this->GetPandora()));
    const double sigma3DFit(sigmaUVW * m_sigma3DFitMultiplier);

    double chi2WrtFit(0.);

    for (const ProtoHit &protoHit : protoHitVector)
    {
        CartesianVector pointOnFit(0.f, 0.f, 0.f);
        const double rL(slidingFitResult.GetLongitudinalDisplacement(protoHit.GetPosition3D()));

        if (STATUS_CODE_SUCCESS != slidingFitResult.GetGlobalFitPosition(rL, pointOnFit))
            continue;

        const double uFit(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoU(pointOnFit.GetY(), pointOnFit.GetZ()));
        const double vFit(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoV(pointOnFit.GetY(), pointOnFit.GetZ()));
        const double wFit(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoW(pointOnFit.GetY(), pointOnFit.GetZ()));

        const double outputU(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoU(protoHit.GetPosition3D().GetY(), protoHit.GetPosition3D().GetZ()));
        const double outputV(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoV(protoHit.GetPosition3D().GetY(), protoHit.GetPosition3D().GetZ()));
        const double outputW(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoW(protoHit.GetPosition3D().GetY(), protoHit.GetPosition3D().GetZ()));

        const double deltaUFit(uFit - outputU), deltaVFit(vFit - outputV), deltaWFit(wFit - outputW);
        chi2WrtFit += ((deltaUFit * deltaUFit) / (sigma3DFit * sigma3DFit)) + ((deltaVFit * deltaVFit) / (sigma3DFit * sigma3DFit)) + ((deltaWFit * deltaWFit) / (sigma3DFit * sigma3DFit));
    }

    return chi2WrtFit;
}

//------------------------------------------------------------------------------------------------------------------------------------------

double ThreeDHitCreationAlgorithm::GetHitMovementChi2(const ProtoHitVector &protoHitVector) const
{
    const double sigmaUVW(m_sigmaUVW); //LArGeometryHelper::GetSigmaUVW(this->GetPandora()));
    double hitMovementChi2(0.);

    for (const ProtoHit &protoHit : protoHitVector)
    {
        const CaloHit *const pCaloHit2D(protoHit.GetParentCaloHit2D());
        const HitType hitType(pCaloHit2D->GetHitType());

        const CartesianVector projectedPosition(LArGeometryHelper::ProjectPosition(this->GetPandora(), protoHit.GetPosition3D(), hitType));
        const double delta(static_cast<double>(pCaloHit2D->GetPositionVector().GetZ() - projectedPosition.GetZ()));

        hitMovementChi2 += (delta * delta) / (sigmaUVW * sigmaUVW);
    }

    return hitMovementChi2;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::RefineHitPositionsCheating(const ThreeDSlidingFitResult &slidingFitResult, ProtoHitVector &protoHitVector) const
{

}

//------------------------------------------------------------------------------------------------------------------------------------------


void ThreeDHitCreationAlgorithm::RefineHitPositions(const ThreeDSlidingFitResult &slidingFitResult, ProtoHitVector &protoHitVector) const
{
    const double sigmaUVW(m_sigmaUVW);  //LArGeometryHelper::GetSigmaUVW(this->GetPandora()));
    const double sigmaFit(sigmaUVW); // ATTN sigmaFit and sigmaHit here should agree with treatment in HitCreation tools
    const double sigmaHit(sigmaUVW);
    const double sigma3DFit(sigmaUVW * m_sigma3DFitMultiplier);

    for (ProtoHit &protoHit : protoHitVector)
    {
        CartesianVector pointOnFit(0.f, 0.f, 0.f);
        const double rL(slidingFitResult.GetLongitudinalDisplacement(protoHit.GetPosition3D()));

        if (STATUS_CODE_SUCCESS != slidingFitResult.GetGlobalFitPosition(rL, pointOnFit))
            continue;

        const CaloHit *const pCaloHit2D(protoHit.GetParentCaloHit2D());
        const HitType hitType(pCaloHit2D->GetHitType());

        const double uFit(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoU(pointOnFit.GetY(), pointOnFit.GetZ()));
        const double vFit(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoV(pointOnFit.GetY(), pointOnFit.GetZ()));
        const double wFit(PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoW(pointOnFit.GetY(), pointOnFit.GetZ()));

        const double sigmaU((TPC_VIEW_U == hitType) ? sigmaHit : sigmaFit);
        const double sigmaV((TPC_VIEW_V == hitType) ? sigmaHit : sigmaFit);
        const double sigmaW((TPC_VIEW_W == hitType) ? sigmaHit : sigmaFit);

        CartesianVector position3D(0.f, 0.f, 0.f);
        double chi2(std::numeric_limits<double>::max());
        double u(std::numeric_limits<double>::max()), v(std::numeric_limits<double>::max()), w(std::numeric_limits<double>::max());

        if (protoHit.GetNTrajectorySamples() == 2)
        {
            u = (TPC_VIEW_U == hitType) ? pCaloHit2D->GetPositionVector().GetZ() : (TPC_VIEW_U == protoHit.GetFirstTrajectorySample().GetHitType()) ? protoHit.GetFirstTrajectorySample().GetPosition().GetZ() : protoHit.GetLastTrajectorySample().GetPosition().GetZ();
            v = (TPC_VIEW_V == hitType) ? pCaloHit2D->GetPositionVector().GetZ() : (TPC_VIEW_V == protoHit.GetFirstTrajectorySample().GetHitType()) ? protoHit.GetFirstTrajectorySample().GetPosition().GetZ() : protoHit.GetLastTrajectorySample().GetPosition().GetZ();
            w = (TPC_VIEW_W == hitType) ? pCaloHit2D->GetPositionVector().GetZ() : (TPC_VIEW_W == protoHit.GetFirstTrajectorySample().GetHitType()) ? protoHit.GetFirstTrajectorySample().GetPosition().GetZ() : protoHit.GetLastTrajectorySample().GetPosition().GetZ();
        }
        else if (protoHit.GetNTrajectorySamples() == 1)
        {
            u = PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoU(protoHit.GetPosition3D().GetY(), protoHit.GetPosition3D().GetZ());
            v = PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoV(protoHit.GetPosition3D().GetY(), protoHit.GetPosition3D().GetZ());
            w = PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->YZtoW(protoHit.GetPosition3D().GetY(), protoHit.GetPosition3D().GetZ());
        }
        else
        {
            std::cout << "ThreeDHitCreationAlgorithm::IterativeTreatment - Unexpected number of trajectory samples" << std::endl;
            throw StatusCodeException(STATUS_CODE_FAILURE);
        }

        double bestY(std::numeric_limits<double>::max()), bestZ(std::numeric_limits<double>::max());
        PandoraContentApi::GetPlugins(*this)->GetLArTransformationPlugin()->GetMinChiSquaredYZ(u, v, w, sigmaU, sigmaV, sigmaW, uFit, vFit, wFit, sigma3DFit, bestY, bestZ, chi2);
        position3D.SetValues(pCaloHit2D->GetPositionVector().GetX(), static_cast<float>(bestY), static_cast<float>(bestZ));

        protoHit.SetPosition3D(position3D, chi2);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::CreateThreeDHits(const ProtoHitVector &protoHitVector, CaloHitList &newThreeDHits) const
{
    for (const ProtoHit &protoHit : protoHitVector)
    {
        const CaloHit *pCaloHit3D(nullptr);
        this->CreateThreeDHit(protoHit, pCaloHit3D);

        if (!pCaloHit3D)
            throw StatusCodeException(STATUS_CODE_FAILURE);

        newThreeDHits.push_back(pCaloHit3D);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::CreateThreeDHit(const ProtoHit &protoHit, const CaloHit *&pCaloHit3D) const
{ 
    if (!this->CheckThreeDHit(protoHit))
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

    PandoraContentApi::CaloHit::Parameters parameters;
    parameters.m_positionVector = protoHit.GetPosition3D();
    parameters.m_hitType = TPC_3D;

    const CaloHit *const pCaloHit2D(protoHit.GetParentCaloHit2D());
    parameters.m_pParentAddress = static_cast<const void*>(pCaloHit2D);

    // TODO Check these parameters, especially new cell dimensions
    parameters.m_cellThickness = pCaloHit2D->GetCellThickness();
    parameters.m_cellGeometry = RECTANGULAR;
    parameters.m_cellSize0 = pCaloHit2D->GetCellLengthScale();
    parameters.m_cellSize1 = pCaloHit2D->GetCellLengthScale();
    parameters.m_cellNormalVector = pCaloHit2D->GetCellNormalVector();
    parameters.m_expectedDirection = pCaloHit2D->GetExpectedDirection();
    parameters.m_nCellRadiationLengths = pCaloHit2D->GetNCellRadiationLengths();
    parameters.m_nCellInteractionLengths = pCaloHit2D->GetNCellInteractionLengths();
    parameters.m_time = pCaloHit2D->GetTime();
    parameters.m_inputEnergy = pCaloHit2D->GetInputEnergy();
    parameters.m_mipEquivalentEnergy = pCaloHit2D->GetMipEquivalentEnergy();
    parameters.m_electromagneticEnergy = pCaloHit2D->GetElectromagneticEnergy();
    parameters.m_hadronicEnergy = pCaloHit2D->GetHadronicEnergy();
    parameters.m_isDigital = pCaloHit2D->IsDigital();
    parameters.m_hitRegion = pCaloHit2D->GetHitRegion();
    parameters.m_layer = pCaloHit2D->GetLayer();
    parameters.m_isInOuterSamplingLayer = pCaloHit2D->IsInOuterSamplingLayer();
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CaloHit::Create(*this, parameters, pCaloHit3D));
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool ThreeDHitCreationAlgorithm::CheckThreeDHit(const ProtoHit &protoHit) const
{
    try
    {
        // Check that corresponding pseudo layer is within range - TODO use full LArTPC geometry here
        (void) PandoraContentApi::GetPlugins(*this)->GetPseudoLayerPlugin()->GetPseudoLayer(protoHit.GetPosition3D());
    }
    catch (StatusCodeException &)
    {
        return false;
    }

    // TODO Check against detector geometry
    return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ThreeDHitCreationAlgorithm::AddThreeDHitsToPfo(const ParticleFlowObject *const pPfo, const CaloHitList &caloHitList) const
{
    if (caloHitList.empty())
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    ClusterList threeDClusterList;
    LArPfoHelper::GetThreeDClusterList(pPfo, threeDClusterList);

    if (!threeDClusterList.empty())
        throw StatusCodeException(STATUS_CODE_FAILURE);

    const ClusterList *pClusterList(nullptr); std::string clusterListName;
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CreateTemporaryListAndSetCurrent(*this, pClusterList, clusterListName));

    PandoraContentApi::Cluster::Parameters parameters;
    parameters.m_caloHitList.insert(parameters.m_caloHitList.end(), caloHitList.begin(), caloHitList.end());

    const Cluster *pCluster3D(nullptr);
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::Cluster::Create(*this, parameters, pCluster3D));

    if (!pCluster3D || !pClusterList || pClusterList->empty())
        throw StatusCodeException(STATUS_CODE_FAILURE);

    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Cluster>(*this, m_outputClusterListName));
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::AddToPfo(*this, pPfo, pCluster3D));
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &ThreeDHitCreationAlgorithm::ProtoHit::GetPosition3D() const
{
    if (!m_isPositionSet)
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    return m_position3D;
}

//------------------------------------------------------------------------------------------------------------------------------------------

double ThreeDHitCreationAlgorithm::ProtoHit::GetChi2() const
{
    if (!m_isPositionSet)
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    return m_chi2;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const ThreeDHitCreationAlgorithm::TrajectorySample &ThreeDHitCreationAlgorithm::ProtoHit::GetFirstTrajectorySample() const
{
    if (m_trajectorySampleVector.empty())
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    return m_trajectorySampleVector.front();
}

//------------------------------------------------------------------------------------------------------------------------------------------

const ThreeDHitCreationAlgorithm::TrajectorySample &ThreeDHitCreationAlgorithm::ProtoHit::GetLastTrajectorySample() const
{
    if (m_trajectorySampleVector.size() < 2)
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    return m_trajectorySampleVector.back();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ThreeDHitCreationAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
/*
    AlgorithmToolVector algorithmToolVector;
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ProcessAlgorithmToolList(*this, xmlHandle,
        "HitCreationTools", algorithmToolVector));

    for (AlgorithmToolVector::const_iterator iter = algorithmToolVector.begin(), iterEnd = algorithmToolVector.end(); iter != iterEnd; ++iter)
    {
        HitCreationBaseTool *const pHitCreationTool(dynamic_cast<HitCreationBaseTool*>(*iter));

        if (!pHitCreationTool)
            return STATUS_CODE_INVALID_PARAMETER;

        m_algorithmToolVector.push_back(pHitCreationTool);
    }
*/
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "InputPfoListName", m_inputPfoListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "OutputCaloHitListName", m_outputCaloHitListName));
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "OutputClusterListName", m_outputClusterListName));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "IterateTrackHits", m_iterateTrackHits));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "IterateShowerHits", m_iterateShowerHits));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "SlidingFitHalfWindow", m_slidingFitHalfWindow));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "NHitRefinementIterations", m_nHitRefinementIterations));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "Sigma3DFitMultiplier", m_sigma3DFitMultiplier));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "IterationMaxChi2Ratio", m_iterationMaxChi2Ratio));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "SigmaUVW", m_sigmaUVW));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "CubeSize", m_wirePitch));

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
