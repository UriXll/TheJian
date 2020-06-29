```javascript
#!/bin/bash
##change filename of *.txt to *.doc
##Written by adai
read -p "Please input a directory:" f
echo "Old filename:" 
ls $f
for i in `ls $f | grep '.txt' | awk -F"." '{print $1}'`
do
     mv $f/$i.txt $f/$i.doc
done
echo "New filename:"
ls $f
```

