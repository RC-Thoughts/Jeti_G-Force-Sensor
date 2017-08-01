//
// This is the main loop where the work is done
//

// May the G-Force be with you
sensors_event_t event;
accel.getEvent(&event);

gX = (round(event.acceleration.x * 1.01972) / 10.0) - (xCalVal / 10);
gY = (round(event.acceleration.y * 1.01972) / 10.0) - (yCalVal / 10);
gZ = (round(event.acceleration.z * 1.01972) / 10.0) + (zCalVal / 10);
gX = gX * -1.0;
gY = gY * -1.0;

gXc = gX * 10;
gYc = gY * 10;
gZc = gZ * 10;

aPitch = atan2(event.acceleration.x, event.acceleration.z) * (180 / PI) - (pCalVal);
aRoll = atan2(event.acceleration.y, event.acceleration.z) * (180 / PI) - (rCalVal);
aPitch = (aPitch * -1);
aRoll = (aRoll * -1);
