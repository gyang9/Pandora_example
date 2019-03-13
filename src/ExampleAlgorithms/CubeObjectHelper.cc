/**
 *  @file   ExampleAlgorithms/CubeObjectHelper.cc
 *
 *  @brief  Implementation of the object helper class.
 *
 *  $Log: $
 */

#include "ExampleAlgorithms/CubeObjectHelper.h"

using namespace pandora;

namespace example_content
{

template <>
CartesianVector CubeObjectHelper::TypeAdaptor::GetPosition(const CartesianVector &t)
{
    return t;
}

template <>
CartesianVector CubeObjectHelper::TypeAdaptor::GetPosition(const CaloHit *const &pT)
{
    return pT->GetPositionVector();
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <>
const CaloHit *CubeObjectHelper::TypeAdaptor::GetCaloHit(const CartesianVector &)
{
    return nullptr;
}

template <>
const CaloHit *CubeObjectHelper::TypeAdaptor::GetCaloHit(const CaloHit *const &pCaloHit3D)
{
    const CaloHit *const pCaloHit2D = static_cast<const CaloHit*>(pCaloHit3D->GetParentAddress());
    return pCaloHit2D;
}

} // namespace example_content
