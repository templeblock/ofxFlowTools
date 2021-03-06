
#pragma once

#include "ofMain.h"
#include "ftShader.h"

namespace flowTools {

	class ftGaussianBlurShader : public ftShader {
	public:
		ftGaussianBlurShader(){
            bInitialized = 1;
			if (ofIsGLProgrammableRenderer()) { glThree(); } else { glTwo(); }
			string shaderName = "ftGaussianBlurShader";
			if (bInitialized) { ofLogVerbose(shaderName + " initialized"); }
			else { ofLogWarning(shaderName + " failed to initialize"); }
		}
		
	protected:
		void glTwo() {
			string fragmentHorizontalBlurShader = GLSL120(
														  uniform sampler2DRect backbuffer;
														  uniform float radius;
														  
														  const float total = (1. + 8. + 28. + 56.) * 2. + 70.;
														  
														  void main(void) {
															  vec2 st = gl_TexCoord[0].st;
															  
															  vec4 color = vec4(0.0,0.0,0.0,0.0);
															  color += (1. / total) * texture2DRect(backbuffer, st - radius * vec2(4. / 4., 0.));
															  color += (8. / total)  * texture2DRect(backbuffer, st - radius * vec2(3. / 4., 0.));
															  color += (28. / total)  * texture2DRect(backbuffer, st - radius * vec2(2. / 4., 0.));
															  color += (56. / total)  * texture2DRect(backbuffer, st - radius * vec2(1. / 4., 0.));
															  
															  color +=  (70. / total) * texture2DRect(backbuffer, st);
															  
															  color += (1. / total) * texture2DRect(backbuffer, st + radius * vec2(4. / 4., 0.));
															  color += (8. / total)  * texture2DRect(backbuffer, st + radius * vec2(3. / 4., 0.));
															  color += (28. / total)  * texture2DRect(backbuffer, st + radius * vec2(2. / 4., 0.));
															  color += (56. / total)  * texture2DRect(backbuffer, st + radius * vec2(1. / 4., 0.));
															  
															  gl_FragColor = color;
														  }
														  );
			
			bInitialized *= blurShader[0].setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentHorizontalBlurShader);
			bInitialized *= blurShader[0].linkProgram();
			
			string fragmentVerticalBlurShader = GLSL120(
														uniform sampler2DRect backbuffer;
														uniform float radius;
														
														const float total = (1. + 8. + 28. + 56.) * 2. + 70.;
														
														void main(void) {
															vec2 st = gl_TexCoord[0].st;
															
															vec4 color = vec4(0.0,0.0,0.0,0.0);
															color += (1. / total) * texture2DRect(backbuffer, st - radius * vec2(0., 4. / 4.));
															color += (8. / total)  * texture2DRect(backbuffer, st - radius * vec2(0., 3. / 4.));
															color += (28. / total)  * texture2DRect(backbuffer, st - radius * vec2(0., 2. / 4.));
															color += (56. / total)  * texture2DRect(backbuffer, st - radius * vec2(0., 1. / 4.));
															
															color +=  (70. / total) * texture2DRect(backbuffer, st);
															
															color += (1. / total) * texture2DRect(backbuffer, st + radius * vec2(0., 4. / 4.));
															color += (8. / total)  * texture2DRect(backbuffer, st + radius * vec2(0., 3. / 4.));
															color += (28. / total)  * texture2DRect(backbuffer, st + radius * vec2(0., 2. / 4.));
															color += (56. / total)  * texture2DRect(backbuffer, st + radius * vec2(0., 1. / 4.));
															
															gl_FragColor = color;
														}
														);
			
