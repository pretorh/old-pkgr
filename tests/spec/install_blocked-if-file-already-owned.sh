. tests/setup.sh

# given a package is already installed
package_files usr/bin/hello usr/lib/libhello.so share/man/hello
./pkgr --pack $PACKAGE_DIR --name package-old
./pkgr --install $PACKAGE_DIR/package-old.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR
empty_package_dir

# and a new package that contains some of the same files
package_files usr/bin/hello share/doc/hello
./pkgr --pack $PACKAGE_DIR --name package-new

# when installed, it fails
if ./pkgr --install $PACKAGE_DIR/package-new.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR ; then
    fail "expected install to fail"
fi

# and the new files are not created
assert_file_not_exists $ROOT_DIR/share/doc/hello
