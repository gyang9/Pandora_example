/**
 *  @file   ExampleAlgorithms/CheatingBeamParticleIdTool.cc
 *
 *  @brief  Implementation of the cheating beam particle id tool class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/CheatingBeamParticleIdTool.h"

#include "ExampleAlgorithms/LArMCParticleHelper.h"
#include "ExampleAlgorithms/LArPfoHelper.h"

using namespace pandora;

namespace example_content
{

CheatingBeamParticleIdTool::CheatingBeamParticleIdTool() : 
    m_minWeightFraction(0.5f)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

void CheatingBeamParticleIdTool::SelectOutputPfos(const pandora::Algorithm *const /*pAlgorithm*/, const SliceHypotheses &nuSliceHypotheses, const SliceHypotheses &crSliceHypotheses, PfoList &selectedPfos)
{
    if (nuSliceHypotheses.size() != crSliceHypotheses.size())
        throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

    for (unsigned int sliceIndex = 0, nSlices = nuSliceHypotheses.size(); sliceIndex < nSlices; ++sliceIndex)
    {
        float beamParticleWeight(0.f), totalWeight(0.f);
        const PfoList &neutrinoPfoList(nuSliceHypotheses.at(sliceIndex));

        for (const Pfo *const pNeutrinoPfo : neutrinoPfoList)
        {
            if (!LArPfoHelper::IsNeutrino(pNeutrinoPfo))
                throw StatusCodeException(STATUS_CODE_INVALID_PARAMETER);

            PfoList downstreamPfos;
            LArPfoHelper::GetAllDownstreamPfos(pNeutrinoPfo, downstreamPfos);

            float thisBeamParticleWeight(0.f), thisTotalWeight(0.f);
            CheatingSliceIdBaseTool::GetTargetParticleWeight(&downstreamPfos, thisBeamParticleWeight, thisTotalWeight, LArMCParticleHelper::IsBeamParticle);

            beamParticleWeight += thisBeamParticleWeight;
            totalWeight += thisTotalWeight;
        }

        const float beamWeightFraction(totalWeight < std::numeric_limits<float>::epsilon() ? 0.f : beamParticleWeight/totalWeight);

        if (beamWeightFraction > m_minWeightFraction)
        {
            const PfoList &sliceOutput(nuSliceHypotheses.at(sliceIndex));
            selectedPfos.insert(selectedPfos.end(), sliceOutput.begin(), sliceOutput.end());
        }
        else 
        {
            const PfoList &sliceOutput(crSliceHypotheses.at(sliceIndex));
            selectedPfos.insert(selectedPfos.end(), sliceOutput.begin(), sliceOutput.end());
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode CheatingBeamParticleIdTool::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::ReadValue(xmlHandle, "MinimumWeightFraction", m_minWeightFraction));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
