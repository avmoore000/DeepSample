Algorithms used by deep sample

1.  Zero-Crossing Rate

        Zero crossing rate is a measure of signal changes from positive to negative 
and vice versa (Zahid, 2.3.1).  This is the first algorithm we will be implementing
in our testing.

2.  Spectrum Flux

        Spectrum Flux is a measure of the changeable power spectrum of an audio 
signal (Zahid, 2.3.3).  It can be used to discrimate between speech, music and
enviromental sound (Zehid, 2.3.3), and we will be using it to help with the 
classification process.

3.  Mel-Frequency Cepstral Coefficients

        The cepstral algorithm is the logarithmic measure of the Mel magnitude 
spectrum (Zahid, 2.3.4).  They are mostly used to discriminte between voices in
speech recognition, and yield a weighted Mel-spectrum graph.  

4.  Artificial Neural Network (ANN)

        An artificial neural network will be trained using the data gained from 
the above algorithms, with the goal of identifying the type of music being input.
