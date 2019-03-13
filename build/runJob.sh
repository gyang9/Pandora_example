rm /home/guang/work/Pandora/ExampleContent/build/*output.txt

for i in $(seq 0 20 980)
do
	echo "now starting from $i to $(($i+20))"
	/home/guang/work/Pandora/ExampleContent/bin/PandoraExample -i /home/guang/work/Pandora/ExampleContent/settings/guang8.xml -n $(($i+20)) -b $i
done
