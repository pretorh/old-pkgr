. tests/setup.sh

# given an install package
package_files usr/bin/hello
./pkgr --pack $PACKAGE_DIR --name test-1
./pkgr --install $PACKAGE_DIR/test-1.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR

# when queried by full path, it is found
./pkgr --query owner --library-dir $LIBRARY_DIR /usr/bin/hello | \
    grep -q "^test-1: /usr/bin/hello$" || fail "file not owned"

# when queried by partial path, it is not found
if ./pkgr --query owner --library-dir $LIBRARY_DIR /usr ; then
    fail "query (wrongly) returned successfully"
fi
if ./pkgr --query owner --library-dir $LIBRARY_DIR usr/bin/hello ; then
    fail "query (wrongly) returned successfully"
fi
if ./pkgr --query owner --library-dir $LIBRARY_DIR hello ; then
    fail "query (wrongly) returned successfully"
fi
