std::unordered_set<GLuint> playerPrograms;
GLuint playerVertexShader = 0, playerMaskShader = 0;
std::mutex playerProgramsMutex;
std::mutex playerShaderMutex;
#include "Wallshader.h"

void (*oglDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
void _glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) {
    	if (KaushikSettings::WallHack) {
        GLuint currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *) &currentProgram);{
        std::lock_guard<std::mutex> lock(playerProgramsMutex);
        if (playerPrograms.find(currentProgram) == playerPrograms.end()) {
        return oglDrawElements(mode, count, type, indices);
        }}
        GLfloat depthRange[2];
        glGetFloatv(GL_DEPTH_RANGE, depthRange);
        GLboolean colorWriteMask[4];
        glGetBooleanv(GL_COLOR_WRITEMASK, colorWriteMask);
        GLboolean blend;
        glGetBooleanv(GL_BLEND, &blend);
        if (!blend) {
        glEnable(GL_BLEND);
        }
        glDepthRangef(1.f, 0.0f);
        glColorMask(1, 1, 1, 1);
		//=========
		oglDrawElements(mode, count, type, indices);
        glDepthRangef(depthRange[0], depthRange[1]);
        glColorMask(colorWriteMask[0], colorWriteMask[1], colorWriteMask[2], colorWriteMask[3]);	
        if (!blend) {
        glDisable(GL_BLEND);
        }return;}						
    	return oglDrawElements(mode, count, type, indices);
		}
        
void (*oglShaderSource)(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
void _glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length) {
    if (!string || !*string) {
    return oglShaderSource(shader, count, string, length);
    }
    if (!count) {
    return oglShaderSource(shader, count, string, length);
    }
 
        if (strstr(*string,OBFUSCATE( "Master_Mask")) || 
       strstr(*string, OBFUSCATE("Master_Mask_Base")) || 
       strstr(*string,OBFUSCATE( "Master_Mask_Base_Elves")) || 
       strstr(*string, OBFUSCATE("Master_Mask_Base_Elves_Player")) || 
       strstr(*string,OBFUSCATE( "Master_Mask_Base_FireMove")) || 
       strstr(*string, OBFUSCATE("Master_Mask_Base_MetalCube")) || 
       strstr(*string,OBFUSCATE( "Master_Mask_Base_Slime")) || 
       strstr(*string, OBFUSCATE("Master_Mask_Base_Xiyou")) || 
       strstr(*string,OBFUSCATE( "Master_Mask_Base_Emisive")) || 
       strstr(*string, OBFUSCATE("Master_Mask_Base_FlowParal")) || 
       strstr(*string,OBFUSCATE( "Master_Mask_Base_Emoji_Vari")) || 
       strstr(*string,OBFUSCATE("Master_Mask_Base_Trans")) || 
       strstr(*string,OBFUSCATE( "Master_Mask_Base_Fly")) || 
       strstr(*string, OBFUSCATE("Master_Mask_Base_MaskedEmiss"))) {
       GLenum shaderTypes = 0;
       glGetShaderiv(shader, GL_SHADER_TYPE, reinterpret_cast<GLint *>(&shaderTypes));
       if (shaderTypes == GL_FRAGMENT_SHADER) {
            std::lock_guard<std::mutex> lock{playerShaderMutex};
            if (KaushikSettings::WallHack) {
            playerMaskShader = shader;
            *string = PLAYER;
        }
    }
}
	
           // HAIR 💇
    if (strstr(*string,OBFUSCATE("M_Hair_Emi")) || 
       strstr(*string,OBFUSCATE("M_Hair_TwoPass_Dissolve")) ||
       strstr(*string,OBFUSCATE("M_ToonHair")) || 
       strstr(*string,OBFUSCATE("M_Hair_TwoPass")) || 
       strstr(*string,OBFUSCATE("Mat_Hair_V2_Player")) || 
       strstr(*string,OBFUSCATE("Mat_Hair_V2")) || 
       strstr(*string,OBFUSCATE("Mat_Hair_V2_Irradiance")) || 
       strstr(*string,OBFUSCATE( "M_PET_int_065_Outline")) || 
       strstr(*string, OBFUSCATE("Master_Pet")) || 
       strstr(*string, OBFUSCATE("M_Pet_int_065")) || 
       strstr(*string,OBFUSCATE( "Master_Pet_Fur")) || 
       strstr(*string, OBFUSCATE("M_Pet_Cloth_int_054_Outter")) || 
       strstr(*string,OBFUSCATE("Mat_Hair_V2_2372"))) {
       GLenum shaderTypes = 0;
       glGetShaderiv(shader, GL_SHADER_TYPE, reinterpret_cast<GLint *>(&shaderTypes));
       if (shaderTypes == GL_FRAGMENT_SHADER) {
            std::lock_guard<std::mutex> lock{playerShaderMutex};
            if (KaushikSettings::WallHack) {
            playerMaskShader = shader;
            *string = Hair;
       }
    }
}

    return oglShaderSource(shader, count, string, length);
}

/*
void (*oglViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
 void _glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
 if (KaushikSettings::WallHack) {
 EGLSurface currentSurface = eglGetCurrentSurface(EGL_DRAW);
 if (currentSurface == EGL_NO_SURFACE) {
 return;
 }
 EGLint eglWidth = 0;
 EGLint eglHeight = 0;
 eglQuerySurface(eglGetCurrentDisplay(), currentSurface, EGL_WIDTH, &eglWidth);
 eglQuerySurface(eglGetCurrentDisplay(), currentSurface, EGL_HEIGHT, &eglHeight);
 float viewportX = 0.0f;
 float viewportY = 10.0f;
 float smallerWidth = static_cast<float>(eglWidth) - (2.0f * viewportX);
 float smallerHeight = static_cast<float>(eglHeight) - (2.0f * viewportY);
 oglViewport(static_cast<GLint>(viewportX), static_cast<GLint>(viewportY),
 static_cast<GLsizei>(smallerWidth), static_cast<GLsizei>(smallerHeight));
 } else {
 oglViewport(x, y, width, height);
 }
 }*/
 

void (*oglAttachShader)(GLuint program, GLuint shader);
void _glAttachShader(GLuint program, GLuint shader) {
    std::unique_lock<std::mutex> ulock{playerShaderMutex};
    if (shader == playerVertexShader || shader == playerMaskShader) {
    ulock.unlock();{
    std::lock_guard<std::mutex> lock{playerProgramsMutex};
    playerPrograms.insert(program);
    }}
    return oglAttachShader(program, shader);
	}
