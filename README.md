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

01/19/2020 - 01/25/2020

Hue and I developed the main idea of DeepSample, and began searching for research papers
to base our work on.  

01/26/2020 - 02/1/2020

Hue created the first draft of our abstract, and I found a paper to base our work on.
I proceeded to email the authors and try to obtain their source.  

02/02/2020 - 02/08/2020

Hue finished creating the beginnings of the user interface for DeepSample, I failed to 
receive a response from the author of the research paper, so we decided to proceed 
without the original source.  Hue recommended looking at cepstrum signal analysis, and I 
found several papers using this algorithm and algorithms related to it.  We are planning to 
use these as the basis of our research.

02/09/2020 - 02/15/2020

- Andrew Moore
	- Created a working implementation of the zero-crossing algorithm.  
	- Added a file describing the algorithms we are targeting, and began a works cited list for use in the final paper.

02/16/2020 - 02/22/2020

- Andrew Moore
	- Began the implementation of the spectrum flux and cepstrum algorithms.   
	- Created a skeleton for the ANN to be completed this week. 

02/23/2020 - 02/29/2020

- Andrew Moore
	- Implemented printing of results for both debugging purposes and for sending to the neural network.
	- Generated text file of audio wave using the libsnd library.
	- Split the audio signal to left and right channels, stored them in vector for use by algorithms.
	- Added working implementation of spectrum flux algorithm.
	- Created utility library to abstract away some of the workflow from the driver programs. 

- Hue Truong
	- Implemented cepstrum and complex cepstrum algorithms


03/01/2020 - 03/07/2020

- TO DO:  
	- Update ANN to process data from the audio segmentation algorithms
	- Research graph design
	- Look into 2D FFT
	- Create one build where all algorithms compile

03/08/2020 - 03/14/2020

- Andrew Moore
	-  Started implementation of ANN, using a naive bayesian algorithm
	-  Changed audio input to allow vorbis format
- Hue Truong
	- Worked on improving efficiency of Fourier transforms
	- Worked on implementation of cepstrum algorithm.

03/15/2020 - 03/21/2020

- Andrew Moore
	- Finished initial implementation of ANN
	- Changed help to reflect how to run the program.  Just type ./DeepSample without any arguments
	- Started downloading public domain music for training ANNI.
	- Fixed problem with spectral flux with zero magnitude distances.
	- Wrote a small driver program for creating training databases for ANNI.

03/22/2020 - 03/28/2020

- Andrew Moore
	- Added a plotting function to the utilities
	- Edited SampleGenerator to enable plotting as it goes
	- Created a developer manual for using the program.
	- Downloaded 107 OGG sample files from the Bad Panda collection at archive.org.  They are all creative commons.
	- Changed order of arguments passed to functions to be more consistent for easier development.  Updated dev manual to reflect the changes.

03/29/2020 - 04/04/2020

- Andrew Moore
	- Created an AudioWave object for ease of use.
	- Converted FFT to a more efficient model and altered to use the AudioWave object.
	- Added the resource for the new FFT to the works cited.
	- Altered the zeroCross function to use the AudioWave object.
	- Finished altering the codebase to use the AudioWave object.
	- Updated the dev manaul to reflect changes to the codebase.

- Hue Truong
	- Worked on cepstrum algorithm

- Alex Reno
	- Optimizing code

04/05/2020 - 04/11/2020

Assigned Tasks:
	-  Hue Truong 
		- Working on cepstrum algorithm and optimizing spectral flux

	-  Alex Reno
		- Working on Spectrum centroid algorithm

	-  Andrew Moore
		- Creating sample database and training ANN using the samples.

Completed Tasks
	- Andrew Moore
		- Fixed a problem with sample generation, wrote a small driver program to generate samples.
		- Reworked sample generation to use less memory when running.
		- Changed sample generation and test functions to use new SpectrumFlux functions/vectors.
		- Fixed the plotter to display large graphs properly.
		- Generated sample plots and uploaded them in an archive to the repo (Plots.zip).
		- Updated the README.md file to reflect what is being done / was done by each person during the project.

04/12/2020 - 04/18/2020


TO DO LIST

- Add a working version of cepstrum algorithm to DeepSample
- Start training ANNI
- Make a powerpoint deck explaining the process for use in presentations
- Start rough draft of paper for project
- Enable plotter across all algorithms.
