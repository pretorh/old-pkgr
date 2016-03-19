. tests/setup.sh

# given
package_files usr/bin/hello usr/lib/libhello.so share/man/hello
# and scripts
echo "touch \$R/script-pre-output" > $PACKAGE_DIR/pkgr/scripts/pre-install.sh
echo "touch \$R/script-post-output" > $PACKAGE_DIR/pkgr/scripts/post-install.sh

./pkgr --pack $PACKAGE_DIR

# when installed
./pkgr --install $PACKAGE_DIR/package.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR

# then the scripts were executed
assert_file_exists $ROOT_DIR/script-pre-output
assert_file_exists $ROOT_DIR/script-post-output
