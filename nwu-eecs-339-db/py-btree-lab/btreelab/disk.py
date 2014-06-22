
import sys
import logging 

import util 
from collections import deque 

LOG = logging.getLogger(__name__) 

SEEK_SET = 0 

class Disk(object): 

    def __init__(self): 
        self.data_fd = None 
        self.data_file = 'records.db' 

    def read(self, offset, length): 
        self.data_fd.seek(offset, SEEK_SET)
        return self.data_fd.read(length) 

    def write(self, offset, data): 
        self.data_fd.seek(offset, SEEK_SET) 
        return self.data_fd.write(data) 

    def open(self, mode): 
        self.data_fd = open(self.data_file, mode) 

    def close(self): 
        self.data_fd.close() 

class DiskController(object): 

    def __init__(self, block_size, block_num): 
        self.disk = Disk() 
        self.block_size = block_size 
        self.block_num = block_num 

    def setup(self, create=False): 
        '''open or create disk file for access. 
        ''' 
        if create: 
            self.disk.open('w+') 
            self.format_disk() 
        else: 
            self.disk.open('r+') 

    def close(self): 
        self.disk.close() 

    def blocks(self): 
        '''generator of all blocks on disk file. 
        ''' 
        for index in range(self.block_num): 
            yield self.read_block(index) 
    
    def read_block(self, index): 
        return self.disk.read(index * self.block_size, self.block_size) 

    def write_block(self, index, data): 
        return self.disk.write(index * self.block_size, data) 

    def format_disk(self, data=None): 
        '''clear the entire disk content by default.  
        ''' 
        if data is None:
            data = '\x00' * self.block_size

        for index in range(self.block_num): 
            self.write_block(index, data) 

    def dump_disk(self): 
        '''dump the entire disk as formatted string. 
        ''' 
        return '\n'.join(map(lambda (i, block): 'block #%d: %s' %(i, 
            `block`), enumerate(self.blocks()))) 

