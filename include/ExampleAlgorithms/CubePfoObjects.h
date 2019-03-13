/**
 *  @file   ExampleAlgorithms/CubePfoObjects.h
 *
 *  @brief  Header file for lar pfo objects.
 *
 *  $Log: $
 */
#ifndef EXAMPLE_PFO_OBJECTS_H
#define EXAMPLE_PFO_OBJECTS_H 1

#include "Objects/TrackState.h"
#include "Objects/CartesianVector.h"

#include <vector>

namespace pandora {class CaloHit;}

//------------------------------------------------------------------------------------------------------------------------------------------

namespace example_content
{

/**
 *  @brief  CubeTrackState class
 */
class CubeTrackState : public pandora::TrackState
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  position the position
     *  @param  direction the direction
     *  @param  pCaloHit the address of the associated calo hit
     */
    CubeTrackState(const pandora::CartesianVector &position, const pandora::CartesianVector &direction, const pandora::CaloHit *const pCaloHit);

    /**
     *  @brief  Constructor
     *
     *  @param  position the position
     *  @param  direction the direction
     */
    CubeTrackState(const pandora::CartesianVector &position, const pandora::CartesianVector &direction);

    /**
     *  @brief  Return direction at this trajectory point
     *
     *  @return the direction at this trajectory point
     */
    const pandora::CartesianVector &GetDirection() const;

    /**
     *  @brief  Return calo hit at this trajectory point
     *
     *  @param  the address of the calo hit at this trajectory point
     */
    const pandora::CaloHit *GetCaloHit() const;

private:
    const pandora::CaloHit  *m_pCaloHit;
};

typedef std::vector<CubeTrackState> CubeTrackStateVector;

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  CubeTrackTrajectoryPoint class
 */
class CubeTrackTrajectoryPoint : public std::pair<float, CubeTrackState>
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  projectedDistance the projected distance
     *  @param  larTrackState the lar track state
     */
    CubeTrackTrajectoryPoint(const float projectedDistance, const CubeTrackState &larTrackState);

    /**
     *  @brief  Constructor
     *
     *  @param  projectedDistance the projected distance
     *  @param  larTrackState the lar track state
     *  @param  index the index associated with the trajectory point
     */
    CubeTrackTrajectoryPoint(const float projectedDistance, const CubeTrackState &larTrackState, const int index);

    /**
     *  @brief  Get the index associated with the trajectory point
     *
     *  @return the index associated with the trajectory point
     */
    int GetIndex() const;

private:
    int m_index;    ///< The index associated with the trajectory point
};

typedef std::vector<CubeTrackTrajectoryPoint> CubeTrackTrajectory;

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief  CubeShowerPCA class
 */
class CubeShowerPCA
{
public:
    /**
     *  @brief  Constructor
     *
     *  @param  centroid  centroid of shower
     *  @param  primaryAxis  primary axis of shower
     *  @param  secondaryAxis  secondary axis of shower
     *  @param  tertiaryAxis  tertiary axis of shower
     *  @param  axisLengths  ordered vector of shower lengths
     */
    CubeShowerPCA(const pandora::CartesianVector &centroid, const pandora::CartesianVector &primaryAxis, const pandora::CartesianVector &secondaryAxis,
        const pandora::CartesianVector &tertiaryAxis, const pandora::CartesianVector &eigenvalues);

    /**
     *  @brief  Return centroid
     *
     *  @return the centroid
     */
    const pandora::CartesianVector &GetCentroid() const;

    /**
     *  @brief  Return primary axis
     *
     *  @return the primary axis
     */
    const pandora::CartesianVector &GetPrimaryAxis() const;

    /**
     *  @brief  Return secondary axis
     *
     *  @return the secondary axis
     */
    const pandora::CartesianVector &GetSecondaryAxis() const;

    /**
     *  @brief  Return tertiary axis
     *
     *  @return the tertiary axis
     */
    const pandora::CartesianVector &GetTertiaryAxis() const;

    /**
     *  @brief  Return vector of eigenvalues
     *
     *  @return the vector of eigenvalues
     */
    const pandora::CartesianVector &GetEigenValues() const;

    /**
     *  @brief  Return vector of lengths
     *
     *  @return the vector of lengths
     */
    const pandora::CartesianVector &GetAxisLengths() const;

    /**
     *  @brief  Return primary length
     *
     *  @return the primary length
     */
    float GetPrimaryLength() const;

    /**
     *  @brief  Return secondary length
     *
     *  @return the secondary length
     */
    float GetSecondaryLength() const;

    /**
     *  @brief  Return tertiary length
     *
     *  @return the tertiary length
     */
    float GetTertiaryLength() const;

private:
    const pandora::CartesianVector  m_centroid;         ///< The centroid
    const pandora::CartesianVector  m_primaryAxis;      ///< The primary axis
    const pandora::CartesianVector  m_secondaryAxis;    ///< The secondary axis
    const pandora::CartesianVector  m_tertiaryAxis;     ///< The tertiary axis
    const pandora::CartesianVector  m_eigenValues;      ///< The vector of eigenvalues
    const pandora::CartesianVector  m_axisLengths;      ///< The vector of lengths
};

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

inline CubeTrackTrajectoryPoint::CubeTrackTrajectoryPoint(const float projectedDistance, const CubeTrackState &larTrackState) :
    std::pair<float, CubeTrackState>(projectedDistance, larTrackState),
    m_index(-1)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline CubeTrackTrajectoryPoint::CubeTrackTrajectoryPoint(const float projectedDistance, const CubeTrackState &larTrackState, const int index) :
    std::pair<float, CubeTrackState>(projectedDistance, larTrackState),
    m_index(index)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline int CubeTrackTrajectoryPoint::GetIndex() const
{
    return m_index;
}

} // namespace example_content

#endif // #ifndef EXAMPLE_PFO_OBJECTS_H
