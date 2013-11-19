

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;

uniform vec2 texSize;
uniform float r;//spot r
uniform vec2 c;//spot center in world space
uniform float maxBrightness;
uniform float minBrightness;
uniform vec4 wickBaseColor;
uniform float wickR;
uniform float wickBrightness;

void main() {
    vec2 texCoord=vec2(v_texCoord.s,1.0-v_texCoord.t);//trans texcoord from OatLD to OatLU
    
    
    float maxBrightness=max(maxBrightness,minBrightness);
    float minBrightness=min(maxBrightness,minBrightness);
    vec2 curPixelPos=texCoord*texSize;//curPixel pos in world space
    float dis_curPixelToC=distance(curPixelPos,c);//distance between curPixelPos and spot center
    //spot basic color start fading from center
    float brightness;
    {
        //while r is growing, brightColor decreasing. use the curve y=1/(r*r)*x*x-1/r*x+1.
        //this curve go through (0,1) and bottom at (r,0)
        float temp=max(0.0,1.0-dis_curPixelToC/r);
        float k1=temp*temp;
        brightness=k1*(maxBrightness-minBrightness)+minBrightness;
    }
    //add a extra wick color to the spot
    vec4 wickColor=wickBaseColor*wickBrightness;
    vec4 curPixelWickColor;
    {
        float temp=max(0.0,1.0-dis_curPixelToC/wickR);
        float k1=temp*temp;
        curPixelWickColor=k1*(wickColor-vec4(1.0,1.0,1.0,1.0))+vec4(1.0,1.0,1.0,1.0);
    }
    //final fragment color
   	gl_FragColor=texture2D(CC_Texture0, texCoord)*vec4(vec3(curPixelWickColor)*brightness,1.0);
}

