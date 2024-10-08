/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrTextureProxyCacheAccess_DEFINED
#define GrTextureProxyCacheAccess_DEFINED

#include "src/gpu/ganesh/GrTextureProxy.h"

class GrProxyProvider;

namespace skgpu {
class UniqueKey;
}

/**
 * This class allows GrResourceCache increased privileged access to GrTextureProxy objects.
 */
class GrTextureProxy::CacheAccess {
private:
    void setUniqueKey(GrProxyProvider* proxyProvider, const skgpu::UniqueKey& key) {
        fTextureProxy->setUniqueKey(proxyProvider, key);
    }

    void clearUniqueKey() {
        fTextureProxy->clearUniqueKey();
    }

    explicit CacheAccess(GrTextureProxy* textureProxy) : fTextureProxy(textureProxy) {}
    CacheAccess& operator=(const CacheAccess&) = delete;

    // No taking addresses of this type.
    const CacheAccess* operator&() const;
    CacheAccess* operator&();

    GrTextureProxy* fTextureProxy;

    friend class GrTextureProxy;  // to construct/copy this type.
    friend class GrProxyProvider; // to use this type
};

inline GrTextureProxy::CacheAccess GrTextureProxy::cacheAccess() { return CacheAccess(this); }

inline const GrTextureProxy::CacheAccess GrTextureProxy::cacheAccess() const {  // NOLINT(readability-const-return-type)
    return CacheAccess(const_cast<GrTextureProxy*>(this));
}

#endif
