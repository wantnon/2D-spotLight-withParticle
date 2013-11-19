

#include "maskedSceneSprite.h"
bool CmaskedSceneSprite::init(CCTexture2D *texture){
    this->initWithTexture(texture);
    CCSize texSize=this->getContentSize();
    //mask shader
	{
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("mask.fsh").c_str())->getCString();
		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        //bind attribute
		pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        //link  (must after bindAttribute)
		pProgram->link();
        //get cocos2d-x build-in uniforms
		pProgram->updateUniforms();
        //get my own uniforms
		map<string,GLint> myUnifoMap;
        myUnifoMap["texSize"] = glGetUniformLocation(pProgram->getProgram(),"texSize");
        myUnifoMap["r"] = glGetUniformLocation(pProgram->getProgram(),"r");
        myUnifoMap["c"] = glGetUniformLocation(pProgram->getProgram(),"c");
        myUnifoMap["maxBrightness"] = glGetUniformLocation(pProgram->getProgram(),"maxBrightness");
        myUnifoMap["minBrightness"] = glGetUniformLocation(pProgram->getProgram(),"minBrightness");
        myUnifoMap["wickR"] = glGetUniformLocation(pProgram->getProgram(),"wickR");
        myUnifoMap["wickBaseColor"] = glGetUniformLocation(pProgram->getProgram(),"wickBaseColor");
        myUnifoMap["wickBrightness"] = glGetUniformLocation(pProgram->getProgram(),"wickBrightness");
        //make program
        program.myUnifoMap=myUnifoMap;
        program.setProgram(pProgram);
        //program can be released
        pProgram->release();
        //check gl error
		CHECK_GL_ERROR_DEBUG();
	}
	//check gl error
	CHECK_GL_ERROR_DEBUG();
    
    
    return true;
}
void CmaskedSceneSprite::draw(){
    CCSize texSize=this->getContentSize();
    //----change shader
    this->setShaderProgram(program.getProgram());
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    //pass values for my own uniforms
    float texSize_c[2]={texSize.width,texSize.height};
    glUniform2fv(program.myUnifoMap["texSize"],1,texSize_c);
    glUniform1f(program.myUnifoMap["r"], r);
    float c_c[2]={c.x,c.y};
    glUniform2fv(program.myUnifoMap["c"], 1, c_c);
    glUniform1f(program.myUnifoMap["maxBrightness"], maxBrightness);
    glUniform1f(program.myUnifoMap["minBrightness"], minBrightness);
    glUniform1f(program.myUnifoMap["wickR"], wickR_div_r*r);
    glUniform4fv(program.myUnifoMap["wickBaseColor"], 1, wickBaseColor);
    glUniform1f(program.myUnifoMap["wickBrightness"], wickBrightness);
    //call father draw
    CCSprite::draw();
    
}