/**
 *  @file   ExampleAlgorithms/PreProcessingAlgorithm.cc
 *
 *  @brief  Implementation of the list preparation algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/PreProcessingAlgorithm.h"

#include "ExampleAlgorithms/ExampleClusterHelper.h"

#include "ExampleAlgorithms/KDTreeLinkerAlgoT.h"

using namespace pandora;

namespace example_content
{

PreProcessingAlgorithm::PreProcessingAlgorithm() :
    m_mipEquivalentCut(std::numeric_limits<float>::epsilon()),
    m_minCellLengthScale(std::numeric_limits<float>::epsilon()),
    m_maxCellLengthScale(3.f),
    m_searchRegion1D(0.1f),
    m_onlyAvailableCaloHits(true),
    m_inputCaloHitListName("Input")
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PreProcessingAlgorithm::Reset()
{
    m_processedHits.clear();
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PreProcessingAlgorithm::Run()
{
    if (!this->GetPandora().GetSettings()->SingleHitTypeClusteringMode())
    {
        std::cout << "PreProcessingAlgorithm: expect Pandora to be configured in SingleHitTypeClusteringMode." << std::endl;
        return STATUS_CODE_FAILURE;
    }

    try
    {
        this->ProcessCaloHits();
    }
    catch (StatusCodeException &)
    {
    }

    if (!m_currentCaloHitListReplacement.empty())
    {
        if (STATUS_CODE_SUCCESS != PandoraContentApi::ReplaceCurrentList<CaloHit>(*this, m_currentCaloHitListReplacement))
        {
            if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
                std::cout << "PreProcessingAlgorithm: could not replace current calo hit list with list named: " << m_currentCaloHitListReplacement << std::endl;
        }
    }

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void PreProcessingAlgorithm::ProcessCaloHits()
{
    const CaloHitList *pCaloHitList(nullptr);
    PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetList(*this, m_inputCaloHitListName, pCaloHitList));

    if (pCaloHitList->empty())
        return;

    CaloHitList selectedCaloHitList;

    for (const CaloHit *const pCaloHit : *pCaloHitList)
    {
        if (m_processedHits.count(pCaloHit))
            continue;

        (void) m_processedHits.insert(pCaloHit);

        if (m_onlyAvailableCaloHits && !PandoraContentApi::IsAvailable(*this, pCaloHit))
            continue;

        if (pCaloHit->GetMipEquivalentEnergy() < m_mipEquivalentCut)
            continue;

        if (pCaloHit->GetInputEnergy() < std::numeric_limits<float>::epsilon())
        {
            if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
                std::cout << "PreProcessingAlgorithm: found a hit with zero energy, will remove it" << std::endl;

            continue;
        }

        if ((pCaloHit->GetCellLengthScale() < m_minCellLengthScale) || (pCaloHit->GetCellLengthScale() > m_maxCellLengthScale))
        {
            if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
            {
                std::cout << "PreProcessingAlgorithm: found a hit with extent " << pCaloHit->GetCellLengthScale()
                          << ", require (" << m_minCellLengthScale << " - " << m_maxCellLengthScale << "), will remove it" << std::endl;
            }

            continue;
        }

        selectedCaloHitList.push_back(pCaloHit);
    }

    CaloHitList filteredCaloHitList;
    this->GetFilteredCaloHitList(selectedCaloHitList, filteredCaloHitList);

    CaloHitList filteredInputList;
    filteredInputList.insert(filteredInputList.end(), filteredCaloHitList.begin(), filteredCaloHitList.end());

    if (!filteredInputList.empty() && !m_filteredCaloHitListName.empty())
        PANDORA_THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::SaveList(*this, filteredInputList, m_filteredCaloHitListName));
}

//------------------------------------------------------------------------------------------------------------------------------------------

void PreProcessingAlgorithm::GetFilteredCaloHitList(const CaloHitList &inputList, CaloHitList &outputList)
{
    HitKDTree2D kdTree;
    HitKDNode2DList hitKDNode2DList;

    KDTreeBox hitsBoundingRegion2D = fill_and_bound_2d_kd_tree(inputList, hitKDNode2DList);
    kdTree.build(hitKDNode2DList, hitsBoundingRegion2D);

    // Remove hits that are in the same physical location!
    for (const CaloHit *const pCaloHit1 : inputList)
    {
        bool isUnique(true);
        KDTreeBox searchRegionHits(build_2d_kd_search_region(pCaloHit1, m_searchRegion1D, m_searchRegion1D));

        HitKDNode2DList found;
        kdTree.search(searchRegionHits, found);

        for (const auto &hit : found)
        {
            const CaloHit *const pCaloHit2(hit.data);

            if (pCaloHit1 == pCaloHit2)
                continue;

            const float displacementSquared((pCaloHit2->GetPositionVector() - pCaloHit1->GetPositionVector()).GetMagnitudeSquared());

            if (displacementSquared < std::numeric_limits<float>::epsilon())
            {
                const float deltaMip(pCaloHit2->GetMipEquivalentEnergy() > pCaloHit1->GetMipEquivalentEnergy());

                if ((deltaMip > std::numeric_limits<float>::epsilon()) ||
                    ((std::fabs(deltaMip) < std::numeric_limits<float>::epsilon()) && (outputList.end() != std::find(outputList.begin(), outputList.end(), pCaloHit2))))
                {
                    isUnique = false;
                    break;
                }
            }
        }

        if (isUnique)
        {
            outputList.push_back(pCaloHit1);
        }
        else
        {
            if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
                std::cout << "PreProcessingAlgorithm: found two hits in same location, will remove lowest pulse height" << std::endl;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode PreProcessingAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MipEquivalentCut", m_mipEquivalentCut));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MinCellLengthScale", m_minCellLengthScale));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "MaxCellLengthScale", m_maxCellLengthScale));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "SearchRegion1D", m_searchRegion1D));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "OnlyAvailableCaloHits", m_onlyAvailableCaloHits));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputCaloHitListName", m_inputCaloHitListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "OutputCaloHitListName", m_outputCaloHitListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "FilteredCaloHitListName", m_filteredCaloHitListName));

    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle,
        "CurrentCaloHitListReplacement", m_currentCaloHitListReplacement));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content