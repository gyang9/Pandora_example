/**
 *  @file   ExampleAlgorithms/CubePfoObjects.cc
 *
 *  @brief  Implementation of lar pfo objects.
 *
 *  $Log: $
 */

#include "ExampleAlgorithms/CubePfoObjects.h"

#include "Objects/CaloHit.h"

using namespace pandora;

namespace example_content
{

CubeTrackState::CubeTrackState(const CartesianVector &position, const CartesianVector &direction, const CaloHit *const pCaloHit) :
    TrackState(position, direction),
    m_pCaloHit(pCaloHit)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

CubeTrackState::CubeTrackState(const CartesianVector &position, const CartesianVector &direction) :
    TrackState(position, direction),
    m_pCaloHit(nullptr)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeTrackState::GetDirection() const
{
    return this->GetMomentum();
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CaloHit *CubeTrackState::GetCaloHit() const
{
    if (m_pCaloHit)
        return m_pCaloHit;

    throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

CubeShowerPCA::CubeShowerPCA(const CartesianVector &centroid, const CartesianVector &primaryAxis, const CartesianVector &secondaryAxis,
        const CartesianVector &tertiaryAxis, const CartesianVector &eigenValues) :
    m_centroid(centroid),
    m_primaryAxis(primaryAxis),
    m_secondaryAxis(secondaryAxis),
    m_tertiaryAxis(tertiaryAxis),
    m_eigenValues(eigenValues),
    m_axisLengths(((eigenValues.GetX() > std::numeric_limits<float>::epsilon()) ? 6.f * std::sqrt(eigenValues.GetX()) : 0.f),
                  ((eigenValues.GetY() > std::numeric_limits<float>::epsilon()) ? 6.f * std::sqrt(eigenValues.GetY()) : 0.f),
                  ((eigenValues.GetZ() > std::numeric_limits<float>::epsilon()) ? 6.f * std::sqrt(eigenValues.GetZ()) : 0.f))
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeShowerPCA::GetCentroid() const
{
    return m_centroid;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeShowerPCA::GetPrimaryAxis() const
{
    return m_primaryAxis;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeShowerPCA::GetSecondaryAxis() const
{
    return m_secondaryAxis;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeShowerPCA::GetTertiaryAxis() const
{
    return m_tertiaryAxis;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeShowerPCA::GetEigenValues() const
{
    return m_eigenValues;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const CartesianVector &CubeShowerPCA::GetAxisLengths() const
{
    return m_axisLengths;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeShowerPCA::GetPrimaryLength() const
{
    return m_axisLengths.GetX();
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeShowerPCA::GetSecondaryLength() const
{
    return m_axisLengths.GetY();
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeShowerPCA::GetTertiaryLength() const
{
    return m_axisLengths.GetZ();
}

} // namespace example_content
