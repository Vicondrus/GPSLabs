#version 400

in vec3 colour;
out vec4 fragmentColour;

uniform vec3 uniformColour;

void main() {
fragmentColour = vec4(colour, 1.0);
}
