# HW3-4 Version 1
# 
# Implement the Rabin Miller test for primality
#

from hw3_4_util import mod_exp
from random import randrange

def rabin_miller(n, target=128):
    """returns True if prob(`n` is composite) <= 2**(-`target`)"""
    ###############
    ## Start your code here
    def calculate_t(n):
        t = 0
        n = n-1
        while n%2 == 0:
            n = n/2
            t = t+1
        return t
    if n%2 == 0:
        return False
    t = calculate_t(n)
    s = (n-1)/2**t
    tried = set()
    n_tests = target / 2 + 1
    for i in range(n_tests):
        while True:
            a = radrange(1,n)
            if a not in tried:
                tried.add(a)
                break
        if mod_exp(a,s,n) == 1:
            continue
        found = False
        for j in range(0,t):
            if mod_exp(a,2**j*s,n) == n-1:
                found = True
                break
        if not found:
            return False       
    return True
    ## End of your code
    ###############


