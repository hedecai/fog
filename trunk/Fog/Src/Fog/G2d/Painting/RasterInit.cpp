// [Fog-G2d]
//
// [License]
// MIT, See COPYING file in package

// [Precompiled Headers]
#if defined(FOG_PRECOMP)
#include FOG_PRECOMP
#endif // FOG_PRECOMP

// [Dependencies]
#include <Fog/Core/Global/Global.h>
#include <Fog/Core/Tools/Cpu.h>
#include <Fog/G2d/Painting/RasterApi_p.h>
#include <Fog/G2d/Painting/RasterConstants_p.h>
#include <Fog/G2d/Painting/RasterInit_p.h>

namespace Fog {

FOG_NO_EXPORT void RasterOps_init_C(void);
FOG_NO_EXPORT void RasterOps_init_skipped(void);

// ============================================================================
// [Fog::G2d - Initialization / Finalization]
// ============================================================================

FOG_NO_EXPORT void RasterOps_init(void)
{
  // Install C optimized code (default).
  RasterOps_init_C();

  // Initialize functions marked as 'SKIP'.
  RasterOps_init_skipped();
}

FOG_NO_EXPORT void RasterOps_init_skipped(void)
{
  // Post-initialize function pointers defined by Fog::Raster API. These
  // pointers are always marked as 'SKIP' in the code.

  ApiRaster& api = _api_raster;
  uint i, j;

  // --------------------------------------------------------------------------
  // [RasterOps - Convert - API]
  // --------------------------------------------------------------------------

  RasterConvertFuncs& convert = api.convert;

  // --------------------------------------------------------------------------
  //[RasterOps - Convert - ARGB32 <-> Extended]
  // --------------------------------------------------------------------------

  convert.argb32_from[RASTER_FORMAT_RGB24_888          ] = api.compositeCore[IMAGE_FORMAT_PRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_RGB24 ];
  convert.argb32_from[RASTER_FORMAT_RGB32_888          ] = api.compositeCore[IMAGE_FORMAT_PRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_XRGB32];
  convert.argb32_from[RASTER_FORMAT_ARGB32_8888        ] = api.convert.copy[RASTER_COPY_32];
  convert.argb32_from[RASTER_FORMAT_RGB48_161616       ] = api.compositeCore[IMAGE_FORMAT_PRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_RGB48];
  convert.argb32_from[RASTER_FORMAT_ARGB64_16161616    ] = api.compositeCore[IMAGE_FORMAT_PRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB64];
  convert.argb32_from[RASTER_FORMAT_I8                 ] = api.compositeCore[IMAGE_FORMAT_PRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_I8    ];

  convert.from_argb32[RASTER_FORMAT_RGB24_888          ] = api.compositeCore[IMAGE_FORMAT_RGB24 ][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB32];
  convert.from_argb32[RASTER_FORMAT_RGB32_888          ] = api.compositeCore[IMAGE_FORMAT_XRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB32];
  convert.from_argb32[RASTER_FORMAT_RGB48_161616       ] = api.compositeCore[IMAGE_FORMAT_RGB48 ][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB32];
  convert.from_argb32[RASTER_FORMAT_ARGB32_8888        ] = api.convert.copy[RASTER_COPY_32];
  convert.from_argb32[RASTER_FORMAT_ARGB64_16161616    ] = api.compositeCore[IMAGE_FORMAT_PRGB64][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB32];

  // --------------------------------------------------------------------------
  //[RasterOps - Convert - ARGB64 <-> Extended]
  // --------------------------------------------------------------------------

  convert.argb64_from[RASTER_FORMAT_RGB24_888          ] = api.compositeCore[IMAGE_FORMAT_PRGB64][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_RGB24 ];
  convert.argb64_from[RASTER_FORMAT_RGB32_888          ] = api.compositeCore[IMAGE_FORMAT_PRGB64][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_XRGB32];
  convert.argb64_from[RASTER_FORMAT_ARGB32_8888        ] = api.compositeCore[IMAGE_FORMAT_PRGB64][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB32];
  convert.argb64_from[RASTER_FORMAT_RGB48_161616       ] = api.compositeCore[IMAGE_FORMAT_PRGB64][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_RGB48 ];
  convert.argb64_from[RASTER_FORMAT_ARGB64_16161616    ] = api.convert.copy[RASTER_COPY_64];
  convert.argb64_from[RASTER_FORMAT_I8                 ] = api.compositeCore[IMAGE_FORMAT_PRGB64][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_I8    ];

  convert.from_argb64[RASTER_FORMAT_RGB24_888          ] = api.compositeCore[IMAGE_FORMAT_RGB24 ][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB64];
  convert.from_argb64[RASTER_FORMAT_RGB32_888          ] = api.compositeCore[IMAGE_FORMAT_XRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB64];
  convert.from_argb64[RASTER_FORMAT_ARGB32_8888        ] = api.compositeCore[IMAGE_FORMAT_PRGB32][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB64];
  convert.from_argb64[RASTER_FORMAT_RGB48_161616       ] = api.compositeCore[IMAGE_FORMAT_RGB48 ][RASTER_COMPOSITE_CORE_SRC].vblit_line[IMAGE_FORMAT_PRGB64];
  convert.from_argb64[RASTER_FORMAT_ARGB64_16161616    ] = api.convert.copy[RASTER_COPY_64];

  // --------------------------------------------------------------------------
  // [RasterOps - Composite - Src/SrcOver]
  // --------------------------------------------------------------------------

  for (i = 0; i < IMAGE_FORMAT_COUNT; i++)
  {
    RasterCompositeCoreFuncs& fCopy = api.compositeCore[i][RASTER_COMPOSITE_CORE_SRC];
    RasterCompositeCoreFuncs& fOver = api.compositeCore[i][RASTER_COMPOSITE_CORE_SRC_OVER];

    fCopy.cblit_line[RASTER_CBLIT_XRGB     ] = fCopy.cblit_line[RASTER_CBLIT_PRGB];
    fCopy.cblit_span[RASTER_CBLIT_XRGB     ] = fCopy.cblit_span[RASTER_CBLIT_PRGB];

    fOver.cblit_line[RASTER_CBLIT_XRGB     ] = fCopy.cblit_line[RASTER_CBLIT_PRGB];
    fOver.cblit_span[RASTER_CBLIT_XRGB     ] = fCopy.cblit_span[RASTER_CBLIT_PRGB];

    fOver.vblit_line[IMAGE_FORMAT_XRGB32   ] = fCopy.vblit_line[IMAGE_FORMAT_XRGB32   ];
    fOver.vblit_line[IMAGE_FORMAT_RGB24    ] = fCopy.vblit_line[IMAGE_FORMAT_RGB24    ];
    fOver.vblit_line[IMAGE_FORMAT_RGB48    ] = fCopy.vblit_line[IMAGE_FORMAT_RGB48    ];

    fOver.vblit_span[IMAGE_FORMAT_XRGB32   ] = fCopy.vblit_span[IMAGE_FORMAT_XRGB32   ];
    fOver.vblit_span[IMAGE_FORMAT_RGB24    ] = fCopy.vblit_span[IMAGE_FORMAT_RGB24    ];
    fOver.vblit_span[IMAGE_FORMAT_RGB48    ] = fCopy.vblit_span[IMAGE_FORMAT_RGB48    ];
  }

  api.compositeCore[IMAGE_FORMAT_PRGB32][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_PRGB32] = api.convert.copy[RASTER_COPY_32];
  api.compositeCore[IMAGE_FORMAT_XRGB32][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_XRGB32] = api.convert.copy[RASTER_COPY_32];
  api.compositeCore[IMAGE_FORMAT_RGB24 ][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_RGB24 ] = api.convert.copy[RASTER_COPY_24];
  api.compositeCore[IMAGE_FORMAT_A8    ][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_A8    ] = api.convert.copy[RASTER_COPY_8];
  api.compositeCore[IMAGE_FORMAT_PRGB64][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_PRGB64] = api.convert.copy[RASTER_COPY_64];
  api.compositeCore[IMAGE_FORMAT_RGB48 ][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_RGB48 ] = api.convert.copy[RASTER_COPY_48];
  api.compositeCore[IMAGE_FORMAT_A16   ][COMPOSITE_SRC].vblit_line[IMAGE_FORMAT_A16   ] = api.convert.copy[RASTER_COPY_16];

  // --------------------------------------------------------------------------
  // [RasterOps - Composite - Clear]
  // --------------------------------------------------------------------------

  for (i = 0; i < IMAGE_FORMAT_COUNT; i++)
  {
    RasterCompositeExtFuncs& fClear = api.compositeExt[i][RASTER_COMPOSITE_EXT_CLEAR];

    for (j = 1; j < RASTER_VBLIT_INVALID; j++)
    {
      fClear.vblit_line[j] = fClear.vblit_line[0];
      fClear.vblit_span[j] = fClear.vblit_span[0];
    }
  }

  // --------------------------------------------------------------------------
  // [RasterOps - Composite - Other]
  // --------------------------------------------------------------------------

  // If CBLIT operator doesn't contain implementation for XRGB then we link it
  // with PRGB operator, because it's guaranteed that alpha component is always
  // set to fully opaque for CBLITs.

  for (i = 0; i < IMAGE_FORMAT_COUNT; i++)
  {
    for (j = 0; j < RASTER_COMPOSITE_EXT_COUNT; j++)
    {
      RasterCompositeExtFuncs& fOp = api.compositeExt[i][j];

      if (fOp.cblit_line[RASTER_CBLIT_XRGB] == NULL)
        fOp.cblit_line[RASTER_CBLIT_XRGB] = fOp.cblit_line[RASTER_CBLIT_PRGB];
      if (fOp.cblit_span[RASTER_CBLIT_XRGB] == NULL)
        fOp.cblit_span[RASTER_CBLIT_XRGB] = fOp.cblit_span[RASTER_CBLIT_PRGB];
    }
  }
}

} // Fog namespace