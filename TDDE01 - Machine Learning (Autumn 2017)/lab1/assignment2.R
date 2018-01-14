# Calculate the log-likelihood
log_likelihood = function(x, theta) {
  distribution = theta*exp((-theta)*x)
  return(log(prod(distribution)))
}

l_func = function(x, theta, lambda) {
  distr = prod(theta*exp((-theta)*x))
  prior = exp((-lambda)*theta)
  return((log(distr*prior)))
}

# LAB 1, EX 2: Lifetime of Machines
setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab1")
data <- read.csv("./machines.csv")

# Task 2: Plot dependency curve of theta
theta = seq(0.0, 3.0, 0.01)
log_lh1 = sapply(theta, log_likelihood, x=data)
plot(theta, log_lh1, col="blue", ylim=c(-120,0), main="Comparison log-likelihood", xlab = "Theta", ylab = "Log-LH")
theta_max1 = theta[which(log_lh1==max(log_lh1))]

# Task 3: Plot curve of 6 first observations
nObs = 6
obs = head(data, nObs)
log_lh2 = sapply(theta, log_likelihood, x=obs)
points(theta, log_lh2, col="red")
theta_max2 = theta[which(log_lh2==max(log_lh2))]

# Task 4: Bayesian model with prior
l_theta = sapply(theta, l_func, x=data, lambda=10)
points(theta, l_theta, col="green")
theta_maxL = theta[which(l_theta==max(l_theta))]
legend("bottomright", lty=c(1,1), col=c("blue", "red", "green"), legend = c("All data", "First 6 obs.", "Bayesian"))

# Task 5: New observations
newObs = 50
set.seed(12345)
random_distr = rexp(newObs, rate=theta_max1)

yLabel = seq(0,6, 0.5)
p1 = hist(random_distr, breaks=yLabel, main="Random exponential distribution", xlab="Lifetime")
p2 = hist(data$Length, main="Machine lifetime", xlab="Lifetime")
plot( p1, col=rgb(0,0,1,1/4), xlim=c(0,6), main="Comparison exponential distributions", xlab="Lifetime")  # first histogram
plot( p2, col=rgb(1,0,0,1/2), xlim=c(0,6), add=T)  # second
legend("topright", lty=c(1,1), col=c("blue", "red"), legend = c("Generated data", "Original data"))