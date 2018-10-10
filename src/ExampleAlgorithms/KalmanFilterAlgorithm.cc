/**
 *  @file   ExampleAlgorithms/KalmanFilterAlgorithm.cc
 *
 *  @brief  Implementation of the list preparation algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/KalmanFilterAlgorithm.h"
#include "ExampleAlgorithms/LArClusterHelper.h"
#include "ExampleAlgorithms/KDTreeLinkerAlgoT.h"
#include <fstream>

using namespace pandora;

namespace example_content
{

KalmanFilterAlgorithm::KalmanFilterAlgorithm() :
  m_inputCaloHitListName("Input"),
  m_outputCaloHitListName(""),
  m_currentCaloHitListReplacement("")
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode KalmanFilterAlgorithm::Run()
{
  // List of noisy position measurements (y)
  measurements.clear();

  const CaloHitList *pCaloHitList(nullptr);
  PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_INITIALIZED, !=, PandoraContentApi::GetList(*this , m_inputCaloHitListName, pCaloHitList));
  //pCaloHitList->sort(LArClusterHelper::SortHitsByPosition);

  std::cout<<"just setup Kalman ... "<<std::endl;
  const Cluster* pCluster(nullptr);
  depositEnergy = 0.;
  this->CreateClusters(*pCaloHitList, pCluster);

  /* 
  for (const CaloHit *pCaloHit : *pCaloHitList)
  {
      // Process calo hits, e.g. ...
      if (pCaloHit->GetInputEnergy() > 0.f && pCaloHit->GetPositionVector().GetY()>0)
      {
	  depositEnergy += pCaloHit->GetInputEnergy();
  	  measurements.push_back(pCaloHit->GetPositionVector().GetY());
	  //pCluster->AddCaloHit(pCaloHit);
	  PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::AddToCluster(*this, pCluster, pCaloHit));
      }
  }
  */

  std::cout<<"preparing Kalman filter .."<<std::endl;
  ParticleList particleList;
  //particleList.push_back(Particle(pCluster));

  std::cout<<"ready to run Kalman filter .."<<std::endl;
  int n = 3; // Number of states
  int m = 1; // Number of measurements

  double dt = 1.0/30; // Time step

  Eigen::MatrixXd A(n, n); // System dynamics matrix
  Eigen::MatrixXd C(m, n); // Output matrix
  Eigen::MatrixXd Q(n, n); // Process noise covariance
  Eigen::MatrixXd R(m, m); // Measurement noise covariance
  Eigen::MatrixXd P(n, n); // Estimate error covariance

  // Discrete LTI projectile motion, measuring position only
  A << 1, dt,  0,
       0, 1, dt,
       0, 0, 1;
  C << 1, 0, 0;

  // Reasonable covariance matrices
  Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
  R << 5;
  P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;

  std::cout << "A: \n" << A << std::endl;
  std::cout << "C: \n" << C << std::endl;
  std::cout << "Q: \n" << Q << std::endl;
  std::cout << "R: \n" << R << std::endl;
  std::cout << "P: \n" << P << std::endl;

  // Construct the filter
  KalmanFilterAlgorithm kf(0, A, C, Q, R, P);

  // Best guess of initial states
  Eigen::VectorXd x0(n);
  x0 << measurements[0], 0, 0; //-9.81;
  kf.init(0, x0);

  // Feed measurements into filter, output estimated states
  double t 		= 0;
  double signVote 	= 0;
  double meanFirstOrder = 0.;
  double meanSecondOrder= 0.;
  Eigen::VectorXd y(m);
  //std::cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << std::endl;
  for(int i = 0; i < measurements.size(); i++) {
    t += dt;
    y << measurements[i];
    kf.update(y);
    //std::cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
    //    << ", x_hat[" << i << "] = " << kf.state().transpose() << std::endl;
    std::cout<<i<<" measurements "<<y.transpose()<<" predictions "<<kf.state().transpose()<<std::endl;
    //std::cout<<"test "<<kf.state().transpose()(0)<<"  |  "<<kf.state().transpose()(1)<<std::endl;
    signVote += kf.state().transpose()(2);
    meanFirstOrder  +=  kf.state().transpose()(1);
    meanSecondOrder +=  kf.state().transpose()(2);
  }

  meanFirstOrder /= measurements.size();
  meanSecondOrder /= measurements.size();
  int m_muonSign2 = 0;
  if (signVote < 0)
      m_muonSign2 = -1;
  else 
      m_muonSign2 = 1; 

  //const PfoList *pPfoList(nullptr); 
  //std::string pfoListName;
  //PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::CreateTemporaryListAndSetCurrent(*this, pPfoList, pfoListName));
