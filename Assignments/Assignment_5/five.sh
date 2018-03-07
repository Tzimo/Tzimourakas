# Problem 5
a=$1
mkdir -p MISC_clean
tar -xzf $a -C ./MISC_clean
for file in $( ls ./MISC_clean ); do
    mkdir -p "./MISC_clean/${file[*]##*.}" 2>/dev/null
    mv "./MISC_clean/$file" "./MISC_clean/${file[*]##*.}" 2>/dev/null
done
NAME=`echo "$a" | cut -d'.' -f1`
tar -czf "$NAME"_clean.tar.gz ./MISC_clean/*
rm -rf MISC_clean