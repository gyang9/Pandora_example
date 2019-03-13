/**
 *  @file   ExampleAlgorithms/CubeClusterHelper.cc
 *
 *  @brief  Implementation of the cluster helper class.
 *
 *  $Log: $
 */

#include "ExampleAlgorithms/CubeClusterHelper.h"

#include <algorithm>
#include <cmath>
#include <limits>

using namespace pandora;

namespace example_content
{

HitType CubeClusterHelper::GetClusterHitType(const Cluster *const pCluster)
{
    if (0 == pCluster->GetNCaloHits())
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    // TODO Find a way of confirming single hit-type clustering mode; currently only checked in ListPreparation algorithm
    // if (!pandora->GetSettings()->SingleHitTypeClusteringMode())
    //     throw StatusCodeException(STATUS_CODE_FAILURE);

    return (*(pCluster->GetOrderedCaloHitList().begin()->second->begin()))->GetHitType();
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClustersUVW(const ClusterList &inputClusters, ClusterList &clusterListU, ClusterList &clusterListV, ClusterList &clusterListW)
{
    for (ClusterList::const_iterator iter = inputClusters.begin(), iterEnd = inputClusters.end(); iter != iterEnd; ++iter)
    {
        const HitType hitType(CubeClusterHelper::GetClusterHitType(*iter));

        if (TPC_VIEW_U == hitType) clusterListU.push_back(*iter);
        else if (TPC_VIEW_V == hitType) clusterListV.push_back(*iter);
        else if (TPC_VIEW_W == hitType) clusterListW.push_back(*iter);
        else throw StatusCodeException(STATUS_CODE_NOT_FOUND);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClustersByHitType(const ClusterList &inputClusters, const HitType hitType, ClusterList &clusterList)
{
    for (ClusterList::const_iterator iter = inputClusters.begin(), iterEnd = inputClusters.end(); iter != iterEnd; ++iter)
    {
        if (hitType == CubeClusterHelper::GetClusterHitType(*iter))
            clusterList.push_back(*iter);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetLengthSquared(const Cluster *const pCluster)
{
    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());

    if (orderedCaloHitList.empty())
        throw StatusCodeException(STATUS_CODE_NOT_INITIALIZED);

    // ATTN In 2D case, we will actually calculate the quadrature sum of deltaX and deltaU/V/W
    float minX(std::numeric_limits<float>::max()), maxX(-std::numeric_limits<float>::max());
    float minY(std::numeric_limits<float>::max()), maxY(-std::numeric_limits<float>::max());
    float minZ(std::numeric_limits<float>::max()), maxZ(-std::numeric_limits<float>::max());

    for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
    {
        for (CaloHitList::const_iterator hitIter = iter->second->begin(), hitIterEnd = iter->second->end(); hitIter != hitIterEnd; ++hitIter)
        {
            const CartesianVector &hitPosition((*hitIter)->GetPositionVector());
            minX = std::min(hitPosition.GetX(), minX);
            maxX = std::max(hitPosition.GetX(), maxX);
            minY = std::min(hitPosition.GetY(), minY);
            maxY = std::max(hitPosition.GetY(), maxY);
            minZ = std::min(hitPosition.GetZ(), minZ);
            maxZ = std::max(hitPosition.GetZ(), maxZ);
        }
    }

    const float deltaX(maxX - minX), deltaY(maxY - minY), deltaZ(maxZ - minZ);
    return (deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetLength(const Cluster *const pCluster)
{
    return std::sqrt(CubeClusterHelper::GetLengthSquared(pCluster));
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetEnergyFromLength(const Cluster *const pCluster)
{
    const float dEdX(0.002f); // approximately 2 MeV/cm
    return (dEdX * CubeClusterHelper::GetLength(pCluster));
}

//------------------------------------------------------------------------------------------------------------------------------------------

unsigned int CubeClusterHelper::GetLayerSpan(const Cluster *const pCluster)
{
    return (1 + pCluster->GetOuterPseudoLayer() - pCluster->GetInnerPseudoLayer());
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetLayerOccupancy(const Cluster *const pCluster)
{
    const unsigned int nOccupiedLayers(pCluster->GetOrderedCaloHitList().size());
    const unsigned int nLayers(1 + pCluster->GetOuterPseudoLayer() - pCluster->GetInnerPseudoLayer());

    if (nLayers > 0)
        return (static_cast<float>(nOccupiedLayers) / static_cast<float>(nLayers));

    return 0.f;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetLayerOccupancy(const Cluster *const pCluster1, const Cluster *const pCluster2)
{
    const unsigned int nOccupiedLayers(pCluster1->GetOrderedCaloHitList().size() + pCluster2->GetOrderedCaloHitList().size());
    const unsigned int nLayers(1 + std::max(pCluster1->GetOuterPseudoLayer(), pCluster2->GetOuterPseudoLayer()) -
        std::min(pCluster1->GetInnerPseudoLayer(), pCluster2->GetInnerPseudoLayer()));

    if (nLayers > 0)
        return (static_cast<float>(nOccupiedLayers) / static_cast<float>(nLayers));

    return 0.f;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetClosestDistance(const ClusterList &clusterList1, const ClusterList &clusterList2)
{
    if (clusterList1.empty() || clusterList2.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    float closestDistance(std::numeric_limits<float>::max());

    for (ClusterList::const_iterator iter1 = clusterList1.begin(), iterEnd1 = clusterList1.end(); iter1 != iterEnd1; ++iter1)
    {
        const Cluster *const pCluster1 = *iter1;
        const float thisDistance(CubeClusterHelper::GetClosestDistance(pCluster1, clusterList2));
 
        if (thisDistance < closestDistance)
            closestDistance = thisDistance; 
    }

    return closestDistance;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetClosestDistance(const Cluster *const pCluster, const ClusterList &clusterList)
{
    if (clusterList.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    float closestDistance(std::numeric_limits<float>::max());

    for (ClusterList::const_iterator iter = clusterList.begin(), iterEnd = clusterList.end(); iter != iterEnd; ++iter)
    {
        const Cluster *const pTestCluster = *iter;
        const float thisDistance(CubeClusterHelper::GetClosestDistance(pCluster, pTestCluster));

        if (thisDistance < closestDistance)
            closestDistance = thisDistance; 
    }

    return closestDistance;
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetClosestDistance(const Cluster *const pCluster1, const Cluster *const pCluster2)
{
    CartesianVector closestPosition1(0.f, 0.f, 0.f);
    CartesianVector closestPosition2(0.f, 0.f, 0.f);

    CubeClusterHelper::GetClosestPositions(pCluster1, pCluster2, closestPosition1, closestPosition2);

    return (closestPosition1 - closestPosition2).GetMagnitude();
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetClosestDistance(const CartesianVector &position, const ClusterList &clusterList)
{
    return (position - CubeClusterHelper::GetClosestPosition(position, clusterList)).GetMagnitude();
}

//------------------------------------------------------------------------------------------------------------------------------------------

float CubeClusterHelper::GetClosestDistance(const CartesianVector &position, const Cluster *const pCluster)
{
    return (position - CubeClusterHelper::GetClosestPosition(position, pCluster)).GetMagnitude();
}

//------------------------------------------------------------------------------------------------------------------------------------------

CartesianVector CubeClusterHelper::GetClosestPosition(const CartesianVector &position, const ClusterList &clusterList)
{
    bool distanceFound(false);
    float closestDistanceSquared(std::numeric_limits<float>::max());
    CartesianVector closestPosition(0.f, 0.f, 0.f);    

    for (ClusterList::const_iterator iter = clusterList.begin(), iterEnd = clusterList.end(); iter != iterEnd; ++iter)
    {
        const Cluster *const pTestCluster = *iter;
        const CartesianVector thisPosition(CubeClusterHelper::GetClosestPosition(position, pTestCluster));
        const float thisDistanceSquared((position - thisPosition).GetMagnitudeSquared());

        if (thisDistanceSquared < closestDistanceSquared)
        {
            distanceFound = true;
            closestDistanceSquared = thisDistanceSquared;
            closestPosition = thisPosition;
        }
    }

    if (distanceFound)
        return closestPosition;

    throw StatusCodeException(STATUS_CODE_NOT_FOUND);
}

//------------------------------------------------------------------------------------------------------------------------------------------

CartesianVector CubeClusterHelper::GetClosestPosition(const CartesianVector &position, const Cluster *const pCluster)
{
    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());

    const CaloHit *pClosestCaloHit(NULL);
    float closestDistanceSquared(std::numeric_limits<float>::max());

    for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
    {
        for (CaloHitList::const_iterator hitIter = iter->second->begin(), hitIterEnd = iter->second->end(); hitIter != hitIterEnd; ++hitIter)
        {
            const CaloHit *const pCaloHit = *hitIter;
            const float distanceSquared((pCaloHit->GetPositionVector() - position).GetMagnitudeSquared());

            if (distanceSquared < closestDistanceSquared)
            {
                closestDistanceSquared = distanceSquared;
                pClosestCaloHit = pCaloHit;
            }
        }
    }

    if (pClosestCaloHit)
        return pClosestCaloHit->GetPositionVector();

    throw StatusCodeException(STATUS_CODE_NOT_FOUND);
}
 
//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClosestPositions(const Cluster *const pCluster1, const Cluster *const pCluster2, CartesianVector &outputPosition1, 
    CartesianVector &outputPosition2)
{
    bool distanceFound(false);
    float minDistanceSquared(std::numeric_limits<float>::max());

    CartesianVector closestPosition1(0.f, 0.f, 0.f);
    CartesianVector closestPosition2(0.f, 0.f, 0.f);

    const OrderedCaloHitList &orderedCaloHitList1(pCluster1->GetOrderedCaloHitList());
    const OrderedCaloHitList &orderedCaloHitList2(pCluster2->GetOrderedCaloHitList());

    // Loop over hits in cluster 1
    for (OrderedCaloHitList::const_iterator iter1 = orderedCaloHitList1.begin(), iter1End = orderedCaloHitList1.end(); iter1 != iter1End; ++iter1)
    {
        for (CaloHitList::const_iterator hitIter1 = iter1->second->begin(), hitIter1End = iter1->second->end(); hitIter1 != hitIter1End; ++hitIter1)
        {
            const CartesianVector &positionVector1((*hitIter1)->GetPositionVector());

            // Loop over hits in cluster 2
            for (OrderedCaloHitList::const_iterator iter2 = orderedCaloHitList2.begin(), iter2End = orderedCaloHitList2.end(); iter2 != iter2End; ++iter2)
            {
                for (CaloHitList::const_iterator hitIter2 = iter2->second->begin(), hitIter2End = iter2->second->end(); hitIter2 != hitIter2End; ++hitIter2)
                { 
                    const CartesianVector &positionVector2((*hitIter2)->GetPositionVector());

                    const float distanceSquared((positionVector1 - positionVector2).GetMagnitudeSquared());

                    if (distanceSquared < minDistanceSquared)
                    {
                        minDistanceSquared = distanceSquared;
                        closestPosition1 = positionVector1;
                        closestPosition2 = positionVector2;
                        distanceFound = true;
                    }
                }
            }
        }
    }

    if (!distanceFound)
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    outputPosition1 = closestPosition1;
    outputPosition2 = closestPosition2;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClusterBoundingBox(const Cluster *const pCluster, CartesianVector &minimumCoordinate, CartesianVector &maximumCoordinate)
{
    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());

    float xmin(std::numeric_limits<float>::max());
    float ymin(std::numeric_limits<float>::max());
    float zmin(std::numeric_limits<float>::max());
    float xmax(-std::numeric_limits<float>::max());
    float ymax(-std::numeric_limits<float>::max());
    float zmax(-std::numeric_limits<float>::max());

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());
            xmin = std::min(hit.GetX(), xmin);
            xmax = std::max(hit.GetX(), xmax);
            ymin = std::min(hit.GetY(), ymin);
            ymax = std::max(hit.GetY(), ymax);
            zmin = std::min(hit.GetZ(), zmin);
            zmax = std::max(hit.GetZ(), zmax);
        }
    }

    minimumCoordinate.SetValues(xmin, ymin, zmin);
    maximumCoordinate.SetValues(xmax, ymax, zmax);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClusterSpanX(const Cluster *const pCluster, float &xmin, float &xmax)
{
    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());
    xmin = std::numeric_limits<float>::max();
    xmax = -std::numeric_limits<float>::max();

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());
            xmin = std::min(hit.GetX(), xmin);
            xmax = std::max(hit.GetX(), xmax);
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClusterSpanY(const Cluster *const pCluster, float &xmin, float &xmax)
{
    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());
    xmin = std::numeric_limits<float>::max();
    xmax = -std::numeric_limits<float>::max();

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());
            xmin = std::min(hit.GetY(), xmin);
            xmax = std::max(hit.GetY(), xmax);
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClusterSpanZ(const Cluster *const pCluster, float &xmin, float &xmax)
{
    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());
    xmin = std::numeric_limits<float>::max();
    xmax = -std::numeric_limits<float>::max();

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());
            xmin = std::min(hit.GetZ(), xmin);
            xmax = std::max(hit.GetZ(), xmax);
        }
    }
}



//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetClusterSpanZ(const Cluster *const pCluster, const float xmin, const float xmax, 
    float &zmin, float &zmax)
{
    if (xmin > xmax)
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());

    zmin = std::numeric_limits<float>::max();
    zmax = -std::numeric_limits<float>::max();

    bool foundHits(false);
    
    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());

            if (hit.GetX() < xmin || hit.GetX() > xmax)
                continue;

            zmin = std::min(hit.GetZ(), zmin);
            zmax = std::max(hit.GetZ(), zmax);
            foundHits = true;
        }
    }

    if (!foundHits)
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode CubeClusterHelper::GetAverageZ(const Cluster *const pCluster, const float xmin, const float xmax, float &averageZ)
{
    averageZ = std::numeric_limits<float>::max();

    if (xmin > xmax)
        return STATUS_CODE_INVALID_PARAMETER;

    const OrderedCaloHitList &orderedCaloHitList(pCluster->GetOrderedCaloHitList());

    float zsum(0.f);
    int count(0);

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());

            if (hit.GetX() < xmin || hit.GetX() > xmax)
                continue;

            zsum += hit.GetZ();
            ++count;
        }
    }

    if (count == 0)
        return STATUS_CODE_NOT_FOUND;

    averageZ = zsum / static_cast<float>(count);
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetExtremalCoordinates(const ClusterList &clusterList, CartesianVector &innerCoordinate, CartesianVector &outerCoordinate)
{
    OrderedCaloHitList orderedCaloHitList;

    for (ClusterList::const_iterator cIter = clusterList.begin(), cIterEnd = clusterList.end(); cIter != cIterEnd; ++cIter)
    {
        const Cluster *const pCluster = *cIter;
        PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, orderedCaloHitList.Add(pCluster->GetOrderedCaloHitList()));
    }

    return CubeClusterHelper::GetExtremalCoordinates(orderedCaloHitList, innerCoordinate, outerCoordinate);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetExtremalCoordinates(const Cluster *const pCluster, CartesianVector &innerCoordinate, CartesianVector &outerCoordinate)
{
  return CubeClusterHelper::GetExtremalCoordinates(pCluster->GetOrderedCaloHitList(), innerCoordinate, outerCoordinate);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetExtremalCoordinates(const OrderedCaloHitList &orderedCaloHitList, CartesianVector &innerCoordinate,
    CartesianVector &outerCoordinate)
{
    if (orderedCaloHitList.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    CartesianPointVector coordinateVector;

    for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
    {
        for (CaloHitList::const_iterator hitIter = iter->second->begin(), hitIterEnd = iter->second->end(); hitIter != hitIterEnd; ++hitIter)
        {
            const CaloHit *const pCaloHit = *hitIter;
            coordinateVector.push_back(pCaloHit->GetPositionVector());
        }
    }

    std::sort(coordinateVector.begin(), coordinateVector.end(), CubeClusterHelper::SortCoordinatesByPosition);
    return CubeClusterHelper::GetExtremalCoordinates(coordinateVector, innerCoordinate, outerCoordinate);
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetExtremalCoordinates(const CartesianPointVector &coordinateVector, CartesianVector &innerCoordinate,
    CartesianVector &outerCoordinate)
{
    if (coordinateVector.empty())
        throw StatusCodeException(STATUS_CODE_NOT_FOUND);

    // Find the extremal values of the X, Y and Z coordinates
    float xMin(+std::numeric_limits<float>::max());
    float yMin(+std::numeric_limits<float>::max());
    float zMin(+std::numeric_limits<float>::max());
    float xMax(-std::numeric_limits<float>::max());
    float yMax(-std::numeric_limits<float>::max());
    float zMax(-std::numeric_limits<float>::max());

    for (CartesianPointVector::const_iterator pIter = coordinateVector.begin(), pIterEnd = coordinateVector.end(); pIter != pIterEnd; ++pIter)
    {
        const CartesianVector &pos = *pIter;
        xMin = std::min(pos.GetX(), xMin);
        xMax = std::max(pos.GetX(), xMax);
        yMin = std::min(pos.GetY(), yMin);
        yMax = std::max(pos.GetY(), yMax);
        zMin = std::min(pos.GetZ(), zMin);
        zMax = std::max(pos.GetZ(), zMax);
    }

    // Choose the coordinate with the greatest span (keeping any ties)
    const float xAve(0.5f * (xMin + xMax));
    const float yAve(0.5f * (yMin + yMax));
    const float zAve(0.5f * (zMin + zMax));

    const float xSpan(xMax - xMin);
    const float ySpan(yMax - yMin);
    const float zSpan(zMax - zMin);

    const bool useX((xSpan > std::numeric_limits<float>::epsilon()) && (xSpan + std::numeric_limits<float>::epsilon() > std::max(ySpan, zSpan)));
    const bool useY((ySpan > std::numeric_limits<float>::epsilon()) && (ySpan + std::numeric_limits<float>::epsilon() > std::max(zSpan, xSpan)));
    const bool useZ((zSpan > std::numeric_limits<float>::epsilon()) && (zSpan + std::numeric_limits<float>::epsilon() > std::max(xSpan, ySpan)));

    // Find the extremal hits separately for the chosen coordinates
    CartesianPointVector candidateVector;

    for (CartesianPointVector::const_iterator pIter = coordinateVector.begin(), pIterEnd = coordinateVector.end(); pIter != pIterEnd; ++pIter)
    {
        const CartesianVector &pos = *pIter;

        if (useX)
        {
            if (((pos.GetX() - xMin) < std::numeric_limits<float>::epsilon()) || ((pos.GetX() - xMax) > -std::numeric_limits<float>::epsilon()))
                candidateVector.push_back(pos);
        }

        if (useY)
        {
            if (((pos.GetY() - yMin) < std::numeric_limits<float>::epsilon()) || ((pos.GetY() - yMax) > -std::numeric_limits<float>::epsilon()))
                candidateVector.push_back(pos);
        }

        if (useZ)
        {
            if (((pos.GetZ() - zMin) < std::numeric_limits<float>::epsilon()) || ((pos.GetZ() - zMax) > -std::numeric_limits<float>::epsilon()))
                candidateVector.push_back(pos);
        }
    }

    // Finally, find the pair of hits that are separated by the greatest distance
    CartesianVector firstCoordinate(xAve, yAve, zAve);
    CartesianVector secondCoordinate(xAve, yAve, zAve);
    float maxDistanceSquared(+std::numeric_limits<float>::epsilon());

    for (CartesianPointVector::const_iterator iterI = candidateVector.begin(), iterEndI = candidateVector.end(); iterI != iterEndI; ++iterI)
    {
        const CartesianVector &posI = *iterI;

        for (CartesianPointVector::const_iterator iterJ = iterI, iterEndJ = candidateVector.end(); iterJ != iterEndJ; ++iterJ)
        {
            const CartesianVector &posJ = *iterJ;

            const float distanceSquared((posI - posJ).GetMagnitudeSquared());

            if (distanceSquared > maxDistanceSquared)
            {
                maxDistanceSquared = distanceSquared;
                firstCoordinate = posI;
                secondCoordinate = posJ;
            }
        }
    }

    // Set the inner and outer coordinates (Check Z first, then X in the event of a tie)
    const float deltaZ(secondCoordinate.GetZ() - firstCoordinate.GetZ());
    const float deltaX(secondCoordinate.GetX() - firstCoordinate.GetX());

    if ((deltaZ > 0.f) || ((std::fabs(deltaZ) < std::numeric_limits<float>::epsilon()) && (deltaX > 0.f)))
    {
        innerCoordinate = firstCoordinate;
        outerCoordinate = secondCoordinate;
    }
    else
    {
        innerCoordinate = secondCoordinate;
        outerCoordinate = firstCoordinate;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CubeClusterHelper::GetCoordinateVector(const Cluster *const pCluster, CartesianPointVector &coordinateVector)
{
    for (const OrderedCaloHitList::value_type &layerEntry : pCluster->GetOrderedCaloHitList())
    {
        for (const CaloHit *const pCaloHit : *layerEntry.second)
            coordinateVector.push_back(pCaloHit->GetPositionVector());
    }

    std::sort(coordinateVector.begin(), coordinateVector.end(), CubeClusterHelper::SortCoordinatesByPosition);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortByNOccupiedLayers(const Cluster *const pLhs, const Cluster *const pRhs)
{
    const unsigned int nOccupiedLayersLhs(pLhs->GetOrderedCaloHitList().size());
    const unsigned int nOccupiedLayersRhs(pRhs->GetOrderedCaloHitList().size());

    if (nOccupiedLayersLhs != nOccupiedLayersRhs)
        return (nOccupiedLayersLhs > nOccupiedLayersRhs);

    return SortByNHits(pLhs, pRhs);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortByNHits(const Cluster *const pLhs, const Cluster *const pRhs)
{
    const unsigned int nHitsLhs(pLhs->GetNCaloHits());
    const unsigned int nHitsRhs(pRhs->GetNCaloHits());

    if (nHitsLhs != nHitsRhs)
        return (nHitsLhs > nHitsRhs);

    return SortByLayerSpan(pLhs, pRhs);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortByLayerSpan(const Cluster *const pLhs, const Cluster *const pRhs)
{
    const unsigned int layerSpanLhs(pLhs->GetOuterPseudoLayer() - pLhs->GetInnerPseudoLayer());
    const unsigned int layerSpanRhs(pRhs->GetOuterPseudoLayer() - pRhs->GetInnerPseudoLayer());

    if (layerSpanLhs != layerSpanRhs)
        return (layerSpanLhs > layerSpanRhs);

    return SortByInnerLayer(pLhs, pRhs);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortByInnerLayer(const Cluster *const pLhs, const Cluster *const pRhs)
{
    const unsigned int innerLayerLhs(pLhs->GetInnerPseudoLayer());
    const unsigned int innerLayerRhs(pRhs->GetInnerPseudoLayer());

    if (innerLayerLhs != innerLayerRhs)
      return (innerLayerLhs < innerLayerRhs);

    return SortByPosition(pLhs, pRhs);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortByPosition(const Cluster *const pLhs, const Cluster *const pRhs)
{
    const CartesianVector deltaPositionIL(pRhs->GetCentroid(pRhs->GetInnerPseudoLayer()) - pLhs->GetCentroid(pLhs->GetInnerPseudoLayer()));

    if (std::fabs(deltaPositionIL.GetZ()) > std::numeric_limits<float>::epsilon())
        return (deltaPositionIL.GetZ() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPositionIL.GetX()) > std::numeric_limits<float>::epsilon())
        return (deltaPositionIL.GetX() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPositionIL.GetY()) > std::numeric_limits<float>::epsilon())
        return (deltaPositionIL.GetY() > std::numeric_limits<float>::epsilon());

    const CartesianVector deltaPositionOL(pRhs->GetCentroid(pRhs->GetOuterPseudoLayer()) - pLhs->GetCentroid(pLhs->GetOuterPseudoLayer()));

    if (std::fabs(deltaPositionOL.GetZ()) > std::numeric_limits<float>::epsilon())
        return (deltaPositionOL.GetZ() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPositionOL.GetX()) > std::numeric_limits<float>::epsilon())
        return (deltaPositionOL.GetX() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPositionOL.GetY()) > std::numeric_limits<float>::epsilon())
        return (deltaPositionOL.GetY() > std::numeric_limits<float>::epsilon());

    // Use pulse height to resolve ties
    return SortByPulseHeight(pLhs, pRhs);
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortByPulseHeight(const Cluster *const pLhs, const Cluster *const pRhs)
{
    return (pLhs->GetHadronicEnergy() > pRhs->GetHadronicEnergy());
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortHitsByPosition(const CaloHit *const pLhs, const CaloHit *const pRhs)
{
    const CartesianVector deltaPosition(pRhs->GetPositionVector() - pLhs->GetPositionVector());
    
    if (std::fabs(deltaPosition.GetZ()) > std::numeric_limits<float>::epsilon())
        return (deltaPosition.GetZ() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPosition.GetX()) > std::numeric_limits<float>::epsilon())
        return (deltaPosition.GetX() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPosition.GetY()) > std::numeric_limits<float>::epsilon())
        return (deltaPosition.GetY() > std::numeric_limits<float>::epsilon());

    // Use pulse height to resolve ties
    return SortHitsByPulseHeight(pLhs, pRhs);
}
  
//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortHitsByPulseHeight(const CaloHit *const pLhs, const CaloHit *const pRhs)
{
    // TODO: Think about the correct energy to use here (should they ever be different)
    return (pLhs->GetHadronicEnergy() > pRhs->GetHadronicEnergy());
}

//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::SortCoordinatesByPosition(const CartesianVector &lhs, const CartesianVector &rhs)
{
    const CartesianVector deltaPosition(rhs - lhs);

    if (std::fabs(deltaPosition.GetZ()) > std::numeric_limits<float>::epsilon())
        return (deltaPosition.GetZ() > std::numeric_limits<float>::epsilon());

    if (std::fabs(deltaPosition.GetX()) > std::numeric_limits<float>::epsilon())
        return (deltaPosition.GetX() > std::numeric_limits<float>::epsilon());

    return (deltaPosition.GetY() > std::numeric_limits<float>::epsilon());
}


//------------------------------------------------------------------------------------------------------------------------------------------

bool CubeClusterHelper::CombiningTwoDClusters(const Cluster *const mCluster, const Cluster *const nCluster, const double tolerance)
{

    if (mCluster->GetNCaloHits()<2 || nCluster->GetNCaloHits()<2) return false;

    const OrderedCaloHitList &orderedCaloHitList(mCluster->GetOrderedCaloHitList());
    const OrderedCaloHitList &orderedCaloHitList2(nCluster->GetOrderedCaloHitList());

    int m = mCluster->GetNCaloHits(); 
    double x[m],y[m],a,b;
    int counter = 0;
    int i = 0;

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList.begin(), ochIterEnd = orderedCaloHitList.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());

	    x[counter] = hit.GetX();
	    y[counter] = hit.GetZ();

	    counter ++; 
        }
    }

    double xsum=0,x2sum=0,ysum=0,xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    for (i=0;i<m;i++)
    {
        xsum=xsum+x[i];                        //calculate sigma(xi)
        ysum=ysum+y[i];                        //calculate sigma(yi)
        x2sum=x2sum+pow(x[i],2);                //calculate sigma(x^2i)
        xysum=xysum+x[i]*y[i];                    //calculate sigma(xi*yi)
    }
    a=(m*xysum-xsum*ysum)/(m*x2sum-xsum*xsum);            //calculate slope
    b=(x2sum*ysum-xsum*xysum)/(x2sum*m-xsum*xsum);            //calculate intercept
    double y_fit[m];                        //an array to store the new fitted values of y    
    for (i=0;i<m;i++)
        y_fit[i]=a*x[i]+b;                    //to calculate y(fitted) at given x points
    for (i=0;i<m;i++)
        std::cout<<"\nThe linear fit line is of the form:\n\n"<<a<<"x + "<<b<<std::endl;        //print the best fit line

    counter = 0;
    int n = nCluster->GetNCaloHits();
    double xx[n],yy[n],aa,bb;

    for (OrderedCaloHitList::const_iterator ochIter = orderedCaloHitList2.begin(), ochIterEnd = orderedCaloHitList2.end(); ochIter != ochIterEnd; ++ochIter)
    {
        for (CaloHitList::const_iterator hIter = ochIter->second->begin(), hIterEnd = ochIter->second->end(); hIter != hIterEnd; ++hIter)
        {
            const CaloHit *const pCaloHit = *hIter;
            const CartesianVector &hit(pCaloHit->GetPositionVector());

            xx[counter] = hit.GetX();
            yy[counter] = hit.GetZ();
            
	    counter++;
	}
    }

    xsum=0;x2sum=0;ysum=0;xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    for (i=0;i<n;i++)
    {   
        xsum=xsum+xx[i];                        //calculate sigma(xi)
        ysum=ysum+yy[i];                        //calculate sigma(yi)
        x2sum=x2sum+pow(xx[i],2);                //calculate sigma(x^2i)
        xysum=xysum+xx[i]*yy[i];                    //calculate sigma(xi*yi)
    }
    aa=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);            //calculate slope
    bb=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);            //calculate intercept
    double yy_fit[n];                        //an array to store the new fitted values of y    
    for (i=0;i<n;i++)
        yy_fit[i]=aa*xx[i]+bb;                    //to calculate y(fitted) at given x points
    for (i=0;i<n;i++)
        std::cout<<"\nThe linear fit line is of the form:\n\n"<<a<<"x + "<<b<<std::endl;        //print the best fit line

    std::cout<<"calcuated slopes are: "<<a <<"  "<< aa<<"  and tolerance is : "<<tolerance<<std::endl;
    if (aa - a > tolerance) return false;
    else return true;
}

} // namespace example_content