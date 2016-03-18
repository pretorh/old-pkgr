. tests/setup.sh

# given an installed package
package_files usr/bin/hello
./pkgr --pack $PACKAGE_DIR --name test-1
./pkgr --install $PACKAGE_DIR/test-1.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR

# when ownership removed
./pkgr --library remove-ownership --name test-1 --library-dir $LIBRARY_DIR /usr/bin/hello

# then the file is not owned
if ./pkgr --query owner --library-dir $LIBRARY_DIR /usr/bin/hello 2>/dev/null | grep -q "^test-1: /usr/bin/hello$" ; then
    fail "expected file to not be owned"
fi
