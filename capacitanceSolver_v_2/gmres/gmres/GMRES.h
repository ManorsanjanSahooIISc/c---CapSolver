#ifndef GMRES_H_
#define GMRES_H_
#pragma once
#include <cmath>
#include <vector>


template <class Approximation, class Double>
void Update
(Double **H, Approximation *x, Double *s, std::vector<Approximation> *v, int dimension){
	int lupe;
	for (lupe = dimension; lupe >= 0; --lupe)
	{
		s[lupe] = s[lupe] / H[lupe][lupe];
		for (int innerLupe = lupe - 1; innerLupe >= 0; --innerLupe)
		{
			s[innerLupe] -= s[lupe] * H[innerLupe][lupe];
		}
	}
	typename std::vector<Approximation>::iterator ptr = v->begin();
	for (lupe = 0; lupe <= dimension; lupe++)
		*x += (*ptr++) * s[lupe];
}

template<class Operation, class Approximation, class Preconditioner, class Double>
int GMRES
(Operation* linearization, Approximation* solution,Approximation* rhs, Preconditioner* precond, int krylovDimension, int numberRestarts, Double tolerance)
{
	Double **H = ArrayUtils<Double>::twotensor(krylovDimension + 1, krylovDimension);

	Double **givens = ArrayUtils<Double>::twotensor(krylovDimension + 1, 2);

	Double *s = ArrayUtils<Double>::onetensor(krylovDimension + 1);

	std::vector<Approximation> V(krylovDimension + 1,
		Approximation(solution->getN()));
	Approximation residual = precond->solve((*rhs) - (*linearization)*(*solution));
	Double rho = residual.norm();
	Double normRHS = rhs->norm();

	int totalRestarts = 0;

	if (normRHS < 1.0E-5)
		normRHS = 1.0;

	int iteration = 1;
	while ((--numberRestarts >= 0) && (rho > tolerance*normRHS))
	{
		V[0] = residual * (1.0 / rho);

		for (int lupe = 0;lupe <= krylovDimension;++lupe)
			s[lupe] = 0.0;
		s[0] = rho;

		for (iteration = 0;iteration<krylovDimension;++iteration)
		{
			V[iteration + 1] = precond->solve((*linearization)*V[iteration]);

			int row;
			typename std::vector<Approximation>::iterator ptr = V.begin();
			for (row = 0;row <= iteration;++row)
			{
				H[row][iteration] = Approximation::dot(V[iteration + 1], *ptr);
				//subtract H[row][iteration]*V[row] from the current vector
				V[iteration + 1].axpy(&(*ptr++), -H[row][iteration]);
			}

			H[iteration + 1][iteration] = V[iteration + 1].norm();
			V[iteration + 1] *= (1.0 / H[iteration + 1][iteration]);

			double tmp;
			for (row = 0; row < iteration; row++)
			{
				tmp = givens[row][0] * H[row][iteration] +
					givens[row][1] * H[row + 1][iteration];
				H[row + 1][iteration] = -givens[row][1] * H[row][iteration]
					+ givens[row][0] * H[row + 1][iteration];
				H[row][iteration] = tmp;
			}

			if (H[iteration + 1][iteration] == 0.0)
			{
				givens[iteration][0] = 1.0;
				givens[iteration][1] = 0.0;
			}
			else if (fabs(H[iteration + 1][iteration]) > fabs(H[iteration][iteration]))
			{
				tmp = H[iteration][iteration] / H[iteration + 1][iteration];
				givens[iteration][1] = 1.0 / sqrt(1.0 + tmp*tmp);
				givens[iteration][0] = tmp*givens[iteration][1];
			}
			else
			{
				tmp = H[iteration + 1][iteration] / H[iteration][iteration];
				givens[iteration][0] = 1.0 / sqrt(1.0 + tmp*tmp);
				givens[iteration][1] = tmp*givens[iteration][0];
			}
			tmp = givens[iteration][0] * H[iteration][iteration] +
				givens[iteration][1] * H[iteration + 1][iteration];
			H[iteration + 1][iteration] = -givens[iteration][1] * H[iteration][iteration] +
				givens[iteration][0] * H[iteration + 1][iteration];
			H[iteration][iteration] = tmp;

			tmp = givens[iteration][0] * s[iteration] + givens[iteration][1] * s[iteration + 1];
			s[iteration + 1] = -givens[iteration][1] * s[iteration] + givens[iteration][1] * s[iteration + 1];
			s[iteration] = tmp;

			rho = fabs(s[iteration + 1]);
			if (rho < tolerance*normRHS)
			{
				Update(H, solution, s, &V, iteration);
				ArrayUtils<double>::deltwotensor(givens);
				ArrayUtils<double>::deltwotensor(H);
				ArrayUtils<double>::delonetensor(s);
				return(iteration + totalRestarts*krylovDimension);
			}

		} 
		totalRestarts += 1;
		Update(H, solution, s, &V, iteration - 1);
		residual = precond->solve((*linearization)*(*solution) - (*rhs));
		rho = residual.norm();

	} 
	ArrayUtils<double>::deltwotensor(givens);
	ArrayUtils<double>::deltwotensor(H);
	ArrayUtils<double>::delonetensor(s);

	if (rho < tolerance*normRHS)
		return(iteration + totalRestarts*krylovDimension);

	return(0);
}
#endif // !GMRES_H_