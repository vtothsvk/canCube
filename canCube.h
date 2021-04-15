#ifndef CAN_CUBE_H_
#define CAN_CUBE_H_

#include "canCube_types.h"

/**
 * \defgroup driver-canCube
 * 
 * @brief modular peristaltic pump CAN module driver
 */

/**
 * \defgroup canCube class
 * \ingroup driver-canCube
 * @{
 */

/**
 * @brief canCube driver class
 */
class canCube{
public:
    /**
     * @brief Creates an instance of the driver and initialises the module
     * 
     * @param can   pointer to a CAN driver object
     * @param ADDR  modules CAN address
     */
    canCube(CAN* can, uint8_t ADDR = DEFAULT_CANCUBE_ADDR);

    /**
     * @brief Pump control method
     * 
     * @param dir       pumping direction
     * @param enable    state
     * 
     * @returns
     *      CUBE_OK on success
     *      cube_status error otherwise
     */
    cube_status_t pump(bool dir, bool enable);

    /**
     * @brief Pump volume
     * 
     * Uses pump control method and cube calibration to pump a specific volume
     * 
     * @param dir   pumping direction
     * @param vol   pumping volume
     * 
     * @returns
     *      CUBE_OK on success
     *      cube_status error otherwise
     */
    cube_status_t pumpV(bool dir, float vol);

    /**
     * @brief Pump stop method
     * 
     * Uses general pump control method to stop the pump
     * 
     * @returns
     *      CUBE_OK on success
     *      cube_status error otherwise
     */
    cube_status_t stop(void);

    /**
     * @brief Calibration method
     * 
     * Pumps for a defined amount of time, ressulting pumped out liquid volume is then used for calibration corrections
     * 
     * @param dir   pumping direction
     * 
     * @returns
     *      CUBE_OK on success
     *      cube_status error otherwise
     */
    cube_status_t calibrate(bool dir);

    /**
     * @brief Calibration correction
     * 
     * Used to correct the curently set pumping calibration constant
     * 
     * @param vol   volume pumped out using the canCube::calibrate method
     */
    void setCalibration(float val);

    /**
     * @brief Get input voltage, current and power
     * 
     * @returns
     *      CUBE_OK on success
     *      cube_status error otherwise
     */
    cube_status_t getVIP(void);

    /**
     * @brief Get module temperature
     * 
     * @returns
     *      CUBE_OK on success
     *      cube_status error otherwise
     */
    cube_status_t getTemperature(void);

    /**
     * @brief Set peristltic pump tube volume
     * 
     * @param vol   tube volume
     */
    void setTubeV(float vol);

private:
    /**
     * @brief CAN interface reset method
     */
    void CanReset(void);

    CAN* cubeCan;//CAN driver pointer
    float v, i, p;//last measured input current
    uint8_t moduleAddr;
    unsigned long cal;
    float tubeV;
};

/** @} */

#endif//CAN_CUBE_H_