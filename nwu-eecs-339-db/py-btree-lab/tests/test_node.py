
import sys 
import logging 

from btreelab import util 
from btreelab.types import * 
from btreelab.node import Node, Meta 

LOG = logging.getLogger(__name__) 

def test_construct(): 
    default_node = Node() 
    LOG.info('default node: %s' %(`default_node.to_bytes()`)) 

def test_meta_serialize(): 
    raw = Meta(1, INTE_NODE, 7, 4, 8, 32).to_bytes() 
    meta = Meta() 
    meta.from_bytes(raw) 
    LOG.info('meta: %s' %(`meta`)) 

def test_set_meta(): 
    default_node = Node() 
    LOG.info('original meta: %s' %(`default_node.get_meta()`)) 

    _meta = (1, INTE_NODE, 7, 4, 8, 32) 
    default_node.set_meta(*(_meta)) 
    LOG.info('changed meta: %s' %(`default_node.get_meta()`)) 

def test_set_records_and_ptrs(): 
    default_node = Node() 
    default_node.set_meta(4, INTE_NODE, 7, 4, 8, 4) 

    ptrs = range(5) 
    records = [('0827108%d' %i, 'c++ 98pt') for i in range(4)] 

    default_node.set_ptrs(ptrs) 
    default_node.set_records(records) 

    LOG.info('node content: %s' %(`default_node.to_bytes()`)) 

