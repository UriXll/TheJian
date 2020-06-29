```javascript
#!/bin/bash
function getdir(){
    for element in `ls $1`
    do  
        dir_or_file=$1"/"$element
        if [ -d $dir_or_file ]
        then 
            getdir $dir_or_file
        else
	    if test ${element##*.} = "png"
	    then
	        base=${dir_or_file%.png}
            	mv $dir_or_file ${base}.$newext
	    fi
        fi  
    done
}
oldext="png"   
newext="data"
root_dir=$(cd "$(dirname "$0")";pwd)
echo $root_dir
getdir $root_dir
```

