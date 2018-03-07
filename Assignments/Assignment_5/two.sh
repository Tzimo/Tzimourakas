# problem 2
a=$1
[ -w $a ] && W="Write = yes" || W="Write = No"
[ -x $a ] && X="Execute = yes" || X="Execute = No"
[ -r $a ] && R="Read = yes" || R="Read = No"
echo "$file permissions"
echo "$W"
echo "$R"
echo "$X"
if [[ -d "$a" ]] ; then
	echo "$a is a directory"
elif [[ -f "$a" ]]; then
		echo "$a is a file"
else
	echo "${a} is not a file or directory"
	exit 1
fi