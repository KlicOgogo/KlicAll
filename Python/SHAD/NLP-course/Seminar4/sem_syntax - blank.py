from itertools import product
from collections import defaultdict

class CYKParser:
    def __init__(self, rules):
        assert(rules['PP'] == True)
        """
            `rules` - your grammar
        """
        
    
    ### SOME ADDITION FUNCTIONS IF YOU NEED IT
    ### END YOUR ADDITIONAL FUNCTIONS
    
    def parse(self, in_tokens):
        pass
        """
            `in_tokens` - input sentence
            return chain of rules in case of sentence can be parsed, empty list otherwise
        """
        ### YOUR CODE HERE
        ### END OF YOUR CODE

EX_1 = ['Shift', 'Shift', 'Left-Arc', 'Right-Arc', 'Right-Arc', 'Reduce', 'Reduce', 'Shift', 'Left-Arc', 'Left-Arc', 'Right-Arc', 
        'Right-Arc', 'Right-Arc', 'Shift', 'Left-Arc', 'Right-Arc', 'Right-Arc', 'Right-Arc', 'Reduce', 'Reduce', 'Right-Arc', 
        'Right-Arc', 'Reduce', 'Reduce', 'Reduce', 'Reduce', 'Reduce', 'Reduce']

EX_2 = ['Shift', 'Left-Arc', 'Right-Arc', 'Right-Arc', 'Shift', 'Left-Arc', 'Right-Arc', 'Shift', 'Shift', 'Left-Arc', 'Shift', 
       'Left-Arc', 'Left-Arc', 'Right-Arc', 'Reduce', 'Right-Arc', 'Right-Arc', 'Reduce', 'Reduce', 'Reduce', 'Reduce', 'Reduce']

EX_3 = None

chmo = CYKParser({'PP': ['chmo']})
