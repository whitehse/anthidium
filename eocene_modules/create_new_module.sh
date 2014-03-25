#!/bin/sh

if [ $# -ne 2 ]; then
    echo "Usage:"
    echo "./create_new_module.sh <new module name> <short name>"
    echo "Example:"
    echo "  ./create_new_module.sh http ht"
    echo "    Will create a new module named eocene_http"
    exit
fi

newname=$1
shortname=$2

newnameuc=`echo $newname | tr 'a-z' 'A-Z'`
shortnameuc=`echo $shortname | tr 'a-z' 'A-Z'`

cp -a eocene_template eocene_${newname}

for foo in `ls eocene_${newname}`
do
    echo $foo | grep -q template
    if [ $? -eq 0 ]; then
        newfooname=`echo $foo | sed "s/template/${newname}/g"`
        mv eocene_${newname}/$foo eocene_${newname}/$newfooname
    fi
  echo ""
done

for foo in `ls eocene_${newname}`
do
    sed -i -e "s/template/$newname/g"    \
        -e "s/TEMPLATE/$newnameuc/g"     \
        -e "s/_TP_/_${shortnameuc}_/g" eocene_${newname}/$foo
done

echo "Don't forget to add the new module to configure.ac, and eocene_modules/Makefile.am"
echo "execute 'autoreconf' before rerunning ./configure"

exit
