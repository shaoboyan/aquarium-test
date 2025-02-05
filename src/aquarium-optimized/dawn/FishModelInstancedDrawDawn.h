//
// Copyright (c) 2019 The WebGLNativePorts Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// FishModelDawn.h: Defnes fish model of Dawn

#pragma once
#ifndef FISHMODELINSTANCEDDRAWDAWN_H
#define FISHMODELINSTANCEDDRAWDAWN_H 1

#include <string>

#include "../FishModel.h"
#include "ContextDawn.h"
#include "ProgramDawn.h"
#include "dawn/dawncpp.h"
#include "utils/ComboRenderPipelineDescriptor.h"

class FishModelInstancedDrawDawn : public FishModel
{
  public:
    FishModelInstancedDrawDawn(const Context *context,
                               Aquarium *aquarium,
                               MODELGROUP type,
                               MODELNAME name,
                               bool blend);
    ~FishModelInstancedDrawDawn();

    void init() override;
    void preDraw() const override;
    void draw() override;

    void updatePerInstanceUniforms(WorldUniforms *WorldUniforms) override;
    void updateFishPerUniforms(float x,
                               float y,
                               float z,
                               float nextX,
                               float nextY,
                               float nextZ,
                               float scale,
                               float time,
                               int index) override;

    struct FishVertexUniforms
    {
        float fishLength;
        float fishWaveLength;
        float fishBendAmount;
    } fishVertexUniforms;

    struct LightFactorUniforms
    {
        float shininess;
        float specularFactor;
    } lightFactorUniforms;

    struct FishPer
    {
        float worldPosition[3];
        float scale;
        float nextPosition[3];
        float time;
    };
    FishPer *fishPers;

    TextureDawn *diffuseTexture;
    TextureDawn *normalTexture;
    TextureDawn *reflectionTexture;
    TextureDawn *skyboxTexture;

    BufferDawn *positionBuffer;
    BufferDawn *normalBuffer;
    BufferDawn *texCoordBuffer;
    BufferDawn *tangentBuffer;
    BufferDawn *binormalBuffer;

    BufferDawn *indicesBuffer;

  private:
    utils::ComboVertexInputDescriptor vertexInputDescriptor;
    dawn::RenderPipeline pipeline;

    dawn::BindGroupLayout groupLayoutModel;
    dawn::BindGroupLayout groupLayoutPer;
    dawn::PipelineLayout pipelineLayout;

    dawn::BindGroup bindGroupModel;
    dawn::BindGroup bindGroupPer;

    dawn::Buffer fishVertexBuffer;
    dawn::Buffer lightFactorBuffer;

    dawn::Buffer fishPersBuffer;

    int instance;

    ProgramDawn *programDawn;
    const ContextDawn *contextDawn;
};

#endif