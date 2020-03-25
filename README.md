#DeepSample
Audio Processing Project

Audio samples are clips of instrument(s) copied from another song, usually manipulated by changing tempo or speed to 
support or enhance the creation of a new unique song.  Professional music creators sample music by obtaining the sample 
from the original producer by influence and networking.  More amatueur music creators, such as up and coming artists,
often crop raw audio from a song to add to their own.  While an efficient method, cropping raw audio leads to background 
noise from failure to isolate specific instument(s) the user is focused on.  This research will focus on two key components
(a) the comparison of efficiency between four audio segmentation algorithms and (b) the creation of an application "Deep Sample"
that will isolate audio with artificial neural networking methods.  The basis of this research is influence by Fawad Hussain's
Optimized Audio Classificatoin and Segmentation Algorithm by Using Ensemble Methods.

Week of Jan 25 2020

Hue and I developed the main idea of DeepSample, and began searching for research papers
to base our work on.  

Week of Feb 1 2020

Hue created the first draft of our abstract, and I found a paper to base our work on.
I proceeded to email the authors and try to obtain their source.  

Week of Feb 8 2020

Hue finished creating the beginnings of the user interface for DeepSample, I failed to 
receive a response from the author of the research paper, so we decided to proceed 
without the original source.  Hue recommended looking at cepstrum signal analysis, and I 
found several papers using this algorithm and algorithms related to it.  We are planning to 
use these as the basis of our research.

Week of Feb 15 2020

- Created a working implementation of the zero-crossing algorithm.  
- Added a file describing the algorithms we are targeting, and began a works cited list for use in the final paper.

Week of Feb 22 2020

- Began the implementation of the spectrum flux and cepstrum algorithms.   
- Created a skeleton for the ANN to be completed this week. 

Week of Feb 29 2020

- Implemented printing of results for both debugging purposes and for sending to the neural network.
- Generated text file of audio wave using the libsnd library.
- Split the audio signal to left and right channels, stored them in vector for use by algorithms.
- Added working implementation of spectrum flux algorithm.
- Created utility library to abstract away some of the workflow from the driver programs. 
- Implemented cepstrum and complex cepstrum algorithms
- 

Week of March 7 2020
TO DO:  
- Update ANN to process data from the audio segmentation algorithms
- Research graph design
- Look into 2D FFT
- Create one build where all algorithms compile

Week of March 14 2020
-  Started implementation of ANN, using a naive bayesian algorithm
-  Changed audio input to allow vorbis format
-  Worked on improving efficiency of Fourier transforms
-  Worked on implementation of cepstrum algorithm.

Week of March 21 2020
- Finished initial implementation of ANN
- Changed help to reflect how to run the program.  Just type ./DeepSample without any arguments
- Started downloading public domain music for training ANNI.
- Fixed problem with spectral flux with zero magnitude distances.
- Wrote a small driver program for creating training databases for ANNI.

Week of March 28 2020
- Added a plotting function to the utilities
- Edited SampleGenerator to enable plotting as it goes
- Created a developer manual for using the program.

TO DO
- Add a working version of cepstrum algorithm to DeepSample
- Download files for training ANNI
- Start training ANNI
- Make a powerpoint deck explaining the process for use in presentations
- Start rough draft of paper for project
CREEPER AW MAN
