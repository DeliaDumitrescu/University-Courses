#' @export
mean_and_disp <- function(g){
  pdf_func <- function(x){dnorm(x, 1, 2)}

  #media
  prod <- function(x) { g(x) * pdf_func(x) }
  mean <- integrate(Vectorize(prod), lower = -Inf, upper = Inf)
  print("Mean")
  print(mean)

  #media2 = E(h[x]^2) - media^2
  prod2 <- function(x) { g(x) * g(x) * pdf_func(x) }
  mean2 <- integrate(Vectorize(prod2), lower = -Inf, upper = Inf)
  dispersion <- mean2$value - (mean$value)*(mean$value)
  print("Dispersion")
  print(dispersion)
}

#g <- function(x) {2*x+3}
#mean_and_disp(g)
