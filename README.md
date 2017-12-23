# BitTorrent Traffic Detection with Deep Flow Inspection
## 1. What is Deep Flow Inspection(DFI)?
As the name implies, the analysis or the classification of P2P traffic is a flow-based, focusing on the connection level patterns of P2P applications. Thus, it does not require any payload analysis, unlike DPI. Because it doesn’t require payload analysis, encrypted data packets can be easily supported. The down side of this approach is that there is an additional step of extracting the connection level pattern for the P2P traffics. And yet, there is no rule of thumb for which network feature should be used in this method. 
## 2. Proposed System
### 2.1 Training Module

** Figure 1: Proposed system to classify BT packet flows **
### 2.2
#### 2.2.1 Ground truth generation
The ground truth is the packet flows with known classes. In order to train a classifier, there are two types of packet flows needed to capture, namely the BT and non-BT packet flows. To capture the BT packets, I manually force the BT client to use a single TCP port (i.e. 1200) for data transfer. Thus, all the BT traffic must go through thisTCP port. Then, I start a sample torrent file and the BT client will automatically start downloading/uploading the contents. At the same time, I start my packet capturing program to obtain the packets.Similarly, to capture non-BT packets, I start my packet capturing program while we were creating non-BT network activities including HTTP,FTP and SSH. With the known class of the packets in the PCAP files, I could start training the classifier.    
#### 2.2.2  Study of DFI classifier accuracy 

** Figure 2: Classifier accuracy with different training samples **
Figure 2 shows the classifier accuracy with increasing number of BT packet flows used to train the classifier. The classifier was first trained with a set of BT samples, and then it was tested against with some otherBT packet flows to observe the accuracy. This experiment gives us some clues about the number of packet flows should be used in order train a reliable classifier for the DFI module.As expected, the moreBT packets are used to train the classifier, the better the accuracy is. However, as the number of the BT packets increase, the classifier will be saturated at some point.  After that, even more packets is provided, the accuracy does not increase significantly.   




