
import struct 
import logging 
import logging.config 

log_config = { 
        'version': 1, 
        'formatters': { 
            'standard': { 
                'format': '%(asctime)s [%(levelname)s] %(name)s: %(message)s' 
                }
            }, 
        'handlers': { 
            'file': { 
                'level': 'INFO', 
                'formatter': 'standard', 
                'class': 'logging.FileHandler', 
                'filename': 'btreelab.log', 
                'mode':'a' 
                }
            }, 
        'loggers': { 
            '': {
                'handlers': ['file'], 
                'level': 'INFO', 
                'propagate': True
                }
            }
        }

logging.config.dictConfig(log_config) 

def calc_order(block_size, meta_size, key_size, val_size):
    return 2 

class IntUtil(object): 

    packer = struct.Struct('i')

    @classmethod
    def size(cls): 
        return cls.packer.size 

    @classmethod
    def to_bytes(cls, num): 
        return cls.packer.pack(num)
    
    @classmethod 
    def from_bytes(cls, raw_bytes): 
        return cls.packer.unpack(raw_bytes) 

