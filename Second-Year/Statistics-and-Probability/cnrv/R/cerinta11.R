#' @export
pdfmX <- function(pdfcom, a, b, c, d) {
  function(x) {
    integrate(function(y) { pdfcom(x, y) }, c, d)$value
  }
}

#' @export
pdfmY <- function(pdfcom, a, b, c, d) {
  function(y) {
    integrate(function(x) { pdfcom(x, y) }, a, b)$value
  }
}
