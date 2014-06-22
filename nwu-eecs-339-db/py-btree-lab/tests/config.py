
import pytest 
from btreelab.disk import Disk, DiskController 

@pytest.fixture() 
def dc(): 
    '''disk controller
    ''' 
    return DiskController(block_size=124, block_num=8) 

