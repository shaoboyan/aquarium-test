//
// Copyright (c) 2018 The WebGLNativePorts Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// FishModel.h: Define fish model. Update fish specific uniforms.

#pragma once
#ifndef FISHMODEL_H
#define FISHMODEL_H 1

#include <string>

#include "Model.h"

class FishModel : public Model
{
  public:
    FishModel(MODELGROUP type, MODELNAME name, bool blend) : Model(type, name, blend){}

    virtual void updateFishPerUniforms(float x,
                                       float y,
                                       float z,
                                       float nextX,
                                       float nextY,
                                       float nextZ,
                                       float scale,
                                       float time,
                                       int index) = 0;
};

#endif
