## This is a music visualizer

<p> Julia sets contain bounded solutions to the function <i>f(z) = z^2 + c</i>. This visualizer calculates parameters in real-time from the microphone signal and plots some interesting Julia sets. </p>

<p> Real-time calculation of Julia sets is slow, the Jupyter notebook contains Python code for generating interesting Julia sets (that are saved as images). The real-time processing is done with C++ in OpenFrameworks. Each <i> c </i> corresponding to a particular Julia set is represented as a node in a graph. Weighted graph traversal smoothly interpolates between similar sets based on the spectral flux of the incoming mic signal. </p>

<p> Some of these sets are visually beautiful, here is an example : 

https://user-images.githubusercontent.com/18227419/146802800-50d70a61-037b-4ca0-9571-1305fde129b1.mov
</p>

