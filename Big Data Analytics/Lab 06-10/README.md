## Lab Description
Objective of each Lab is to build models from real world data sets and conduct evaluations of different data mining algorithms

### Algorithms Used
* C4.5
* RIPPER
* Id3
* k-Nearest Neighbor
* Naive Bayesian Classification
* Neural Networks

### Dataset
These labs use several datasets
* Lymphography dataset - Describes 148 patients with 19 attributes
* Monks-3 - 7 nominal attributes that's labelled
* Credit Card Application Approval - 690 Customers with 16 attributes
* Ecoli Database
* Glass Identification Database
* Image Segmentation Database

### Lab Schedule

| Lab Number |Description |Algorithms Used   |
| ------------ | ------------ | ------------ |
|Lab 1 | Use classification algorithms to create a model on the the lymphography dataset |<ul><li>C4.5</li><li>RIPPER</li></ul> |
|Lab 2 | Use classification algorithms on the monks-3 dataset and report the classification accuracy and confusion matrix |<ul><li>C4.5</li><li>Id3</li><li>RIPPER</li><li>k-Nearest Neighbor</li><li>Naive Bayesian Classification</li><li>Neural Networks</li></ul> |
|Lab 3 | Using the Credit Card Application Approval data split the dataset into a training set (70%) and a test set (30%) and use algorithms to create a classification model |<ul><li>C4.5</li><li>Naive</li><li>Neural Networks</li></ul> |
|Lab 4 | Conduct a 10-fold cross validation on the following datasets <ul><li>Ecoli database</li><li>Glass Identification Database</li><li>Image Segmentation Database</li></ul>  |<ul><li>C4.5</li><li>RIPPER</li><li>Naive Bayesian Classification</li><li>k-Nearest Neighbor</li><li>Neural Networks</li></ul> |
|Lab 5 | Detailed Results of Labs 1 - 4 |Final Report |


## Algorithm Description
### J.48 (C.45) Algorithm
The J48 Algorithm (C4.5 algorithm) generates a pruned or unpruned decision tree classifier  that’s authored by Ross Quinlan. The Decision Tree is made by using a set of data used specifically for training. Based, on the data it will create a decision tree using information entropy similar to the ID3 (Iterative Dichotomiser 3) Algorithm. 

### JRIP Algorithm 
The JRIP Algorithm (RIPPER Algorithm) is a supervised rule learning algorithm. It’s an optimized version of IREP++. Since JRIP is an optimized version of IREP++ it inherits its learning concept known as the propositional rule learner. In essence, the proposition rule learning concept will develop an algorithm strictly for the set of positive examples and no negative examples. The JRIP algorithm goes through several stages which is listed below:

### IBk Algorithm
The IBk algorithm is a K-nearest neighbor classifier that selects the appropriate value of K using cross-validation. The algorithm is used for classification and regression and is a lazy learning algorithm. This means that it will approximate our function and will delay its computation until classification.

### NaïveBayes Algorithm
The NaïveBayes algorithm is a simple probabilistic classifier. This means that the algorithm is classifying the inputs. The algorithm uses probability to filter such input. It makes use of Bayes’ Theorem which adjusts the probability for each event as new input is entered the algorithm.

### Multilater Perceptron Algorithm
The Multilayer Perceptron (MLP) is a supervised learning algorithm that uses a technique known as backpropagation for training. It uses backpropagation to calculate the weights to be used in the function and is used to distinguish data that is unable to be separable linearly. 