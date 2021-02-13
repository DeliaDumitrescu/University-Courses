# calcularea unei constante de normalizare k
# se realizeaza determinand inversul valorii integralei functiei pe R

#' @export
normalizing_constant <- function (f)
{
  tryCatch (
    (1/(integrate(f, -Inf, +Inf) $ value)),

    error = function (e) { print("Can't determine normalizing constant") }
  )
}


#g <- function (x)
#{
#  f(x) / 50
#}


#normalizing_constant(g)