			bInitialized *= blurShader[1].setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentVerticalBlurShader);
			bInitialized *= blurShader[1].linkProgram();
		}
		
		void glThree() {
			string fragmentHorizontalBlurShader = GLSL410(
														  uniform sampler2DRect backbuffer;
														  uniform float radius;
														  
														  const float total = (1. + 8. + 28. + 56.) * 2. + 70.;
														  
														  in vec2 texCoordVarying;
														  out vec4 fragColor;
														  
														  void main(void) {
															  vec2 st = texCoordVarying;
															  
															  vec4 color = vec4(0.0,0.0,0.0,0.0);
															  color += (1. / total) * texture(backbuffer, st - radius * vec2(4. / 4., 0.));
															  color += (8. / total)  * texture(backbuffer, st - radius * vec2(3. / 4., 0.));
															  color += (28. / total)  * texture(backbuffer, st - radius * vec2(2. / 4., 0.));
															  color += (56. / total)  * texture(backbuffer, st - radius * vec2(1. / 4., 0.));
															  
															  color +=  (70. / total) * texture(backbuffer, st);
															  
															  color += (1. / total) * texture(backbuffer, st + radius * vec2(4. / 4., 0.));
															  color += (8. / total)  * texture(backbuffer, st + radius * vec2(3. / 4., 0.));
															  color += (28. / total)  * texture(backbuffer, st + radius * vec2(2. / 4., 0.));
															  color += (56. / total)  * texture(backbuffer, st + radius * vec2(1. / 4., 0.));
															  
															  fragColor = color;
														  }
														  );
			
			bInitialized *= blurShader[0].setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
			bInitialized *= blurShader[0].setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentHorizontalBlurShader);
			bInitialized *= blurShader[0].bindDefaults();
			bInitialized *= blurShader[0].linkProgram();
			
			string fragmentVerticalBlurShader = GLSL410(
														uniform sampler2DRect backbuffer;
														uniform float radius;
														
														const float total = (1. + 8. + 28. + 56.) * 2. + 70.;
														
														in vec2 texCoordVarying;
														out vec4 fragColor;
														
														void main(void) {
															vec2 st = texCoordVarying;
															
															vec4 color = vec4(0.0,0.0,0.0,0.0);
															color += (1. / total) * texture(backbuffer, st - radius * vec2(0., 4. / 4.));
															color += (8. / total)  * texture(backbuffer, st - radius * vec2(0., 3. / 4.));
															color += (28. / total)  * texture(backbuffer, st - radius * vec2(0., 2. / 4.));
															color += (56. / total)  * texture(backbuffer, st - radius * vec2(0., 1. / 4.));
															
															color +=  (70. / total) * texture(backbuffer, st);
															
															color += (1. / total) * texture(backbuffer, st + radius * vec2(0., 4. / 4.));
															color += (8. / total)  * texture(backbuffer, st + radius * vec2(0., 3. / 4.));
															color += (28. / total)  * texture(backbuffer, st + radius * vec2(0., 2. / 4.));
															color += (56. / total)  * texture(backbuffer, st + radius * vec2(0., 1. / 4.));
															
															fragColor = color;
														}
														);
			
			bInitialized *= blurShader[1].setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
			bInitialized *= blurShader[1].setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentVerticalBlurShader);
			bInitialized *= blurShader[1].bindDefaults();
			bInitialized *= blurShader[1].linkProgram();
		}
		
	public:
		void update(ofFbo& _fbo, int _passes, int _radius){
			if (pingPong.getWidth() != _fbo.getWidth() ||
				pingPong.getHeight() != _fbo.getHeight() ||
				ftUtil::getInternalFormat(pingPong.get()) != ftUtil::getInternalFormat(_fbo)) {
				allocate(_fbo.getWidth(),  _fbo.getHeight(), ftUtil::getInternalFormat(_fbo) );
			}
			
			ftUtil::zero(pingPong);
			ftUtil::stretch(pingPong.get(), _fbo);
	
			for(int i = 0; i < _passes; i++) {
				for(int j = 0; j < 2; j++) {
					pingPong.swap();
					pingPong.begin();
					blurShader[j].begin();
					blurShader[j].setUniformTexture("backbuffer", pingPong.getBackTexture(), 0 );
					blurShader[j].setUniform1f("radius", _radius);
					renderFrame(pingPong.getWidth(), pingPong.getHeight());
					blurShader[j].end();
					pingPong.end();
					
				}
			}
	
			ftUtil::stretch(_fbo, pingPong.getTexture());
		}
		
	protected:
		void allocate(int _width, int _height, int _internalFormat = GL_RGBA){
			pingPong.allocate( _width, _height, _internalFormat);
			ftUtil::zero(pingPong);
		}
		
		ofShader	blurShader[2];
		ftPingPongFbo	pingPong;
		
		int		internalFormat;
		int		width;
		int		height;
		
	};
}
