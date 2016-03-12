. tests/setup.sh

# given
package_files usr/bin/hello usr/lib/libhello.so share/man/hello

# when packed
./pkgr --pack $PACKAGE_DIR

# then tar file created
assert_file_exists $PACKAGE_DIR/package.tar.xz
# with the files added correctly in it
tar -tf $PACKAGE_DIR/package.tar.xz | grep "^files/usr/bin/hello$" || fail "expected file not found in tar"
