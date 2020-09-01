
#version 130

attribute vec4 aVtxPos;

attribute vec2 aTexCoord;
attribute vec4 aFog;
attribute vec4 aInput1;
attribute vec4 aInput2;
attribute vec4 aInput3;
attribute vec4 aInput4;

varying   vec2 vTexCoord;
varying   vec4 vFog;
varying   vec4 vInput1;
varying   vec4 vInput2;
varying   vec4 vInput3;
varying   vec4 vInput4;

void main() {
    vTexCoord = aTexCoord;
    vFog = aFog;
    vInput1 = aInput1;
    vInput2 = aInput2;
    vInput3 = aInput3;
    vInput4 = aInput4;

    gl_Position = aVtxPos;
}
