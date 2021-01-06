shuffle() {
   local i tmp size max rand

   # $RANDOM % (i+1) is biased because of the limited range of $RANDOM
   # Compensate by using a range which is a multiple of the array size.
   size=${#array[*]}
   max=$(( 32768 / size * size ))

   for ((i=size-1; i>0; i--)); do
      while (( (rand=$RANDOM) >= max )); do :; done
      rand=$(( rand % (i+1) ))
      tmp=${array[i]} array[i]=${array[rand]} array[rand]=$tmp
   done
}

if [ "$#" -ne 1 ]; then
 echo "$0 [nb]";
 exit 1;
fi

declare -a array
for ((i=0 ; $i < $1 ; i++)); do
	array[$i]=$i
done

shuffle
str="${array[0]}"
for ((i=1 ; $i < $1 ; i++)); do
	str="${str} ${array[$i]}"
done

echo $str
result=$(./push_swap $str)
echo "$result" | ./checker $str
echo "$result" | wc -l
