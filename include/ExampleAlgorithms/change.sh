for file in * 
do
	echo $file
        if [ "$file" == "change.sh" ] ; then
              continue;
        fi

	sed -i 's/larpandoracontent\/LArObjects\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArHelpers\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArUtility\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArTwoDReco\/LArClusterSplitting\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArTwoDReco\/LArClusterAssociation\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArTwoDReco\/LArClusterMopUp\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArTwoDReco\/LArClusterCreation\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArTwoDReco\/LArCosmicRay\//ExampleAlgorithms\//g' $file 

	sed -i 's/larpandoracontent\/LArCheating\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArControlFlow\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArCustomParticles\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArMonitoring\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArPersistency\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArPlugins\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArVertex\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArTrackShowerId\//ExampleAlgorithms\//g' $file 

	sed -i 's/larpandoracontent\/LArThreeDReco\/LArCosmicRay\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArEventBuilding\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArHitCreation\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArLongitudinalTrackMatching\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArPfoMopUp\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArPfoRecovery\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArShowerFragments\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArShowerMatching\//ExampleAlgorithms\//g' $file 

	sed -i 's/larpandoracontent\/LArThreeDReco\/LArThreeDBase\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArTrackFragments\//ExampleAlgorithms\//g' $file 
	sed -i 's/larpandoracontent\/LArThreeDReco\/LArTransverseTrackMatching\//ExampleAlgorithms\//g' $file 

	sed -i 's/larpandoracontent\/LArContent/ExampleContent\//g' $file
	sed -i 's/LArContent/ExampleContent\//g' $file
	sed -i 's/ExampleContent\//ExampleContent/g' $file
	scp ../../include/ExampleContent.h .
	sed -i 's/lar_content/example_content/g' $file 
	sed -i 's/LAR/EXAMPLE/g' $file 
	sed -i 's/RECTANGUEXAMPLE/RECTANGULAR/g' $file 

done
