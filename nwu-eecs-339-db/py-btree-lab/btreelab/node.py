
import struct 

from types import * 
from util import IntUtil 

class Meta(object): 
    '''meta format: (n, status, parent/root, order, key_size, val_size) 
    '''
    META_FORMAT = 'i i i i i i' 
    packer = struct.Struct(META_FORMAT) 
    size = packer.size 

    def __init__(self, *args): 
        self._meta = args 

    def key_num(self): 
        return self._meta[0] 

    def status(self): 
        return self._meta[1] 
    
    def root(self): 
        return self._meta[2]
    
    def parent(self): 
        return self._meta[2] 

    def order(self): 
        return self._meta[3] 

    def key_size(self): 
        return self._meta[4] 

    def val_size(self): 
        return self._meta[5] 

    def kv_size(self): 
        return self.key_size() + self.val_size() 
    
    def set_key_num(self, n): 
        self._meta[0] = n 

    def set_status(self, status): 
        self._meta[1] = status 

    def to_bytes(self): 
        return self.packer.pack(*self._meta) 

    def from_bytes(self, raw_bytes): 
        self._meta = self.packer.unpack(raw_bytes)

    def __repr__(self): 
        return `self._meta` 

class Node(object): 

    meta_size = Meta.packer.size 

    def __init__(self, meta=(0, NULL_NODE, NULL_NODE, 0, 0, 0), 
            records=[], ptrs=[NULL_NODE]): 
        '''by default, the constructor makes an unallocated node.
        ''' 
        self.key_list = map(lambda r: r[0], records) 
        self.val_list = map(lambda r: r[1], records)
        self.ptr_list = ptrs 
        self.meta = Meta(*meta) 

    def key_num(self): 
        return self.meta.key_num() 

    def status(self): 
        return self.meta.status() 

    def records(self): 
        return zip(self.key_list, self.val_list) 

    def keys(self): 
        return self.key_list

    def values(self): 
        return self.val_list 

    def ptrs(self): 
        return self.ptr_list 

    def get_meta(self): 
        return self.meta 

    def set_meta(self, n, status, p, order, key_size, val_size): 
        self.meta = Meta(n, status, p, order, key_size, val_size) 

    def set_key_num(self, n): 
        self.meta.set_key_num(n) 

    def set_status(self, status): 
        self.meta.set_status(status) 

    def set_records(self, records): 
        self.key_list = map(lambda r: r[0], records) 
        self.val_list = map(lambda r: r[1], records)

    def set_ptrs(self, ptr_list): 
        self.ptr_list = ptr_list 

    def to_bytes(self): 
        meta_bytes = self.meta.to_bytes() 
        def pack_ptr_kv(ptr, kv): 
            return IntUtil.to_bytes(ptr) + ''.join(kv)

        data_bytes = ''.join(map(pack_ptr_kv, self.ptr_list[:-1], 
            self.records())) + IntUtil.to_bytes(self.ptr_list[-1]) 

        return meta_bytes + data_bytes 

    def from_bytes(self, raw_bytes): 
        meta_bytes = raw_bytes[:self.meta_size] 
        data_bytes = raw_bytes[self.meta_size:] 

        # meta 
        self.meta.from_bytes(meta_bytes) 

        # kv list 
        for i in range(self.meta.key_num()): 
            s = i * (IntUtil.size() + self.meta.kv_size())
            t = s + self.meta.kv_size() 
            kv_bytes = data_bytes[s:t] 
            self.key_list.append(kv_bytes[:self.meta.key_size()]) 
            self.val_list.append(kv_bytes[self.meta.key_size():]) 

        # ptr list 
        for i in range(self.meta.key_num() + 1): 
            s = i * (IntUtil.size() + self.meta.kv_size())
            t = s + IntUtil.size()
            ptr = IntUtil.from_bytes(data_bytes[s:t]) 
            self.ptr_list.append(ptr) 

        return self 

    def __repr__(self): 
        return "{'meta': %s, 'ptrs': %s, 'records': %s}" %(`self.meta`, 
                str(self.ptr_list), str(self.records())) 


