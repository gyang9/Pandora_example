/**
 *  @file   ExamplePandora/test/PandoraExample.cc
 * 
 *  @brief  Implementation for the pandora example application
 * 
 *  $Log: $
 */

#include "Api/PandoraApi.h"

#include "ExampleContent.h"

#ifdef MONITORING
#include "TApplication.h"
#endif

#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include <TTree.h>
#include <TFile.h>

/**
 *  @brief  Parameters class
 */
class Parameters
{
public:
    /**
     *  @brief Default constructor
     */
    Parameters();

    std::string     m_pandoraSettingsFile;          ///< The path to the pandora settings file (mandatory parameter)
    int             m_nEventsToProcess;             ///< The number of events to process (default all events in file)
    int             m_nEventsStartProcess;
    int             m_nHitGroupings;                ///< The number of hit groupings to generate for test purposes
    int             m_nHitsPerGroup;                ///< The number of hits per group to generate for test purposes
    float           m_worldSideLength;              ///< The world volume cube side length
    float           m_groupSideLength;              ///< The group volume cube side length
};

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Parse the command line arguments, setting the application parameters
 * 
 *  @param  argc argument count
 *  @param  argv argument vector
 *  @param  parameters to receive the application parameters
 * 
 *  @return success
 */
bool ParseCommandLine(int argc, char *argv[], Parameters &parameters);

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Print the list of configurable options
 *
 *  @return false, to force abort
 */
bool PrintOptions();

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  Generate a specified number of example pandora hits, randomly positioned in groups in a world volume cube of defined length
 * 
 *  @param  pandora the relevant pandora instance
 *  @param  parameters the application parameters
 *  @param  randomEngine for random number generation
 * 
 *  @return success
 */
pandora::StatusCode GenerateExampleHits(const pandora::Pandora &pandora, const Parameters &parameters , const int nEvents);

