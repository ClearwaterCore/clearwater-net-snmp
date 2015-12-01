DEB_COMPONENT := clearwater-net-snmp
DEB_MAJOR_VERSION := 1.0${DEB_VERSION_QUALIFIER}
DEB_NAMES := clearwater-net-snmp
DEB_ARCH := all

CW_SIGNER ?= maintainers@projectclearwater.org
CW_SIGNER_REAL := Project Clearwater Maintainers

deb_build:
	echo "${DEB_COMPONENT} (${DEB_VERSION}) unstable; urgency=low" >debian/changelog
	echo "  * build from $$(git config --get remote.origin.url|sed -e 's#^git@\([^:]*\):\([^/]*\)\([^.]*\)[.]git#https://\1/\2\3/tree/#')$$(git rev-parse HEAD)" >>debian/changelog;
	echo " -- $(CW_SIGNER_REAL) <$(CW_SIGNER)>  $$(date -R)" >>debian/changelog
	debuild --no-lintian -b -uc -us

deb: deb_build
	sed -i~ "s#-clearwater1#-$(DEB_VERSION)#" clearwater1.patch Makefile
	rm -f clearwater1.patch~ Makefile~
	make clean all
	git checkout -- clearwater1.patch Makefile
	mv *.deb ${REPO_DIR}/binary
	mv ../clearwater-net-snmp_${DEB_VERSION}_${DEB_ARCH}.deb ${REPO_DIR}/binary
