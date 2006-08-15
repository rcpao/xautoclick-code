#!/bin/bash

for i in news about screenshots documentation download mailinglists subversion
do
    cat head.tmpl "$i.txt" foot.tmpl > "$i.html"
done

