. tests/setup.sh

# given a package is already installed
package_files usr/bin/hello usr/lib/libhello.so share/man/hello
./pkgr --pack $PACKAGE_DIR --name package-old
./pkgr --install $PACKAGE_DIR/package-old.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR
empty_package_dir

# and a new package that contains some of the same files
package_files usr/bin/hello share/doc/hello
./pkgr --pack $PACKAGE_DIR --name package-new

# (setup: one of the old files do not exist)
rm $ROOT_DIR/usr/bin/hello

# when installed with setting to replace files of the old package
./pkgr --install $PACKAGE_DIR/package-new.tar.xz --root-dir $ROOT_DIR  --library-dir $LIBRARY_DIR \
    --replace-files package-old

# then the files are owned by the new package
./pkgr --query owner --library-dir $LIBRARY_DIR /usr/bin/hello | \
    grep -q "^package-new: /usr/bin/hello$" || fail "file not owned / not owned by package-new"
./pkgr --query owner --library-dir $LIBRARY_DIR /share/doc/hello | \
    grep -q "^package-new: /share/doc/hello$" || fail "file not owned / not owned by package-new"

# and the old package still owns its remaining files
./pkgr --query owner --library-dir $LIBRARY_DIR /usr/lib/libhello.so | \
    grep -q "^package-old: /usr/lib/libhello.so$" || fail "file not owned / not owned by package-old"

# and the new files are created (doc)
assert_file_exists $ROOT_DIR/share/doc/hello

# and the old files are replaced (they were manually removed before install)
assert_file_exists $ROOT_DIR/usr/bin/hello

# and the old files are still present
assert_file_exists $ROOT_DIR/usr/lib/libhello.so $ROOT_DIR/share/man/hello
