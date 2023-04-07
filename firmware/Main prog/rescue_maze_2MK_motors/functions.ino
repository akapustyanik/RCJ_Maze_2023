
void forward_test(int speed_motors)
{

  //while ((abs(motorA.encoder()) + abs(motorB.encoder()) + abs(motorC.encoder()) + abs(motorD.encoder())) / 4 < 360 / (diam * 3.14) * distance)
  int err1 = abs(motorA.encoder()) - abs(motorD.encoder());
  int err2 = abs(motorB.encoder()) - abs(motorC.encoder());

  motorA.followSpeed(constrain(speed_motors + err1 * 0.05, -68.5, 68.5));
  motorB.followSpeed(constrain(speed_motors + err2 * 0.05, -68.5, 68.5));
  motorC.followSpeed(constrain(speed_motors - err2 * 0.05, -68.5, 68.5));
  motorD.followSpeed(constrain(speed_motors - err1 * 0.05, -68.5, 68.5));
}
void forward(int speed_motors)
{
  motorA.justSpeed(speed_motors);
  motorB.justSpeed(speed_motors);
  motorC.justSpeed(speed_motors+5);
  motorD.justSpeed(speed_motors+5);
}
void left()
{
  errP = ((alpha - z) * 1.6);
  errI = errI + errP * 0.55;
  if (abs(errI) > 10)
  {
    errI = sgn(errI) * 10;
  }//-(errP + errI)
  motorA.followSpeed(25);
  motorB.followSpeed(25);
  motorC.followSpeed(-25);
  motorD.followSpeed(-25);
}

void right()
{
  errP = ((alpha - z) * 1.6);
  errI = errI + errP * 0.55;
  if (abs(errI) > 10)
  {
    errI = sgn(errI) * 10;
  }
  motorA.followSpeed(-25);
  motorB.followSpeed(-25);
  motorC.followSpeed(25);
  motorD.followSpeed(25);
}
