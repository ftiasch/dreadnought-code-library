make a
make b
make gen

$i

while [ true ]
do
	echo $((i=i+1))
	./gen > a.in
	./a < a.in > a.out
	./b < a.in > b.out
	if ! diff a.out b.out
	then
		echo Wrong
		break
	fi
done
