w
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
- Hue Truong
	- Implementation of Fourier Transform algorithm
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

TO DO:  
	- Update ANN to process data from the audio segmentation algorithms
	- Research graph design
	- Look into 2D FFT
	- Create one build where all algorithms compile

03/08/2020 - 03/14/2020

- Andrew Moore
	-  Started implementation of ANN, using a naive bayesian algorithm
	-  Changed audio input to allow vorbis format
- Hue Truong
	- Worked on improving efficiency of Fourier transform
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
	- Working on hamming window algorithm, a precursor of the cepstrum algorithm

- Alex Reno
	- Optimizing code

04/05/2020 - 04/11/2020

Assigned Tasks (04/05/2020 - 04/11/2020)

-  Hue Truong 
	- Working on cepstrum algorithm and optimizing spectral flux

-  Alex Reno
	- Working on Spectrum centroid algorithm

-  Andrew Moore
	- Creating sample database and training ANN using the samples.

Completed Tasks (04/05/2020 - 04/11/2020)

- Andrew Moore
	- Fixed a problem with sample generation, wrote a small driver program to generate samples.
	- Reworked sample generation to use less memory when running.
	- Changed sample generation and test functions to use new SpectrumFlux functions/vectors.
	- Fixed the plotter to display large graphs properly.
	- Generated sample plots and uploaded them in an archive to the repo (Plots.zip).
	- Updated the README.md file to reflect what is being done / was done by each person during the project.

- Alex Reno
	- Mostly implemented Spectrum Centroid [added to this file retroactively as of April 20]

04/12/2020 - 04/18/2020

Completed Tasks

- Andrew Moore
	- Altered spectrumFlux to use the FFT properly.
	- Worked on adding FFT support to ANNI
	- Started testing ANN Learning Vector Quantization function
	- Started generating samples using the updated FFT code, so the graphs will be correct.
	- Enabled plotting for all existing algorithms.
	- Updated the Developer Handbook to reflect current codebase.

04/19/2020 - 04/25/2020

Completed Tasks

- Alex Reno
	- Figured out what part of Spectral Centroid I didn't understand
	- Finished implementing SpectrumCentroid
	- Implemented the test for Spectrum Centroid

- Andrew Moore
	- Started rough draft of research paper
	- Reworked abstract 
	- Wrote introduction for research paper
	- Wrote the background for zero crossing, spectral flux, and Deep Sample in research paper.
	- Created block diagram for general audio segmentation algorithm and placed in introduction section of paper.
	- Created block diagram for Deep Sample and placed in introduction section of paper.
	- Updated user manual with spectrum centroid documentation.
	- Updated Makefile to include spectrumCentroid in the build.

- Hue Truong
	- Revised statistical testing procedures for algorithm comparisons.
	- Revised statistical testing procedures for DeepSample accuracy.
	- Updated research paper

4/26/2020 - 5/2/2020

Completed Tasks

-  Andrew Moore
	- Research Big-O analysis for analyzing algorithm performance.
	- Enabled plotting / sample generation using the Real Cepstrum and Spectrum Centroid implementations provided by Hue and Alex.
	- Finished ANN implementation.
	- Added methods for Zero Cross, Spectrum Flux and the ANN to research paper.	
	- Fixed a bunch of errors with the databases, they were not formating or saving properly
	- Added all of the function documentation to the development manual.
	- Reorganized source code to better reflect the development documentation.
-  Hue Truong
	- Research Big-O analysis for analyzing algorithm performance.
	- Started sample generation with BadPanda library
	- Started sample generation with FreeMusic 2010 library
	- Started sample generation with FreeMusic 2011 library

5/3/2020 - 5/9/2020

Completed Tasks

-  Andrew Moore
	- Finished cleaning up ANN errors
	- Implemented a Fold object to take care of the ANN seg faulting with multiple samples.
	- Finished the final draft of the Developers Handbook
	- Started a powerpoint for the group presentation
	- Added slides to the power point:
		- Spectrum flux and zero cross background
		- Spectrum flux and zero cross methods
		- Spectrum flux and zero cross results
		- Deep Sample results
		- Deep sample match example
	- Finished Section 1, Section 2.2, Section 2.3, Section 3.2, Section 3.3, Section 3.6 and Section 4 of the research paper.
	- Regenerated graphs and put them in all sections of the research paper.
	- Created archive with all data used to create the research paper and placed in the repo, DeepSampleData.zip
	- Pushed the research paper to the repository, CS212DeepSample.pdf
-  Hue Truong
	- Due to time constraint, removed BadPanda library out of sample generation
	- Tested FreeMusic2010 samples against FreeMusic2011 samples (Refer to Training Sample 1 of research paper)
	- Tested FreeMusic2010 samples against FreeMusic2011 samples (Refer to Training Sample 2 of research paper)
	- Tested FreeMusic2010 samples against FreeMusic2011 samples (Refer to Training Sample 3 of research paper)
	- Final changes to research paper and presentation
-  Alex Reno
	- Finished Sections 2.4, 3.5, and 4.3 of the research paper
	- Fixed grammar and formatting errors in the research paper and improved wording in a few places
	- Added slides to the PowerPoint: Spectrum Centroid Background, Methods, and Results

