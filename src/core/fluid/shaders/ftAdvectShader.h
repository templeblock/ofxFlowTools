
#pragma once

#include "ofMain.h"
#include "ftShader.h"

namespace flowTools {
	
	class ftAdvectShader : public ftShader {
	public:
		ftAdvectShader() {
            bInitialized = 1;
			if (ofIsGLProgrammableRenderer()) { glThree(); } else { glTwo(); }
			string shaderName = "ftAdvectShader";
			if (bInitialized) { ofLogVerbose(shaderName + " initialized"); }
			else { ofLogWarning(shaderName + " failed to initialize"); }
//			load("tempShader/ftVertexShader.vert", "tempShader/" + shaderName + ".frag");
		}
		
	protected:
		void glTwo() {
			fragmentShader = GLSL120(
									 uniform sampler2DRect Backbuffer;
									 uniform sampler2DRect Velocity;
									 
									 uniform float	TimeStep;
									 uniform float	Dissipation;
									 uniform vec2	Scale;
									 
									 void main(){
										 vec2 st = gl_TexCoord[0].st;
										 vec2 st2 = st * Scale;
										 vec2 u = texture2DRect(Velocity, st2).rg / Scale;
										 gl_FragColor = Dissipation * texture2DRect(Backbuffer,  st - TimeStep * u);
									 }
									 );
			
			bInitialized *= setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
			bInitialized *= linkProgram();
		}
		
		void glThree() {
			fragmentShader = GLSL410(
									 uniform sampler2DRect Backbuffer;
									 uniform sampler2DRect Velocity;
									 
									 uniform float	TimeStep;
									 uniform float	Dissipation;
									 uniform vec2	Scale;
									 
									 in vec2 texCoordVarying;
									 out vec4 fragColor;
									 
									 void main(){
										 vec2 st = texCoordVarying;
										 vec2 st2 = st * Scale;
										 vec2 u = texture(Velocity, st2).rg / Scale;
										 fragColor = Dissipation * texture(Backbuffer,  st - TimeStep * u);
									 }
									 );
			
			bInitialized *= setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
			bInitialized *= setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
			bInitialized *= bindDefaults();
			bInitialized *= linkProgram();
		}
		
	public:
		void update(ofFbo& _fbo, ofTexture& _backTex,  ofTexture& _velTex, float _timeStep, float _dissipation){
			_fbo.begin();
			begin();
			setUniform1f("TimeStep", _timeStep);
			setUniform1f("Dissipation", _dissipation);
			setUniform2f("Scale", _velTex.getWidth() / _fbo.getWidth(), _velTex.getHeight()/ _fbo.getHeight());
			setUniformTexture("Backbuffer", _backTex, 0);
			setUniformTexture("Velocity", _velTex, 1);
			renderFrame(_fbo.getWidth(), _fbo.getHeight());
			end();
			_fbo.end();
		}
	};
}


