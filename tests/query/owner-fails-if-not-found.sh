. tests/setup.sh

# given nothing is installed

# when queried by full path, it is not found and the process exits with error
./pkgr --query owner --library-dir $LIBRARY_DIR /usr/bin/hello && fail "query (wrongly) returned successfully" || echo "pass: exit with error code"
