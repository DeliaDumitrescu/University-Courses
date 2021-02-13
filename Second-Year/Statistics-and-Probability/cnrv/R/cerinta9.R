# Cerinta 9

#' @export
cdfFromPDF <- function(f, lowerBound){
  res = function(x){
    if ( x < lowerBound ){
      return (0)
    }
    integrate(f, lower=lowerBound, upper = x) $ value
  }
  class(res) <- "CDF"
  return(res)
}

#' Uniform 0-1 number to CDF-based number
#'
#' @param CDF A CDF
#' @param num A number
#' @return The number \code{num} mapped according to the \code{CDF}
#' @examples
#' utocdf(f, 0.3)
#' uto(f, 0.2)
utocdf <- function ( CDF, num ){
  uniroot( function(y) {CDF(y) - num}, c(0.5, 1), extendInt="yes") $ root
}

# Random Generator based on CDF
#' @export
RGCDF <- function (CDF, quantity){
  nums <- runif(quantity)
  sapply(nums, function(x) { utocdf(CDF, x) } )
}

#TEST :

#f <- function(x){
#  sigma = 2
#  miu = 10
#  ( 1 / ( sigma * sqrt(2 * pi))) * exp( (-1/2) * (( x - miu) / sigma ) ^2)
#}

#a = cdfFromPDF(f, -Inf)

#plot(RGCDF(a,10000))
