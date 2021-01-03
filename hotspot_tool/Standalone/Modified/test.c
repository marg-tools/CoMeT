#include "flp.h"
#include "temperature.h"

int do_detailed_3D = 1;

int main() 
{

    char *flp_file, *power_file;
    char *init_temp_file, *steady_temp_file;

    flp_t *flp;
    RC_model_t *model;
    thermal_config_t config;
    double *power, *temp;
    /* transient simulation for 1 ms    */
    double delta_t = 0.001;

    flp = read_flp(flp_file, FALSE);
    config = default_thermal_config();
    model = alloc_RC_model(&config, flp, do_detailed_3D);
    temp = hotspot_vector(model);
    power = hotspot_vector(model);

    read_power(model, power, power_file);
    read_temp(model, temp, init_temp_file, FALSE);

    populate_R_model(model, flp);
    populate_C_model(model, flp);

    /* transient solver    */
    compute_temp(model, power, temp, delta_t);
    /* steady state solver    */
    steady_state_temp(model, power, temp);

    dump_temp(model, temp, steady_temp_file);

    delete_RC_model(model);
    free_flp(flp, FALSE);
    free_dvector(temp);
    free_dvector(power);

    return 0;
}