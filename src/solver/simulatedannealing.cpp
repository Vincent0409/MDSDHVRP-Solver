//
// Created by Mark van der Broek on 10/03/2017.
//

/**
 * @brief Simulated annealing procedure to select new current solution.
 *
 * @param [in] sPrime   New current solution
 * @param [in] s        Old current solution
 *
 * @return Solution to assign as new old current solution
 */

#include "solver.ih"

Solution &Solver::simulatedAnnealing(Solution &sPrime, Solution &s)
{
    d_env->d_temp = d_env->d_temp * d_env->d_r;
    if (sPrime.totalCost() <= s.totalCost())
    {
        return sPrime;
    }
    else
    {
        double diff = sPrime.totalCost() - s.totalCost();
        uniform_real_distribution<double> uni(0.0, 1.0);

        double U(uni(d_env->d_rng));
        if (U < exp(-diff/d_env->d_temp))
        {
            return sPrime;
        }
        else
        {
            return s;
        }
    }
}