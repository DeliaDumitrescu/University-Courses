# Dispersia se noteaza cu Var(x)
# si e egala cu E(x^2) - E^2(x), unde
# E(x) = int(-Inf, +Inf) x * f(x)
# si E(x^2) = int(-Inf, +Inf) x ^ 2 * f(x)

#' @export
get_dispersion <- function (f)
{
  # interior sunt variabilele care urmeaza a fi
  # adaugate in integrale
  # E(x)
  interiorEx <- function (x) { return (x * f(x)) }
  # E(x^2)
  interiorEx2 <- function (x) { return (x ^ 2 * f(x)) }

  part1 <- integrate(interiorEx, -Inf, +Inf) $ value

  part1final <- part1 * part1

  part2 <- integrate(interiorEx2, -Inf, +Inf) $ value

  return (sqrt(part2 - part1final))
}

# Media se noteaza cu E(x)
# aceasta se calculeaza realizand
# int(-Inf, +Inf) x * f(x)

f <- function (x)
{
  sigma <- 4
  miu <- 2
  1/(sigma * sqrt(2 * pi)) * exp((-1/2) * ((x - miu) / sigma) ^ 2)
}

#' @export
get_mean <- function (f)
{
  interior <- function (x) { return (x * f(x)) }

  integrate(interior, -Inf, +Inf) $ value
}

# momentul centrat de ordin r al v.a. X
# = E((X - E(X)) ^ r), unde
# E((X - E(X)) ^ r) = int(-Inf, +Inf) (x-media) ^ r * f(x)

#' @export
get_central_moment <- function (f, r)
{
  m <- get_mean(f)

  interior1 <- function (x) { return ((x - m) ^ r) }

  interior2 <- function (x) { return (interior1(x) * f(x)) }

  tryCatch (

    (integrate(interior2, -Inf, +Inf)) $ value,

    error = function (e) { print("Error calculating central moment")}
  )
}

# momentul initial de ordin r al v.a. X
# mr = E(x^r), unde E(x^r) = Int(-inf, +inf) x^r*f(x)

# Avem ca parametri functia noastra f si ordinul r
#' @export
get_initial_moment <- function (f, r)
{
  interior <- function (x) { return (x ^ r * f(x)) }

  tryCatch (

    (integrate(interior, -Inf, +Inf)) $ value,

    error = function (e) { print("Error calculating inital moment") }
  )
}
