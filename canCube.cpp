#include canCube.h

canCube::canCube(CAN* can, uint8_t ADDR){
    //init cube
    this -> moduleAddr = ADDR;
    this -> cal = CANCUBE_DEF_CAL;
    this -> cubeCan = can;
    cubeCan -> frequency(250000);
}//canCube

cube_status_t canCube::pump(bool dir, bool enable){
    //create can message ID
    uint32_t canId = (CUBE_DEV_TYPE << 17)|(this -> moduleAddr << 11)|(CUBE_PUMP_STATE_ID)|(enable << 2)|(dir << 1);
    
    //send command
    if (!cubeCan -> write(CANMessage(canId, "\0", 1, CANData, CANExtended))){
        this -> canReset();

        return CUBE_TX_ERROR;
    }//if (!cubeCan -> write(CANMessage(canId, "\0", 1, CANData, CANExtended)))

    return CUBE_OK;
}//pump

cube_status_t canCube::stop(){
    return this -> pump(CUBE_DIR_LEFT, CUBE_STOP);
}//stop

cube_status_t canCube::pumpV(bool dir, float vol){
    cube_status_t status;

    //start pump
    status = this -> pump(dir, CUBE_START);
    if(status) return CUBE_TX_ERROR;

    //pump specified volume
    ThisThread::sleep_for((long)((vol + this -> tubeV) * (this -> cal)));

    //flush tube
    status = this -> pump(!dir, CUBE_START);
    if(status) return CUBE_TX_ERROR;

    ThisThread::sleep_for((long)((5 + this -> tubeV) * (this -> cal)));

    //stop pump
    status = this -> stop();
    if(status) return CUBE_TX_ERROR;

    return CUBE_OK;
}//pumpV

cube_status_t canCube::calibrate(bool dir){
    cube_status_t status;

    status = this -> pump(dir, CUBE_START);
    if(status) return CUBE_TX_ERROR;

    ThisThread::sleep_for(10000);

    status = this -> stop();
    if(status) return CUBE_TX_ERROR;

    return CUBE_OK;
}//calibrate

void canCube::setCalibration(float val){
    this -> cal = (unsigned long)(cal * (10 / val));
}//setCalibration

cube_status_t canCube::getVIP() {
    //TODO
    return CUBE_ERR;
}//getVIP

cube_status_t canCube::getTemperature() {
    //TODO
    return CUBE_ERR;
}//getVIP

void canCube::setTubeV(float vol){
    this -> tubeV = vol;
}//setTubeV

void canCube::CanReset(){
    cubeCan -> mode(CAN::Reset);
    cubeCan -> mode(CAN::Normal);
}//canReset