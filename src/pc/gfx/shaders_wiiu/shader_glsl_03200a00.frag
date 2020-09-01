
#version 130

varying vec2      vTexCoord;
varying vec4      vFog;
varying vec4      vInput1;
varying vec4      vInput2;
varying vec4      vInput3;
varying vec4      vInput4;

uniform sampler2D uTex0;
uniform sampler2D uTex1;

//uniform int       frame_count;
//uniform int       window_height;

#define tex_flags 1
#define fog_used true
#define alpha_used true
#define noise_used false
#define texture_edge false
#define color_alpha_same false

#define c_0_0 0
#define c_0_1 0
#define c_0_2 0
#define c_0_3 5
#define c_1_0 0
#define c_1_1 0
#define c_1_2 0
#define c_1_3 1

#define do_single_0 true
#define do_single_1 true
#define do_multiply_0 false
#define do_multiply_1 false
#define do_mix_0 false
#define do_mix_1 false

vec4 texVal0 = vec4(0.0, 0.0, 0.0, 0.0);
vec4 texVal1 = vec4(0.0, 0.0, 0.0, 0.0);

float random(in vec3 value) {
    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));
    return fract(sin(random) * 143758.5453);
}

vec3 get_color(int item) {
    switch (item) {
        case 0: // SHADER_0
            return vec3(0.0, 0.0, 0.0);
        case 1: // SHADER_INPUT_1
            return vInput1.rgb;
        case 2: // SHADER_INPUT_2
            return vInput2.rgb;
        case 3: // SHADER_INPUT_3
            return vInput3.rgb;
        case 4: // SHADER_INPUT_4
            return vInput4.rgb;
        case 5: // SHADER_TEXEL0
            return texVal0.rgb;
        case 6: // SHADER_TEXEL0A
            return vec3(texVal0.a, texVal0.a, texVal0.a);
        case 7: // SHADER_TEXEL1
            return texVal1.rgb;
    }

    return vec3(0.0, 0.0, 0.0);
}

float get_alpha(int item) {
    switch (item) {
        case 0: //SHADER_0
            return 0.0;
        case 1: // SHADER_INPUT_1
            return vInput1.a;
        case 2: // SHADER_INPUT_2
            return vInput2.a;
        case 3: // SHADER_INPUT_3
            return vInput3.a;
        case 4: // SHADER_INPUT_4
            return vInput4.a;
        case 5: // SHADER_TEXEL0
            return texVal0.a;
        case 6: // SHADER_TEXEL0A
            return texVal0.a;
        case 7: // SHADER_TEXEL1
            return texVal1.a;
    }

    return 0.0;

}

vec4 get_color_alpha(int item) {
    switch (item) {
        case 0: // SHADER_0
            return vec4(0.0, 0.0, 0.0, 0.0);
        case 1: // SHADER_INPUT_1
            return vInput1;
        case 2: // SHADER_INPUT_2
            return vInput2;
        case 3: // SHADER_INPUT_3
            return vInput3;
        case 4: // SHADER_INPUT_4
            return vInput4;
        case 5: // SHADER_TEXEL0
            return texVal0;
        case 6: // SHADER_TEXEL0A
            return vec4(texVal0.a, texVal0.a, texVal0.a, texVal0.a);
        case 7: // SHADER_TEXEL1
            return texVal1;
    }

    return vec4(0.0, 0.0, 0.0, 0.0);
}

vec4 get_texel() {
    if (alpha_used) {
        if (!color_alpha_same) {
            vec3 color;
            float alpha;

            if (do_single_0) {
                color = get_color(c_0_3);
            } else if (do_multiply_0) {
                color = get_color(c_0_0) * get_color(c_0_2);
            } else if (do_mix_0) {
                color = mix(get_color(c_0_1), get_color(c_0_0), get_color(c_0_2));
            } else {
                color = (get_color(c_0_0) - get_color(c_0_1)) * get_color(c_0_2) + get_color(c_0_3);
            }

            if (do_single_1) {
                alpha = get_alpha(c_1_3);
            } else if (do_multiply_1) {
                alpha = get_alpha(c_1_0) * get_alpha(c_1_2);
            } else if (do_mix_1) {
                alpha = mix(get_alpha(c_1_1), get_alpha(c_1_0), get_alpha(c_1_2));
            } else {
                alpha = (get_alpha(c_1_0) - get_alpha(c_1_1)) * get_alpha(c_1_2) + get_alpha(c_1_3);
            }

            return vec4(color, alpha);
        } else {
            if (do_single_0) {
                return get_color_alpha(c_0_3);
            } else if (do_multiply_0) {
                return get_color_alpha(c_0_0) * get_color_alpha(c_0_2);
            } else if (do_mix_0) {
                return mix(get_color_alpha(c_0_1), get_color_alpha(c_0_0), get_color_alpha(c_0_2));
            } else {
                return (get_color_alpha(c_0_0) - get_color_alpha(c_0_1)) * get_color_alpha(c_0_2) + get_color_alpha(c_0_3);
            }
        }
    } else {
        if (do_single_0) {
            return vec4(get_color(c_0_3), 1.0);
        } else if (do_multiply_0) {
            return vec4(get_color(c_0_0) * get_color(c_0_2), 1.0);
        } else if (do_mix_0) {
            return vec4(mix(get_color(c_0_1), get_color(c_0_0), get_color(c_0_2)), 1.0);
        } else {
            return vec4((get_color(c_0_0) - get_color(c_0_1)) * get_color(c_0_2) + get_color(c_0_3), 1.0);
        }
    }
}

void main() {
    switch (tex_flags) {
        case 0:
            break;
        case 1:
            texVal0 = texture(uTex0, vTexCoord);
            break;
        case 2:
            texVal1 = texture(uTex1, vTexCoord);
            break;
        case 3:
            texVal0 = texture(uTex0, vTexCoord);
            texVal1 = texture(uTex1, vTexCoord);
            break;
    }

    vec4 texel = get_texel();
    if (alpha_used && texture_edge) {
        if (texel.a > 0.3) texel.a = 1.0; else discard;
    }

    if (fog_used) {
        texel = vec4(mix(texel.rgb, vFog.rgb, vFog.a), texel.a);
    }

    if (alpha_used && noise_used) {
        //texel.a *= floor(random(vec3(floor(gl_FragCoord.xy * (240.0 / float(window_height))), float(frame_count))) + 0.5);
    }

    gl_FragColor = texel;
}
