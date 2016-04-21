make gen
make force
make a
$i
while [ true ]
do
	echo $((i=i+1))
	./gen > a.in
	./a < a.in > a.out
	./force < a.in > force.out
	if ! diff a.out force.out
	then
		echo Wrong
		break
	fi
done
