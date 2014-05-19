#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
#endif

uniform float time;
varying vec2 surfacePosition;

#define MAX_ITER 10
void main( void ) {
    vec2 sp = surfacePosition;
    vec2 p = sp*8.0- vec2(20.0);
    vec2 i = p;
    float c = 1.0;
    float inten = .05;

    for (int n = 0; n < MAX_ITER; n++) 
    {
        float t = time * (1.0 - (3.0 / float(n+1)));
        i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
        c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    }
    c /= float(MAX_ITER);
    c = 1.5-sqrt(c);
    gl_FragColor = vec4(pow(c, 7.0)) + vec4(0.0, 0.15, 0.25, 1.0);
}