. tests/setup.sh

# given a package with scripts
package_files usr/bin/hello
echo "echo 'PRE'" > $PACKAGE_DIR/pkgr/scripts/pre-install.sh
echo "echo 'POST'" > $PACKAGE_DIR/pkgr/scripts/post-install.sh
./pkgr --pack $PACKAGE_DIR

# when installed
./pkgr --install $PACKAGE_DIR/package.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR > $TEST_ROOT_DIR/output

# then the scripts are executed
grep "^PRE$" $TEST_ROOT_DIR/output || fail "pre script not executed"
grep "^POST$" $TEST_ROOT_DIR/output || fail "post script not executed"
