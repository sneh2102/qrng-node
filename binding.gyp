{
  "targets": [
    {
      "target_name": "qrng",
      "sources": [
        "qrng_c/src/quantum_rng/qrng.cc",
        "qrng_c/src/quantum_rng/quantum_rng.c"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "qrng_c/src/quantum_rng",
        "qrng_c/src"
      ],
      "dependencies": [
        "<!@(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "cflags": [ "-fPIC" ],
      "cflags_cc": [ "-fPIC", "-std=c++17" ],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7"
      },
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 }
      },
      "defines": [
        "NAPI_CPP_EXCEPTIONS"
      ]
    }
  ]
}
