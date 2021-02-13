# Cerinta 7

#' Converts a function to a package-compatible function
#'
#' @param f A function
#' @return The function bound to the class PDF
#' @export
#' @examples
#' a <- CV(f)
#' b <- CV(g)
CV <- function( f ){
  res <- f
  class(res) <- "PDF"
  return (res)
}

#' @export
outputCV <- function(number){
  res <- list()
  res $ value <- number
  class(res) <- "CVResult"
  return (res)
}

#' @export
"<.PDF" <- function(X, x){
  probability <- integrate(X, lower=-Inf, upper = x) $ value
  ret = list()
  ret $ value = probability
  ret $ interval = c(-Inf,x)
  ret $ func = X
  class(ret) <- "CVCond"

  return (ret)
}


#' @export
">.PDF" <- function(X, x){
  probability <- integrate(X, lower=x, upper = +Inf) $ value
  ret = list()
  ret $ value = probability
  ret $ interval = c(x, +Inf)
  ret $ func = X
  class(ret) <- "CVCond"

  return (ret)
}

#' @export
opposing <- function( int1, int2 ){
  if ( int1[1] == -Inf && int2[2] == +Inf )
    return (TRUE)
  if ( int1[2] == +Inf && int2[1] == -Inf )
    return (TRUE)
  return(FALSE)
}

#' @export
intersection <- function ( int1, int2 ){
  if ( int1[2] <= int2[1] )
    return ( c (0,0) )
  if ( int2[2] <= int1[1] )
    return ( c (0,0) )

  if ( int1[1] < int2[1] && int2[2] < int1[2] )
    return ( c ( int2[1], int2[2] ) )

  if ( int2[1] < int1[1] && int1[2] < int2[2] )
    return ( c ( int1[1], int1[2] ) )

  if ( int1[2] >= int2[1] && int2[1] < int1[1] && int1[2] > int2[2] )
    return ( c ( int1[1], int2[2] ) )
  if ( int2[2] >= int1[1] && int1[1] < int2[1] && int2[2] > int1[2] )
    return ( c ( int2[1], int1[2] ) )

  if( int1[2] == Inf && int2[2] == Inf ){
    return ( c ( max(int1[1],int2[1]), Inf ) )
  }
  if (int1[1] == -Inf && int1[1] == -Inf){
    return ( c (-Inf, min (int1[2], int2[2]) ) )
  }
}

#' @export
intersects <- function ( int1, int2 ){
  if ( int1[2] <= int2[1] )
    return (FALSE)
  if ( int2[2] <= int1[1] )
    return (FALSE)

  return (TRUE)
}

#' @export
"|.CVCond" <- function(vec1, vec2) {
  v1 = vec1 $ value
  v2 = vec2 $ value

  if (!(  identical( vec1 $ func, vec2 $ func ) ) ){
    noquote("Different PDF functions used")
  }

  int1 = vec1 $ interval
  int2 = vec2 $ interval

  if ( opposing( int1, int2 ) ){
    # opposing things like ( f > 90 ) | ( f < 100 )
    if ( intersects( int1, int2 ) ){
      newinterval = intersection(int1,int2)
      integration = integrate( vec1 $ func ,
                               lower=newinterval[1],
                               upper = newinterval[2]) $ value
      return ( outputCV( min ( integration / v2, 1 ) ) )
    } else { # things like ( f < 10 ) | ( f > 100 )
      return ( outputCV(0) )
    }
  }
  else { # things like ( f > 110 ) | (f> 90)

    if ( v2 == 0 ){
      noquote("Cannot divide by 0")
      return (undefined)
    }

    res = v1 / v2

    return ( outputCV ( min(res, 1) ) )
  }
}

#' @export
"%AND%" <- function(vec1, vec2) {
  v1 = vec1 $ value
  v2 = vec2 $ value

  if (!(  identical( vec1 $ func, vec2 $ func ) ) ){
    noquote("Different PDF functions used")
  }

  int1 = vec1 $ interval
  int2 = vec2 $ interval

  if ( intersects( int1, int2 ) ){
    newinterval = intersection(int1,int2)
    integration = integrate( vec1 $ func ,
                             lower = newinterval[1],
                             upper = newinterval[2])
    return (outputCV( integration $ value))
  } else { # things like ( f < 10 ) | ( f > 100 )
    return (outputCV(0))
  }
}

#' Calculates the probability for certain conditions
#'
#' @param cvRes A condition
#' @return The probability as a number
#' @export
#' @examples
#' f <- CV(X)
#' P ( f > 110 )
#' P ( f < 110 )
#' P ( ( f < 99 ) | ( f < 100 ) )
#' P ( ( f > 90 ) %AND% ( f < 110 ) )
P <- function ( cvRes ) {
  print( cvRes $ value )
}


# TEST:

#X <- function(x){
#  sigma = 5
#  miu = 100
#  ( 1 / ( sigma * sqrt(2 * pi))) * exp( (-1/2) * (( x - miu) / sigma ) ^2)
#}

#f <- CV(X)
#P ( f > 110 )
#P ( f < 110 )
#P ( ( f < 99 ) | ( f < 100 ) )
#P ( ( f > 90 ) %AND% ( f < 110 ) )

