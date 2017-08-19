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

if (FilterOnOff == 1) {
  gXv = round(Xfilter(gXc) * pow(10, Ndec));
  gYv = round(Yfilter(gYc) * pow(10, Ndec));
  gZv = round(Zfilter(gZc) * pow(10, Ndec));
} else {
  gXv = round(gXc * pow(10, Ndec));
  gYv = round(gYc * pow(10, Ndec));
  gZv = round(gZc * pow(10, Ndec));
}
