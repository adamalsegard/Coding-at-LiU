# LAB 1, Ex 4: Linear regression and regularization
#setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab1")
data <- read.csv("./tecator.csv")

# Task 1: Plot Moisture vs Protein
plot(data$Moisture, data$Protein, xlab="Moisture", ylab="Protein")

# Task 2: Find a probabilistic model Mi

# Task 3: Linear Regression: Fit Mi, i = [1:6]
# Divide into Train and Test data
n = dim(data)[1]
set.seed(12345)
id = sample(1:n, floor(n*0.5))
train = data[id,]
test = data[-id,]

nr_models = 6
train_error = numeric(nr_models)
test_error = numeric(nr_models)
avg_error = numeric(nr_models)

for(i in 1:nr_models) {
  Mi = lm(Moisture ~ poly(Protein, i), data = train)
  pred_train = predict(Mi, train)
  pred_test = predict(Mi, test)
  
  train_error[i] = mean((train$Moisture - pred_train)^2) # = mean(Mi$residuals^2)
  test_error[i] = mean((test$Moisture - pred_test)^2)
  avg_error[i] = (train_error[i]+test_error[i])/2
}

I = seq(1, nr_models)
plot(I, train_error, col="blue", type="b", xlab="i", ylab="MSE", main="Mean Square Errors", ylim=c(31, 35))
points(I, test_error, col="red",type="b")
legend("right", lty=c(1,1), col=c("blue", "red"), legend = c("Train data", "Test data"))
#points(I, avg_error, col="green", type="b")


# Task 4: Variable selection with stepAIC
library(MASS)
model_VS = lm(Fat ~ .-(Protein+Sample+Moisture), data=data) # Formula: Fat vs All channels
step = stepAIC(model_VS, direction="both", trace=FALSE)
nr_vars = length(step$coefficients)-1 # -1 because "(Intercept)" 
summary(step)
plot(model_VS, xvar="lambda")
mean(model_VS$residuals^2)
pred_VS = predict(model_VS, test)
mean((test$Fat - pred_VS)^2)
mean(step$residuals^2)
mean((data$Fat - step$fitted.values)^2)

# Task 5: Ridge regression
library(glmnet)
covariates = scale(data[, 2:101]) # All Channels
response = scale(data$Fat) # Only Fat
model_RR = glmnet(as.matrix(covariates), response, alpha=0, family="gaussian")
plot(model_RR, xvar="lambda", main="Ridge Regression")

# Task 6: LASSO
# Same but with alpha=1
model_LASSO = glmnet(as.matrix(covariates), response, alpha=1, family="gaussian")
plot(model_LASSO, xvar="lambda", main="LASSO")

# Task 7: Choose best model with cross-validation
myLambda = seq(0.00, 3, 0.01)
model_CV=cv.glmnet(as.matrix(covariates), response, alpha=1, family="gaussian", lambda=myLambda)
model_CV$lambda.min
plot(model_CV, main="Cross-validation")
length(coef(model_CV, s="lambda.min"))-1
sum(coef(model_CV, s="lambda.min") != 0)

cv.fit$cvm[cv.fit$lambda == cv.fit$lambda.min]

# Task 8: Compare results form step 4 and 7