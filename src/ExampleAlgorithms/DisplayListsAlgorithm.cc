/**
 *  @file   ExampleContent/src/ExampleAlgorithms/DisplayListsAlgorithm.cc
 * 
 *  @brief  Implementation of the display lists algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/DisplayListsAlgorithm.h"

using namespace pandora;

namespace example_content
{

DisplayListsAlgorithm::DisplayListsAlgorithm() :
    m_displayCurrentCaloHits(false),
    m_displayCurrentTracks(false),
    m_displayCurrentMCParticles(false),
    m_displayCurrentClusters(false),
    m_displayCurrentVertices(false),
    m_displayCurrentPfos(false)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode DisplayListsAlgorithm::Run()
{
    // Useful event display functionality for visualizing the operations performed in other example algorithms.

    // The PANDORA_MONITORING_API preprocessor macro automatically checks whether monitoring has been enabled via the
    // PandoraSettings xml file. If the MONITORING preprocessor flag has not been defined, its arguments will collapse to no code.

    if (m_displayCurrentCaloHits)
    {
        const CaloHitList *pCaloHitList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pCaloHitList));
        PANDORA_MONITORING_API(VisualizeCaloHits(this->GetPandora(), pCaloHitList, "CurrentCaloHits", GRAY));
    }

    if (m_displayCurrentTracks)
    {
        const TrackList *pTrackList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pTrackList));
        PANDORA_MONITORING_API(VisualizeTracks(this->GetPandora(), pTrackList, "CurrentTracks", MAGENTA));
    }

    if (m_displayCurrentMCParticles)
    {
        const MCParticleList *pMCParticleList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pMCParticleList));
        PANDORA_MONITORING_API(VisualizeMCParticles(this->GetPandora(), pMCParticleList, "CurrentMCParticles", CYAN));
    }

    if (m_displayCurrentClusters)
    {
        const ClusterList *pClusterList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pClusterList));
        PANDORA_MONITORING_API(VisualizeClusters(this->GetPandora(), pClusterList, "CurrentClusterList", RED));
    }

    if (m_displayCurrentVertices)
    {
        const VertexList *pVertexList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pVertexList));
        PANDORA_MONITORING_API(VisualizeVertices(this->GetPandora(), pVertexList, "CurrentVertexList", GREEN));
    }

    if (m_displayCurrentPfos)
    {
        const PfoList *pPfoList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pPfoList));
        PANDORA_MONITORING_API(VisualizeParticleFlowObjects(this->GetPandora(), pPfoList, "CurrentPfoList", BLUE));
    }

    PANDORA_MONITORING_API(ViewEvent(this->GetPandora()));

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode DisplayListsAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "DisplayCurrentCaloHits", m_displayCurrentCaloHits));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "DisplayCurrentTracks", m_displayCurrentTracks));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "DisplayCurrentMCParticles", m_displayCurrentMCParticles));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "DisplayCurrentClusters", m_displayCurrentClusters));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "DisplayCurrentVertices", m_displayCurrentVertices));

    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "DisplayCurrentPfos", m_displayCurrentPfos));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
