# Assignment 3: Uncertainty estimation

# Read data
setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab2")
data <- read.csv("./State.csv", sep=";", dec=",")

# Task 1: Order data wrt MET and plot EXvsMET
ordered_data = data[order(data$MET),]
plot(ordered_data$MET, ordered_data$EX, xlab="MET", ylab="EX", main="EX vs MET")


# Task 2: Fit a regression tree model
library(tree)
n = dim(ordered_data)[1]
fit = tree(EX~MET, data=ordered_data, control=tree.control(n, minsize=8))

# Use cross-validation
set.seed(12345)
cv.res = cv.tree(fit)
plot(cv.res$size, cv.res$dev, type="b", col="red", main="Cross-validation", xlab="#leaves", ylab="Residuals")
#plot(log(cv.res$k), cv.res$dev, type="b", col="red")

# Best tree = 3 leaves
finalTree = prune.tree(fit, best=3)
plot(finalTree, main="Regression best tree model")
text(finalTree, pretty=0)

pred_data = predict(finalTree, newdata=ordered_data)

plot(ordered_data$MET, ordered_data$EX, xlab="MET", ylab="EX", col="red", main="Original vs. Fitted")
points(ordered_data$MET, pred_data, col="blue")
legend("top", pch=c(1,1), col=c("red", "blue"), legend=c("Original", "Fitted"))

# Plot residuals 
tree_residuals = ordered_data$EX-pred_data
hist(tree_residuals, xlab="Residuals", main="Histrogram of residuals")


# Task 3: Compute non-parametric bootstrap
# Computing bootstrap samples
bootFunc = function(inData, ind){
  dataBoot = inData[ind,] # extract bootstrap sample
  fittedTree = tree(EX~MET, data=dataBoot, control=tree.control(n, minsize=8)) # fit linear model

  prunedTree = prune.tree(fittedTree, best=3)
  #predict values from the original data
  pred = predict(prunedTree, newdata=ordered_data)
  return(pred)
}

library(boot)
boot_result = boot(ordered_data, statistic=bootFunc, R=1500) # Make bootstrap
plot(boot_result)

# Compute non-parametric confidence bands
env_NonPar = envelope(boot_result, level=0.95)

plot(ordered_data$MET, ordered_data$EX, pch=21, xlab="MET", 
     ylab="EX", col="red", main="Non-parametric bootstrap")
points(ordered_data$MET, pred_data, col="blue", type="b")
legend("top", pch=c(1,1), col=c("red", "blue"), legend=c("Original", "Fitted"))

#plot cofidence bands
points(ordered_data$MET, env_NonPar$point[2,], type="l", col="green")
points(ordered_data$MET, env_NonPar$point[1,], type="l", col="green")


# Task 4: Compute parametric bootstrap
mle=tree(EX~MET, data=ordered_data, control=tree.control(n, minsize=8))

bootParFunc = function(inData){
  fittedTree = tree(EX~MET, data=inData, control=tree.control(n, minsize=8))
  prunedTree = prune.tree(fittedTree, best=3)
  #predict values from the original data
  pred = predict(prunedTree, newdata=inData)
  return(pred)
}

# Generate random parameters
rng = function(inData, inModel) {
  dataRNG = data.frame(MET=inData$MET, EX=inData$EX)
  #generate new data
  n = length(inData$EX)
  predRNG = predict(inModel, newdata=dataRNG)
  dataRNG$EX = rnorm(n, predRNG, sd(inData$EX-predRNG))
  return(dataRNG)
}
boot_par_res = boot(ordered_data, statistic=bootParFunc, R=2000, mle=mle, ran.gen=rng, sim="parametric")
plot(boot_par_res)

# Compute non-parametric confidence bands
env_Par = envelope(boot_par_res, level=0.95)

plot(ordered_data$MET, ordered_data$EX, pch=21, xlab="MET", 
     ylab="EX", col="red", ylim=c(140, 460), main="Parametric bootstrap")
points(ordered_data$MET, pred_data, col="blue", type="b")

#plot cofidence bands
points(ordered_data$MET, env_Par$point[2,], type="l", col="green")
points(ordered_data$MET, env_Par$point[1,], type="l", col="green")

# Prediction boundaries
bootParPred = function(inData) {
  predictions = bootParFunc(inData)
  return(rnorm(n, predictions, sd(resid(mle))))
}

boot_Par_predict = boot(ordered_data, statistic=bootParPred, R=2000, mle=mle, ran.gen=rng, sim="parametric")
env_Par_pred = envelope(boot_Par_predict, level=0.95)

#plot prediction bands
points(ordered_data$MET, env_Par_pred$point[2,], type="l", col="orange")
points(ordered_data$MET, env_Par_pred$point[1,], type="l", col="orange")
legend("top", lty=c(1,1), col=c("green", "orange"), legend=c("Conf. bands", "Pred. bands"))
