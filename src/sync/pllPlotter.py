from ast import Str
from pylab import *

def line2complex(line):
    vals = line.split(',')
    if len(vals) == 2:
        return float(vals[0]) + 1j*float(vals[1])
    else:
        return None

def data2array(data):
    list = []
    for line in data:
        num = line2complex(line)
        if not (num is None):
            list.append(num)
        else:
            break    
    list = array(list)
    return list

def main():
    stripped = loadtxt('stripped.txt',dtype = str)
    vco = loadtxt('vco.txt',dtype = str)
    data = loadtxt('data.txt',dtype = str)
    fixed = loadtxt('fixed.txt',dtype = str)

    valuesstrip = data2array(stripped)
    valuesvco = data2array(vco)
    valuesdata = data2array(data)
    valuesfixed = data2array(fixed)


    figure()
    plot(valuesstrip)
    plot(valuesvco)
    legend(('stripped', 'vco'))

    figure()
    subplot(2,1,1)
    plot(valuesdata)
    subplot(2,1,2)
    plot(valuesfixed)

    show()


if __name__ == '__main__':
    main()
