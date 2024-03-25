#include <vector>

#include "ffrechet-cuda/common.hpp"
#include "ffrechet-cuda/ffrechet-cuda.hpp"

__device__ static float metric(float dx, float dy)
{
    return hypot(dx, dy);
}

__global__ static void kernel(const float* px,
                              const float* py,
                              const unsigned* P,
                              const unsigned N,
                              const float* qx,
                              const float* qy,
                              unsigned Q,
                              float* buffer,
                              float* res)
{
    for (auto idx = blockIdx.x * blockDim.x + threadIdx.x; idx < N; idx += gridDim.x * blockDim.x)
    {
        float acc = 0.F;
        for (unsigned j = 0; j < Q; j++)
        {
            acc = max(acc, metric(px[idx] - qx[j], py[idx] - qy[j]));
            buffer[j * N + idx] = acc;
        }

        for (unsigned i = 1; i < P[idx]; i++)
        {
            for (unsigned j = Q - 1; j > 0; j--)
            {
                buffer[j * N + idx] = min(buffer[j * N + idx], buffer[(j - 1) * N + idx]);
            }
            buffer[idx] =
                max(buffer[idx], metric(px[i * N + idx] - qx[0], py[i * N + idx] - qy[0]));

            for (unsigned j = 1; j < Q; j++)
            {
                buffer[j * N + idx] = max(min(buffer[j * N + idx], buffer[(j - 1) * N + idx]),
                                          metric(px[i * N + idx] - qx[j], py[i * N + idx] - qy[j]));
            }
        }

        res[idx] = buffer[(Q - 1) * N + idx];
    }
}

namespace
{
template <typename T>
[[nodiscard]] T max_element(const T* v, std::size_t N)
{
    T max = v[0];

    for (std::size_t i = 1; i < N; i++)
    {
        max = std::max(max, v[i]);
    }

    return max;
}
} // namespace

void cuda_frechet_distance(const float* const* px,
                           const float* const* py,
                           const unsigned* P,
                           const unsigned N,
                           const float* qx,
                           const float* qy,
                           unsigned Q,
                           float* d,
                           CUDAKernelConfig cfg)
{
    using ::fast_frechet::cuda::cuda_check;

    const auto P_MAX = ::max_element(P, N);

    std::vector<float> buffer(static_cast<std::size_t>(N) * Q);
    std::vector<float> px_flat(static_cast<std::size_t>(N) * P_MAX);
    std::vector<float> py_flat(static_cast<std::size_t>(N) * P_MAX);

    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < P_MAX; j++)
        {
            const auto k = std::min(j, static_cast<std::size_t>(P[i]) - 1U);
            px_flat[j * N + i] = px[i][k];
            py_flat[j * N + i] = py[i][k];
        }
    }

    float* px_d;
    cuda_check(cudaMalloc(&px_d, px_flat.size() * sizeof(float)));
    cuda_check(
        cudaMemcpy(px_d, px_flat.data(), px_flat.size() * sizeof(float), cudaMemcpyHostToDevice));

    float* py_d;
    cuda_check(cudaMalloc(&py_d, py_flat.size() * sizeof(float)));
    cuda_check(
        cudaMemcpy(py_d, py_flat.data(), py_flat.size() * sizeof(float), cudaMemcpyHostToDevice));

    unsigned* P_d;
    cuda_check(cudaMalloc(&P_d, N * sizeof(unsigned)));
    cuda_check(cudaMemcpy(P_d, P, N * sizeof(unsigned), cudaMemcpyHostToDevice));

    float* qx_d;
    cuda_check(cudaMalloc(&qx_d, Q * sizeof(float)));
    cuda_check(cudaMemcpy(qx_d, qx, Q * sizeof(float), cudaMemcpyHostToDevice));

    float* qy_d;
    cuda_check(cudaMalloc(&qy_d, Q * sizeof(float)));
    cuda_check(cudaMemcpy(qy_d, qy, Q * sizeof(float), cudaMemcpyHostToDevice));

    float* buffer_d;
    cuda_check(cudaMalloc(&buffer_d, Q * N * sizeof(float)));

    float* res_d;
    cuda_check(cudaMalloc(&res_d, N * sizeof(float)));

    kernel<<<cfg.grid_size, cfg.block_size>>>(px_d, py_d, P_d, N, qx_d, qy_d, Q, buffer_d, res_d);
    cuda_check();
    cuda_check(cudaDeviceSynchronize());

    cuda_check(cudaMemcpy(d, res_d, N * sizeof(float), cudaMemcpyDeviceToHost));

    cudaFree(px_d);
    cudaFree(py_d);
    cudaFree(qx_d);
    cudaFree(qy_d);
    cudaFree(buffer_d);
    cudaFree(res_d);
}
