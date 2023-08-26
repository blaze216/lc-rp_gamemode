enum SPEEDCAM_INFO
{
    sc_id,
    sc_object,
    sc_speed,
    sc_name[32],
    Float:sc_x,
    Float:sc_y,
    Float:sc_z,
    Float:sc_rx,
    Float:sc_ry,
    Float:sc_rz,
    sc_int,
    sc_vw,
    
    sc_areaid
};
new speedcam[MAX_SPEEDCAMS][SPEEDCAM_INFO],
    Iterator:speedcamObjects<MAX_SPEEDCAMS>;