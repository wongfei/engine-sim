#include "../include/convolution_filter.h"

#include <assert.h>
#include <string.h>

#include <cstdlib>
#include <memory>
#define CONVOLUTION_ALIGN 16

ConvolutionFilter::ConvolutionFilter() {
    m_shiftRegister = nullptr;
    m_impulseResponse = nullptr;

    m_shiftOffset = 0;
    m_sampleCount = 0;
}

ConvolutionFilter::~ConvolutionFilter() {
    assert(m_shiftRegister == nullptr);
    assert(m_impulseResponse == nullptr);
}

void ConvolutionFilter::initialize(int samples) {
    assert(samples > 0);
    m_sampleCount = samples;
    m_shiftOffset = 0;

    #if CONVOLUTION_ALIGN
    m_shiftRegister = (float*)_aligned_malloc(sizeof(float) * (size_t)samples, CONVOLUTION_ALIGN);
    m_impulseResponse = (float*)_aligned_malloc(sizeof(float) * (size_t)samples, CONVOLUTION_ALIGN);
    #else
    m_shiftRegister = new float[samples];
    m_impulseResponse = new float[samples];
    #endif

    memset(m_shiftRegister, 0, sizeof(float) * samples);
    memset(m_impulseResponse, 0, sizeof(float) * samples);
}

void ConvolutionFilter::destroy() {
    #if CONVOLUTION_ALIGN
    _aligned_free(m_shiftRegister);
    _aligned_free(m_impulseResponse);
    #else
    delete[] m_shiftRegister;
    delete[] m_impulseResponse;
    #endif

    m_shiftRegister = nullptr;
    m_impulseResponse = nullptr;
}

static float unroll_conv_f(int first, int limit, int offset, const float* impulseResponse, const float* shiftRegister)
{
    float res = 0;

    const int unroll_N = 4;
    const int nitems = limit - first;
    int nloops = nitems / unroll_N;
    int i = first;

    for (int n = 0; n < nloops; ++n) {

        #if 1
        auto l0 = (impulseResponse)[i+0];
        auto l1 = (impulseResponse)[i+1];
        auto l2 = (impulseResponse)[i+2];
        auto l3 = (impulseResponse)[i+3];
        auto r0 = (shiftRegister)[i+0+offset];
        auto r1 = (shiftRegister)[i+1+offset];
        auto r2 = (shiftRegister)[i+2+offset];
        auto r3 = (shiftRegister)[i+3+offset];
        res += l0 * r0;
        res += l1 * r1;
        res += l2 * r2;
        res += l3 * r3;
        #else
        res += impulseResponse[i+0] * shiftRegister[i+0+offset];
        res += impulseResponse[i+1] * shiftRegister[i+1+offset];
        res += impulseResponse[i+2] * shiftRegister[i+2+offset];
        res += impulseResponse[i+3] * shiftRegister[i+3+offset];
        #endif

        i += unroll_N;
    }

    nloops = nitems % unroll_N;
    for (int n = 0; n < nloops; ++n) {
        res += impulseResponse[i] * shiftRegister[i+offset];
        ++i;
    }

    return res;
}

float ConvolutionFilter::f(float sample) {

    //if (!m_sampleCount) return 0;

    m_shiftRegister[m_shiftOffset] = sample;

    float result = 0;

#if 1

    // orig code

    for (int i = 0; i < m_sampleCount - m_shiftOffset; ++i) {
        result += m_impulseResponse[i] * m_shiftRegister[i + m_shiftOffset];
    }

    for (int i = m_sampleCount - m_shiftOffset; i < m_sampleCount; ++i) {
        result += m_impulseResponse[i] * m_shiftRegister[i - (m_sampleCount - m_shiftOffset)];
    }

#else

    // perf hack

    const float* impulseResponse = (m_impulseResponse);
    const float* shiftRegister = (m_shiftRegister);

    const auto sampleCount = m_sampleCount;
    const auto shiftOffset = m_shiftOffset;
    const auto shiftId = sampleCount - shiftOffset;

    result += unroll_conv_f(0, shiftId, shiftOffset, impulseResponse, shiftRegister);
    result += unroll_conv_f(shiftId, sampleCount, -shiftId, impulseResponse, shiftRegister);

#endif

    m_shiftOffset = (m_shiftOffset - 1 + m_sampleCount) % m_sampleCount;

    return result;
}
