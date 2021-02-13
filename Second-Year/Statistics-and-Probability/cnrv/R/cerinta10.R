#' @export
Mean <- function(f, a, b) {
  prod <- function(x) { return (x * f(x)) }
  m <- integrate(prod, a, b)
  return(m$value)
}

#' @export
marginal_x <- function(f, a, b) {
  return(Vectorize(function (y) {
    integrate(function(x) { f(x, y) }, a, b)$value
  }))
}

#' @export
marginal_y <- function(f, c, d) {
  return(Vectorize(function (x) {
    integrate(function(y) { f(x, y) }, c, d)$value
  }))
}

#' @export
common_mean_x <- function(f, a, b, c, d) {
  mcx <- integrate(function(x) {
    return(x*marginal_y(f, c, d)(x))
  }, a, b)
  return(mcx$value)
}

#' @export
common_mean_y <- function(f, a, b, c, d) {
  mcy <- integrate(function(y) {
    return(y*marginal_x(f, a, b)(y))
  }, c, d)
  return(mcy$value)
}

#' @export
double_integ <- function(f, a, b, c, d) {
  i <- integrate(Vectorize(function(y) {
    integrate(function(x) { f(x, y) }, a, b)$value
  }), c, d)
  return(i$value)
}

#' @export
varx <- function(f, a, b, c, d, mean) {
  i <- integrate(function(x) {
    return((x-mean)^2 * marginal_y(f, c, d)(x))
  }, a, b)
  return(i$value)
}

#' @export
vary <- function(f, a, b, c, d, mean) {
  i <- integrate(function(y) {
    return((y-mean)^2 * marginal_x(f, a, b)(y))
  }, c, d)
  return(i$value)
}

#' @export
Cov <- function(pdfcom, a, b, c, d, print = 1){
  #media in x
  meanx <- common_mean_x(pdfcom, a, b, c, d)
  #media in y
  meany <- common_mean_y(pdfcom, c, d, c, d)

  #covarianta
  InnerFun <- function(x, y) { return (x * y * pdfcom(x, y)) }
  covariance <- double_integ(InnerFun, a, b, c, d) - meanx*meany
  return(covariance)
  if(print == 1) {
    print(covariance)
  }
}

#' @export
Cor <- function(pdfcom, a, b, c, d) {
  #calculam covarianta
  covariance <- cov(pdfcom, a, b, c, d, 0)
  #media in x
  meanx <- common_mean_x(pdfcom, a, b, c, d)
  #media in y
  meany <- common_mean_y(pdfcom, c, d, c, d)

  #dispersiile
  dispx <- varx(pdfcom, a, b, c, d, meanx)
  dispy <- vary(pdfcom, a, b, c, d, meany)

  #deviatiile
  devf <- sqrt(dispx)
  devg <- sqrt(dispy)

  #corelatia
  correlation <- covariance / (devf*devg)
  print(correlation)
}
