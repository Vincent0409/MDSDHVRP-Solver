//
// Created by Mark van der Broek on 11/03/2017.
//

/**
 * @brief Perturbation operator to remove customers from the solution. Remove q customers from the solution where
 *        the gain of removing them is the highest.
 *
 * @param [in] solution Solution to remove the customers from
 * @param [in] q        Number of customers to delete
 *
 * @return Vector of customer IDs to remove
 */

#include "solver.ih"

vector<int> Solver::costRemoval(Solution &solution, int q)
{
    // Customerlist to be deleted
    vector<int> orderedCustomers(solution.getCustomers().size());
    iota(begin(orderedCustomers), end(orderedCustomers), 0);

    vector<double> gains(solution.getCustomers().size());
    uniform_real_distribution<double> uni(0.8, 1.2);

    for (size_t customerIdx = 0; customerIdx != solution.getCustomers().size(); ++customerIdx)
    {
        gains[customerIdx] = uni(d_env->d_rng) * computeRemovalGain(solution, customerIdx);

    }

    // Sort customers on descending gains
    sort(begin(orderedCustomers), end(orderedCustomers),
         [&](int lhs, int rhs)
         {
             return gains[lhs] > gains[rhs];
         });


    vector<int> customersToRemove{begin(orderedCustomers), begin(orderedCustomers) + q};
    removeCustomers(solution, customersToRemove);

    return customersToRemove;
}