set -e

trap fail HUP INT QUIT TERM ERR

TEST_ROOT_DIR=$(mktemp -d /tmp/pkgr-tests-XXXXXX)
PACKAGE_DIR=$TEST_ROOT_DIR/pack
ROOT_DIR=$TEST_ROOT_DIR/root
LIBRARY_DIR=$TEST_ROOT_DIR/lib

function empty_package_dir {
    rm -rf $PACKAGE_DIR
    mkdir -p $PACKAGE_DIR/files
    mkdir -p $PACKAGE_DIR/pkgr/scripts
}

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

function assert_file_not_exists {
    for v in "$@" ; do
        (test -f $v && fail "$v file exist") || true
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

echo "TEST_ROOT_DIR = $TEST_ROOT_DIR"

empty_package_dir
mkdir -p $ROOT_DIR
mkdir -p $LIBRARY_DIR
