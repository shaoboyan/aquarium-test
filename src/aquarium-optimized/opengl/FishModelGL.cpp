//
// Copyright (c) 2018 The WebGLNativePorts Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// FishModelGL.h: Implements fish model of OpenGL.

#include "ContextGL.h"
#include "FishModelGL.h"
#include "ProgramGL.h"

FishModelGL::FishModelGL(const ContextGL *contextGL,
                         Aquarium *aquarium,
                         MODELGROUP type,
                         MODELNAME name,
                         bool blend)
    : FishModel(type, name, blend), contextGL(contextGL)
{
    viewInverseUniform.first = aquarium->lightWorldPositionUniform.viewInverse;
    lightWorldPosUniform.first = aquarium->lightWorldPositionUniform.lightWorldPos;
    lightColorUniform.first = aquarium->lightUniforms.lightColor;
    specularUniform.first = aquarium->lightUniforms.specular;
    shininessUniform.first = 5.0f;
    specularFactorUniform.first = 0.3f;
    ambientUniform.first = aquarium->lightUniforms.ambient;
    fogPowerUniform.first = g_fogPower;
    fogMultUniform.first = g_fogMult;
    fogOffsetUniform.first = g_fogOffset;
    fogColorUniform.first = aquarium->fogUniforms.fogColor;

    viewProjectionUniform.first = aquarium->lightWorldPositionUniform.viewProjection;
    scaleUniform.first = 1;

    const Fish &fishInfo              = fishTable[name - MODELNAME::MODELSMALLFISHA];
    fishLengthUniform.first     = fishInfo.fishLength;
    fishBendAmountUniform.first = fishInfo.fishBendAmount;
    fishWaveLengthUniform.first = fishInfo.fishWaveLength;
}

void FishModelGL::init()
{
    ProgramGL *programGL = static_cast<ProgramGL *>(mProgram);
    viewInverseUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "viewInverse");
    lightWorldPosUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "lightWorldPos");
    lightColorUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "lightColor");
    specularUniform.second  = contextGL->getUniformLocation(programGL->getProgramId(), "specular");
    ambientUniform.second   = contextGL->getUniformLocation(programGL->getProgramId(), "ambient");
    shininessUniform.second = contextGL->getUniformLocation(programGL->getProgramId(), "shininess");
    specularFactorUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "specularFactor");

    fogPowerUniform.second  = contextGL->getUniformLocation(programGL->getProgramId(), "fogPower");
    fogMultUniform.second   = contextGL->getUniformLocation(programGL->getProgramId(), "fogMult");
    fogOffsetUniform.second = contextGL->getUniformLocation(programGL->getProgramId(), "fogOffset");
    fogColorUniform.second  = contextGL->getUniformLocation(programGL->getProgramId(), "fogColor");

    viewProjectionUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "viewProjection");
    fishLengthUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "fishLength");
    fishWaveLengthUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "fishWaveLength");
    fishBendAmountUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "fishBendAmount");

    worldPositionUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "worldPosition");
    nextPositionUniform.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "nextPosition");
    scaleUniform.second = contextGL->getUniformLocation(programGL->getProgramId(), "scale");
    timeUniform.second  = contextGL->getUniformLocation(programGL->getProgramId(), "time");

    diffuseTexture.first    = static_cast<TextureGL *>(textureMap["diffuse"]);
    diffuseTexture.second   = contextGL->getUniformLocation(programGL->getProgramId(), "diffuse");
    normalTexture.first     = static_cast<TextureGL *>(textureMap["normalMap"]);
    normalTexture.second    = contextGL->getUniformLocation(programGL->getProgramId(), "normalMap");
    reflectionTexture.first = static_cast<TextureGL *>(textureMap["reflectionMap"]);
    reflectionTexture.second =
        contextGL->getUniformLocation(programGL->getProgramId(), "reflectionMap");
    skyboxTexture.first  = static_cast<TextureGL *>(textureMap["skybox"]);
    skyboxTexture.second = contextGL->getUniformLocation(programGL->getProgramId(), "skybox");

    positionBuffer.first  = static_cast<BufferGL *>(bufferMap["position"]);
    positionBuffer.second = contextGL->getAttribLocation(programGL->getProgramId(), "position");
    normalBuffer.first    = static_cast<BufferGL *>(bufferMap["normal"]);
    normalBuffer.second   = contextGL->getAttribLocation(programGL->getProgramId(), "normal");
    texCoordBuffer.first  = static_cast<BufferGL *>(bufferMap["texCoord"]);
    texCoordBuffer.second = contextGL->getAttribLocation(programGL->getProgramId(), "texCoord");
    tangentBuffer.first   = static_cast<BufferGL *>(bufferMap["tangent"]);
    tangentBuffer.second  = contextGL->getAttribLocation(programGL->getProgramId(), "tangent");
    binormalBuffer.first  = static_cast<BufferGL *>(bufferMap["binormal"]);
    binormalBuffer.second = contextGL->getAttribLocation(programGL->getProgramId(), "binormal");

    indicesBuffer = static_cast<BufferGL *>(bufferMap["indices"]);
}

