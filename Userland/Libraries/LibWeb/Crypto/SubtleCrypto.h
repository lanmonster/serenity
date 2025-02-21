/*
 * Copyright (c) 2021-2022, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2023, stelar7 <dudedbz@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/HashMap.h>
#include <AK/String.h>
#include <AK/Vector.h>
#include <LibJS/Forward.h>
#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/Bindings/SubtleCryptoPrototype.h>
#include <LibWeb/Crypto/CryptoAlgorithms.h>
#include <LibWeb/Crypto/CryptoBindings.h>
#include <LibWeb/Crypto/CryptoKey.h>

namespace Web::Crypto {

class SubtleCrypto final : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(SubtleCrypto, Bindings::PlatformObject);
    JS_DECLARE_ALLOCATOR(SubtleCrypto);

    struct RegisteredAlgorithm {
        NonnullOwnPtr<AlgorithmMethods> (*create_methods)(JS::Realm&) = nullptr;
        JS::ThrowCompletionOr<NonnullOwnPtr<AlgorithmParams>> (*parameter_from_value)(JS::VM&, JS::Value) = nullptr;
    };
    using SupportedAlgorithmsMap = HashMap<String, HashMap<String, RegisteredAlgorithm, AK::ASCIICaseInsensitiveStringTraits>>;

public:
    [[nodiscard]] static JS::NonnullGCPtr<SubtleCrypto> create(JS::Realm&);

    virtual ~SubtleCrypto() override;

    JS::NonnullGCPtr<JS::Promise> digest(AlgorithmIdentifier const& algorithm, JS::Handle<WebIDL::BufferSource> const& data);

    JS::ThrowCompletionOr<JS::NonnullGCPtr<JS::Promise>> generate_key(AlgorithmIdentifier algorithm, bool extractable, Vector<Bindings::KeyUsage> key_usages);

    JS::ThrowCompletionOr<JS::NonnullGCPtr<JS::Promise>> import_key(Bindings::KeyFormat format, KeyDataType key_data, AlgorithmIdentifier algorithm, bool extractable, Vector<Bindings::KeyUsage> key_usages);

private:
    explicit SubtleCrypto(JS::Realm&);
    virtual void initialize(JS::Realm&) override;

    struct NormalizedAlgorithmAndParameter {
        NonnullOwnPtr<AlgorithmMethods> methods;
        NonnullOwnPtr<AlgorithmParams> parameter;
    };
    WebIDL::ExceptionOr<NormalizedAlgorithmAndParameter> normalize_an_algorithm(AlgorithmIdentifier const& algorithm, String operation);

    static SubtleCrypto::SupportedAlgorithmsMap& supported_algorithms_internal();
    static SubtleCrypto::SupportedAlgorithmsMap supported_algorithms();

    template<typename Methods, typename Param = AlgorithmParams>
    static void define_an_algorithm(String op, String algorithm);
};

}
