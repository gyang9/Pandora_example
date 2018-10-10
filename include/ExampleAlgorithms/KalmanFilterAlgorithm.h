/**
 *  @file   ExampleAlgorithms/KalmanFilterAlgorithm.h
 * 
 *  @brief  Header file for the pre processing algorithm class.
 * 
 *  $Log: $
 */
#ifndef EXAMPLE_KALMANFILTER_ALGORITHM_H
#define EXAMPLE_KALMANFILTER_ALGORITHM_H 1

#include "Pandora/Algorithm.h"
#include "Pandora/AlgorithmTool.h"
#include "Pandora/AlgorithmHeaders.h"

#include <vector>
#include <Eigen/Dense>

#pragma once

namespace example_content
{

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  KalmanFilterAlgorithm class
 */
class KalmanFilterAlgorithm : public pandora::Algorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    KalmanFilterAlgorithm();

  /**
  * Create a Kalman filter with the specified matrices.
  *   A - System dynamics matrix
  *   C - Output matrix
  *   Q - Process noise covariance
  *   R - Measurement noise covariance
  *   P - Estimate error covariance
  */
   
    KalmanFilterAlgorithm(
        double kdt,
        const Eigen::MatrixXd& kA,
        const Eigen::MatrixXd& kC,
        const Eigen::MatrixXd& kQ,
        const Eigen::MatrixXd& kR,
        const Eigen::MatrixXd& kP
    );


    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };


private:


  pandora::StatusCode Run();
  pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);


  // Matrices for computation
  Eigen::MatrixXd kA, kC, kQ, kR, kP, kK, kP0;

  // System dimensions
  int m, n;

  // Initial and current time
  double kt0, kt;

  // Discrete time step
  double kdt;

  // Is the filter initialized?
  bool kinitialized;

  // n-size identity
  Eigen::MatrixXd kI;

  // Estimated states
  Eigen::VectorXd kx_hat, kx_hat_new;


  /**
  * Create a blank estimator.
  */
  //KalmanFilterAlgorithm();

  /**
  * Initialize the filter with initial states as zero.
  */
  //void init();

  /**
  * Initialize the filter with a guess for initial states.
  */
  void init(double t0, const Eigen::VectorXd& x0);

  /**
  * Update the estimated state based on measured values. The
  * time step is assumed to remain constant.
  */
  void update(const Eigen::VectorXd& y);

  /**
  * Update the estimated state based on measured values,
  * using the given time step and dynamics matrix.
  */
  void update(const Eigen::VectorXd& y, double dt, const Eigen::MatrixXd A);

  pandora::StatusCode CreateClusters(const pandora::CaloHitList &caloHitList , const pandora::Cluster* pCluster) ;

  /**
  * Return the current state and time.
  */
  Eigen::VectorXd state() { return kx_hat; };
  double time() { return kt; };

  double depositEnergy ;
  double trueEnergy;
  std::vector<double> measurements;

  std::string         m_inputCaloHitListName;             ///< The input calo hit list name
  std::string         m_outputCaloHitListName;           ///< The output calo hit list name for TPC_VIEW_U hits
  std::string         m_currentCaloHitListReplacement;    ///< The name of the calo hit list to replace the current list (optional)
  std::string         m_outputPfoListName;

  class Particle
  {
  public:
      /**
       *  @brief  Constructor
       *
       *  @param  pCluster the cluster 
       */
       Particle(const pandora::Cluster *const pCluster);
  };

  typedef std::vector<Particle> ParticleList;

};

//---------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *KalmanFilterAlgorithm::Factory::CreateAlgorithm() const
{
    return new KalmanFilterAlgorithm();
}


} // namespace example_content

#endif // #ifndef EXAMPLE_PRE_PROCESSING_ALGORITHM_H
