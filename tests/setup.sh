set -e

trap fail HUP INT QUIT TERM ERR

TEST_ROOT_DIR=$(mktemp -d /tmp/pkgr-tests-XXXXXX)
PACKAGE_DIR=$TEST_ROOT_DIR/pack
ROOT_DIR=$TEST_ROOT_DIR/root
LIBRARY_DIR=$TEST_ROOT_DIR/lib

mkdir -p $PACKAGE_DIR/files
mkdir -p $ROOT_DIR
mkdir -p $LIBRARY_DIR

function package_files {
    for v in "$@" ; do
        mkdir -p `dirname $PACKAGE_DIR/files/$v`
        touch $PACKAGE_DIR/files/$v
    done
}

function assert_file_exists {
    for v in "$@" ; do
        test -f $v || fail "$v file does not exist"
    done
}

function fail {
    set +e
    echo "FAILED"
    echo "  $1"
    local frame=0
    while caller $frame; do
        ((frame++));
    done
    exit 1
}

echo "TEST_ROOT_DIR=$TEST_ROOT_DIR"
