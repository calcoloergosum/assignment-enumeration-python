import numpy
from numpy.distutils.misc_util import Configuration
from scipy._build_utils import numpy_nodepr_api
from scipy._build_utils.compiler_helper import (set_c_flags_hook,
                                                set_cxx_flags_clib_hook)

numpy_nodepr_api = dict(define_macros=[("NPY_NO_DEPRECATED_API",
                                        "NPY_1_9_API_VERSION")])

def configuration(parent_package='', top_path=None):

    config = Configuration('lsap', parent_package, top_path)

    # include_dirs = [join(os.path.dirname(__file__), '..', '_lib', 'src')]
    include_dirs = [numpy.get_include()]

    config.add_library('rectangular_lsap',
                       sources='rectangular_lsap/rectangular_lsap.cpp',
                       headers='rectangular_lsap/rectangular_lsap.h',
                       _pre_build_hook=set_cxx_flags_clib_hook)
    _lsap = config.add_extension(
        'lsap',
        sources=['lsap.c'],
        libraries=['rectangular_lsap'],
        depends=(['rectangular_lsap/rectangular_lsap.cpp',
                  'rectangular_lsap/rectangular_lsap.h']),
        include_dirs=include_dirs,
        **numpy_nodepr_api)
    _lsap._pre_build_hook = set_c_flags_hook

    # Add license files
    config.add_data_files('lbfgsb_src/README')

    return config


if __name__ == '__main__':
    from numpy.distutils.core import setup
    setup(**configuration(top_path='').todict())
