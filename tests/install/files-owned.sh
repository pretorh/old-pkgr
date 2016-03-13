. tests/setup.sh

# given
package_files usr/bin/hello
./pkgr --pack $PACKAGE_DIR --name test-1

# when installed
./pkgr --install $PACKAGE_DIR/test-1.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR

# then the files are owned
./pkgr --query owner --library-dir $LIBRARY_DIR usr/bin/hello | \
    grep -q "^test-1: usr/bin/hello$" || fail "file not owned"