//------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    try
    {
        // Parse command line parameters
        Parameters parameters;

        if (!ParseCommandLine(argc, argv, parameters))
            return 1;
#ifdef MONITORING
        TApplication *const pTApplication = new TApplication("MyTest", &argc, argv);
        pTApplication->SetReturnFromRun(kTRUE);
#endif
        // Construct pandora instance
        const pandora::Pandora *const pPandora = new pandora::Pandora();

        // Register content from external pandora libraries
        PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, ExampleContent::RegisterExampleAlgorithms(*pPandora));
        PANDORA_RETURN_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, ExampleContent::RegisterExamplePlugins(*pPandora));

        // Read in the PandoraSettings
        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::ReadSettings(*pPandora, parameters.m_pandoraSettingsFile));

        // Process the events
        int nEvents(parameters.m_nEventsStartProcess);

        while ((nEvents++ < parameters.m_nEventsToProcess) || (0 > parameters.m_nEventsToProcess))
        {
            PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, GenerateExampleHits(*pPandora, parameters, nEvents));
            PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::ProcessEvent(*pPandora));
            PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::Reset(*pPandora));
        }

        delete pPandora;
    }
    catch (pandora::StatusCodeException &statusCodeException)
    {
        std::cerr << "Pandora Exception caught: " << statusCodeException.ToString() << std::endl;
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool ParseCommandLine(int argc, char *argv[], Parameters &parameters)
{
    if (1 == argc)
        return PrintOptions();

    int c(0);

    while ((c = getopt(argc, argv, "i:n:b:g:p:w:s:h")) != -1)
    {
        switch (c)
        {
        case 'i':
            parameters.m_pandoraSettingsFile = optarg;
            break;
        case 'n':
            parameters.m_nEventsToProcess = atoi(optarg);
            break;
        case 'b':
            parameters.m_nEventsStartProcess = atoi(optarg);
            break;
	case 'g':
            parameters.m_nHitGroupings = std::min(100, atoi(optarg));
            break;
        case 'p':
            parameters.m_nHitsPerGroup = std::min(1000, atoi(optarg));
            break;
        case 'w':
            parameters.m_worldSideLength = atof(optarg);
            break;
        case 's':
            parameters.m_groupSideLength = atof(optarg);
            break;
        case 'h':
        default:
            return PrintOptions();
        }
    }

    return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool PrintOptions()
{
    std::cout << std::endl << "PandoraExample " << std::endl
              << "    -i PandoraSettings.xml  (required)" << std::endl
              << "    -n NEventsToProcess     (optional)" << std::endl
	      << "    -b NEventsStartProcess  (optional)" << std::endl
              << "    -g NHitGroupings        (optional)" << std::endl
              << "    -p NHitsPerGroup        (optional)" << std::endl
              << "    -w WorldSideLength      (optional, may require algorithm retuning)" << std::endl
              << "    -s GroupSideLength      (optional, may require algorithm retuning)" << std::endl << std::endl;

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode GenerateExampleHits(const pandora::Pandora &pandora, const Parameters &inputParameters, const int nEvents)
{

    int event;
    double hitLocation[3],hitPE[3],hitT[3],adc[3],loadc[3],Q[3],hitLowQ[3];
    double trueCos,trueC;
    double true3Mom[3];
    double trueLen,trueL;
    double trueMom,trueM;
    int prim, PDG;
    double ener;
    double nuEnergy;
    int muonID = 0;
    int if3DST = 0;

    //std::uniform_real_distribution<float> randomDistribution(0.f, 1.f);

    //TFile file("/home/guang/work/Pandora/WorkshopContent/data/testEvent_3DST+emptyECAL_222_particleGun1000MeVMuon_0.4Bfield_burst_sample0.root");
    TFile file("/home/guang/work/Pandora/WorkshopContent/data/testEvent_3DST_222_2Dvs3D_sampleT.root");
    //TFile file("/home/guang/work/Pandora/WorkshopContent/data/testEvent_3DST_222_muonFlat_sampleT.root");
    //TFile file("/home/guang/work/Pandora/WorkshopContent/data/testEvent_3DST_222_muonLowEnergy_sample0.root");
    TTree* c = (TTree*)file.Get("EDepSimTree");
    c->SetBranchAddress("event",&event);
    c->SetBranchAddress("hitLocation",&hitLocation);
    c->SetBranchAddress("hitPE",&hitPE);
    c->SetBranchAddress("hitT",&hitT);
    c->SetBranchAddress("hitADC",&adc);
    c->SetBranchAddress("hitLowADC",&loadc);
    c->SetBranchAddress("hitQ",&Q);
    c->SetBranchAddress("hitLowQ",&hitLowQ);
    c->SetBranchAddress("hitPrim",&prim);
    c->SetBranchAddress("hitPDG",&PDG);
    c->SetBranchAddress("hitE",&ener);
    c->SetBranchAddress("trueLen",&trueLen);
    c->SetBranchAddress("trueMom",&trueMom);
    c->SetBranchAddress("true3Mom",&true3Mom);
    c->SetBranchAddress("trueCos",&trueCos);
    c->SetBranchAddress("Enu",&nuEnergy);

    Int_t nevent = c->GetEntries();

    Int_t eventS_XY = nEvents;
    Int_t eventS_XZ = nEvents;
    Int_t eventS_YZ = nEvents;
    Int_t iHit = 0;
    std::cout<<"event number: "<<nEvents<<std::endl;

    //lar_content::LArCaloHitFactory caloHitFactory;
    int hitCounter(0);

    //for(Int_t typeLoop=0;typeLoop<3;typeLoop++){

    for(Int_t ii=0;ii<nevent;ii++){

    	    c->GetEntry(ii);
	    // muon PDG 13 electron 11 pion 211 proton 2212
            if(event == eventS_XY){
            	PandoraApi::CaloHit::Parameters Parameters;
            	Parameters.m_expectedDirection = pandora::CartesianVector(0.f, 0.f, 1.f);
            	Parameters.m_cellNormalVector = pandora::CartesianVector(0.f, 0.f, 1.f);
            	Parameters.m_cellGeometry = pandora::RECTANGULAR;
            	Parameters.m_cellSize0 = 10.f;
            	Parameters.m_cellSize1 = 10.f;
            	Parameters.m_cellThickness = 10.f;
            	Parameters.m_nCellRadiationLengths = 1.f;
            	Parameters.m_nCellInteractionLengths = 1.f;
                //if(TMath::Abs(PDG) == 13) 
                Parameters.m_time = 0.;
                //else
                //        Parameters.m_time = 100.f;		
            	Parameters.m_inputEnergy = ener;
            	Parameters.m_mipEquivalentEnergy = 2.2;
            	Parameters.m_electromagneticEnergy = 0.01;
            	Parameters.m_hadronicEnergy = trueMom;
            	Parameters.m_isDigital = false;

            	Parameters.m_positionVector = pandora::CartesianVector(hitLocation[0],0, hitLocation[1]);
	        Parameters.m_hitType = (pandora::HitType)(4) ;
	    	Parameters.m_hitRegion = pandora::SINGLE_REGION;
            	Parameters.m_layer = 0;
            	Parameters.m_isInOuterSamplingLayer = false;
            	Parameters.m_pParentAddress = (void*)(static_cast<uintptr_t>(iHit));
	    	iHit++;

            	PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::CaloHit::Create(pandora, Parameters));

            }
            else iHit = 0;
    }



    for(Int_t ii=0;ii<nevent;ii++){

    	    c->GetEntry(ii);

            if(event == eventS_XZ ){

                PandoraApi::CaloHit::Parameters parameters2;
                parameters2.m_expectedDirection = pandora::CartesianVector(0.f, 0.f, 1.f);
                parameters2.m_cellNormalVector = pandora::CartesianVector(0.f, 0.f, 1.f);
                parameters2.m_cellGeometry = pandora::RECTANGULAR;
                parameters2.m_cellSize0 = 10.f;
                parameters2.m_cellSize1 = 10.f;
                parameters2.m_cellThickness = 10.f;
                parameters2.m_nCellRadiationLengths = 1.f;
                parameters2.m_nCellInteractionLengths = 1.f;
                //if(TMath::Abs(PDG) == 13) 
                parameters2.m_time = 0.;
                //else
                //        parameters2.m_time = 100.f;		
                parameters2.m_inputEnergy = ener;
                parameters2.m_mipEquivalentEnergy = 2.2;
                parameters2.m_electromagneticEnergy = 0.01;
                parameters2.m_hadronicEnergy = trueMom;
                parameters2.m_isDigital = false;

                parameters2.m_positionVector = pandora::CartesianVector(hitLocation[0],0 ,hitLocation[2]);
                parameters2.m_hitType = pandora::TPC_VIEW_V;
                parameters2.m_hitRegion = pandora::SINGLE_REGION;
                parameters2.m_layer = 0;
                parameters2.m_isInOuterSamplingLayer = false;
                parameters2.m_pParentAddress = (void*)(static_cast<uintptr_t>(iHit));
                iHit++;
		try
		{
                PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::CaloHit::Create(pandora, parameters2));
		}
		catch (const pandora::StatusCodeException &)
        	{
                std::cout << "CreatePandoraHits2D - unable to create calo hit, insufficient or invalid information supplied " << std::endl;
            	continue;
		}

            }
            else iHit = 0;
    }


    for(Int_t ii=0;ii<nevent;ii++){

    	    c->GetEntry(ii);

            if(event == eventS_YZ ){


                PandoraApi::CaloHit::Parameters parameters3;
                parameters3.m_expectedDirection = pandora::CartesianVector(0.f, 0.f, 1.f);
                parameters3.m_cellNormalVector = pandora::CartesianVector(0.f, 0.f, 1.f);
                parameters3.m_cellGeometry = pandora::RECTANGULAR;
                parameters3.m_cellSize0 = 10.f;
                parameters3.m_cellSize1 = 10.f;
                parameters3.m_cellThickness = 10.f;
                parameters3.m_nCellRadiationLengths = 1.f;
                parameters3.m_nCellInteractionLengths = 1.f;
                //if(TMath::Abs(PDG) == 13) 
		parameters3.m_time = 0.;
		//else
		//	parameters3.m_time = 100.f;
                parameters3.m_inputEnergy = ener;
                parameters3.m_mipEquivalentEnergy = 2.2;
                parameters3.m_electromagneticEnergy = 0.01;
                parameters3.m_hadronicEnergy = trueMom;
                parameters3.m_isDigital = false;

                parameters3.m_positionVector = pandora::CartesianVector(hitLocation[1], 0 ,hitLocation[2]);
		parameters3.m_hitType = pandora::TPC_VIEW_W;
                parameters3.m_hitRegion = pandora::SINGLE_REGION;
                parameters3.m_layer = 0;
                parameters3.m_isInOuterSamplingLayer = false;
                parameters3.m_pParentAddress = (void*)((intptr_t)(iHit));
                iHit++;

                PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::CaloHit::Create(pandora, parameters3));		

	    }
	    else iHit = 0;
    }
    std::cout<<"event processed "<<std::endl;
		//}

    return pandora::STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

Parameters::Parameters() :
    m_pandoraSettingsFile(),
    m_nEventsToProcess(-1),
    m_nEventsStartProcess(-1),
    m_nHitGroupings(10),
    m_nHitsPerGroup(100),
    m_worldSideLength(500.f),
    m_groupSideLength(10.f)
{
}
