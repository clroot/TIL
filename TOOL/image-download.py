import sys
from urllib import request

target_list = [line.strip() for line in sys.stdin]

for idx, target in enumerate(target_list):
    target_name = target.split("/")[-1]
    print(idx, target_name)
    request.urlretrieve(target, str(idx) + "_" + target_name)
