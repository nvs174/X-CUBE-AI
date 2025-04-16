/**
  ******************************************************************************
  * @file    sine_model_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-04-10T15:16:59+0300
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "sine_model_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_sine_model_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_sine_model_weights_array_u64[161] = {
  0xbeec69743e418fa6U, 0xbef504133e70905bU, 0x3e0eb5c93ece8361U, 0xbe979c40be8ccd0bU,
  0xbdd9cbbcbbc87300U, 0xbefa7277bea6e20fU, 0xbf0ef5e63f2f6090U, 0x3e1761d1be176b46U,
  0xbf0567bbU, 0xbf0ae584U, 0xbdb16abbbef66ad1U, 0x0U,
  0x0U, 0x0U, 0xbd1e4b17U, 0x3f37f17700000000U,
  0xbec341b7be7e2b70U, 0x3eaa4cc9be1d4d58U, 0x3e38e194becc6308U, 0xbe8edb863e26830aU,
  0xbe210dd23b064480U, 0x3d84a1c4be185ab2U, 0xbe1d0924bd12cc84U, 0xbdacf8e6bb986d40U,
  0x3e15f3b63ec0ba8aU, 0xbab699003e1fbb60U, 0x3e5d68c6be7c90feU, 0xbda8e88cbdaa6a5cU,
  0xbea08a9ebe081864U, 0xbd682f003ed89ce5U, 0x3b9d63c03dadf8e8U, 0xbe395123be24e576U,
  0xbedc7e8fbe895a60U, 0xbeae8e993e876c9fU, 0xbe945143bf1d80a1U, 0xbba4d6003eb4d3e9U,
  0xbd9f5db4be993f70U, 0xbeada1523e0907deU, 0xbecf3952bf05bc47U, 0x3effd91a3e07093eU,
  0x3d061b50bf8ebc52U, 0x3e098a52bf855b72U, 0xbf0133acbf291c49U, 0xbd81409c3d007fe0U,
  0xbec16a923e80d2bfU, 0x3e5fa75a3e236ecaU, 0x3ec68a193e2d13f8U, 0x3f1ebb993e26155aU,
  0x3ec6407b3e2d332dU, 0xbe3be83f3edd681bU, 0xbe9012c53e338cd3U, 0xbe8102003e594d6aU,
  0x3e54a6c2bcfb7260U, 0x3e962aa7bea8b38dU, 0xbdd659a43e816cedU, 0xbf10974a3e7a856eU,
  0x3e94237b3ea320b7U, 0xbd144cd03ecb6ef7U, 0x3ebbb706beb1e047U, 0x3eb4110f3edad46dU,
  0xbe27bf24bea57a59U, 0xbe7baf04bedd1e62U, 0x3e22f87abec68411U, 0xbdb15a81bdc30294U,
  0x3cd9a7303e2852bdU, 0xbeda80453ea27125U, 0x3e276982bd6f1fddU, 0x3e79a58ebedd4cadU,
  0xbe4cc091be5db3c2U, 0xbe93b1663cc53a90U, 0x3ea8c98d3ec0ce8eU, 0xbf15ee013e1093caU,
  0xbeb056c43ea07aa0U, 0xbde8f9e0be72f7d0U, 0x3e9a57903ddc554bU, 0xbe5213113ed4576dU,
  0x3edc3d7d3ed3eb2fU, 0x3d89d694be5f0614U, 0xbea1129cbf56b39aU, 0x3efb169cbedbbccdU,
  0xbe94b9f0be153721U, 0xbe2b3d2e3f081ebdU, 0x3e8eb6cc3df384fcU, 0xbe104c5e3eb25863U,
  0xbdbb3a74be307566U, 0x3e74657ebdbf324cU, 0x3cc701703f024ff1U, 0xbe004558be655af4U,
  0xbe9393d13e0dbfe9U, 0x3e97474dbd069665U, 0xbf088abebe379976U, 0xbe01cd96be49f60aU,
  0xbe96caec3e3ad88eU, 0x3e9748c7bdea5378U, 0x3eb981a13e07a209U, 0x3ec4d613be70b8ccU,
  0xbde6d644bd8d7e44U, 0x3e52bd663ea8de59U, 0x3ca144803d308900U, 0x3e5682cebe985f84U,
  0xbe9bd13a3eb14e6fU, 0x3ebf7b113ea9a9b5U, 0x3e6608c6bed43708U, 0xbe08f95e3eac6647U,
  0xbed3ae1b3e802595U, 0xbe0f17023d129aa0U, 0x3d6e1749bd9517ddU, 0xbe387de2be1667bcU,
  0x3e1f3f263e35682eU, 0xbdc17e603eb66e6bU, 0xbeb02bf3beb57fe3U, 0xbd309931bcc25200U,
  0x3eaf9a073e2c6cc7U, 0x3bc9f0803ecfb396U, 0xbe8560f9bca35b85U, 0x3dd0013c3e054766U,
  0xbec5cbfabe9ea43fU, 0xbed5a2d43e63ee7eU, 0x3ec6075d3e5f9636U, 0xbecfbf02bc09c3a0U,
  0xbd9f74443e383e56U, 0x3e263cdebe4fff08U, 0xbece5b58bd7afea8U, 0xbe8402de3e1dc88eU,
  0xbe77a965be6992c7U, 0xbe1ca2aebc948fc0U, 0xbeceb748bd3ff7b0U, 0xbeaf4a64be6f6eaeU,
  0x3e69499abf1c635cU, 0x3e272456be3f4a70U, 0xbe615a2f3c444241U, 0x3d3708183ecd672bU,
  0xbe1086fc3eb7a071U, 0x3e546352bd40f500U, 0x3e768a623d13fe33U, 0x3cb5af0cbde7a68cU,
  0x3e159bae3efe995bU, 0xbb608f003eb4e903U, 0x3d310858bc1b7c24U, 0x3e9c71773dae50d4U,
  0x3ea42e833ebbc04dU, 0xbe9c964c3e1e18baU, 0x3ed45d613da8ca49U, 0xbe2b6cf33dd74514U,
  0xbdbab2e3baa18d54U, 0x3ecd13563e8b98faU, 0xbbbbc1c2bef01093U, 0x3e35452cbeda6906U,
  0x3e0597e7be1b8ca8U, 0x3a122f1000000000U, 0xbeb46950U, 0xbef248443e8ed41cU,
  0x3f31d9babec968b4U, 0x3f766625bf85863aU, 0x3eccccda3fcc1996U, 0xbf4ff3893f74d8bcU,
  0x3e71e432bf441999U, 0xbe7e605f3ccf2460U, 0x3dabfca83f8e54e4U, 0x3fb2e6853ebb7d8fU,
  0x3e086f86U,
};


ai_handle g_sine_model_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_sine_model_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

