/************************************************************************/
/* Original equations by Robert Penner									*/                      
/* http://www.robertpenner.com/easing/									*/
/* Modification by Bahadir Katipoglu									*/
/* http://bahadir.me													*/
/*																		*/
/* Easing cheat sheet: http://easings.net/								*/
/************************************************************************/

#include "stdafx.h"
#include "Ease.h"
#include <math.h>


Ease::Ease(void)
{
}

float Ease::get( EaseType easeType, float t,float b , float c, float d ) {
	switch (easeType){
	case EaseType::LINEAR:
		return linear(t, b, c, d);
		break;
	case EaseType::BACK_IN:
		return backIn(t, b, c, d);
		break;
	case EaseType::BACK_OUT:
		return backOut(t, b, c, d);
		break;
	case EaseType::BACK_INOUT:
		return backInOut(t, b, c, d);
		break;
	case EaseType::BOUNCE_IN:
		return bounceIn(t, b, c, d);
		break;
	case EaseType::BOUNCE_OUT:
		return bounceOut(t, b, c, d);
		break;
	case EaseType::BOUNCE_INOUT:
		return bounceInOut(t, b, c, d);
		break;
	case EaseType::CIRC_IN:
		return circIn(t, b, c, d);
		break;
	case EaseType::CIRC_OUT:
		return circOut(t, b, c, d);
		break;
	case EaseType::CIRC_INOUT:
		return cubicInOut(t, b, c, d);
		break;
	case EaseType::CUBIC_IN:
		return cubicIn(t, b, c, d);
		break;
	case EaseType::CUBIC_OUT:
		return cubicOut(t, b, c, d);
		break;
	case EaseType::CUBIC_INOUT:
		return cubicInOut(t, b, c, d);
		break;
	case EaseType::ELASTIC_IN:
		return elasticIn(t, b, c, d);
		break;
	case EaseType::ELASTIC_OUT:
		return elasticOut(t, b, c, d);
		break;
	case EaseType::ELASTIC_INOUT:
		return elasticInOut(t, b, c, d);
		break;
	case EaseType::QUAD_IN:
		return quadIn(t, b, c, d);
		break;
	case EaseType::QUAD_OUT:
		return quadOut(t, b, c, d);
		break;
	case EaseType::QUAD_INOUT:
		return quadInOut(t, b, c, d);
		break;
	case EaseType::QUART_IN:
		return quartIn(t, b, c, d);
		break;
	case EaseType::QUART_OUT:
		return quartOut(t, b, c, d);
		break;
	case EaseType::QUART_INOUT:
		return quartInOut(t, b, c, d);
		break;
	case EaseType::QUINT_IN:
		return quintIn(t, b, c, d);
		break;
	case EaseType::QUINT_OUT:
		return quintOut(t, b, c, d);
		break;
	case EaseType::QUINT_INOUT:
		return quintInOut(t, b, c, d);
		break;
	case EaseType::SINE_IN:
		return sineIn(t, b, c, d);
		break;
	case EaseType::SINE_OUT:
		return sineOut(t, b, c, d);
		break;
	case EaseType::SINE_INOUT:
		return sineInOut(t, b, c, d);
		break;
	default: // Linear
		return linear(t, b, c, d);
		break;
	}

}
Ease::~Ease(void)
{
}

float Ease::backIn( float t,float b , float c, float d )
{
	float s = 1.70158f;
	float postFix = t/=d;
	return c*(postFix)*t*((s+1)*t - s) + b;
}

float Ease::backOut( float t,float b , float c, float d )
{
	float s = 1.70158f;
	return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}

float Ease::backInOut( float t,float b , float c, float d )
{
	float s = 1.70158f;
	if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
	float postFix = t-=2;
	return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
}

float Ease::bounceIn( float t,float b , float c, float d )
{
	return c - bounceOut(d-t, 0, c, d) + b;
}

