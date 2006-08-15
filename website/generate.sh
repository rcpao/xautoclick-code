#!/bin/bash

for i in news about screenshots documentation download mailinglists cvs ; do
    cat head.tmpl "$i.txt" foot.tmpl > "$i.html"
done

