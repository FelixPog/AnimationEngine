
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 pos = vec4(inputPosition, 1.0f);
	vec4 animPos = vec4(0.0f, 0.0f, 0.0f, 1.0f); 
	vec3 animNormal = vec3(0.0f, 0.0f, 0.0f); 
	
	for (int i = 0; i < 4; ++i)
    {
        animPos += boneWeights[i] * (skin.mat[int(boneIndices[i])] * pos);
		animNormal += boneWeights[i] * (mat3(skin.mat[int(boneIndices[i])]) * normal);
    }

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(animPos.xyz, 1.0f));
	outNormal = mat3(modelViewMatrix) * animNormal;

	outNormal = normalize(outNormal);
}
