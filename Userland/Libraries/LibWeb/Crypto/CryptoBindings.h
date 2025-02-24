/*
 * Copyright (c) 2023, stelar7 <dudedbz@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Optional.h>
#include <AK/String.h>
#include <AK/Vector.h>
#include <LibJS/Runtime/Object.h>
#include <LibWeb/WebIDL/Buffers.h>

// FIXME: Generate these from IDL
namespace Web::Bindings {

// https://w3c.github.io/webcrypto/#JsonWebKey-dictionary
struct RsaOtherPrimesInfo {
    Optional<String> r;
    Optional<String> d;
    Optional<String> t;
};

// https://w3c.github.io/webcrypto/#JsonWebKey-dictionary
struct JsonWebKey {
    Optional<String> kty;
    Optional<String> use;
    Optional<Vector<String>> key_ops;
    Optional<String> alg;
    Optional<bool> ext;
    Optional<String> crv;
    Optional<String> x;
    Optional<String> y;
    Optional<String> d;
    Optional<String> n;
    Optional<String> e;
    Optional<String> p;
    Optional<String> q;
    Optional<String> dp;
    Optional<String> dq;
    Optional<String> qi;
    Optional<Vector<RsaOtherPrimesInfo>> oth;
    Optional<String> k;
};

}
