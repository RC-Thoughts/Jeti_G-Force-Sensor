//
// For any extra functions needed before loop()
//

// Restart by user
void(* resetFunc) (void) = 0;

// Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
#define NZEROS 2
#define NPOLES 2
#define GAIN  1.482463775e+01

#define C0 -0.4128015981
#define C1  1.1429805025

float Xxv[NZEROS + 1], Xyv[NPOLES + 1];
float Yxv[NZEROS + 1], Yyv[NPOLES + 1];
float Zxv[NZEROS + 1], Zyv[NPOLES + 1];

float Xfilter(float Xfilterin) {
  for (int fx = 0; fx < (NZEROS); fx++) {
    Xxv[fx] = Xxv[fx + 1];
  }
  for (int fy = 0; fy < (NPOLES); fy++) {
    Xyv[fy] = Xyv[fy + 1];
  }
  Xxv[NZEROS] = Xfilterin / GAIN;
  Xyv[NPOLES] =  (Xxv[0] + Xxv[2]) + 2 * Xxv[1]
                 + ( C0 * Xyv[0]) + (  C1 * Xyv[1]);
  return Xyv[NPOLES];
}

float Yfilter(float Yfilterin) {
  for (int fx = 0; fx < (NZEROS); fx++) {
    Yxv[fx] = Yxv[fx + 1];
  }
  for (int fy = 0; fy < (NPOLES); fy++) {
    Yyv[fy] = Yyv[fy + 1];
  }
  Yxv[NZEROS] = Yfilterin / GAIN;
  Yyv[NPOLES] = (Yxv[0] + Yxv[2]) + 2 * Yxv[1]
                + ( C0 * Yyv[0]) + (  C1 * Yyv[1]);
  return Yyv[NPOLES];
}

float Zfilter(float Zfilterin) {
  for (int fx = 0; fx < (NZEROS); fx++) {
    Zxv[fx] = Zxv[fx + 1];
  }
  for (int fy = 0; fy < (NPOLES); fy++) {
    Zyv[fy] = Zyv[fy + 1];
  }
  Zxv[NZEROS] = Zfilterin / GAIN;
  Zyv[NPOLES] =  (Zxv[0] + Zxv[2]) + 2 * Zxv[1]
                 + ( C0 * Zyv[0]) + (  C1 * Zyv[1]);
  return Zyv[NPOLES];
}
