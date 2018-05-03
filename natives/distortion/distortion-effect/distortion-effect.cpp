#include "distortion.h"

#include <math.h>

Distortion::Distortion() {}
Distortion::~Distortion() {}

#define SETTER(_NAME,_FIELD) \
    void Distortion::_NAME(jdouble v) {\
        this->_FIELD = v;\
    }

SETTER(setSinOffset, sinOffset)
SETTER(setSinScale, sinScale)

SETTER(setCosOffset, cosOffset)
SETTER(setCosScale, cosScale)

SETTER(setTanOffset, tanOffset)
SETTER(setTanScale, tanScale)

SETTER(setOffset, offset)
SETTER(setScale, scale)

void Distortion::process(jfloat* input, jint inputOffset, jfloat* output, jint outputOffset, jint size) {
    jfloat* actualIn = input + inputOffset;
    jfloat* actualOut = output + outputOffset;
    jdouble o_sin = sinOffset;
    jdouble s_sin = sinScale;
    jdouble o_cos = cosOffset;
    jdouble s_cos = cosScale;
    jdouble o_tan = tanOffset;
    jdouble s_tan = tanScale;
    jdouble o = offset;
    jdouble s = scale;
    bool useSin = isEnabled(FUNCTION_SIN);
    bool useCos = isEnabled(FUNCTION_COS);
    bool useTan = isEnabled(FUNCTION_TAN);
    for(jint i = 0; i < size; i++) {
        jfloat sample = actualIn[i];
        double sampleSin = o_sin + sin(sample * s_sin);
        double sampleCos = o_cos + cos(sample * s_cos);
        double sampleTan = o_tan + tan(sample * s_tan);
        double result = o + s * (useSin ? sampleSin : 1) * (useCos ? sampleCos : 1) * (useTan ? sampleTan : 1);
        actualOut[i] = fmax(-1.0, fmin(1.0, result));
    }
}