void FishModelGL::draw()
{
    contextGL->drawElements(indicesBuffer);
}

void FishModelGL::preDraw() const
{
    mProgram->setProgram();
    contextGL->enableBlend(mBlend);

    ProgramGL *programGL = static_cast<ProgramGL *>(mProgram);
    contextGL->bindVAO(programGL->getVAOId());

    contextGL->setAttribs(positionBuffer.first, positionBuffer.second);
    contextGL->setAttribs(normalBuffer.first, normalBuffer.second);
    contextGL->setAttribs(texCoordBuffer.first, texCoordBuffer.second);

    contextGL->setAttribs(tangentBuffer.first, tangentBuffer.second);
    contextGL->setAttribs(binormalBuffer.first, binormalBuffer.second);

    contextGL->setIndices(indicesBuffer);

    contextGL->setUniform(viewInverseUniform.second, viewInverseUniform.first, GL_FLOAT_MAT4);
    contextGL->setUniform(lightWorldPosUniform.second, lightWorldPosUniform.first, GL_FLOAT_VEC3);
    contextGL->setUniform(lightColorUniform.second, lightColorUniform.first, GL_FLOAT_VEC4);
    contextGL->setUniform(specularUniform.second, specularUniform.first, GL_FLOAT_VEC4);
    contextGL->setUniform(shininessUniform.second, &shininessUniform.first, GL_FLOAT);
    contextGL->setUniform(specularFactorUniform.second, &specularFactorUniform.first, GL_FLOAT);
    contextGL->setUniform(ambientUniform.second, ambientUniform.first, GL_FLOAT_VEC4);
    contextGL->setUniform(fogPowerUniform.second, &fogPowerUniform.first, GL_FLOAT);
    contextGL->setUniform(fogMultUniform.second, &fogMultUniform.first, GL_FLOAT);
    contextGL->setUniform(fogOffsetUniform.second, &fogOffsetUniform.first, GL_FLOAT);
    contextGL->setUniform(fogColorUniform.second, fogColorUniform.first, GL_FLOAT_VEC4);

    contextGL->setUniform(viewProjectionUniform.second, viewProjectionUniform.first, GL_FLOAT_MAT4);
    contextGL->setUniform(fishBendAmountUniform.second, &fishBendAmountUniform.first, GL_FLOAT);
    contextGL->setUniform(fishLengthUniform.second, &fishLengthUniform.first, GL_FLOAT);
    contextGL->setUniform(fishWaveLengthUniform.second, &fishWaveLengthUniform.first, GL_FLOAT);

    // Fish models includes small, medium and big. Some of them contains reflection and skybox
    // texture, but some doesn't.
    contextGL->setTexture(diffuseTexture.first, diffuseTexture.second, 0);
    contextGL->setTexture(normalTexture.first, normalTexture.second, 1);
    if (skyboxTexture.second != -1 && reflectionTexture.second != -1)
    {
        contextGL->setTexture(reflectionTexture.first, reflectionTexture.second, 2);
        contextGL->setTexture(skyboxTexture.first, skyboxTexture.second, 3);
    }
}

void FishModelGL::updatePerInstanceUniforms(WorldUniforms *WorldUniforms)
{
    contextGL->setUniform(scaleUniform.second, &scaleUniform.first, GL_FLOAT);
    contextGL->setUniform(timeUniform.second, &timeUniform.first, GL_FLOAT);
    contextGL->setUniform(worldPositionUniform.second, worldPositionUniform.first, GL_FLOAT_VEC3);
    contextGL->setUniform(nextPositionUniform.second, nextPositionUniform.first, GL_FLOAT_VEC3);
}

void FishModelGL::updateFishPerUniforms(float x,
                                        float y,
                                        float z,
                                        float nextX,
                                        float nextY,
                                        float nextZ,
                                        float scale,
                                        float time,
                                        int index)
{
    worldPositionUniform.first[0] = x;
    worldPositionUniform.first[1] = y;
    worldPositionUniform.first[2] = z;
    nextPositionUniform.first[0]  = nextX;
    nextPositionUniform.first[1]  = nextY;
    nextPositionUniform.first[2]  = nextZ;
    scaleUniform.first            = scale;
    timeUniform.first             = time;
}
