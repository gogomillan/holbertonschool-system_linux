#!/usr/bin/env python3
import re
maps_file = open("/proc/self/maps", 'r')
for line in maps_file.readlines():  # for each mapped region
    if re.match(r'^.*heap.*', line):
        print(line, end='')

        m = re.match(r'([0-9A-Fa-f]+)-([0-9A-Fa-f]+) ([-r]).+[heap].*', line)
        if m.group(3) == 'r':  # if this is a readable region
            start = int(m.group(1), 16)
            end = int(m.group(2), 16)
            print(start, end)
            mem_file = open("/proc/self/mem", 'r', start)
            mem_file.seek(start)  # seek to region start
            chunk = mem_file.read(1)  # read region contents
            mem_file.close()
    """
    print(m.group(1))
    print(m.group(2))
    print(m.group(3))
    print(m.string)
    print([item for item in m])
    if m.group(3) == 'r':  # if this is a readable region
        start = int(m.group(1), 16)
        end = int(m.group(2), 16)
        mem_file.seek(start)  # seek to region start
        chunk = mem_file.read(end - start)  # read region contents
        print(chunk)  # dump contents to standard output
    """
maps_file.close()
