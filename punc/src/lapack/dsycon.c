/* ./src_f77/dsycon.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int dsycon_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *ipiv, doublereal *anorm, doublereal *rcond, doublereal *
	work, integer *iwork, integer *info, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;

    /* Local variables */
    static integer i__, kase;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static logical upper;
    extern /* Subroutine */ int dlacon_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *, integer *), xerbla_(char *, integer *, 
	    ftnlen);
    static doublereal ainvnm;
    extern /* Subroutine */ int dsytrs_(char *, integer *, integer *, 
	    doublereal *, integer *, integer *, doublereal *, integer *, 
	    integer *, ftnlen);


/*  -- LAPACK routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     March 31, 1993 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DSYCON estimates the reciprocal of the condition number (in the */
/*  1-norm) of a real symmetric matrix A using the factorization */
/*  A = U*D*U**T or A = L*D*L**T computed by DSYTRF. */

/*  An estimate is obtained for norm(inv(A)), and the reciprocal of the */
/*  condition number is computed as RCOND = 1 / (ANORM * norm(inv(A))). */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies whether the details of the factorization are stored */
/*          as an upper or lower triangular matrix. */
/*          = 'U':  Upper triangular, form is A = U*D*U**T; */
/*          = 'L':  Lower triangular, form is A = L*D*L**T. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The block diagonal matrix D and the multipliers used to */
/*          obtain the factor U or L as computed by DSYTRF. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  IPIV    (input) INTEGER array, dimension (N) */
/*          Details of the interchanges and the block structure of D */
/*          as determined by DSYTRF. */

/*  ANORM   (input) DOUBLE PRECISION */
/*          The 1-norm of the original matrix A. */

/*  RCOND   (output) DOUBLE PRECISION */
/*          The reciprocal of the condition number of the matrix A, */
/*          computed as RCOND = 1/(ANORM * AINVNM), where AINVNM is an */
/*          estimate of the 1-norm of inv(A) computed in this routine. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (2*N) */

/*  IWORK    (workspace) INTEGER array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
    --work;
    --iwork;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U", (ftnlen)1, (ftnlen)1);
    if (! upper && ! lsame_(uplo, "L", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -4;
    } else if (*anorm < 0.) {
	*info = -6;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DSYCON", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    *rcond = 0.;
    if (*n == 0) {
	*rcond = 1.;
	return 0;
    } else if (*anorm <= 0.) {
	return 0;
    }

/*     Check that the diagonal matrix D is nonsingular. */

    if (upper) {

/*        Upper triangular storage: examine D from bottom to top */

	for (i__ = *n; i__ >= 1; --i__) {
	    if (ipiv[i__] > 0 && a[i__ + i__ * a_dim1] == 0.) {
		return 0;
	    }
/* L10: */
	}
    } else {

/*        Lower triangular storage: examine D from top to bottom. */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (ipiv[i__] > 0 && a[i__ + i__ * a_dim1] == 0.) {
		return 0;
	    }
/* L20: */
	}
    }

/*     Estimate the 1-norm of the inverse. */

    kase = 0;
L30:
    dlacon_(n, &work[*n + 1], &work[1], &iwork[1], &ainvnm, &kase);
    if (kase != 0) {

/*        Multiply by inv(L*D*L') or inv(U*D*U'). */

	dsytrs_(uplo, n, &c__1, &a[a_offset], lda, &ipiv[1], &work[1], n, 
		info, (ftnlen)1);
	goto L30;
    }

/*     Compute the estimate of the reciprocal condition number. */

    if (ainvnm != 0.) {
	*rcond = 1. / ainvnm / *anorm;
    }

    return 0;

/*     End of DSYCON */

} /* dsycon_ */

