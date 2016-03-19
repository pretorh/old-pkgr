. tests/setup.sh

# given sripts
echo "touch \$R/script-pre-output" > $PACKAGE_DIR/pkgr/scripts/pre-install.sh
echo "touch \$R/script-post-output" > $PACKAGE_DIR/pkgr/scripts/post-install.sh

# when packed
./pkgr --pack $PACKAGE_DIR

# with the scripts added correctly in it
tar -tf $PACKAGE_DIR/package.tar.xz | grep -q "^pkgr/scripts/pre-install.sh$" || fail "expected pre script not found in tar"
tar -tf $PACKAGE_DIR/package.tar.xz | grep -q "^pkgr/scripts/post-install.sh$" || fail "expected post script not found in tar"
