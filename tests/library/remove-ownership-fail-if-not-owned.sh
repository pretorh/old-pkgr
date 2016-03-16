. tests/setup.sh

# given an installed package
package_files usr/bin/hello
./pkgr --pack $PACKAGE_DIR --name test-1
./pkgr --install $PACKAGE_DIR/test-1.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR

# when trying to remove ownership of file that is not owned by any package, it fails
if ./pkgr --library remove-ownership --name test-1 --library-dir $LIBRARY_DIR /usr/bin/hello-none 2>/dev/null ; then
    fail "expected command to fail (not owned by any package)"
fi

# when trying to remove ownership of file that is owned by another package (not the specified one), it fails
if ./pkgr --library remove-ownership --name test-2 --library-dir $LIBRARY_DIR /usr/bin/hello 2>/dev/null ; then
    fail "expected command to fail (not owned by this package)"
fi
