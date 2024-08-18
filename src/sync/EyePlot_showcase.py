#Brandon Nieman Eye Diagram Plotter showcase for SCRUM only - For use in ECE6710 Class Project
from matplotlib import pyplot as plt #For plotting
import numpy as np                   #For math


def main():
      t = np.linspace(-np.pi, np.pi, 200)
      #making a bunch of different signals to mimic BPSK for demonstration
      ys = [np.random.normal(1, .05) *0.5* np.sin(np.random.normal(1, .01) * t + np.random.normal(0, .15)) +0.5
            for i in range(0, 1000)]
      yd = [np.random.normal(1, .05) *0.5* np.sin(-np.random.normal(1, .01) * t + np.random.normal(0, .15)) +0.5
            for i in range(0, 1000)]
      yup = [np.random.normal(1, .1) * 0.05* np.sin(np.random.normal(1, .1) * t + np.random.normal(0, 1))+1
            for i in range(0, 300)]
      ydown = [np.random.normal(1, .1) * 0.05 * -np.sin(np.random.normal(1, .1) * t + np.random.normal(0, 1))
            for i in range(0, 300)]
      yhist = ys + yd + yup + ydown

      #Plotting mimiced BPSK signals
      fig, axs = plt.subplots(nrows=2, sharex=True)
      axs[0].plot(t, np.array(yhist).T, color='crimson', alpha=.1, lw=.1)
      axs[1].hist2d(np.tile(t, len(yhist)), np.ravel(yhist), bins=(200, 50), cmap='jet')


      plt.show()

if __name__ == '__main__':
      main()