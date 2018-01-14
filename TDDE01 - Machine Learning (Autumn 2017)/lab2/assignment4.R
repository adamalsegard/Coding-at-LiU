# Assignment 4: Principal components

# Read data
#setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab2")
data_orig <- read.csv("./NIRSpectra.csv", sep=";", dec=",")

data_new = data_orig # Copy data for later use
data_new$Viscosity = c() # Remove vistosity column

# Task 1: Conduct a standard PCA
pca_res = prcomp(data_new)
lambda = pca_res$sdev^2 # eigenvalues

# Proportion of variance
sprintf("%2.3f",lambda/sum(lambda)*100)
screeplot(pca_res, main="Variation of each feature")

# First 2 values gives 99.6% 
#93.332+6.263

# Plot the scores in coordinates of PC1 & PC2
plot(pca_res$x[,1], pca_res$x[,2], main="Scores", ylim=c(-0.15, 0.15), xlab="PC1", ylab="PC2")
# Unusual diesel fueld: outliers to the right!


# Task 2: Make trace plots of loadings of first 2 components
U = pca_res$rotation
# Rotation is the matrix of variable loadings (i.e. columns contain eigenvectors)
plot(U[,1], main="Traceplot: PC1", ylab="Loadings", col="blue")
plot(U[,2], main="Traceplot: PC2", ylab="Loadings", col="red")
# Combine them
plot(U[,2], main="Traceplots PCA", ylab="Loadings", col="red")
points(U[,1], col="blue")
legend("topleft", pch=c(1,1), col=c("blue", "red"), legend=c("PC1", "PC2"))

# Task 3: Independent Component Analysis
library(fastICA)
set.seed(12345)

# Compute W' = K*W and present columns in W' in form of trace plots
a = fastICA(data_new, 2, alg.typ="parallel", fun="logcosh", alpha=1, method="R", 
            row.norm=FALSE, maxit=200, tol=0.0001, verbose=TRUE) #ICA
Wprim = a$K %*% a$W 

plot(Wprim[,1], main="Traceplot ICA, PC1", ylab="PC1", col="blue")
plot(Wprim[,2], main="Traceplot ICA, PC2", ylab="PC2", col="red")
# Combine them
plot(Wprim[,2], main="Traceplots ICA", ylab="W'", col="red")
points(Wprim[,1], col="blue")
legend("bottomleft", pch=c(1,1), col=c("blue", "red"), legend=c("IC1", "IC2"))

# Make plot of first 2 latent features
# S is the vector of latent variables (independent components)
plot(a$S[,1], a$S[,2], ylab="Latent feature 2", xlab="Latent feature 1", main="Scores of latent features of ICA")
# Mirrored around x=0 with regards to scores in step 1 


# Task 4: Fit a PCR model with cross-validation
library(pls)
fit = pcr(Viscosity~., data=data_orig, validation="CV")
validationplot(fit, val.type="MSEP", main="Viscosity of PCR (all comp)", legend="topright")
validationplot(fit, xlim=c(0, 10), val.type="MSEP", main="Viscosity of PCR", legend="topright")
