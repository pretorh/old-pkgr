. tests/setup.sh

# given
package_files usr/bin/hello usr/lib/libhello.so share/man/hello

# when packed with a name
./pkgr --pack $PACKAGE_DIR --name abc

# then tar file is created with that name
assert_file_exists $PACKAGE_DIR/abc.tar.xz
