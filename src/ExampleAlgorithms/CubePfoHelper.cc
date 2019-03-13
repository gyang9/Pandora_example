/**
 *  @file   ExampleAlgorithms/CubePfoHelper.cc
 *
 *  @brief  Implementation of the pfo helper class.
 *
 *  $Log: $
 */

#include "Pandora/PdgTable.h"

#include "ExampleAlgorithms/CubePfoHelper.h"
#include "ExampleAlgorithms/CubePcaHelper.h"
#include "ExampleAlgorithms/CubeClusterHelper.h"
#include "ExampleAlgorithms/CubeObjectHelper.h"

#include "ExampleAlgorithms/CubeThreeDSlidingFitResult.h"

#include <algorithm>
#include <cmath>
#include <limits>

using namespace pandora;

namespace example_content
{

void CubePfoHelper::GetCoordinateVector(const ParticleFlowObject *const pPfo, const HitType &hitType, CartesianPointVector &coordinateVector)
{
    ClusterList clusterList;
    CubePfoHelper::GetClusters(pPfo, hitType, clusterList);

    for (const Cluster *const pCluster : clusterList)
        CubeClusterHelper::GetCoordinateVector(pCluster, coordinateVector);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetCaloHits(const PfoList &pfoList, const HitType &hitType, CaloHitList &caloHitList)
{
    for (const ParticleFlowObject *const pPfo : pfoList)
        CubePfoHelper::GetCaloHits(pPfo, hitType, caloHitList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetCaloHits(const ParticleFlowObject *const pPfo, const HitType &hitType, CaloHitList &caloHitList)
{
    ClusterList clusterList;
    CubePfoHelper::GetClusters(pPfo, hitType, clusterList);

    for (const Cluster *const pCluster : clusterList)
        pCluster->GetOrderedCaloHitList().FillCaloHitList(caloHitList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetIsolatedCaloHits(const PfoList &pfoList, const HitType &hitType, CaloHitList &caloHitList)
{
    for (const ParticleFlowObject *const pPfo : pfoList)
        CubePfoHelper::GetIsolatedCaloHits(pPfo, hitType, caloHitList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetIsolatedCaloHits(const ParticleFlowObject *const pPfo, const HitType &hitType, CaloHitList &caloHitList)
{
    ClusterList clusterList;
    CubePfoHelper::GetClusters(pPfo, hitType, clusterList);

    for (const Cluster *const pCluster : clusterList)
        caloHitList.insert(caloHitList.end(), pCluster->GetIsolatedCaloHitList().begin(), pCluster->GetIsolatedCaloHitList().end());
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetClusters(const PfoList &pfoList, const HitType &hitType, ClusterList &clusterList)
{
    for (const ParticleFlowObject *const pPfo : pfoList)
        CubePfoHelper::GetClusters(pPfo, hitType, clusterList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetClusters(const ParticleFlowObject *const pPfo, const HitType &hitType, ClusterList &clusterList)
{
    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (hitType != CubeClusterHelper::GetClusterHitType(pCluster))
            continue;

        clusterList.push_back(pCluster);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetTwoDClusterList(const ParticleFlowObject *const pPfo, ClusterList &clusterList)
{
    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (TPC_3D == CubeClusterHelper::GetClusterHitType(pCluster))
            continue;

        clusterList.push_back(pCluster);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetThreeDClusterList(const ParticleFlowObject *const pPfo, ClusterList &clusterList)
{
    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (TPC_3D != CubeClusterHelper::GetClusterHitType(pCluster))
            continue;

        clusterList.push_back(pCluster);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetAllConnectedPfos(const PfoList &inputPfoList, PfoList &outputPfoList)
{
    for (const ParticleFlowObject *const pPfo : inputPfoList)
        CubePfoHelper::GetAllConnectedPfos(pPfo, outputPfoList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetAllConnectedPfos(const ParticleFlowObject *const pPfo, PfoList &outputPfoList)
{
    if (outputPfoList.end() != std::find(outputPfoList.begin(), outputPfoList.end(), pPfo))
        return;

    outputPfoList.push_back(pPfo);
    CubePfoHelper::GetAllConnectedPfos(pPfo->GetParentPfoList(), outputPfoList);
    CubePfoHelper::GetAllConnectedPfos(pPfo->GetDaughterPfoList(), outputPfoList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetAllDownstreamPfos(const PfoList &inputPfoList, PfoList &outputPfoList)
{
    for (const ParticleFlowObject *const pPfo : inputPfoList)
        CubePfoHelper::GetAllDownstreamPfos(pPfo, outputPfoList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetAllDownstreamPfos(const ParticleFlowObject *const pPfo, PfoList &outputPfoList)
{
    if (outputPfoList.end() != std::find(outputPfoList.begin(), outputPfoList.end(), pPfo))
        return;

    outputPfoList.push_back(pPfo);
    CubePfoHelper::GetAllDownstreamPfos(pPfo->GetDaughterPfoList(), outputPfoList);
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubePfoHelper::GetTwoDLengthSquared(const ParticleFlowObject *const pPfo)
{
    if (!CubePfoHelper::IsTwoD(pPfo))
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

    float lengthSquared(0.f);

    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (TPC_3D == CubeClusterHelper::GetClusterHitType(pCluster))
            continue;

        lengthSquared += CubeClusterHelper::GetLengthSquared(pCluster);
    }

    return lengthSquared;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubePfoHelper::GetThreeDLengthSquared(const ParticleFlowObject *const pPfo)
{
    if (!CubePfoHelper::IsThreeD(pPfo))
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

    float lengthSquared(0.f);

    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (TPC_3D != CubeClusterHelper::GetClusterHitType(pCluster))
            continue;

        lengthSquared += CubeClusterHelper::GetLengthSquared(pCluster);
    }

    return lengthSquared;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubePfoHelper::GetClosestDistance(const ParticleFlowObject *const pPfo, const Cluster *const pCluster)
{
    const HitType hitType(CubeClusterHelper::GetClusterHitType(pCluster));

    ClusterList clusterList;
    CubePfoHelper::GetClusters(pPfo, hitType, clusterList);

    if (clusterList.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    float bestDistance(std::numeric_limits<float>::max());

    for (const Cluster *const pPfoCluster : clusterList)
    {
        const float thisDistance(CubeClusterHelper::GetClosestDistance(pCluster, pPfoCluster));

        if (thisDistance < bestDistance)
            bestDistance = thisDistance;
    }

    return bestDistance;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubePfoHelper::GetTwoDSeparation(const ParticleFlowObject *const pPfo1, const ParticleFlowObject *const pPfo2)
{
    ClusterList clusterListU1, clusterListV1, clusterListW1;
    ClusterList clusterListU2, clusterListV2, clusterListW2;

    CubePfoHelper::GetClusters(pPfo1, TPC_VIEW_U, clusterListU1);
    CubePfoHelper::GetClusters(pPfo1, TPC_VIEW_V, clusterListV1);
    CubePfoHelper::GetClusters(pPfo1, TPC_VIEW_W, clusterListW1);

    CubePfoHelper::GetClusters(pPfo2, TPC_VIEW_U, clusterListU2);
    CubePfoHelper::GetClusters(pPfo2, TPC_VIEW_V, clusterListV2);
    CubePfoHelper::GetClusters(pPfo2, TPC_VIEW_W, clusterListW2);

    float numViews(0.f);
    float distanceSquared(0.f);

    if (!clusterListU1.empty() && !clusterListU2.empty())
    {
        distanceSquared += CubeClusterHelper::GetClosestDistance(clusterListU1, clusterListU2);
        numViews += 1.f;
    }

    if (!clusterListV1.empty() && !clusterListV2.empty())
    {
        distanceSquared += CubeClusterHelper::GetClosestDistance(clusterListV1, clusterListV2);
        numViews += 1.f;
    }

    if (!clusterListW1.empty() && !clusterListW2.empty())
    {
        distanceSquared += CubeClusterHelper::GetClosestDistance(clusterListW1, clusterListW2);
        numViews += 1.f;
    }

    if (numViews < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    return std::sqrt(distanceSquared / numViews);
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubePfoHelper::GetThreeDSeparation(const ParticleFlowObject *const pPfo1, const ParticleFlowObject *const pPfo2)
{
    ClusterList clusterList1, clusterList2;

    CubePfoHelper::GetClusters(pPfo1, TPC_3D, clusterList1);
    CubePfoHelper::GetClusters(pPfo2, TPC_3D, clusterList2);

    if (clusterList1.empty() || clusterList2.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    return CubeClusterHelper::GetClosestDistance(clusterList1, clusterList2);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsTwoD(const ParticleFlowObject *const pPfo)
{
    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (TPC_3D != CubeClusterHelper::GetClusterHitType(pCluster))
            return true;
    }

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsThreeD(const ParticleFlowObject *const pPfo)
{
    for (const Cluster *const pCluster : pPfo->GetClusterList())
    {
        if (TPC_3D == CubeClusterHelper::GetClusterHitType(pCluster))
            return true;
    }

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsTrack(const ParticleFlowObject *const pPfo)
{
    const int pdg(pPfo->GetParticleId());

    // muon, pion, proton, kaon
    return ((MU_MINUS == std::abs(pdg)) || (PI_PLUS == std::abs(pdg)) || (PROTON == std::abs(pdg)) || (K_PLUS == std::abs(pdg)));
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsShower(const ParticleFlowObject *const pPfo)
{
    const int pdg(pPfo->GetParticleId());

    // electron, photon
    return ((E_MINUS == std::abs(pdg)) || (PHOTON == std::abs(pdg)));
}

//------------------------------------------------------------------------------------------------------------------------------------------

int CubePfoHelper::GetPrimaryNeutrino(const ParticleFlowObject *const pPfo)
{
    try
    {
        const ParticleFlowObject *const pParentPfo = CubePfoHelper::GetParentNeutrino(pPfo);
        return pParentPfo->GetParticleId();
    }
    catch (const StatusCodeException &)
    {
        return 0;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsFinalState(const ParticleFlowObject *const pPfo)
{
    if (pPfo->GetParentPfoList().empty() && !CubePfoHelper::IsNeutrino(pPfo))
        return true;

    if (CubePfoHelper::IsNeutrinoFinalState(pPfo))
        return true;

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsNeutrinoFinalState(const ParticleFlowObject *const pPfo)
{
    return ((pPfo->GetParentPfoList().size() == 1) && (CubePfoHelper::IsNeutrino(*(pPfo->GetParentPfoList().begin()))));
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsNeutrino(const ParticleFlowObject *const pPfo)
{
    const int absoluteParticleId(std::abs(pPfo->GetParticleId()));

    if ((NU_E == absoluteParticleId) || (NU_MU == absoluteParticleId) || (NU_TAU == absoluteParticleId))
        return true;

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::IsTestBeam(const ParticleFlowObject *const pPfo)
{
    const PropertiesMap &properties(pPfo->GetPropertiesMap());
    const PropertiesMap::const_iterator iter(properties.find("IsTestBeam"));

    if (iter != properties.end())
        return ((iter->second > 0.f) ? true : false);

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetRecoNeutrinos(const PfoList *const pPfoList, PfoList &recoNeutrinos)
{
    if (!pPfoList)
        return;

    for (const ParticleFlowObject *const pPfo : *pPfoList)
    {
        if (CubePfoHelper::IsNeutrino(pPfo))
            recoNeutrinos.push_back(pPfo);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

const ParticleFlowObject *CubePfoHelper::GetParentPfo(const ParticleFlowObject *const pPfo)
{
    const ParticleFlowObject *pParentPfo = pPfo;

    while (pParentPfo->GetParentPfoList().empty() == false)
    {
        pParentPfo = *(pParentPfo->GetParentPfoList().begin());
    }

    return pParentPfo;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const ParticleFlowObject *CubePfoHelper::GetParentNeutrino(const ParticleFlowObject *const pPfo)
{
    const ParticleFlowObject *const pParentPfo = CubePfoHelper::GetParentPfo(pPfo);

    if(!CubePfoHelper::IsNeutrino(pParentPfo))
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    return pParentPfo;
}

//------------------------------------------------------------------------------------------------------------------------------------------

const Vertex *CubePfoHelper::GetVertex(const ParticleFlowObject *const pPfo)
{
    if (pPfo->GetVertexList().empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    if (pPfo->GetVertexList().size() != 1)
        throw StatusCodeException(STATUS_CODE_FAILURE);

    const Vertex *const pVertex = *(pPfo->GetVertexList().begin());

    if (VERTEX_3D != pVertex->GetVertexType())
        throw StatusCodeException(STATUS_CODE_FAILURE);

    return pVertex;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetSlidingFitTrajectory(const CartesianPointVector &pointVector, const CartesianVector &vertexPosition,
    const unsigned int layerWindow, const float layerPitch, CubeTrackStateVector &trackStateVector, IntVector *const pIndexVector)
{
    CubePfoHelper::SlidingFitTrajectoryImpl(&pointVector, vertexPosition, layerWindow, layerPitch, trackStateVector, pIndexVector);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubePfoHelper::GetSlidingFitTrajectory(const ParticleFlowObject *const pPfo, const Vertex *const pVertex,
    const unsigned int layerWindow, const float layerPitch, CubeTrackStateVector &trackStateVector)
{
    CaloHitList caloHitList;
    CubePfoHelper::GetCaloHits(pPfo, TPC_3D, caloHitList);
    CubePfoHelper::SlidingFitTrajectoryImpl(&caloHitList, pVertex->GetPosition(), layerWindow, layerPitch, trackStateVector);
}

//------------------------------------------------------------------------------------------------------------------------------------------

CubeShowerPCA CubePfoHelper::GetPrincipalComponents(const CartesianPointVector &pointVector, const CartesianVector &vertexPosition)
{
    // Run the PCA analysis
    CartesianVector centroid(0.f, 0.f, 0.f);
    CubePcaHelper::EigenVectors eigenVecs;
    CubePcaHelper::EigenValues eigenValues(0.f, 0.f, 0.f);
    CubePcaHelper::RunPca(pointVector, centroid, eigenValues, eigenVecs);

    // Require that principal eigenvalue should always be positive
    if (eigenValues.GetX() < std::numeric_limits<float>::epsilon())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    // By convention, principal axis should always point away from vertex
    const float testProjection(eigenVecs.at(0).GetDotProduct(vertexPosition - centroid));
    const float directionScaleFactor((testProjection > std::numeric_limits<float>::epsilon()) ? -1.f : 1.f);

    const CartesianVector primaryAxis(eigenVecs.at(0) * directionScaleFactor);
    const CartesianVector secondaryAxis(eigenVecs.at(1) * directionScaleFactor);
    const CartesianVector tertiaryAxis(eigenVecs.at(2) * directionScaleFactor);

    return CubeShowerPCA(centroid, primaryAxis, secondaryAxis, tertiaryAxis, eigenValues);
}

//------------------------------------------------------------------------------------------------------------------------------------------

CubeShowerPCA CubePfoHelper::GetPrincipalComponents(const ParticleFlowObject *const pPfo, const Vertex *const pVertex)
{
    CartesianPointVector pointVector;
    CubePfoHelper::GetCoordinateVector(pPfo, TPC_3D, pointVector);
    return CubePfoHelper::GetPrincipalComponents(pointVector, pVertex->GetPosition());
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::SortByHitProjection(const CubeTrackTrajectoryPoint &lhs, const CubeTrackTrajectoryPoint &rhs)
{
    if (lhs.first != rhs.first)
        return (lhs.first < rhs.first);

    // ATTN Removed to support use with CartesianVector only (no CaloHit) input
    // if (lhs.second.GetCaloHit() && rhs.second.GetCaloHit())
    //     return (lhs.second.GetCaloHit()->GetInputEnergy() > rhs.second.GetCaloHit()->GetInputEnergy());

    const float dx(lhs.second.GetPosition().GetX() - rhs.second.GetPosition().GetX());
    const float dy(lhs.second.GetPosition().GetY() - rhs.second.GetPosition().GetY());
    const float dz(lhs.second.GetPosition().GetZ() - rhs.second.GetPosition().GetZ());
    return (dx + dy + dz > 0.f);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubePfoHelper::SortByNHits(const ParticleFlowObject *const pLhs, const ParticleFlowObject *const pRhs)
{
    unsigned int nTwoDHitsLhs(0), nThreeDHitsLhs(0); float energyLhs(0.f);
    for (ClusterList::const_iterator iter = pLhs->GetClusterList().begin(), iterEnd = pLhs->GetClusterList().end(); iter != iterEnd; ++iter)
    {
        const Cluster *const pClusterLhs = *iter;

        if (TPC_3D != CubeClusterHelper::GetClusterHitType(pClusterLhs))
            nTwoDHitsLhs += pClusterLhs->GetNCaloHits();
        else
            nThreeDHitsLhs += pClusterLhs->GetNCaloHits();

        energyLhs += pClusterLhs->GetHadronicEnergy();
    }

    unsigned int nTwoDHitsRhs(0), nThreeDHitsRhs(0); float energyRhs(0.f);
    for (ClusterList::const_iterator iter = pRhs->GetClusterList().begin(), iterEnd = pRhs->GetClusterList().end(); iter != iterEnd; ++iter)
    {
        const Cluster *const pClusterRhs = *iter;

        if (TPC_3D != CubeClusterHelper::GetClusterHitType(pClusterRhs))
            nTwoDHitsRhs += pClusterRhs->GetNCaloHits();
        else
            nThreeDHitsRhs += pClusterRhs->GetNCaloHits();

        energyRhs += pClusterRhs->GetHadronicEnergy();
    }

    if (nTwoDHitsLhs != nTwoDHitsRhs)
        return (nTwoDHitsLhs > nTwoDHitsRhs);

    if (nThreeDHitsLhs != nThreeDHitsRhs)
        return (nThreeDHitsLhs > nThreeDHitsRhs);

    // ATTN Need an efficient (balance with well-motivated) tie-breaker here. Pfo length, for instance, is extremely slow.
    return (energyLhs > energyRhs);
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void CubePfoHelper::SlidingFitTrajectoryImpl(const T *const pT, const CartesianVector &vertexPosition, const unsigned int layerWindow,
    const float layerPitch, CubeTrackStateVector &trackStateVector, IntVector *const pIndexVector)
{
    CartesianPointVector pointVector;

    for (const auto &nextPoint : *pT)
        pointVector.push_back(CubeObjectHelper::TypeAdaptor::GetPosition(nextPoint));

    if (pointVector.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    std::sort(pointVector.begin(), pointVector.end(), CubeClusterHelper::SortCoordinatesByPosition);

    CubeTrackTrajectory trackTrajectory;
    IntVector indicesWithoutSpacePoints;
    if (pIndexVector) pIndexVector->clear();

    try
    {
        const ThreeDSlidingFitResult slidingFitResult(&pointVector, layerWindow, layerPitch);
        const CartesianVector minPosition(slidingFitResult.GetGlobalMinLayerPosition());
        const CartesianVector maxPosition(slidingFitResult.GetGlobalMaxLayerPosition());

        if ((maxPosition - minPosition).GetMagnitudeSquared() < std::numeric_limits<float>::epsilon())
            throw StatusCodeException(STATUS_CODE_NOT_FOUND);

        const CartesianVector seedPosition((maxPosition + minPosition) * 0.5f);
        const CartesianVector seedDirection((maxPosition - minPosition).GetUnitVector());

        const float scaleFactor((seedDirection.GetDotProduct(seedPosition - vertexPosition) > 0.f) ? +1.f : -1.f);

        int index(-1);
        for (const auto &nextPoint : *pT)
        {
            ++index;

            try
            {
                const float rL(slidingFitResult.GetLongitudinalDisplacement(CubeObjectHelper::TypeAdaptor::GetPosition(nextPoint)));

                CartesianVector position(0.f, 0.f, 0.f);
                const StatusCode positionStatusCode(slidingFitResult.GetGlobalFitPosition(rL, position));

                if (positionStatusCode != STATUS_CODE_SUCCESS)
                    throw StatusCodeException(positionStatusCode);

                CartesianVector direction(0.f, 0.f, 0.f);
                const StatusCode directionStatusCode(slidingFitResult.GetGlobalFitDirection(rL, direction));

                if (directionStatusCode != STATUS_CODE_SUCCESS)
                    throw StatusCodeException(directionStatusCode);

                const float projection(seedDirection.GetDotProduct(position - seedPosition));

                trackTrajectory.push_back(CubeTrackTrajectoryPoint(projection * scaleFactor,
                    CubeTrackState(position, direction * scaleFactor, CubeObjectHelper::TypeAdaptor::GetCaloHit(nextPoint)), index));
            }
            catch (const StatusCodeException &statusCodeException1)
            {
                indicesWithoutSpacePoints.push_back(index);

                if (STATUS_CODE_FAILURE == statusCodeException1.GetStatusCode())
                    throw statusCodeException1;
            }
        }
    }
    catch (const StatusCodeException &statusCodeException2)
    {
        if (STATUS_CODE_FAILURE == statusCodeException2.GetStatusCode())
            throw statusCodeException2;
    }

    // Sort trajectory points by distance along track
    std::sort(trackTrajectory.begin(), trackTrajectory.end(), CubePfoHelper::SortByHitProjection);

    for (const CubeTrackTrajectoryPoint &larTrackTrajectoryPoint : trackTrajectory)
    {
        trackStateVector.push_back(larTrackTrajectoryPoint.second);
        if (pIndexVector) pIndexVector->push_back(larTrackTrajectoryPoint.GetIndex());
    }

    // Store indices of spacepoints with no associated trajectory point at the end of pIndexVector
    if (pIndexVector)
    {
        for (const int index : indicesWithoutSpacePoints)
            pIndexVector->push_back(index);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

template void CubePfoHelper::SlidingFitTrajectoryImpl(const CartesianPointVector *const, const CartesianVector &, const unsigned int, const float, CubeTrackStateVector &, IntVector *const);
template void CubePfoHelper::SlidingFitTrajectoryImpl(const CaloHitList *const, const CartesianVector &, const unsigned int, const float, CubeTrackStateVector &, IntVector *const);

} // namespace example_content
