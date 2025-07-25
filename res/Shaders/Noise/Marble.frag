#version 460 core

out vec4 FragColour;

in vec2 coords;
in vec3 pos;

const vec3 tileSize = vec3(1.1,1.0, 1.1);
const vec3 tilePct = vec3(0.98,1.0, 0.98);


vec3 Integral(vec3 x, vec3 p, vec3 np) {
return (floor(x)*(p)) + max(fract (x) - (np), 0.0);
}

vec3 marble_color(float x)
{
   vec3 col;
    x = 0.5*(x+1.);          // transform -1<x<1 to 0<x<1
    x = sqrt(x);             // make x fall of rapidly...
    x = sqrt(x);
    x = sqrt(x);
    col = vec3(.2 + .75*x);  // scale x from 0<x<1 to 0.2<x<0.95
    col.b*=0.95;             // slightly reduce blue component (make color "warmer"):
    return col;
}

vec3 hash(vec3 p) {
    // Generate pseudo-random gradients
    return fract(sin(vec3(dot(p, vec3(127.1, 311.7, 74.7)),
                           dot(p, vec3(269.5, 183.3, 246.1)),
                           dot(p, vec3(113.5, 271.9, 124.6)))) * 43758.5453);
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float fade(float t) {
    // Fade function to smooth interpolation
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

float perlinNoise(vec3 uv) {
    // Grid cell coordinates
    vec3 i = floor(uv);
    vec3 f = fract(uv);

    // Generate gradients at the cell corners
    vec3 g000 = hash(i + vec3(0.0, 0.0, 0.0));
    vec3 g100 = hash(i + vec3(1.0, 0.0, 0.0));
    vec3 g010 = hash(i + vec3(0.0, 1.0, 0.0));
    vec3 g110 = hash(i + vec3(1.0, 1.0, 0.0));
    vec3 g001 = hash(i + vec3(0.0, 0.0, 1.0));
    vec3 g101 = hash(i + vec3(1.0, 0.0, 1.0));
    vec3 g011 = hash(i + vec3(0.0, 1.0, 1.0));
    vec3 g111 = hash(i + vec3(1.0, 1.0, 1.0));

    // Compute dot products
    float d000 = dot(g000, f - vec3(0.0, 0.0, 0.0));
    float d100 = dot(g100, f - vec3(1.0, 0.0, 0.0));
    float d010 = dot(g010, f - vec3(0.0, 1.0, 0.0));
    float d110 = dot(g110, f - vec3(1.0, 1.0, 0.0));
    float d001 = dot(g001, f - vec3(0.0, 0.0, 1.0));
    float d101 = dot(g101, f - vec3(1.0, 0.0, 1.0));
    float d011 = dot(g011, f - vec3(0.0, 1.0, 1.0));
    float d111 = dot(g111, f - vec3(1.0, 1.0, 1.0));

    // Interpolation weights
    vec3 u = vec3(fade(f.x),fade(f.y),fade(f.z));

    // Trilinear interpolation
    float lerpX0 = lerp(lerp(d000, d100, u.x), lerp(d010, d110, u.x), u.y);
    float lerpX1 = lerp(lerp(d001, d101, u.x), lerp(d011, d111, u.x), u.y);
    return lerp(lerpX0, lerpX1, u.z);
}

float turbulence (vec3 P, int numFreq)
{
   float val = 0.0;
   float freq = 1.0;
   for (int i=0; i<numFreq; i++) {
      val += abs (perlinNoise (P*freq) / freq);
      freq *= 2.07;
   }
   return val;
}



void main()
{
    // Definition of tiles, in meter:
     const vec3 tileSize = vec3(1.1,1.0, 1.1);
     const vec3 tilePct = vec3(0.98,1.0, 0.98);

     // Get tile number - this adapts tileSize, transforming 0..tileSize to 0..1.
     // (factor 16 comes from vs and should be removed at both ends!):
     vec3 Tpos = pos / tileSize;

     // move each other row of tiles:
     if (fract (Tpos.x*0.5) > 0.5)
       Tpos.z += 0.5;

     // Make position relative to tile:
     vec3 pos = fract (Tpos);

     // --- Calculate the marble color ---
     const int roughness = 4;     // noisiness of veins (#octaves in turbulence)

     vec3 tileID = ceil(Tpos); // get ID of tile, unique to a tile and common to all its pixels
     float asc    = 3*perlinNoise (2.3*(tileID));  // use this as m in t=my+x, rather than just using t=x.

     const float PI = 3.1415;
     float amplitude = 6.0;
     float t = 2.0*PI*(pos.x + (asc*pos.z)) / tileSize.x ;
     t += amplitude*turbulence (pos, roughness);
     // replicate over rows of tiles (wont be identical, because noise is depending on all coordinates of the input vector):
     t = sin(t);
     vec3 marbleColor = marble_color(t);
  
     // get filter size:
     vec3 fw = fwidth (pos);
  
     // Determine if marble or joint: isMarble will be 0 if there is marble and 1 if we are in a joint
     // vec3 isMarble = step (pos, tilePct);
     vec3 isMarble = (Integral (pos+fw, tilePct, 1.-tilePct) - Integral (pos, tilePct, 1.-tilePct)) / fw;

     // mix the two colors together, isMarble decides which color to use:
     vec3 color = mix (vec3 (0.2, 0.2, 0.2), marbleColor, isMarble.x*isMarble.z);

     FragColour = vec4 (color, 1.0);
}
 




   

  