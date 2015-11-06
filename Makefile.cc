deb:
	sed -i~ "s#-clearwater1#-$(DEB_VERSION)#" clearwater1.patch Makefile
	rm -f clearwater1.patch~ Makefile~
	make clean all
	git checkout -- clearwater1.patch Makefile
	mv *.deb ${REPO_DIR}/binary