float Ease::bounceOut( float t,float b , float c, float d )
{
	if ((t/=d) < (1/2.75f)) {
		return c*(7.5625f*t*t) + b;
	} else if (t < (2/2.75f)) {
		float postFix = t-=(1.5f/2.75f);
		return c*(7.5625f*(postFix)*t + .75f) + b;
	} else if (t < (2.5/2.75)) {
		float postFix = t-=(2.25f/2.75f);
		return c*(7.5625f*(postFix)*t + .9375f) + b;
	} else {
		float postFix = t-=(2.625f/2.75f);
		return c*(7.5625f*(postFix)*t + .984375f) + b;
	}
}

float Ease::bounceInOut( float t,float b , float c, float d ){
	if (t < d/2) return bounceIn (t*2, 0, c, d) * .5f + b;
	else return bounceOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
}

float Ease::circIn( float t,float b , float c, float d ){
	return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
}

float Ease::circOut( float t,float b , float c, float d ){
	return c * sqrt(1 - (t=t/d-1)*t) + b;
}

float Ease::circInOut( float t,float b , float c, float d ){
	if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
	return c/2 * (sqrt(1 - t*(t-=2)) + 1) + b;
}

float Ease::cubicIn( float t,float b , float c, float d ){
	return c*(t/=d)*t*t + b;
}

float Ease::cubicOut( float t,float b , float c, float d ){
	return c*((t=t/d-1)*t*t + 1) + b;
}

float Ease::cubicInOut( float t,float b , float c, float d ){
	if ((t/=d/2) < 1) return c/2*t*t*t + b;
	return c/2*((t-=2)*t*t + 2) + b;
}

float Ease::elasticIn( float t,float b , float c, float d ){
	if (t==0) return b;  if ((t/=d)==1) return b+c;  
	float p=d*.3f;
	float a=c; 
	float s=p/4;
	float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
	return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
}

float Ease::elasticOut( float t,float b , float c, float d ){
	if (t==0) return b;  if ((t/=d)==1) return b+c;  
	float p=d*.3f;
	float a=c; 
	float s=p/4;
	return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);	
}

float Ease::elasticInOut( float t,float b , float c, float d ){
	if (t==0) return b;  if ((t/=d/2)==2) return b+c; 
	float p=d*(.3f*1.5f);
	float a=c; 
	float s=p/4;

	if (t < 1) {
		float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
		return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
	} 
	float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
	return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
}

float Ease::expoIn( float t,float b , float c, float d ){
	return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
}

float Ease::expoOut( float t,float b , float c, float d ){
	return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;	
}

float Ease::expoInOut( float t,float b , float c, float d ){
	if (t==0) return b;
	if (t==d) return b+c;
	if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
	return c/2 * (-pow(2, -10 * --t) + 2) + b;
}

float Ease::quadIn( float t,float b , float c, float d ){
	return c*(t/=d)*t + b;
}

float Ease::quadOut( float t,float b , float c, float d ){
	return -c *(t/=d)*(t-2) + b;
}

float Ease::quadInOut( float t,float b , float c, float d ){
	if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
	return -c/2 * (((t-2)*(--t)) - 1) + b;
}

float Ease::quartIn( float t,float b , float c, float d ){
	return c*(t/=d)*t*t*t + b;
}

float Ease::quartOut( float t,float b , float c, float d ){
	return -c * ((t=t/d-1)*t*t*t - 1) + b;
}

float Ease::quartInOut( float t,float b , float c, float d ){
	if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
	return -c/2 * ((t-=2)*t*t*t - 2) + b;
}

float Ease::quintIn( float t,float b , float c, float d ){
	return c*(t/=d)*t*t*t*t + b;
}

float Ease::quintOut( float t,float b , float c, float d ){
	return c*((t=t/d-1)*t*t*t*t + 1) + b;
}

float Ease::quintInOut( float t,float b , float c, float d ){
	if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
	return c/2*((t-=2)*t*t*t*t + 2) + b;
}

float Ease::sineIn( float t,float b , float c, float d ){
	return -c * cos(t/d * (PI/2)) + c + b;	
}

float Ease::sineOut( float t,float b , float c, float d ){
	return c * sin(t/d * (PI/2)) + b;
}

float Ease::sineInOut( float t,float b , float c, float d ){
	return -c/2 * (cos(PI*t/d) - 1) + b;
}

float Ease::linear( float t,float b , float c, float d )
{
	return c*t/d + b;
}
