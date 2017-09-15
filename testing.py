import subprocess
from os import system

tests = ['1','2','3','4','5','6','7','8c','8m','9c','9m','10','11','12','13']

for t in tests:
    system("g++ -std=c++14 -Werror -Wall test" + t + ".cpp")
    a = subprocess.getoutput("./a.out")
    b = subprocess.getoutput("cat result" + t + ".txt")
    print(a == b)
