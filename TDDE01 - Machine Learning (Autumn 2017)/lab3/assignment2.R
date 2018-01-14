# Assignment 2: Neural Networks

library(neuralnet)
set.seed(1234567890)

# Generate data
data = runif(50, 0, 10)
trainval = data.frame(Var=data, Sin=sin(data))
train = trainval[1:25,] # Training
val = trainval[26:50,] # Validation
mse = numeric(10)

# Random initialization of the weights in the interval [-1, 1]
weights = runif(31, -1, 1) # 2*10 connections, 10+1 bias terms

# Find the best threshold
for(i in 1:10) {
  th = i/1000
  nn = neuralnet(Sin~Var, data=train, hidden=10, threshold=th, startweights=weights)
  
  # Predict the validation data
  nnOut = compute(nn, val$Var)
  mse[i] = sum((val$Sin - nnOut$net.result)^2)/nrow(val)
}

# Plot MSE and choose the best neural net
plot(mse, main="Mean-square error", xlab="threshold (*1000)")
bestTH = which.min(mse)/1000
bestNN = neuralnet(Sin~Var, data=trainval, hidden=10, threshold=bestTH, startweights=weights)
plot(bestNN)

# Plot of the predictions (black dots) and the training data (red dots)
plot(prediction(bestNN)$rep1, main="Predictions of best NN")
points(trainval, col = "red")
