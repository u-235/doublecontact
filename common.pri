
PROJECT_ROOT_DIR = $${PWD}

#------------------#
# iwyu support     #
#------------------#

# https://doc.qt.io/qt-5/qmake-manual.html
# https://wiki-qt-io-staging.herokuapp.com/Undocumented_QMake

defineReplace(iwyu_out) {
    return ($${OUT_PWD}/$$basename(1).log)
}

defined(CHECK_IWYU, var) {
    linux*:IWYU_FLAGS += -fPIE

    IWYU_FLAGS += $(DEFINES) -w $(INCPATH)

    for(include, IWYU_INCLUDES) {
        IWYU_FLAGS += -I$$include
    }

    IWYU_EXTRA_FLAGS += -Xiwyu --max_line_length=160 -Xiwyu --mapping_file=$${PROJECT_ROOT_DIR}/tools/iwyu.imp

    iwyu.output_function  = iwyu_out
    iwyu.commands = $${PROJECT_ROOT_DIR}/tools/iwyu_comp.sh $${IWYU_EXTRA_FLAGS} $${IWYU_FLAGS} ${QMAKE_FILE_NAME}
    iwyu.input = SOURCES
    iwyu.CONFIG += no_link target_predeps
    QMAKE_EXTRA_COMPILERS += iwyu
}

