/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "src/gpu/GrTextureContext.h"

#include "src/gpu/GrAuditTrail.h"
#include "src/gpu/GrContextPriv.h"
#include "src/gpu/GrDrawingManager.h"

#define ASSERT_SINGLE_OWNER \
    SkDEBUGCODE(GrSingleOwner::AutoEnforce debug_SingleOwner(this->singleOwner());)
#define RETURN_FALSE_IF_ABANDONED  if (this->drawingManager()->wasAbandoned()) { return false; }

GrTextureContext::GrTextureContext(GrRecordingContext* context,
                                   sk_sp<GrTextureProxy> textureProxy,
                                   GrColorType colorType,
                                   SkAlphaType alphaType,
                                   sk_sp<SkColorSpace> colorSpace)
        : GrSurfaceContext(context, colorType, alphaType, std::move(colorSpace))
        , fTextureProxy(std::move(textureProxy)) {
    SkDEBUGCODE(this->validate();)
}

#ifdef SK_DEBUG
void GrTextureContext::validate() const {
    SkASSERT(fTextureProxy);
    fTextureProxy->validate(fContext);
}
#endif

GrTextureContext::~GrTextureContext() {
    ASSERT_SINGLE_OWNER
}

GrRenderTargetProxy* GrTextureContext::asRenderTargetProxy() {
    // If the proxy can return an RTProxy it should've been wrapped in a RTContext
    SkASSERT(!fTextureProxy->asRenderTargetProxy());
    return nullptr;
}

sk_sp<GrRenderTargetProxy> GrTextureContext::asRenderTargetProxyRef() {
    // If the proxy can return an RTProxy it should've been wrapped in a RTContext
    SkASSERT(!fTextureProxy->asRenderTargetProxy());
    return nullptr;
}
