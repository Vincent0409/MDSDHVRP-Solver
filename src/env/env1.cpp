//
// Created by Mark van der Broek on 03/03/2017.
//

#include "env.ih"

Env::Env(Init &init)
        :
        d_distanceMatrix(init.getDistanceMatrix()),
        d_bestSolution(Solution{this}),
        d_currentSolution(Solution{this}),
        d_newSolution(Solution{this})
{
    vector<vector<double>> depotMatrix      (init.getDepotMatrix());
    vector<vector<double>> vehicleMatrix    (init.getVehicleMatrix());
    vector<vector<double>> customerMatrix   (init.getCustomerMatrix());

    int vehicleIdx = 0;
    for (int depot = 0; depot != init.getNoOfDepots(); ++depot)
    {
        Depot depotToAdd{this, depot, depotMatrix[depot][3]};
        // Add vehicles to depot.
        for (int vehicleType = 4; vehicleType != depotMatrix[depot].size(); ++vehicleType)
        {
            for (int noOfVehicles = 0; noOfVehicles != depotMatrix[depot][vehicleType]; ++noOfVehicles)
            {
                depotToAdd.addVehicle(Vehicle{this,
                                              vehicleIdx,
                                              static_cast<int>(vehicleMatrix[vehicleType-4][0]),
                                              depot,
                                              vehicleMatrix[vehicleType-4][1],
                                              vehicleMatrix[vehicleType-4][2],
                                              vehicleMatrix[vehicleType-4][3],
                                              vehicleMatrix[vehicleType-4][4]});
                ++vehicleIdx;
            }
        }
        d_currentSolution.addDepot(depotToAdd);
    }

    for (int customer = 0; customer != init.getNoOfCustomers(); ++customer)
    {
        Customer customerToAdd{this, customer, customerMatrix[customer][3], customerMatrix[customer][4]};
        d_currentSolution.addCustomer(customerToAdd);
    }
}