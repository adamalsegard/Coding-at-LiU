knearest=function(data,k,newdata) {
  
  n1=dim(data)[1]
  n2=dim(newdata)[1]
  p=dim(data)[2]
  Prob=numeric(n2)
  
  # Step i
  X=as.matrix(data[,-p])
  X_labels=c(data[,p])
  X_hat=X/matrix(sqrt(rowSums(X^2)), nrow=n1, ncol=p-1)

  # Step ii
  Y=as.matrix(newdata[,-p])
  Y_hat=Y/matrix(sqrt(rowSums(Y^2)), nrow=n2, ncol=p-1)
  
  # Step iii
  C=X_hat %*% t(Y_hat)
  
  # Step iv
  D=1.0-C
  
  for (i in 1:n2 ){
    # Use the distance matrix to find which observations are the nearest neighbors to case #i
    NN=head(order(D[,i]), k)
    
    # Derive probability value 'Prob[i]' by using the target values of the nearest neighbours 
    Prob[i]=mean(X_labels[NN])
  }
  return(Prob)
}

# Compute a confusion matrix
confusion_matrix = function(X_prob, X_answer, divider){
  X_prob=replace(X_prob, X_prob <= divider, 0)
  X_prob=replace(X_prob, X_prob > divider, 1)
  return(table(X_prob, X_answer))
}

# Compute ROC values
ROC=function(Y_ans, Y_fit, plot_values){
  m=length(plot_values)
  TPR=numeric(m)
  FPR=numeric(m)
  for(i in 1:m){
    conf_mat = confusion_matrix(Y_fit, Y_ans, plot_values[i]) # Alt 1
    #conf_mat = table(Y_fit>plot_values[i], Y_ans) # Alt 2
    #conf_mat = [[TN, FN], -> col1 = N- (TP+FN) 
    #            [FP, TP]] -> col2 = N+ (FP+TN)
    TPR[i] = conf_mat[2,2] / sum(conf_mat[,2]) # Spam=1 -> positives!
    FPR[i] = conf_mat[2,1] / sum(conf_mat[,1])
  }
  return (list(TPR=TPR,FPR=FPR))
}

# LAB 1, Ex 1: K-NN
setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab1")
data <- read.csv("./spambase.csv")

# Divide data with random seed
n = dim(data)[1]
set.seed(12345)
id = sample(1:n, floor(n*0.5))
train = data[id,]
test = data[-id,]

# Store answers to test data
test_ans = c(test[,49])
train_ans = c(train[,49])
nTest = length(test_ans)
divider = 0.5

# Task 3: K=5, classify test and training data
K=5
test_classified1 = knearest(train, K, test)
conf_mat1 = confusion_matrix(test_classified1, test_ans, divider)
missed1 = 1 - sum(diag(conf_mat1))/nTest

train_classified1 = knearest(train, K, train)
conf_mat_train1 = confusion_matrix(train_classified1, train_ans, divider)
missedTrain1 = 1 - sum(diag(conf_mat_train1))/nTest

# Task 4: K=1, classify test and training data
K=1
test_classified2 = knearest(train, K, test)
conf_mat2 = confusion_matrix(test_classified2, test_ans, divider)
missed2 = 1 - sum(diag(conf_mat2))/nTest

train_classified2 = knearest(train, K, train)
conf_mat_train2 = confusion_matrix(train_classified2, train_ans, divider)
missedTrain2 = 1 - sum(diag(conf_mat_train2))/nTest

# Task 5: Use kknn() with K=5, classify test data only
library(kknn)
test_classified3 = kknn(Spam~., train, test, k=5)
test_pred3 = predict(test_classified3) 
conf_mat3 = confusion_matrix(test_pred3, test_ans, divider)
missed3 = 1 - sum(diag(conf_mat3))/nTest

# Task 6: Use knearest() & kknn() with K=5 for pi = {0.05, 0.95, 0.05}
pi_values = seq(0.05, 0.95, 0.05)
fitMan = knearest(train, 5, test)
fitAuto = predict(kknn(Spam~., train, test, k=5))

# Compute TPR & FPR for ROC curves
ROC_Man = ROC(test_ans, fitMan, pi_values)
ROC_Auto = ROC(test_ans, fitAuto, pi_values)

# Compute sensitivity and specificity values for the 2 methods
sensitivity_Man = ROC_Man[[1]] # a.k.a recall
specificity_Man = 1 - ROC_Man[[2]]
sens_Auto = ROC_Auto[[1]]
spec_Auto = 1 - ROC_Auto[[2]]
#precision = TP / (TP+FP)

# Plot corresponding curves 
plot(spec_Auto, sens_Auto, xlim=c(0.0, 1.0), ylim=c(0.0, 1.0), col="blue", type="b", main="Comparison K-NN functions", xlab = "FPR", ylab = "TPR")
points(specificity_Man, sensitivity_Man, col="red", type="b")

# Plot TPR-FPR
plot(ROC_Auto[[2]], ROC_Auto[[1]], xlim=c(0.0, 0.95), ylim=c(0.0, 0.95), col="blue", type="b", main="Comparison K-NN functions", xlab = "FPR", ylab = "TPR")
points(ROC_Man[[2]], ROC_Man[[1]], col="red", type="b")
legend("bottomright", lty=c(1,1), col=c("red","blue"), legend = c("knearest()", "kknn()"))

