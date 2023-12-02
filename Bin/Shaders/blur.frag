uniform sampler2D texture;
uniform float blur_radius;

void main() {
    vec2 uv = gl_TexCoord[0].xy;

    vec4 sum = vec4(0.0);
    int numSamples = 15; // Количество сэмплов для размытия

    for (int i = 0; i < numSamples; ++i) {
        float offset = float(i) - float(numSamples) / 2.0;
        sum += texture2D(texture, uv + offset * blur_radius);
    }

    gl_FragColor = sum / float(numSamples);
}