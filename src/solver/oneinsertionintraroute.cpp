//
// Created by Mark van der Broek on 10/03/2017.
//

/**
 * @brief One insertion intra route operator. Pick a customer and place it in the best position in his route.
 *
 * @param [in] s    Solution
 */

#include "solver.ih"

void Solver::oneInsertionIntraRoute(Solution &s)
{
    for (Depot &depot: s.getDepots())
    {
        for (Vehicle &vehicle: depot.getVehicles())
        {
            int minCustomer = -1;
            int minDemand = -1;
            int minPos = -1;
            double minInsertion = numeric_limits<double>::max();

            for (int customerIdx = 1; customerIdx != vehicle.getRoute().getRoute().size() - 1; ++customerIdx)
            {
                int customerID = vehicle.getRoute().getRoute()[customerIdx];
                Vehicle newVehicle = vehicle;

                int customerDemand = newVehicle.removeCustomer(customerID);
                auto insertion = newVehicle.cheapestInsertion(customerID, false);

                if (insertion.second < minInsertion)
                {
                    minCustomer = customerID;
                    minDemand = customerDemand;
                    minPos = insertion.first;
                    minInsertion = insertion.second;
                }
            }
            if (minCustomer != -1)
            {
                vehicle.removeCustomer(minCustomer);
                vehicle.addCustomer(minCustomer, minDemand, minPos);
            }
        }
    }
}