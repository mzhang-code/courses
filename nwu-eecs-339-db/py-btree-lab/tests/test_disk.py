
import sys
import logging 
import pytest 

from config import dc 

from btreelab import util 
from btreelab.disk import Disk, DiskController 

LOG = logging.getLogger(__name__) 

def test_create(dc): 
    dc.setup(create=True) 
    LOG.info('\n' + dc.dump_disk()) 
    dc.close() 

def test_rw_block(dc): 
    dc.setup(create=False) 
    dc.write_block(7, '\xab\xcd' * (dc.block_size/2))
    LOG.info(`dc.read_block(7)`) 
    dc.close() 

