# Assignment 2: Analysis of credit scoring

# Task 1: Read data
#setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab2")
data <- read.csv("./creditscoring.csv")

# Divide data with random seed: [50/25/25]
n = dim(data)[1]
set.seed(12345)
id = sample(1:n, floor(n*0.5))
train = data[id,]       # 50%
secondPart = data[-id,] # 50%
m = dim(secondPart)[1]
id = sample(1:m, floor(m*0.5))
validation = secondPart[id,] # 25%
test = secondPart[-id,]      # 25%


# Task 2: Fit a decision tree using different measures of impurity
library(tree)
treeModel = tree(good_bad~., data=train, split=c("deviance")) 
# "deviance" is better than "gini"
plot(treeModel)
text(treeModel, pretty=0)
summary(treeModel)

# Predict test data (tree: deviance)
pred_test = predict(treeModel, newdata=test, type="class")
conf_mat1 = table(test$good_bad, pred_test)
missed1 = 1 - sum(diag(conf_mat1))/sum(conf_mat1)

# Predict train data (tree: deviance)
pred_train = predict(treeModel, newdata=train, type="class")
conf_mat2 = table(train$good_bad, pred_train)
missed2 = 1 - sum(diag(conf_mat2))/sum(conf_mat2)


# Task 3: Choose optimal tree
# With Cross-validation
#set.seed(12345)
#cv.res = cv.tree(treeModel)
#plot(cv.res$size, cv.res$dev, type="b", col="red")
#plot(log(cv.res$k), cv.res$dev, type="b", col="red")

# With train and validation
depth = 15 # Check using all predictors
trainScore = numeric(depth)
validScore = numeric(depth)
for(i in 2:depth) {
  prunedTree = prune.tree(treeModel,best=i)
  pred_val = predict(prunedTree, newdata=validation, type="tree")
  trainScore[i]=deviance(prunedTree)
  validScore[i]=deviance(pred_val)
}
plot(2:depth, trainScore[2:depth], xlab="#leaves", 
     ylab="Deviance", type="b", col="red", ylim=c(250,600))
points(2:depth, validScore[2:depth], type="b", col="blue")
legend("topright", pch=c(1,1), col=c("red", "blue"), legend=c("Train", "Valid."))

# Best tree is given by 4 leaves
bestTree = prune.tree(treeModel,best=4)
plot(bestTree, main="Optimal tree")
text(bestTree, pretty=0)
summary(bestTree)

# Predict test data (Best tree)
pred_best_test = predict(bestTree, newdata=test, type="class")
conf_matBest = table(test$good_bad, pred_best_test)
missedBest = 1 - sum(diag(conf_matBest))/sum(conf_matBest)


# Task 4: Classify with Naive Bayes
library(MASS)
library(e1071)

bayesModel = naiveBayes(good_bad~., data=train)

# Predict test data (Bayes)
pred_test_bayes = predict(bayesModel, newdata=test, type="class")
conf_mat3 = table(test$good_bad, pred_test_bayes)
missed3 = 1 - sum(diag(conf_mat3))/sum(conf_mat3)

# Predict train data (Bayes)
pred_train_bayes = predict(bayesModel, newdata=train, type="class")
conf_mat4 = table(train$good_bad, pred_train_bayes)
missed4 = 1 - sum(diag(conf_mat4))/sum(conf_mat4)


# Task 5: Repeat Naive Bayes for anothe Loss matrix
bayesModel2 = naiveBayes(good_bad~., data=train)
#LossMat = matrix(c(0, 10, 1, 0), 2, 2)

# Predict test data (Bayes new Loss)
pred_test_bayes2 = predict(bayesModel2, newdata=test, type="raw")
pred_test_bayes2[, 1] = pred_test_bayes2[, 1]*10 # Scale "bad" with 10 
pred_test_bayes2 = ifelse(pred_test_bayes2[,1] < pred_test_bayes2[,2], "good", "bad")

conf_mat5 = table(test$good_bad, pred_test_bayes2)
missed5 = 1 - sum(diag(conf_mat5))/sum(conf_mat5)

# Predict train data (Bayes new Loss)
pred_train_bayes2 = predict(bayesModel2, newdata=train, type="raw")
pred_train_bayes2[, 1] = pred_train_bayes2[, 1]*10 # Scale "bad" with 10 
pred_train_bayes2 = ifelse(pred_train_bayes2[,1] < pred_train_bayes2[,2], "good", "bad")

conf_mat6 = table(train$good_bad, pred_train_bayes2)
missed6 = 1 - sum(diag(conf_mat6))/sum(conf_mat6)
