
import sys 
from setuptools import setup 
from setuptools.command.test import test as TestCommand 

class PyTest(TestCommand): 
    '''pytest's integration with setuptools, which is borrowed from: 
    http://pytest.org/latest/goodpractises.html#goodpractises
    '''

    # user_options = [('pytest-args=', 'a', "Arguments to pass to py.test")]
    # 
    # def initialize_option(self): 
    #     TestCommand.initialize_options(self) 
    #     self.pytest_args = None

    def finalize_options(self): 
        TestCommand.finalize_options(self)
        self.test_args = [] 
        self.test_suite = True 

    def run_tests(self): 
        import pytest 
        errcode = pytest.main(self.test_args + ['-s']) 
        sys.exit(errcode) 

setup(
    name            = 'btreelab', 
    version         = '0.0.1', 
    author          = 'mengyu zhang', 
    packages        = ['btreelab', 'tests'], 
    tests_require   = ['pytest'], 
    cmdclass        = {'test': PyTest}, 
    test_suite      = 'tests', 
    extras_require  = {'testing': ['pytest']} 
)

