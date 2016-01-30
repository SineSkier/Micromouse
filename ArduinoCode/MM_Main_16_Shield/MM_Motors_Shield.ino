#define STEP_F_MAX  150  // Maximum step count for moving forward.
#define STEP_F_MIN  150  // Minimum step count for moving forward.
#define STEP_T      66   // Step count for turning.
#define DELAY_F     0    // Delay in milliseconds between moving forward and anything else.
#define DELAY_T     0    // Delay in milliseconds between turning and anything else.

int stepF = STEP_F_MAX;


void moveN(byte & dir, byte & mouRow, byte & mouCol){
  switch (dir) {
    case 0: moveF(dir,mouRow,mouCol); if(stepF>STEP_F_MIN){stepF--;} break;
    case 1: turnL(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 2: centerUpre(); turnR(dir); turnR(dir); /*if(wallExists(m[mouRow][mouCol],(dir+1)%4)&&wallExists(m[mouRow][mouCol],(dir+3)%4)){centerUpost();}*/ moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 3: turnR(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
  }
} // end moveN


void moveE(byte & dir, byte & mouRow, byte & mouCol){
  switch (dir) {
    case 1: moveF(dir,mouRow,mouCol); if(stepF>STEP_F_MIN){stepF--;} break;
    case 2: turnL(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 3: centerUpre(); turnR(dir); turnR(dir); /*if(wallExists(m[mouRow][mouCol],(dir+1)%4)&&wallExists(m[mouRow][mouCol],(dir+3)%4)){centerUpost();}*/ moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 0: turnR(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
  }
} // end moveE


void moveS(byte & dir, byte & mouRow, byte & mouCol){
  switch (dir) {
    case 2: moveF(dir,mouRow,mouCol); if(stepF>STEP_F_MIN){stepF--;} break;
    case 3: turnL(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 0: centerUpre(); turnR(dir); turnR(dir); /*if(wallExists(m[mouRow][mouCol],(dir+1)%4)&&wallExists(m[mouRow][mouCol],(dir+3)%4)){centerUpost();}*/ moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 1: turnR(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
  }
} // end moveS


void moveW(byte & dir, byte & mouRow, byte & mouCol){
  switch (dir) {
    case 3: moveF(dir, mouRow,mouCol); if(stepF>STEP_F_MIN){stepF--;} break;
    case 0: turnL(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 1: centerUpre(); turnR(dir); turnR(dir); /*if(wallExists(m[mouRow][mouCol],(dir+1)%4)&&wallExists(m[mouRow][mouCol],(dir+3)%4)){centerUpost();}*/ moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
    case 2: turnR(dir); moveF(dir,mouRow,mouCol); stepF=STEP_F_MAX; break;
  }
} // end moveW


void moveF(byte dir, byte & mouRow, byte & mouCol){
  switch (dir) {
  case 0: ++mouRow; break;
  case 1: ++mouCol; break;
  case 2: --mouRow; break;
  case 3: --mouCol; break;
  }
  unsigned char stepCount = 0;
  while (stepCount < stepF) {
    if (!senseMotor()) {
      motorL->step(1, FORWARD, SINGLE);
      motorR->step(1, FORWARD, SINGLE); 
    }
    stepCount++;
    if(select){
      digitalWrite(6, HIGH);
      select = false;
    }else{
      digitalWrite(6, LOW);
      select = true;
    }
  }
  delay(DELAY_F);
} // end moveF


void turnR(byte & dir){
  dir = (dir + 1)%4;
  char stepCount = 0;
  while (stepCount < STEP_T) { //alter this value based on the amount of rotation
    motorL->step(1, FORWARD, SINGLE);
    motorR->step(1, BACKWARD, SINGLE);
    stepCount++;
  }
  delay(DELAY_T);
} // end turnR


void turnL(byte & dir){
  dir = (dir + 3)%4;
  char stepCount = 0;
  while (stepCount < STEP_T) { //alter this value based on the amount of rotation
    motorL->step(1, BACKWARD, SINGLE);
    motorR->step(1, FORWARD, SINGLE);
    stepCount++;
  }
  delay(DELAY_T);
} // end turnL
