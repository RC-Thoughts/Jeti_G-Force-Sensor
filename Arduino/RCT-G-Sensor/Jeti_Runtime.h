//
// This is the main loop where the work is done
//

// May the G-Force be with you
sensors_event_t event;
accel.getEvent(&event);

gXc = (event.acceleration.x / 9.80665) - (xCalVal / 100);
gYc = (event.acceleration.y / 9.80665) + (yCalVal / 100);
gZc = (event.acceleration.z / 9.80665) + (zCalVal / 100);
gXc = gXc * -1.0;

gXr = round(gXc * pow(10, Ndec));
gYr = round(gYc * pow(10, Ndec));
gZr = round(gZc * pow(10, Ndec));

gXf = round(Xfilter(gXc) * pow(10, Ndec));
gYf = round(Yfilter(gYc) * pow(10, Ndec));
gZf = round(Zfilter(gZc) * pow(10, Ndec));
