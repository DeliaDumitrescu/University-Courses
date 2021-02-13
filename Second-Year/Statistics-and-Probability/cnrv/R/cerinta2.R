# O functie f este pdf daca f(x) > 0 pt orice x si integrala pe R din f = 1

#' @export
test_with_min <- function(f, lower, upper) {
  lower <- max(lower, -1000)
  upper <- min(upper, 1000)
  min_val <- 1e9
  for (i in seq(lower, upper, 1e-2))
    min_val <- min(min_val, f(i))
  return (min_val >= 0)
}

#' @export
test_with_integrate <- function(f, left, right) {
  for (i in 1:100){
    l <- runif (1, left, left + (right-left)/2)
    r <- runif (1, (right-left)/2, right)
    res <- integrate(Vectorize(f), l, r)
    if(res$value < 0){
      print(res$value)
      return (FALSE)
    }
  }
  return (TRUE)
}

#' @export
isPdf <- function (f, lower, upper, test_positive) {
  tryCatch(
    {
      i <- integrate(Vectorize(f), -Inf, Inf)
      #Daca eroare integrarii e mai mare ca 1e-5, atunci integrala nu este = 1
      if(abs(i$value - 1) > 1e-5)
        return (FALSE)
      else {
        #Daca am ajuns aici, integrala a fost buna si testam pozitivitatea
        left = lower;
        if(lower == -Inf)
          left = -1e9;
        right = upper;
        if(upper == Inf)
          right = 1e9;

        return (test_positive(f, left, right))

      }
    },
    error = function(cond) {
      #Daca am ajuns aici, a existat o problema la integrare si deci integrala nu este = 1
      message(paste("Error: ", cond))
      return (FALSE)
    }
  )
}




# a e pdf
a <- function(x) {
  if(x > 0)
    return (exp(-x))
  else
    return (0)
}
#isPdf(a, -Inf, Inf, test_with_integrate)

# b nu e pdf
b <- function(x) {
  return (exp(x^2))
}
#isPdf(b, 0, Inf, test_with_positive)

#isPdf(tan, -Inf, Inf, test_with_integrate)
#isPdf(exp, -Inf, Inf, test_with_integrate)


