
from bisect import bisect_left 
from collections import deque 

from disk import DiskController 
from node import Node 
from util import * 
from types import * 

class BTree(object): 

    def __init__(self, dc): 
        self.dc = dc 
        self.meta_node_id = 0 
        self.root_node_id = NULL_NODE 
        self.free_list = None

        self.key_size = 0 
        self.val_size = 0 
        self.order = 0 

    def create(self, key_size, val_size): 
        '''create an empty b-tree on disk. 
        ''' 
        order = calc_order(self.dc.block_size, Node.meta_size, 
                key_size, val_size) 

        self.dc.setup(create=True) 
                
        meta_node = Node() 
        meta_node.set_meta(0, META_NODE, root_node_id, 
                order, key_size, val_size) 

        self.dc.write_block(meta_node_id, meta_node.to_bytes()) 

        root_node = Node() 
        root_node_id = 1 
        root_node.set_meta(0, LEAF_NODE, NULL_NODE, 
                order, key_size, val_size) 

        self.dc.write_block(root_node_id, root_node.to_bytes()) 

        for data_node_id in range(2, self.dc.block_num): 
            data_node = Node() 
            data_node.set_meta(0, NULL_NODE, NULL_NODE, 
                    order, key_size, val_size) 
            
            self.dc.write_block(data_node_id, data_node.to_bytes()) 

        self.detach() 

    def attach(self): 
        '''open db file and reconstruct b-tree for operations. 
        '''
        self.dc.setup() 
        meta_node = get_meta_node()      
        
        unalloc_nodes = [i if self.nodes[i].status() == NULL_NODE \
                for i in range(self.dc.block_num] 

        self.free_list = deque(unalloc_nodes) 

    def detach(self): 
        '''sync b-tree to disk and close. 
        '''
        self.dc.close() 

    def get_root_id(self): 
        meta_node = self.get_meta_node() 
        return meta_node.meta.root()

    def get_meta_node(self): 
        return self.get_node(self.meta_node_id) 

    def nodes(self): 
        return map(lambda block: Node().from_bytes(block), self.dc.blocks()) 

    def get_node(self, node_id): 
        tree_node = Node() 
        return tree_node.from_bytes(self.dc.read_block(node_id)) 

    def set_node(self, node_id, tree_node): 
        return self.dc.write_block(node_id, tree_node.to_bytes) 

    def alloc_node(self): 
        return self.free_list.popleft()

    def dealloc_node(self, node_id): 
        self.free_list.append(node_id) 
        self.dc.write(node_id, Node().to_bytes()) 

    def search_node(self, node_id, k): 
        '''search key 'k', starting from the node with id 'node_id'. 
        ''' 
        x = self.get_node(node_id) 
        i = 0
        n = x.key_num() 
        while i < n and k > x.keys()[i]: 
            i += 1 

        if i < n and k == x.keys()[i]: 
            return (x, i) 
        elif x.status() == LEAF_NODE: 
            return None 
        else: 
            return search(x.ptrs[i], k) 

    def search(self, k): 
        return search_node(self.get_root_id(), k)

    def update(self, key, val): 
        res = self.search(key) 
        if res: 
            node_id, offest = res
            x = self.get_node(node_id) 
            x.values[offset] = val 
            self.set_node(node_id, x) 
            return True 

        return False 
        
    def split_child(self, x_id, i): 
        '''split i-th child, which is full, of the given node 'x'. 
        ''' 
        x_id = node_id 
        x = self.get_node(x_id) 

        y_id = x.ptrs[i]
        z_id = self.alloc_node() 

        y = self.get_node(y_id) 
        z = self.get_node(z_id)

        z.set_status(y.status()) 
        z.set_key_num(self.order - 1) 

        # copy the last (order-1) keys of y to z. 
        z.set_records(y.records[-(self.order-1):])
        # copy the last (order) ptrs of y to z. 
        z.set_ptrs(y.ptrs[-(self.order):]) 
        # truncate node y 
        y.set_key_num(self.order - 1)  
        y.set_records(y.records[self.order-1:]) 
        y.set_ptrs(y.ptrs[self.order-1:]) 

        x.ptrs().insert(i + 1, zid) 
        x.keys().insert(i, y.keys()[self.order - 1]) 
        x.set_key_num(x.key_num() + 1) 

        map(set_node, [x_id, y_id, z_id], [x, y, z]) 

    def insert_nonfull(self, x_id, k, v): 
        x = self.get_node(x_id) 
        index = bisect_left(x.keys(), k) 
        if x.status() == LEAF_NODE: 
            x.keys().insert(index, k) 
            x.vals().insert(index, v) 
            x.ptrs().insert(index, NULL_NODE) 
            x.set_key_num(x.key_num() + 1) 
            self.set_node(x_id, x) 
        else: 
            c_id = x.ptrs()[i]
            c = self.get_node(c_id) 
            if c.key_num() == self.order*2 - 1: 
                self.split_child(x_id, i)
                # node x updated 
                x = self.get_node(x_id) 
                # check the newly added key 
                if k > x.keys()[i]: 
                    i += 1 

            # possibly updated 
            insert_nonfull(x.ptrs[i], k, v) 

    def insert(self, k, v): 
        r_id = self.get_root_id() 
        root = self.get_node(r_id) 
        if root.key_num == self.order*2 - 1: 
            n_id = self.alloc_node() 
            self.set_root(n_id) 
            new_root = self.get_node(n_id) 
            new_root.set_status(INTE_NODE) 
            new_root.set_key_num(0) 
            new_root.set_ptrs([r_id]) 
            map(set_node, [r_id, n_id], [root, new_root]) 

            split_child(n_id, 0) 
            insert_nonfull(n_id, k, v) 
        else: 
            insert_nonfull(r_id, k, v) 

    def delete(self): 
        pass 

