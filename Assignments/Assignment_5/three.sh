# problem 3
a=$1 # file name
b=$2 # file extension
counter=1
for file in *.$b; do
  new=$(printf "$a%03d.$b" "$counter")
  mv -- "$file" "$new"
  let counter+=1
done
