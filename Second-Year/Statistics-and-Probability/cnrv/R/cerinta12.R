#' @export
Sum <- function(f, g) {
  function(h) (integrate(function(x) (f(x) * g(h-x)), -Inf, +Inf)$value)
}

#' @export
difference <- function(f, g) {
  function(h) (integrate(function(x) (f(x) * g(x-h)), -Inf, +Inf)$value)
}
