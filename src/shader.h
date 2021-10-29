#ifndef SHADER_H
#define SHADER_H

struct Shader {
	unsigned int id;
};

struct Shader NewShader(const char *vertexPath, const char *fragmentPath);

void useShader(const struct Shader shader);
void setShaderBool(const struct Shader shader, const char *name, int value);
void setShaderInt(const struct Shader shader, const char *name, int value);
void setShaderFloat(const struct Shader shader, const char *name, float value);
void setShaderVec3(const struct Shader shader, const char *name, float x, float y, float z);

#endif // SHADER_H