/*
  for (const Particle &particle : particleList)
  {
      PandoraContentApi::ParticleFlowObject::Parameters pfoParameters;
      pfoParameters.m_particleId     = MU_MINUS;
      pfoParameters.m_charge         = m_muonSign2;
      pfoParameters.m_energy         = depositEnergy;
      pfoParameters.m_momentum       = CartesianVector(0.f, 0.f, 0.f);
      
      const ParticleFlowObject *pPfo(NULL);
      
      //PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::ParticleFlowObject::Create(*this, pfoParameters, pPfo));
  }
*/
  //////////////////////////////////////////////////////////
  //
  //
      int o_id=1;
      std::ofstream out ("/home/guang/work/Pandora/ExampleContent/build/output.txt" , std::ofstream::out | std::ofstream::app);
      out<< o_id <<" "<< m_muonSign2 <<" "<< depositEnergy <<" "<< kf.state().transpose()(1) <<" "<< kf.state().transpose()(2) <<" "<< meanFirstOrder <<" "<< meanSecondOrder <<" "<< trueEnergy << " " <<std::endl;
      
  //
  //
  //////////////////////////////////////////////////////////

  //const PfoList *pPfoList(nullptr);
  //PfoVector pfoVector(pPfoList->begin(), pPfoList->end());

  //PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList<Pfo>(*this, m_outputPfoListName));
  //const StatusCode statusCode(PandoraContentApi::ReplaceCurrentList<Pfo>(*this, m_outputPfoListName));

  return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------


KalmanFilterAlgorithm::KalmanFilterAlgorithm(
    double kdt,
    const Eigen::MatrixXd& kA,
    const Eigen::MatrixXd& kC,
    const Eigen::MatrixXd& kQ,
    const Eigen::MatrixXd& kR,
    const Eigen::MatrixXd& kP)
  : kA(kA), kC(kC), kQ(kQ), kR(kR), kP0(kP),
    m(kC.rows()), n(kA.rows()), kdt(kdt), kinitialized(false),
    kI(n, n), kx_hat(n), kx_hat_new(n)
{
  kI.setIdentity();
}


void KalmanFilterAlgorithm::init(double t0, const Eigen::VectorXd& x0) {
  kx_hat = x0;
  kP = kP0;
  this->kt0 = t0;
  kt = t0;
  kinitialized = true;
}


void KalmanFilterAlgorithm::update(const Eigen::VectorXd& y) {

  if(!kinitialized)
    throw std::runtime_error("Filter is not initialized!");

  kx_hat_new = kA * kx_hat;
  kP = kA*kP*kA.transpose() + kQ;
  kK = kP*kC.transpose()*(kC*kP*kC.transpose() + kR).inverse();
  kx_hat_new += kK * (y - kC*kx_hat_new);
  kP = (kI - kK*kC)*kP;
  kx_hat = kx_hat_new;

  kt += kdt;
}

void KalmanFilterAlgorithm::update(const Eigen::VectorXd& y, double dt, const Eigen::MatrixXd A) {

  this->kA = A;
  this->kdt = dt;
  update(y);
}

//------------------------------------------------------------------------------------------------------------------------------------------

KalmanFilterAlgorithm::Particle::Particle(const Cluster *const pClusterU) 
{
    if (NULL == pClusterU )
        throw StatusCodeException(STATUS_CODE_FAILURE);
}

//------------------------------------------------------------------------------------------------------------------------------------------

pandora::StatusCode KalmanFilterAlgorithm::CreateClusters(const CaloHitList &caloHitList,  const Cluster* pCluster ) 
{
    CaloHitSet vetoList;
    CaloHitVector caloHitVector(caloHitList.begin(), caloHitList.end());
    std::sort(caloHitVector.begin(), caloHitVector.end(), LArClusterHelper::SortHitsByPosition);

    for (const CaloHit *const pSeedCaloHit : caloHitVector)
    {
        if (pSeedCaloHit->GetInputEnergy() > 0.f && pSeedCaloHit->GetPositionVector().GetY()>0)
        {
	  trueEnergy = pSeedCaloHit->GetHadronicEnergy();
          depositEnergy += pSeedCaloHit->GetInputEnergy();
          measurements.push_back(pSeedCaloHit->GetPositionVector().GetY());

	  //PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::AddToCluster(*this, pCluster, pSeedCaloHit));
	}
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode KalmanFilterAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputCaloHitListName", m_inputCaloHitListName));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputCaloHitListNameU", m_outputCaloHitListName));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS,STATUS_CODE_NOT_FOUND,  !=, XmlHelper::ReadValue(xmlHandle,
        "CurrentCaloHitListReplacement", m_currentCaloHitListReplacement));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS,STATUS_CODE_NOT_FOUND,  !=, XmlHelper::ReadValue(xmlHandle,
        "OutputPfoListName", m_outputPfoListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
