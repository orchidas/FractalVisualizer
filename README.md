## This is a fractal music visualizer

<p> Julia sets contain bounded solutions to the function f(z) = z^2 + c. This visualizer calculates parameters in real-time from the microphone signals and plots some interesting Julia sets. </p>

<p> Real-time calculation of Julia sets is slow, the Jupyter notebook contains Python code for generating interesting Julia sets (that are saved as images). The real-time processing is done with C++ in OpenFrameworks. Each c corresponding to a particular Julia set is represented as a node in a graph. Weighted graph traversal smoothly interpolates between similar sets based on the spectral flux of the incoming mic signal. </p>

<p> Some of these sets are visually beautiful </p>

<center>
<video width="320" height="240" controls>
  <source src="demo/fractals.mov" type="video/mp4">
</video>
</center>
