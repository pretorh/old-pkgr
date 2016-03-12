. tests/setup.sh

# given
package_files usr/bin/hello usr/lib/libhello.so share/man/hello
./pkgr --pack $PACKAGE_DIR

# when installed
./pkgr --install $PACKAGE_DIR/package.tar.xz --root $ROOT_DIR  --library $LIBRARY_DIR

# then the files are created
assert_file_exists $ROOT_DIR/usr/bin/hello $ROOT_DIR/usr/lib/libhello.so $ROOT_DIR/share/man/hello
