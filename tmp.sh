#!/bin/bash

QT_PRO="qtconcurrent.pro"

echo -e "\nQt Concurrent algorithms:"
echo "Generating qmake project file ..."
 
QT_PRO_CONTENT=""

# QT_PRO_CONTENT=$( cat <<EOF
#read -d '' QT_PRO_CONTENT  <<"EOF"
cat > $QT_PRO <<_EOF_
config_map {
	TEMPLATE = app
	QT	 = core
	CONFIG   = console
	CXXFLAGS = -Wextra


	TARGET   = QT_map
	SOURCES  = QT_map.cpp
}
_EOF_
 

echo -e $QT_PRO_CONTENT

