#pragma once

#define EASE_CONST_S 1.70158f
#ifndef PI
#define PI  3.14159265
#endif
enum class EaseType {
	LINEAR,
	BACK_IN, BACK_OUT, BACK_INOUT,
	BOUNCE_IN, BOUNCE_OUT, BOUNCE_INOUT,
	CIRC_IN, CIRC_OUT, CIRC_INOUT,
	CUBIC_IN, CUBIC_OUT, CUBIC_INOUT,
	ELASTIC_IN,	ELASTIC_OUT, ELASTIC_INOUT,
	QUAD_IN, QUAD_OUT, QUAD_INOUT,
	QUART_IN, QUART_OUT, QUART_INOUT,
	QUINT_IN, QUINT_OUT, QUINT_INOUT,
	SINE_IN, SINE_OUT, SINE_INOUT
};

class Ease {
public:
	Ease(void);
	~Ease(void);

static float Ease::get( EaseType easeType, float t,float b , float c, float d );

static float linear (float t,float b , float c, float d);

static float backIn(float t,float b , float c, float d);
static float backOut(float t,float b , float c, float d);
static float backInOut(float t,float b , float c, float d);

static float bounceIn(float t,float b , float c, float d);
static float bounceOut(float t,float b , float c, float d);
static float bounceInOut(float t,float b , float c, float d);

static float circIn(float t,float b , float c, float d);
static float circOut(float t,float b , float c, float d);
static float circInOut(float t,float b , float c, float d);

static float cubicIn(float t,float b , float c, float d);
static float cubicOut(float t,float b , float c, float d);
static float cubicInOut(float t,float b , float c, float d);

static float elasticIn(float t,float b , float c, float d);
static float elasticOut(float t,float b , float c, float d);
static float elasticInOut(float t,float b , float c, float d);

static float expoIn(float t,float b , float c, float d);
static float expoOut(float t,float b , float c, float d);
static float expoInOut(float t,float b , float c, float d);

static float quadIn(float t,float b , float c, float d);
static float quadOut(float t,float b , float c, float d);
static float quadInOut(float t,float b , float c, float d);

static float quartIn(float t,float b , float c, float d);
static float quartOut(float t,float b , float c, float d);
static float quartInOut(float t,float b , float c, float d);

static float quintIn(float t,float b , float c, float d);
static float quintOut(float t,float b , float c, float d);
static float quintInOut(float t,float b , float c, float d);

static float sineIn(float t,float b , float c, float d);
static float sineOut(float t,float b , float c, float d);
static float sineInOut(float t,float b , float c, float d);
};