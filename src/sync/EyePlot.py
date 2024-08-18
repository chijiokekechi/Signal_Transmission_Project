#Brandon Nieman Eye Diagram Plotter - For use in ECE6710 Class Project
from matplotlib import pyplot as plt #For plotting
import numpy as np                   #For math
from pylab import *

def main():
      values = []
      #So this will be reading in continuously in real time system, 
      # is likely rest of code will need to be moved to work in real time
      while True:
            line = sys.stdin.readline()
            if not (line is None):
                  values.append(line)
            else:
                  break

      #Looking through signal to find how many samples it takes to 
      #pass through zero and counting it
      Count = 0
      unitInterval = 0
      for i in range(len(values)):
            if (i==0):
                  continue
            elif (values[i] <= 0 and values[i-1] >= 0):
                  Count+=1
            elif (values[i] >= 0 and values[i-1] <= 0):
                  Count+=1
            else:
                  continue
      #getting rough samples per symbol
      unitInterval = len(values)/Count

      unit = [0]
      ys = [0]
      #collecting each  rough unit interval seperately
      for l in range(Count):
            for k in range(unitInterval):
                  ys[k] = values[k+(l*unitInterval)]
            unit.append(ys)

      #Plotting two graphs for ease of viewing, both show same thing just in different ways
      t = np.linspace(-np.pi*2, np.pi*2, unitInterval)

      fig, axs = plt.subplots(nrows=2, sharex=True)
      axs[0].plot(t, np.array(unit).T, color='crimson', alpha=.1, lw=.1)
      axs[1].hist2d(np.tile(t, len(unit)), np.ravel(unit), bins=(500, 50), cmap='inferno')
      plt.show()



if __name__ == '__main__':
      main()
