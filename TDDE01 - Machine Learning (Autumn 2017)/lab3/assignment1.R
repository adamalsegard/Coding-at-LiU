# Assignment 1: Kernel methods
set.seed(1234567890)
library(geosphere)

# Read & merge the data
#setwd("/home/adam/Documents/MT5/TDDE01-Machine-Learning/lab3")
stations <- read.csv("./stations.csv")
temps <- read.csv("./temps50k.csv")
mergedData <- merge(stations, temps, by="station_number")

# Decide the width for the three kernels
h_distance = 80000 # 80 km, covering a part of Mid-East Sweden
# Using Nkpg: Min dist: 1.78k, Mean: 403k, Max:1.15M
h_date = 15 # x2 -> One month 
h_time = 3 # x2 -> 6 hours

# Set prediction point, date & time ("up to students"):  
# Use Nkpg's coordinates
lat = 58.586789 # Latitude
lon = 16.18 # Longitude
point =c(lon, lat) # This is the order distHaversine needs them in
date = "2013-07-20" 
times = c("04:00:00", "06:00:00", "08:00:00", "10:00:00",
          "12:00:00", "14:00:00", "16:00:00" , "18:00:00",
          "20:00:00", "22:00:00", "24:00:00")
n = length(times)
predTemp = matrix(nrow=n, ncol=2)

# Helper function
gaussian = function(x){
  return(exp(-(x^2)))
}

# Define the three kernels
# Kernel 1: Dist between stations and point of interest
distStation = function(poi, data_pos){
  # Use 'Haversine' great circle distance  
  dist = distHaversine(poi, data_pos)
  return(gaussian(dist/h_distance))
}

# Kernel 2: Dist between measured days and day of interest 
distDay = function(doi, data_date){
  dist = as.numeric(difftime(doi, data_date, units="days"))
  # Take into account that the year wraps around 
  # (i.e. the same date one year ago is actually the closest)
  filtDist = dist %% 365
  filtDist[filtDist > 183] = 365 - filtDist[filtDist > 183]
  return (gaussian(filtDist/h_date))
}
  
# Kernel 3: Dist between measured hours and hour of interest  
distHour = function(hoi, data_hour){
  dist = as.numeric(difftime(strptime(hoi, "%H:%M:%S"), 
        strptime(data_hour, "%H:%M:%S"), units="hours"))
  # Same wrap around here, but here we need absolute value
  dist = abs(dist)
  dist[dist > 12] = 24 - dist[dist > 12]
  return (gaussian(dist/h_time))
} 

# Calculate all kernels
calcKernels = function(inData, poi, doi, hoi){
  dataPos = inData[, c("longitude", "latitude")]
  
  # Calculate distance kernels
  station_dist = distStation(poi, dataPos)
  #plot(station_dist, main="Stations")
  date_dist = distDay(doi, inData$date)
  #plot(date_dist, main="Dates")
  hour_dist = distHour(hoi, inData$time)
  #plot( hour_dist, main="Hours")
  
  sumDist = station_dist + date_dist + hour_dist
  prodDist = station_dist * date_dist * hour_dist
  
  # Predict temp with (Gaussian) Kernel Regression
  sumTemp = sum(sumDist*inData$air_temperature)/sum(sumDist)
  prodTemp = sum(prodDist*inData$air_temperature)/sum(prodDist)
  return (c(sumTemp, prodTemp))
}

# Remove posterior dates
filteredData = mergedData[as.Date(mergedData$date) <= as.Date(date),] 

# Do the actual prediction
for(i in 1:n){
  predTemp[i,] = calcKernels(filteredData, point, date, times[i])
}

# Plot the predicted temperatures
hoursToPlot = seq(4, 24, 2)
plot(hoursToPlot, predTemp[,1], type="o", main="Summed kernels [2013-07-20]", ylab="Temp", xlab="hour")
plot(hoursToPlot, predTemp[,2], type="o", main="Multiplied kernels [2013-07-20]", ylab="Temp", xlab="hour")

#index = seq(-3, 3, 0.01)
#plot(index, gaussian(index), main="Gaussian kernel")
